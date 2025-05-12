function [out,x,ex,y,ey,varargout] = getPnS(x,y)

if ~isreal(x) && isreal(y)
    y = complex(y);
end

if ~isreal(y) && isreal(x)
    x = complex(x);
end

precision = ones(2,1);

if(isa(x,"mp"))
    precision(1) = x.precision;
end

if(isa(y,"mp"))
    precision(2) = y.precision;
end

precision = max(precision);
varargout = {precision};

if ~isa(x, 'mp')
    x = mp(x, precision);
elseif precision > x(1).precision
    x = mp(x, precision);
end

if ~isa(y, 'mp')
    y = mp(y, precision);
elseif precision > y(1).precision
    y = mp(y, precision);
end

sx = size(x);
sy = size(y);
ex = prod(sx);
ey = prod(sy);

if ex >= ey
    out = mp(zeros(sx), precision);
else
    out = mp(zeros(sy), precision);
end

if ~(isreal(x) && isreal(y))
    out = complex(out);
end