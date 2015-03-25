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
generateTestCaseFiles(grows, gcols, k_per_row, k_per_col, B, Q, testCaseNum)

%%%%% Generate Test Case 2 I/O Files
testCaseNum = testCaseNum + 1;
grows = g1;
gcols = g6;
k_per_row = 3;
k_per_col = 18;
B = 0;
Q = 6;
generateTestCaseFiles(grows, gcols, k_per_row, k_per_col, B, Q, testCaseNum)

%%%%% Generate Test Case 3 I/O Files
testCaseNum = testCaseNum + 1;
grows = g1;
gcols = g1;
k_per_row = 9;
k_per_col = 9;
B = 4;
Q = 5;
generateTestCaseFiles(grows, gcols, k_per_row, k_per_col, B, Q, testCaseNum)

%%%%% Generate Test Case 4 I/O Files
testCaseNum = testCaseNum + 1;
grows = g1;
gcols = g5;
k_per_row = 17;
k_per_col = 6;
B = 6;
Q = 0;
generateTestCaseFiles(grows, gcols, k_per_row, k_per_col, B, Q, testCaseNum)

%%%%% Generate Test Case 5 I/O Files
testCaseNum = testCaseNum + 1;
grows = g1;
gcols = g1;
k_per_row = 13;
k_per_col = 13;
B = 4;
Q = 5;
generateTestCaseFiles(grows, gcols, k_per_row, k_per_col, B, Q, testCaseNum)

%%%%% Generate Test Case 6 I/O Files
testCaseNum = testCaseNum + 1;
grows = g1;
gcols = g7;
k_per_row = 5;
k_per_col = 41;
B = 0;
Q = 5;
generateTestCaseFiles(grows, gcols, k_per_row, k_per_col, B, Q, testCaseNum)

%%%%% Generate Test Case 7 I/O Files
testCaseNum = testCaseNum + 1;
grows = g6;
gcols = g5;
k_per_row = 22;
k_per_col = 9;
B = 8;
Q = 6;
generateTestCaseFiles(grows, gcols, k_per_row, k_per_col, B, Q, testCaseNum)

%%%%% Generate Test Case 8 I/O Files
testCaseNum = testCaseNum + 1;
grows = g6;
gcols = g1;
k_per_row = 26;
k_per_col = 11;
B = 0;
Q = 6;
generateTestCaseFiles(grows, gcols, k_per_row, k_per_col, B, Q, testCaseNum)

%%%%% Generate Test Case 9 I/O Files
testCaseNum = testCaseNum + 1;
grows = g6;
gcols = g6;
k_per_row = 16;
k_per_col = 16;
B = 4;
Q = 4;
generateTestCaseFiles(grows, gcols, k_per_row, k_per_col, B, Q, testCaseNum)

%%%%% Generate Test Case 10 I/O Files
testCaseNum = testCaseNum + 1;
grows = g6;
gcols = g6;
k_per_row = 18;
k_per_col = 18;
B = 0;
Q = 4;
generateTestCaseFiles(grows, gcols, k_per_row, k_per_col, B, Q, testCaseNum)

end

function [] = generateTestCaseFiles(grows, gcols, k_per_row, k_per_col, B, Q, testCaseNum)
DEBUG_OUTPUT = 0;
testFilesOutputDir = '../../testdata';

testCaseInputFilename = fullfile(testFilesOutputDir, sprintf('test_%d_input.bin', testCaseNum));
testCaseOutputFilename = fullfile(testFilesOutputDir, sprintf('test_%d_output.bin', testCaseNum));

% if the file exists, use it as the data, if nto generate
if(exist(testCaseInputFilename, 'file'))
    fid = fopen(testCaseInputFilename, 'r');
    inputData = fread(fid, 'uchar');
    inputData = inputData';
    fclose(fid);
else
    inputDataSize = (k_per_row*k_per_col - (B+Q));
    inputData = round(rand(1,inputDataSize));  % 18 data bytes
    writeDataToFile(inputData, 'uchar', testCaseInputFilename);
end

% an input should always correspond w/ a certain output, so always generate the output
outputData = BtcEncode(inputData, grows, gcols, k_per_row, k_per_col, B, Q, DEBUG_OUTPUT);
writeDataToFile(outputData, 'uchar', testCaseOutputFilename);

end

function [] = writeDataToFile(data, datatype, filenameWithPath)

fid = fopen(filenameWithPath, 'w');
fwrite(fid, data, datatype);
fclose(fid);

end