function out = plus(x, y)

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

if((length(sx)>length(sy)))
    if(~(all(sy == sx(1:length(sy))))&& ~length(sy)==1)
        error('Array dimensions must match for binary array op.')
    end
    k = prod((sx(length(sy)+1:end)));
    if x(1).is_real
        mp_r_plus( [x.pointer], [y.pointer], [out.pointer],...
            int32(ex), int32(ey), int32(k));
    else
        mp_c_plus( [x.pointer], [y.pointer], [out.pointer],...
            int32(ex), int32(ey), int32(k));
    end

elseif(length(sy)>length(sx) )
    if(~(all(sx == sy(1:length(sx))))&& ~length(sx)==1)
        error('Array dimensions must match for binary array op.')
    end
    k = prod((sy(length(sx)+1:end)));
    if x(1).is_real
        mp_r_plus( [y.pointer], [x.pointer], [out.pointer],...
            int32(ey), int32(ex),  int32(k));
    else
        mp_c_plus( [y.pointer], [x.pointer], [out.pointer],...
            int32(ey), int32(ex),  int32(k));
    end
else
    if(~(all(sy == sx)) && ~length(ex)==1 && ~length(ey)==1)
        error('Array dimensions must match for binary array op.')
    end
    k=1;
    if x(1).is_real
        mp_r_plus( [x.pointer], [y.pointer], [out.pointer],...
            int32(ex), int32(ey), int32(k));
    else
        mp_c_plus( [x.pointer], [y.pointer], [out.pointer],...
            int32(ex), int32(ey), int32(k));
    end
end

end