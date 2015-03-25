function [] = genBerCurve_BTC_parametricConfigurations()

clear;
clc;

Eb_N0_dB = [0:1:10];
% common generator polynomials that will be used in all configurations
g1 = [1 1];
g5 = [1 0 1 0 1 1];
g6 = [1 1 1 1 0 1 1];
g7 = [1 0 1 0 0 0 1 1];

encoder_decoder_configurations = {};
numEncoderDecoderConfigs = 1;
config = {};

EARLY_EXIT_OFF = 0;
EARLY_EXIT_ON = 1;

DECODER_TYPE_LINEAR_LOG_MAP = 0;
DECODER_TYPE_MAX_LOG_MAP = 1;
DECODER_TYPE_CONSTANT_LOG_MAP = 2;
DECODER_TYPE_LOG_MAP_LUT = 3;
DECODER_TYPE_LOG_MAP = 4;

% grows = g1; gcols = g5; k_per_row = 26; k_per_col = 6; B = 9; Q = 3;
% config{1} = grows; config{2} = gcols; config{3} = k_per_row; config{4} = k_per_col;
% config{5} = B; config{6} = Q; config{7} = sprintf('(K_row=%d,K_col=%d,B=%d,Q=%d NoEarlyExit)', k_per_row, k_per_col, B, Q);
% config{8} = EARLY_EXIT_OFF;
% encoder_decoder_configurations{numEncoderDecoderConfigs} = config;
% numEncoderDecoderConfigs = numEncoderDecoderConfigs + 1;

grows = g1; gcols = g5; k_per_row = 26; k_per_col = 6; B = 9; Q = 3;
config{1} = grows; config{2} = gcols; config{3} = k_per_row; config{4} = k_per_col;
config{5} = B; config{6} = Q; config{7} = sprintf('(K_row=%d,K_col=%d,B=%d,Q=%d LinearLogMap)', k_per_row, k_per_col, B, Q);
config{8} = EARLY_EXIT_ON;
config{9} = DECODER_TYPE_LINEAR_LOG_MAP;
encoder_decoder_configurations{numEncoderDecoderConfigs} = config;
numEncoderDecoderConfigs = numEncoderDecoderConfigs + 1;

grows = g1; gcols = g5; k_per_row = 26; k_per_col = 6; B = 9; Q = 3;
config{1} = grows; config{2} = gcols; config{3} = k_per_row; config{4} = k_per_col;
config{5} = B; config{6} = Q; config{7} = sprintf('(K_row=%d,K_col=%d,B=%d,Q=%d MaxLogMap)', k_per_row, k_per_col, B, Q);
config{8} = EARLY_EXIT_ON;
config{9} = DECODER_TYPE_MAX_LOG_MAP;
encoder_decoder_configurations{numEncoderDecoderConfigs} = config;
numEncoderDecoderConfigs = numEncoderDecoderConfigs + 1;

grows = g1; gcols = g5; k_per_row = 26; k_per_col = 6; B = 9; Q = 3;
config{1} = grows; config{2} = gcols; config{3} = k_per_row; config{4} = k_per_col;
config{5} = B; config{6} = Q; config{7} = sprintf('(K_row=%d,K_col=%d,B=%d,Q=%d ConstantLogMap)', k_per_row, k_per_col, B, Q);
config{8} = EARLY_EXIT_ON;
config{9} = DECODER_TYPE_CONSTANT_LOG_MAP;
encoder_decoder_configurations{numEncoderDecoderConfigs} = config;
numEncoderDecoderConfigs = numEncoderDecoderConfigs + 1;

grows = g1; gcols = g5; k_per_row = 26; k_per_col = 6; B = 9; Q = 3;
config{1} = grows; config{2} = gcols; config{3} = k_per_row; config{4} = k_per_col;
config{5} = B; config{6} = Q; config{7} = sprintf('(K_row=%d,K_col=%d,B=%d,Q=%d LogMapLUT)', k_per_row, k_per_col, B, Q);
config{8} = EARLY_EXIT_ON;
config{9} = DECODER_TYPE_LOG_MAP_LUT;
encoder_decoder_configurations{numEncoderDecoderConfigs} = config;
numEncoderDecoderConfigs = numEncoderDecoderConfigs + 1;

