% A simple test Script to showcase the SISO Decoding

clear;
clc;

% add the correct directories to the path so we can call the functions
addpath(fullfile(pwd, '..', 'mat'))
addpath(fullfile(pwd, '..', 'mex'))

code_type = 0;
g = [1 0 1; 1 1 1];
data = [1 1 0 1];
c = ConvEncode(data, g, code_type);

s = 2*c-1;
variance = 1/2;
noise = sqrt(variance)*randn(size(s));
r = s+noise;
llr = 2*r/variance;

input_c = llr;
input_u = zeros(length(data));
dec_type = 4;
[output_u, output_c] = SisoDecode(input_u, input_c, g, code_type, dec_type);

inputBits = data
decodedBits = output_u > 0