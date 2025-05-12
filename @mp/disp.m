function disp(x,varargin)
s = size(x);
l = length(s);
sets = settings;
myformat = sets.matlab.commandwindow.NumericFormat.ActiveValue;
if(nargin==1||nargin==0)
   var_name = "";
elseif(nargin==3 && varargin{2}==1)
    var_name = varargin{1};
else
    error("Too many input arguments!")
end

switch myformat
    case 'short'
        ans1 = getStringShort(x,s);
    case 'shortE'
        ans1 = getStringShort(x,s);
    case 'long'
        ans1 = getStringLong(x,s);
    case 'longE'
        ans1 = getStringLong(x,s);
    otherwise
    error('Only short and long display formats have been implemented!');
end

if(l<=2&&l>1) %its not one, its a lower case L!!!
    fprintf(var_name);
    fprintf(' = \n');
    threedPrintrint(ans1,s,1)
elseif(l>2) %its not one, its a lower case L!!!
    indices = cell(1, ndims(x));
    totalElements = prod(s);
    [indices{:}] = ind2sub(s, 1);
    prev_ind = indices;
    indices(1:2) = {':'};
    % Retrieve elements based on the given dimension
    for i = 1:totalElements
        [indices{:}] = ind2sub(s, i);
        indices(1:2) = {':'};
        if(isequal(indices,prev_ind))
            continue;
        end
        prev_ind = indices;
        fprintf(var_name);
        fprintf("(:,:,");
        temp = num2str(cell2mat(indices(3:end)));
        for k=1:numel(temp)
            if isequal(temp(k),' ')
               continue; 
            end
            if(k < (numel(temp)-1))
                fprintf("%s,",temp(k));
            else
                fprintf("%s",temp(k));
            end
        end
        
        fprintf(") = \n");
        threedPrintrint(ans1(indices{:}),s(1:2),1);
    end
else
    disp([]);
end
end

function threedPrintrint(ans1,s,d)
    fprintf('\n');
    for k = 1:d
        if(d>=2)
            fprintf('(:,:,%i) = \n\n',k);
        end
        for i=1:s(1)
            for j=1:s(2)
                fprintf('%s    ', ans1(i,j,k));
            end
            fprintf('\n');
        end
        fprintf('\n');
    end
end

function ans1 = getStringLong(x,s)
    ans1 = repmat("",s);
    for ii = 1:numel(x)
        if x(ii).is_real
            rval=mp_r_disp(x(ii).pointer);

        else
            rval=mp_c_disp(x(ii).pointer);
        end
        ans1(ii) = (rval);
    end
end

function ans1 = getStringShort(x,s)
    ans1 = repmat("",s);
    for ii = 1:numel(x)
        if x(ii).is_real
            rval=mp_r_disp_short(x(ii).pointer);
        else
            rval=mp_c_disp_short(x(ii).pointer);
        end
        ans1(ii) = (rval);
    end
end