grows = g1; gcols = g5; k_per_row = 26; k_per_col = 6; B = 9; Q = 3;
config{1} = grows; config{2} = gcols; config{3} = k_per_row; config{4} = k_per_col;
config{5} = B; config{6} = Q; config{7} = sprintf('(K_row=%d,K_col=%d,B=%d,Q=%d LogMap)', k_per_row, k_per_col, B, Q);
config{8} = EARLY_EXIT_ON;
config{9} = DECODER_TYPE_LOG_MAP;
encoder_decoder_configurations{numEncoderDecoderConfigs} = config;
numEncoderDecoderConfigs = numEncoderDecoderConfigs + 1;

% grows = g1; gcols = g6; k_per_row = 3; k_per_col = 18; B = 0; Q = 6;
% config{1} = grows; config{2} = gcols; config{3} = k_per_row; config{4} = k_per_col;
% config{5} = B; config{6} = Q; config{7} = sprintf('(K_row=%d,K_col=%d,B=%d,Q=%d)', k_per_row, k_per_col, B, Q);
% encoder_decoder_configurations{numEncoderDecoderConfigs} = config;
% numEncoderDecoderConfigs = numEncoderDecoderConfigs + 1;
% 
% grows = g1; gcols = g1; k_per_row = 9; k_per_col = 9; B = 4; Q = 5;
% config{1} = grows; config{2} = gcols; config{3} = k_per_row; config{4} = k_per_col;
% config{5} = B; config{6} = Q; config{7} = sprintf('(K_row=%d,K_col=%d,B=%d,Q=%d)', k_per_row, k_per_col, B, Q);
% encoder_decoder_configurations{numEncoderDecoderConfigs} = config;
% numEncoderDecoderConfigs = numEncoderDecoderConfigs + 1;
% 
% grows = g1; gcols = g5; k_per_row = 17; k_per_col = 6; B = 6; Q = 0;
% config{1} = grows; config{2} = gcols; config{3} = k_per_row; config{4} = k_per_col;
% config{5} = B; config{6} = Q; config{7} = sprintf('(K_row=%d,K_col=%d,B=%d,Q=%d)', k_per_row, k_per_col, B, Q);
% encoder_decoder_configurations{numEncoderDecoderConfigs} = config;
% numEncoderDecoderConfigs = numEncoderDecoderConfigs + 1;
% 
% grows = g1; gcols = g1; k_per_row = 13; k_per_col = 13; B = 4; Q = 5;
% config{1} = grows; config{2} = gcols; config{3} = k_per_row; config{4} = k_per_col;
% config{5} = B; config{6} = Q; config{7} = sprintf('(K_row=%d,K_col=%d,B=%d,Q=%d)', k_per_row, k_per_col, B, Q);
% encoder_decoder_configurations{numEncoderDecoderConfigs} = config;
% numEncoderDecoderConfigs = numEncoderDecoderConfigs + 1;
% 
% grows = g1; gcols = g7; k_per_row = 5; k_per_col = 41; B = 0; Q = 5;
% config{1} = grows; config{2} = gcols; config{3} = k_per_row; config{4} = k_per_col;
% config{5} = B; config{6} = Q; config{7} = sprintf('(K_row=%d,K_col=%d,B=%d,Q=%d)', k_per_row, k_per_col, B, Q);
% encoder_decoder_configurations{numEncoderDecoderConfigs} = config;
% numEncoderDecoderConfigs = numEncoderDecoderConfigs + 1;
% 
% grows = g6; gcols = g5; k_per_row = 22; k_per_col = 9; B = 8; Q = 6;
% config{1} = grows; config{2} = gcols; config{3} = k_per_row; config{4} = k_per_col;
% config{5} = B; config{6} = Q; config{7} = sprintf('(K_row=%d,K_col=%d,B=%d,Q=%d)', k_per_row, k_per_col, B, Q);
% encoder_decoder_configurations{numEncoderDecoderConfigs} = config;
% numEncoderDecoderConfigs = numEncoderDecoderConfigs + 1;
% 
% grows = g6; gcols = g1; k_per_row = 26; k_per_col = 11; B = 0; Q = 6;
% config{1} = grows; config{2} = gcols; config{3} = k_per_row; config{4} = k_per_col;
% config{5} = B; config{6} = Q; config{7} = sprintf('(K_row=%d,K_col=%d,B=%d,Q=%d)', k_per_row, k_per_col, B, Q);
% encoder_decoder_configurations{numEncoderDecoderConfigs} = config;
% numEncoderDecoderConfigs = numEncoderDecoderConfigs + 1;
% 
% grows = g6; gcols = g6; k_per_row = 16; k_per_col = 16; B = 4; Q = 4;
% config{1} = grows; config{2} = gcols; config{3} = k_per_row; config{4} = k_per_col;
% config{5} = B; config{6} = Q; config{7} = sprintf('(K_row=%d,K_col=%d,B=%d,Q=%d)', k_per_row, k_per_col, B, Q);
% encoder_decoder_configurations{numEncoderDecoderConfigs} = config;
% numEncoderDecoderConfigs = numEncoderDecoderConfigs + 1;
% 
% grows = g6; gcols = g6; k_per_row = 18; k_per_col = 18; B = 0; Q = 4;
% config{1} = grows; config{2} = gcols; config{3} = k_per_row; config{4} = k_per_col;
% config{5} = B; config{6} = Q; config{7} = sprintf('(K_row=%d,K_col=%d,B=%d,Q=%d)', k_per_row, k_per_col, B, Q);
% encoder_decoder_configurations{numEncoderDecoderConfigs} = config;
% numEncoderDecoderConfigs = numEncoderDecoderConfigs + 1;

