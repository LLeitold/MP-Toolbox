function out = isreal(x)

out = true;

for ii = 1:numel(x)
    if ~x(ii).is_real
        out = false;
        break;
    end
end

end