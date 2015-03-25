% Generates Test Inputs and Outputs for the TPC GnuRadio block in Octave
% using the CML library

function [] = genTPCEncoderTestFiles()

clear;
clc;

% add the correct directories to the path so we can call the functions
addpath(fullfile(pwd, '..', 'mat'));
addpath(fullfile(pwd, '..', 'mex'));

% define all the generator polynomials we will use to test different TPC configurations
g1 = [1 1];
g5 = [1 0 1 0 1 1];
g6 = [1 1 1 1 0 1 1];
g7 = [1 0 1 0 0 0 1 1];

%%%%% Generate Test Case 1 I/O Files
testCaseNum = 1;
grows = g1;
gcols = g5;
k_per_row = 26;
k_per_col = 6;
B = 9;
Q = 3;

DEBUG_MODE = 0;
EARLY_EXIT_MODE = 0;

inputDataSize = (k_per_row*k_per_col - (B+Q));
inputData = round(rand(1,inputDataSize));  % 18 data bytes
btcEncodedData = BtcEncode(inputData, grows, gcols, k_per_row, k_per_col, B, Q, DEBUG_MODE);
sig = 2*btcEncodedData-1;

% add noise
Eb_N0_dB = [4:10];
% Eb_N0_dB = 4;
% DEBUG_MODE = 1;

for snr=Eb_N0_dB
    rx = awgn(sig, snr, 'measured');
    expNoisePwr = 1/(10^(snr/10));
    llr = (2*rx)/expNoisePwr;

    numTurboIter = 6;
    decoderType = 2;

    [out, ~, ~, ~] = BtcDecode( llr, inputData, grows, gcols, k_per_row, k_per_col, ...
                                B, Q, numTurboIter, decoderType, ...
                                DEBUG_MODE, EARLY_EXIT_MODE);

    testFilesOutputDir = '../../testdata';
    testCaseInputFilename = fullfile(testFilesOutputDir, sprintf('snrtest_%d_input.bin', snr));
    testCaseOutputFilename = fullfile(testFilesOutputDir, sprintf('snrtest_%d_output.bin', snr));

    if(~exist(testCaseInputFilename,2) || ~exist(testCaseOutputFilename,2))
        fid = fopen(testCaseInputFilename, 'w');
        fwrite(fid, llr, 'float32');
        fclose(fid);

        fid = fopen(testCaseOutputFilename, 'w');
        fwrite(fid, out, 'uchar');
        fclose(fid);
    end
end


end