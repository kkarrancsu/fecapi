% FindBestBerCurves.m
% Given a set of CML BER records, find and sort the N best performing
%  curves at a specified operating point.
%
% The calling syntax is:
%     [ best_records ] = FindBestBerCurves(  scenario,...
%                                                    candidate_records,...
%                                                         N  )
%
%     Inputs
%     scenario          - BER scenario
%     candidate_records - records within scenario to consider
%     N                 - number of records to return
%     BERop             - requested operating point
%
%     Outputs
%     best_records      - records of best thresholds
%
%     Copyright (C) 2012, Terry Ferrett and Matthew C. Valenti
%
%     Last updated on 1/20/2013

function [BestRecords] = FindBestBerCurves(  scenario,...
    CandidateRecords,...
    BERop,...
    N )


M = length(CandidateRecords);

if N > M,
    error('Number of requested curves N exceeds the number available');
end

% get BER data from CML records
[save_param save_state] = CmlPlot(scenario, CandidateRecords);
close all;

% initialize SNR operating point vector
SNRop = zeros(1,M);

% find snr operating points at requested operating ber
for m = 1:M,
    [SNRm BERm] = get_mth_snr_ber(save_param, save_state, m);
    
    [LastBerIndAboveOp BerIndBelowOp] = get_ber_inds_around_op( BERm, BERop );
    
    [BerAboveOp BerBelowOp] = get_bers_around_op(BERm, LastBerIndAboveOp, BerIndBelowOp);
    
    
    if BerBelowOp == 0 || LastBerIndAboveOp == length(SNRm),
        SNRop(m) = 1000; % set to large value, will be ignored
    else
        SnrAboveOp = SNRm(LastBerIndAboveOp);
        SnrBelowOp = SNRm(BerIndBelowOp);
        
        SNRop(m) = find_snr_op_by_interp(BerAboveOp, BerBelowOp, SnrAboveOp, SnrBelowOp, BERop);
    end
end

[BestRecords SNRopS] = get_best_records_by_sorting( SNRop, CandidateRecords, N );

BestRecords = prune_records_with_no_data( BestRecords, SNRopS );


end

function [SNRm BERm] = get_mth_snr_ber(save_param, save_state, m)
SNRm = save_param(m).SNR;
BERm = save_state(m).BER(end,:);
end



function [LastBerIndAboveOp BerIndBelowOp] = get_ber_inds_around_op( BERm, BERop )
BerIndsAboveOp = find( BERm > BERop );
LastBerIndAboveOp = BerIndsAboveOp(end);
BerIndBelowOp = LastBerIndAboveOp + 1;
end


function [BerAboveOp BerBelowOp] = get_bers_around_op(BERm, LastBerIndAboveOp, BerIndBelowOp)
BerAboveOp = BERm(LastBerIndAboveOp);
BerBelowOp = BERm(BerIndBelowOp);
end


function SNRop = find_snr_op_by_interp(BerAboveOp, BerBelowOp, SnrAboveOp, SnrBelowOp, BERop)
% take log of ber values to perform linear interpolation
BERInterp = log10([BerAboveOp BerBelowOp]);
SNRInterp = [SnrAboveOp SnrBelowOp];
SNRop = interp1(BERInterp, SNRInterp, log10(BERop));
end

function [ BestRecords SNRopS ] = get_best_records_by_sorting( SNRop, CandidateRecords, N )
[SNRopS I] =  sort(SNRop);
SortedRecords = CandidateRecords(I);
BestRecords = SortedRecords(1:N);
end

function BestRecords = prune_records_with_no_data( BestRecords, SNRopS )
RecsToIgnore = find(SNRopS == 1000);

if ~isempty(RecsToIgnore)
    FirstRecToIgnore = RecsToIgnore(1);
    
    if length(BestRecords) >= FirstRecToIgnore,
        BestRecords = BestRecords(1:FirstRecToIgnore - 1);
    end
    
end
end


%     Function FindBestBerCurves is part of the Iterative Solutions Coded Modulation
%     Library (ISCML).
%
%     The Iterative Solutions Coded Modulation Library is free software;
%     you can redistribute it and/or modify it under the terms of
%     the GNU Lesser General Public License as published by the
%     Free Software Foundation; either version 2.1 of the License,
%     or (at your option) any later version.
%
%     This library is distributed in the hope that it will be useful,
%     but WITHOUT ANY WARRANTY; without even the implied warranty of
%     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
%     Lesser General Public License for more details.
%
%     You should have received a copy of the GNU Lesser General Public
%     License along with this library; if not, write to the Free Software
%     Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
