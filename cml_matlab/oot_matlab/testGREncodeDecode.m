% Helps Debug GR Encode & Decode versus Matlab (full chain test)

clear;
clc;

% add the correct directories to the path so we can call the functions
addpath(fullfile(pwd, '..', 'mat'))
addpath(fullfile(pwd, '..', 'mex'))

% Setup the Encoder/Decoder
grows = [1 1];
gcols = [1 0 1 0 1 1];
k_per_row = 26;
k_per_col = 6;
B = 9;
Q = 3;

% read the encoder input from GR
grEncoderInputFname = '../../testdata/gr_encoder_input.bin';
grEncoderInputFid = fopen(grEncoderInputFname);
grEncoderOutputFname = '../../testdata/gr_encoder_output.bin';
grEncoderOutputFid = fopen(grEncoderOutputFname);
grDecoderInputFname = '../../testdata/gr_decoder_input.bin';
grDecoderInputFid = fopen(grDecoderInputFname);
grDecoderOutputFname = '../../testdata/gr_decoder_output.bin';
grDecoderOutputFid = fopen(grDecoderOutputFname);

gr_encoder_input = fread(grEncoderInputFid, Inf, 'uint8')';
gr_encoder_output = fread(grEncoderOutputFid, Inf, 'float32')';
gr_decoder_input = fread(grDecoderInputFid, Inf, 'float32')';
gr_decoder_output = fread(grDecoderOutputFid, Inf, 'float32')';

% there are 2 blocks so we need to run the encoder twice
encodedData = [];
for ii=[1:144:length(gr_encoder_input)]
    data = gr_encoder_input(ii:ii+144-1);
    c = BtcEncode(data, grows, gcols, k_per_row, k_per_col, B, Q, 0);
    encodedData = [encodedData c];
end

decodedData = [];
jj = 1;
DEBUG_OUTPUT = 1;
EARLY_EXIT_MODE = 1;
for ii=[1:288:length(gr_decoder_input)]
    llr = gr_decoder_input(ii:ii+288-1);
    cmpData = gr_encoder_input(jj:jj+144-1);
    [out, errors] = BtcDecode( llr, cmpData, grows, gcols, k_per_row, k_per_col, B, Q, 6, 0, ...
        DEBUG_OUTPUT, EARLY_EXIT_MODE);
    jj = jj + 144;
end