bersToPlot = {};
legendCell = {};
avgItersCellArr = {};

numTurboIter = 6;
    
for ii=1:length(encoder_decoder_configurations)
    curConfig = encoder_decoder_configurations{ii};
    grows = curConfig{1};
    gcols = curConfig{2};
    k_per_row = curConfig{3};
    k_per_col = curConfig{4};
    B = curConfig{5};
    Q = curConfig{6};
    EARLY_EXIT_MODE = curConfig{8};
    decoderType = curConfig{9};
    
    [bers, avgIters] = genBerCurve_BTC(Eb_N0_dB, grows, gcols, k_per_row, k_per_col, B, Q, decoderType, numTurboIter, EARLY_EXIT_MODE);
    bersToPlot{ii} = bers;
    legendCell{ii} = curConfig{7};
    avgItersCellArr{ii} = avgIters;
end

% plot all the bers
plotConfigurations = {'rx-', 'bx-', 'gx-', 'mx-', 'cx-', 'bx-', 'r+-', 'g+-', 'b+-', 'm+-'};
save('turbo_data.mat', 'Eb_N0_dB', 'bersToPlot', 'plotConfigurations', 'numTurboIter', 'avgItersCellArr', 'legendCell');      % to create special plots
subplot(2,1,1)
avgItersMat = [];
for ii=1:length(bersToPlot)
    berVals = bersToPlot{ii};
    % if 0 ber, then put it to a very low value, 10^-12
    zeroIdx = find(berVals==0);
    berVals(zeroIdx) = 10^-12;
    semilogy(Eb_N0_dB, berVals, plotConfigurations{ii})
    
    hold on;
    
    avgItersMat(:,ii) = avgItersCellArr{ii};
end
grid on
xlabel('E_b/N_0 (SNR)')
ylabel('Bit Error Rate (BER)')
titleStr = sprintf('BER of multiple encoder/decoder configurations, MaxTurboIters=%d', numTurboIter);
title(titleStr)
legend(legendCell)

xAxisLegend = {};
for ii=1:length(Eb_N0_dB)
    xAxisLegend{ii} = sprintf('%2.1f dB', Eb_N0_dB(ii));
end

subplot(2,1,2)
bar(avgItersMat, 'grouped')
set(gca, 'XTickLabel', xAxisLegend);
legend('Linear Log Map', 'Max Log Map', 'Constant Log Map', 'Log Map LUT', 'Log Map')
title('Average Number of Turbo Iterations for each SNR Level')
ylabel('Number of Turbo Iterations')

end