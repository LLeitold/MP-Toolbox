function out = minus(x, y)

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

[x,y] = compatibleArrays(x,y);
[out,x,ex,y,ey,~] = getPnS(x,y);
sx =size(x);
sy =size(y);
flag = -1;

if (sx(1) ~= sy(1) || sx(2) ~= sy(2))
    if ~(length(x) == 1 || length(y) == 1)
        disp(['size of matrix 1 => ', num2str(sx(1)), 'x', num2str(sx(2))]);
        disp(['size of matrix 2 => ', num2str(sy(1)), 'x', num2str(sy(2))]);
        error('Size mismatch for mp objects');
    end
end

if((length(sx)>length(sy)))
    if(~(all(sy == sx(1:length(sy))))&& ~length(sy)==1)
        error('Array dimensions must match for binary array op.')
    end
    flag = 0;
    k = prod((sx(length(sy)+1:end)));
elseif(length(sy)>length(sx))
    if(~(all(sx == sy(1:length(sx))))&& ~length(sx)==1)
        error('Array dimensions must match for binary array op.')
    end
    flag = 1;
    k = prod((sy(length(sx)+1:end)));
else
    if(~(all(sy == sx)) && ~length(ex)==1 || ~length(ey)==1)
        error('Array dimensions must match for binary array op.')
    end
    k=1;
end

if isreal(out)
    mp_r_minus( [x.pointer], [y.pointer], [out.pointer],...
        int32(ex), int32(ey), int32(k), int32(flag));
else
    mp_c_minus( [x.pointer], [y.pointer], [out.pointer],...
        int32(ex), int32(ey), int32(k), int32(flag));
end