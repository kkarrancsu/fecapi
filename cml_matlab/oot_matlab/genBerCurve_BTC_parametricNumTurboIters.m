function [] = genBerCurve_BTC_parametricDecoderTypes()

clear;
clc;

Eb_N0_dB = [0:0.5:5];
% common generator polynomials that will be used in all configurations
g1 = [1 1];
g5 = [1 0 1 0 1 1];
g6 = [1 1 1 1 0 1 1];
g7 = [1 0 1 0 0 0 1 1];

encoder_decoder_configurations = {};
numEncoderDecoderConfigs = 1;
config = {};

grows = g1; gcols = g5; k_per_row = 26; k_per_col = 6; B = 9; Q = 3;

bersToPlot = {};
legendCell = {};

decoderType = 1;
numTurboIters = [2 4 6 8 10];
    
for ii=1:length(numTurboIters)
    numTurboIter = numTurboIters(ii);
    
    [bers] = genBerCurve_BTC(Eb_N0_dB, grows, gcols, k_per_row, k_per_col, B, Q, decoderType, numTurboIter);
    bersToPlot{ii} = bers;
    legendCell{ii} = sprintf('Num Turbo Iters = %d', numTurboIter);
end

% plot all the bers
plotConfigurations = {'rx-', 'gx-', 'bx-', 'mx-', 'cx-', 'bx-', 'r+-', 'g+-', 'b+-', 'm+-'};
hold on;
for ii=1:length(bersToPlot)
    semilogy(Eb_N0_dB, bersToPlot{ii}, plotConfigurations(ii))
end
xlabel('E_b/N_0 (SNR)')
ylabel('Bit Error Rate (BER)')
titleStr = sprintf('BER of (K_row=%d,K_col=%d,B=%d,Q=%d), DecoderType=%d', k_per_row, k_per_col, B, Q, decoderType);
title(titleStr)
legend(legendCell)

end