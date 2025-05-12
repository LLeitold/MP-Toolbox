function C = rdivide(A, B)

if isempty(A)
    C = A;
    return;
elseif isempty(B)
    C = B;
    return
end

if ~isreal(A) || ~isreal(B)
    if isreal(A)
        A = complex(A, 0);
    end

    if isreal(B)
        B = complex(B, 0);
    end
end

[A,B] = compatibleArrays(A,B);
[C,A,ex,B,ey,~] = getPnS(A,B);
sx =size(A);
sy =size(B);
flag = -1;

if (sx(1) ~= sy(1) || sx(2) ~= sy(2))
    if ~(length(A) == 1 || length(B) == 1)
        disp(['size of matrix 1 => ', num2str(sx(1)), 'x', num2str(sx(2))]);
        disp(['size of matrix 2 => ', num2str(sy(1)), 'x', num2str(sy(2))]);
        error('Size mismatch for mp objects');
    end
end

if((length(sx)>length(sy)))
    if(~(all(sy == sx(1:length(sy)))) && ~length(sy)==1)
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
    if(~(all(sy == sx(1:length(sy))))&& ~length(sy)==1)
        error('Array dimensions must match for binary array op.')
    end
    k=1;
end

if isreal(C)
    mp_r_rdivide( [A.pointer], [B.pointer], [C.pointer],...
        int32(ex), int32(ey), int32(k), int32(flag));
else
    mp_c_rdivide( [A.pointer], [B.pointer], [C.pointer],...
        int32(ex), int32(ey), int32(k), int32(flag));
end
end