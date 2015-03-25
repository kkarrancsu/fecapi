% Attempts to generate the BER curve for the BTC

function [bers, avgActualIters, llrVec] = genBerCurve_BTC(Eb_N0_dB, grows, gcols, k_per_row, k_per_col, B, Q, decoderType, ...
    numTurboIter, EARLY_EXIT_MODE)
% decoderType
%    0 - linear LOG-MAP
%    1 - MAX-LOG-MAP approximation
%    2 - Constant LOG-MAP
%    3 - log map (correction factor table)
%    4 - log map (correction factor w/ c function calls)

% load the communications package for octave to add noise
isOctave = exist('OCTAVE_VERSION', 'builtin') ~= 0;
if(isOctave)
    pkg load communications
end
% add the correct paths to ensure that we can use the BtcEncode & BtcDecode functions
addpath(fullfile(pwd, '..', 'mat'))
addpath(fullfile(pwd, '..', 'mex'))

DEBUG_OUTPUT = 0;

% determine the input size of each block
inputSize = (k_per_row*k_per_col - (B+Q));
bers = zeros(1,length(Eb_N0_dB));

llrVec = [];

for ii=1:length(Eb_N0_dB)
    printf('Running simulation for Eb/N0=%f\n', Eb_N0_dB(ii));
    if(isOctave)
        fflush(stdout);
    else
        drawnow('update');
    end
    
    % we want to run ~1 million bits for each iteration of eb/n0
    numTimesToRun = ceil(1e6/inputSize);
    errorVec = zeros(1,numTimesToRun);
    numActualItersVec = zeros(1,numTimesToRun);
    for jj=1:numTimesToRun
        data = round(rand(1,inputSize));
        
        % encode it
        inputDataEncoded = BtcEncode(data, grows, gcols, k_per_row, k_per_col, B, Q, DEBUG_OUTPUT);
        sig = 2*inputDataEncoded-1;
        
        % add noise
        rx = awgn(sig, Eb_N0_dB(ii), 'measured');
        expNoisePwr = 1/(10^(Eb_N0_dB(ii)/10));
        llr = (2*rx)/expNoisePwr;       % LLR formula for BPSK modulated (+1 or -1)
        
        llrVec = [llrVec llr];
        
        % decode
        [out, errors, ~, turbo_iter] = BtcDecode( llr, data, grows, gcols, k_per_row, k_per_col, B, Q, numTurboIter, decoderType, ...
            DEBUG_OUTPUT, EARLY_EXIT_MODE);
        errorVal = errors(end);  % choose the last turbo iteration for the errorVal
        
        % add into error rate into the vec
        errorVec(jj) = (errorVal/inputSize);
        numActualItersVec(jj) = turbo_iter;
    end
    avgError = mean(errorVec);
    avgActualIters(ii) = mean(numActualItersVec);
    bers(ii) = avgError;
    
    printf('Eb/N0 = %f avgError=%f avgNumIters=%f\n', Eb_N0_dB(ii), avgError, avgActualIters(ii));
    if(isOctave)
        fflush(stdout);
    else
        drawnow('update');
    end
    
end

end
