% A high level test script for BTC Encoding & Decoding using CML library

clear;
clc;

% add the correct directories to the path so we can call the functions
addpath(fullfile(pwd, '..', 'mat'))
addpath(fullfile(pwd, '..', 'mex'))

filename = '../../testdata/test.bin';
diaryFilename = '~/octaveOutput.txt';

% Encode some random data using BTCEncode
grows = [1 1];
%grows = [1 1; 0 1];
gcols = [1 0 1 0 1 1];
k_per_row = 26;
k_per_col = 6;
B = 9;
Q = 3;
DEBUG_OUTPUT = 0;
EARLY_EXIT_MODE = 1;

if(exist(filename, 'file'))
    disp 'reading file'
    fid = fopen(filename, 'r');
    data = fread(fid, 'uchar');
    data = data';
    fclose(fid);
else
    disp 'creating new file'
    data = round(rand(1,144));  % 18 data bytes
    % write it out to a file too for next time
    fid = fopen(filename, 'w');
    fwrite(fid, data, 'uchar');
    fclose(fid);
end

% turn the diary on so we can log all the output if we are in debug mode
if DEBUG_OUTPUT
    if(exist(diaryFilename, 'file'))
        % remove it to start fresh
        delete(diaryFilename)
    end
    diary(diaryFilename);
end

c = BtcEncode(data, grows, gcols, k_per_row, k_per_col, B, Q, DEBUG_OUTPUT);

% now lets decode it too
s = 2*c-1;
variance = .05;
noise = sqrt(variance)*randn(size(c));
r = s + noise;
llr = 2*r/variance;

[out, errors] = BtcDecode( llr, data, grows, gcols, k_per_row, k_per_col, B, Q, 6, 4, ...
    DEBUG_OUTPUT, EARLY_EXIT_MODE);
errors

if DEBUG_OUTPUT
     diary off
end