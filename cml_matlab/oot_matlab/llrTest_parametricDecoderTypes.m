function [] = genBerCurve_BTC_parametricDecoderTypes()

clear;
clc;

Eb_N0_dB = [-5:1:5];
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

%  decoderTypes = [0 1 2 3 4];
decoderTypes = [1];
numTurboIter = 10;
    
for ii=1:length(decoderTypes)
    decoderType = decoderTypes(ii);
    
    testBTCDecode_llrCompute(Eb_N0_dB, grows, gcols, k_per_row, k_per_col, B, Q, decoderType, numTurboIter);
end


end