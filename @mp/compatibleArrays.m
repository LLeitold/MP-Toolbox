function [x,y] = compatibleArrays(x,y)
sx =size(x);
sy =size(y);
f=0;

if (length(sx)<3 && length(sy)<3)
    if(~isequal(sx,sy))
        if(~(isscalar(x) || isscalar(y)))
            if(any(sy==1) && all(sx~=1))
                if(sx(1)==sy(1))
                    y = repmat(y,1,size(x,2));
                    f = 1;
                elseif (sx(2)==sy(2))
                    y = repmat(y,size(x,1),1);
                    f = 1;
                else
                    error("Array dimensions must match for binary array op.")
                end
            elseif(any(sx==1) && all(sy~=1))
                if(sx(1)==sy(1))
                    x = repmat(x,1,size(y,2));
                    f = 1;
                elseif (sx(2)==sy(2))
                    x = repmat(x,size(y,1),1);
                    f = 1;
                else
                    error("Array dimensions must match for binary array op.")
                end
            end %end of one matrix/one vector
            if(any(sy==1) && any(sx==1))
                if (sx(1)==1 && sy(2)==1)
                    y =repmat(y,1,size(x,2));
                    x =repmat(x,size(y,1),1);
                elseif sx(2)==1 && sy(1)==1
                    x = repmat(x,1,size(y,2));
                    y = repmat(y,size(x,1),1);
                else
                    error("Array dimensions must match for binary array op.")
                end
            elseif f~=1
                error("Array dimensions must match for binary array op.")
            end %end of 1 column / 1row vector
        end %neither is scalar
    end %end of not equal
else
    if length(sx)>=length(sy)
        sy2 = size(y,1:length(size(x)));
        sy3 = ones(1,length(sy2));
        sx3 = ones(1,length(sx));
        com = sx-sy2;
        for i=1:length(com)
            if com(i)==0
                sy3(i) = 1;
                sx3(i) = 1;
            elseif com(i)>0
                if(sy2(i))==1
                    sy3(i) = sx(i);
                else
                    error("Array dimensions must match for binary array op.")
                end
            elseif com(i)<0
                if(sx(i))==1
                    sx3(i) = sy2(i);
                else
                    error("Array dimensions must match for binary array op.")
                end
            end
        end
    else %sy longer then sx
        sx2 = size(x,1:length(size(y)));
        sx3 = ones(1,length(sx2));
        sy3 = ones(1,length(sy));
        com = sy-sx2;
        for i=1:length(com)
            if com(i)==0
                sy3(i) = 1;
                sx3(i) = 1;
            elseif com(i)>0
                if(sx2(i))==1
                    sx3(i) = sy(i);
                else
                    error("Array dimensions must match for binary array op.")
                end
            elseif com(i)<0
                if(sy(i))==1
                    sy3(i) = sx2(i);
                else
                    error("Array dimensions must match for binary array op.")
                end
            end
        end
    end
    x = repmat(x,sx3);
    y = repmat(y,sy3);
end %end dims < 3
end