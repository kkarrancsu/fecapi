% A high level test script meant specifically to test 
% the C output versus matlab output of the BTC Decoder

clear;
clc;

% add the correct directories to the path so we can call the functions
addpath(fullfile(pwd, '..', 'mat'))
addpath(fullfile(pwd, '..', 'mex'))

decoder_input_filename = '../../testdata/test_1_output.bin';
decoder_output_check = '../../testdata/test_1_input.bin';

diaryFilename = 'diary';

% Setup decoder parameters
grows = [1 1];
gcols = [1 0 1 0 1 1];
k_per_row = 26;
k_per_col = 6;
B = 9;
Q = 3;
DEBUG_OUTPUT = 0;
EARLY_EXIT_MODE = 1;

% input to decoder will be read in from the file
if(exist(decoder_input_filename, 'file'))
    fid = fopen(decoder_input_filename, 'r');
    bits = fread(fid, 'uchar');
    bits = bits';
    signal = 2*bits-1;
    noise_var = 2;
    llr = 2*signal/noise_var;
    fclose(fid);
else
    printf('Invalid file\n');
end

if(exist(decoder_output_check, 'file'))
    fid = fopen(decoder_output_check, 'r');
    data = fread(fid, 'uchar');
    data = data';
    fclose(fid);
else
    printf('Invalid file\n');
end


% turn the diary on so we can log all the output if we are in debug mode
if DEBUG_OUTPUT
    if(exist(diaryFilename, 'file'))
        % remove it to start fresh
        delete(diaryFilename)
    end
    diary on;
end


numTurboIter = 6;
decoderType = 1; % for MAX-LOG-MAP approx
[out, errors] = BtcDecode( llr, data, grows, gcols, k_per_row, k_per_col, B, Q, ...
                           numTurboIter, decoderType, DEBUG_OUTPUT, EARLY_EXIT_MODE);

errors
                           
if DEBUG_OUTPUT
     diary off
end