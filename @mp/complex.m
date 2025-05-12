function C = complex(A,B)

if nargin == 1
    if isreal(A)
        B = 0;
        C = complex(A,B);
    else
        C = mp(A);
    end
else

    if ~isreal(A)
        error('Error using complex\n Input for real part must be a real numeric value.');
    end

    if ~isreal(B)
        error('Error using complex\n Input for imaginary part must be a real numeric value.');
    end

    if isscalar(A) && ~isscalar(B)
        A = repmat(A, size(B));
    elseif isscalar(B) && ~isscalar(A)
        B = repmat(B, size(A));
    end

    if ~ any(size(A) == size(B))
        error('MP:complex',...
            'Input arrays must have the same size.')
    end

    [~,A,~,B,~,precision] = getPnS(A,B);

    C = mp(repmat(complex(0,1),size(A)), precision);
    mp_c_construct_mpmp([A.pointer], [B.pointer], [C.pointer], precision);
end