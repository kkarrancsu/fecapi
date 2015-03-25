function [] = printFloatArray(array)

    for ii=1:length(array)
        fprintf('%f ', array(ii));
    end

end