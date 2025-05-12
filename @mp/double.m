function out = double(x)

if isempty(x)
    s = size(x);
    if(isequal(s,[0 1]))
        out = double.empty(0,1);
    elseif(isequal(s,[1 0]))
        out = double.empty(1,0);
    elseif (isequal(s,[0 0]))
        out = double.empty;
    else
        out = double.empty;
    end
    return;
end

if isreal(x)
    out = zeros(size(x));
    for i = 1:numel(x)
        out(i) = mp_r_double(x(i).pointer);
    end
else
    out = repmat(complex(0,1),size(x));
    for i = 1:numel(x)
        out(i) = mp_c_double(x(i).pointer);
    end
end