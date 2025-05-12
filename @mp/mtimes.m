 function out = mtimes(x, y)

if isempty(x)
    out = x;
    return;
elseif isempty(y)
    out = y;
    return
end

if ~isreal(x) || ~isreal(y)
    if isreal(x)
        x = complex(x, 0);
    end

    if isreal(y)
        y = complex(y, 0);
    end
end

[out,x,ex,y,ey,precision] = getPnS(x,y); %#ok<ASGLU> 

if ex == 1 || ey == 1
    out = x.*y;
else %%% out=x*y;
    sx = size(x);
    sy = size(y);
    if sx(2) ~= sy(1)
        disp(['size of matrix 1 => ', num2str(sx(1)), 'x', num2str(sx(2))]);
        disp(['size of matrix 2 => ', num2str(sy(1)), 'x', num2str(sy(2))]);
        error('array size mismatch for mtimes')
    else
        if isreal(x)
            out = mp(zeros(sx(1), sy(2)), precision);
            mp_r_mtimes([x.pointer],[y.pointer],[out.pointer],int32(sx(1)),int32(sy(2)),int32(sx(2)),int32(precision));
        else
            out = complex(mp(zeros(sx(1), sy(2)), precision));
            mp_c_mtimes([x.pointer],[y.pointer],[out.pointer],int32(sx(1)),int32(sy(2)),int32(sx(2)),int32(precision));
        end
    end
end
