% Script which attempts to characterize the LLR's over different noise levels
% to see if we can exit early in the BTC decode process

function [] = testBTCDecode_llrCompute(Eb_N0_dB, grows, gcols, k_per_row, k_per_col, B, Q, decoderType, numTurboIter)
% decoderType
%    0 - linear LOG-MAP
%    1 - MAX-LOG-MAP approximation
%    2 - Constant LOG-MAP
%    3 - log map (correction factor table)
%    4 - log map (correction factor w/ c function calls)

% load the communications package for octave to add noise
pkg load communications
% add the correct paths to ensure that we can use the BtcEncode & BtcDecode functions
addpath(fullfile(pwd, '..', 'mat'))
addpath(fullfile(pwd, '..', 'mex'))

DEBUG_OUTPUT = 0;
EARLY_EXIT_MODE = 0;

% determine the input size of each block
inputSize = (k_per_row*k_per_col - (B+Q));

for ii=1:length(Eb_N0_dB)
    printf('Running simulation for Eb/N0=%f\n', Eb_N0_dB(ii));
    fflush(stdout);
    
    % we want to run ~1 million bits for each iteration of eb/n0
%      numTimesToRun = ceil(1e6/inputSize);
    numTimesToRun = 10;
    
    errorMat = zeros(numTurboIter,numTimesToRun);
    distanceFromZeroMat = zeros(numTurboIter, numTimesToRun);
    
    for jj=1:numTimesToRun
        data = round(rand(1,inputSize));
        
        % encode it
        inputDataEncoded = BtcEncode(data, grows, gcols, k_per_row, k_per_col, B, Q, DEBUG_OUTPUT);
        sig = 2*inputDataEncoded-1;
        
%          % add noise
%          rx = awgn(sig, Eb_N0_dB(ii));
%          llr = rx;    % we could do something more fancy and measure the snr and divide by teh appropriate var .. something ot test
%                       % to see if we get better performance w/ actual llr rather than approximation
        
        
        % add noise to the signal
        SNR = 10^(Eb_N0_dB(ii)/10);
        Ps = sum(sig.^2)/length(sig);       % measure power of signal
        Pn = Ps/SNR;                        % wanted noise power
        w = randn(1,length(sig));
        w = w - sum(w)/length(sig);         % force zero mean signal, b/c of approximations we do this
        Pw = 1/(length(w))*sum(w.^2);       % measure power of white noise generate
        variance = sqrt((Pn/Pw));
        w = variance.*w;                    % scale noise to power to acheive desired SNR
        
        rx = sig + w;
        llr = 2*rx/variance;                % the llr equation for BPSK modulation
        
        % decode
        [out, errors, distanceFromZeroVec] = ...
            BtcDecode( llr, data, grows, gcols, k_per_row, k_per_col, B, Q, numTurboIter, decoderType, ...
            DEBUG_OUTPUT, EARLY_EXIT_MODE);
        
        % add into error rate into the vec
        errorMat(:,jj) = errors;
        distanceFromZeroMat(:,jj) = distanceFromZeroVec;
        
    end
    
    % display the average results for this SNR
    avgErrorVec = mean(errorMat,2);
    avgDistanceFromZeroVec = mean(distanceFromZeroMat,2);
    
    figure(1);
    subplot(2,1,1)
    plot(avgErrorVec)
    ylabel('Avg Number of Bit Errors')
    title(sprintf('SNR = %f dB\n', Eb_N0_dB(ii)));
    grid on
    subplot(2,1,2)
    plot(avgDistanceFromZeroVec)
    xlabel('Turbo Iteration')
    ylabel('Avg Distance from Zero Metric')
    title(sprintf('SNR = %f dB\n', Eb_N0_dB(ii)));
    grid on
    
    keyboard()
end

end
