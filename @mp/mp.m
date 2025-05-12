classdef mp < handle
    properties (Constant,Hidden)
        defaultPrecision = 70; %must be integer value
    end

    properties
        pointer = []; % pointer to mpreal/mpcomplex in memory
        precision = mp.defaultPrecision; %precision
        is_real = true; % to track internally if real or complex number stored
    end

    methods (Static)
        function setDefaultPrecision(value)
            if(mod(value,1)~=0 || value < 0)
                error("Precision must be positive scalar integer value!")
            end

            p = which('mp');
            p = extractBefore(p,'mp.m');
            p = [p 'precision.txt'];
            fileID = fopen(p,'w');
            if(fileID < 0)
                error('Error opening default precision file!');
            end

            line1 = "This file containes the default precision in bits for the Multiple-precision arithmetic Toolbox for MATLAB (mp) class\n";
            line2 = "Default precision is: %d\n";
            line3 = "Please use the static functions mp.getDefaultPrecision and mp.setDefaultPrecision\nto get and set the value!\n";
            fprintf(fileID,line1);
            fprintf(fileID,line2,value);
            fprintf(fileID,line3);
            c = fclose(fileID);
            if(c)
                error('Error closing default precision file!');
            else
                disp("Default precision updated successfully!");
            end
        end

        function y = getDefaultPrecision
            p = which('mp');
            p = extractBefore(p,'mp.m');
            p = [p 'precision.txt'];
            fileID = fopen(p,'r');
            if(fileID == -1)
                y = mp.defaultPrecision;
                warning("Cound't find mp root directory! Using built in default precision!");
            else
                tline = fgetl(fileID); %#ok<NASGU> we need the second line from the file
                tline = fgetl(fileID);
                c = split(tline,":");
                y = str2double(c{2,1});
                if(fclose(fileID))
                    error('Error closing default precision file!');
                end
            end
        end
    end

    methods
        function obj = mp(x, y)
            if nargin == 0
                obj=mp.empty;
            elseif nargin > 0
                if nargin == 1
                    y = mp.getDefaultPrecision;
                end

                if y < 1
                    error('MP Toolbox precision must be larger than zero')
                end

                if isempty(x)
                    obj=mp.empty;
                elseif (isa(x, 'double') && isscalar(x))
                    if isreal(x)
                        obj.pointer = mp_r_construct_d(x, y);
                    else
                        obj.is_real = false;
                        obj.pointer = mp_c_construct_d(x, y);
                    end

                    obj.precision = y;
                elseif (isa(x, 'single') && isscalar(x))
                    x = double(x);
                    obj = mp(x,y);
                elseif isa(x, 'string')
                    if isscalar(x)
                        x = convertStringsToChars(x);
                        obj = mp(x,y);
                    else
                        obj = repmat(obj,size(x));
                        for i = 1:numel(x)
                            obj(i) = mp(x(i), y);
                        end
                    end
                elseif isa(x,'char')
                    if strcmpi(x,'pi')
                        obj.pointer = mp_r_construct_pi(y);
                    elseif strcmpi(x,'')
                        mp.empty;
                    else
                        if strcmpi(x(end), 'i') || strcmpi(x(end), 'j')
                            x = x(1:end-1);
                            if strcmpi(x(end), '*')
                                x = x(1:end-1);
                            end
                            if contains(x, '+')
                                C = split(x, '+');
                                obj.pointer = mp_c_construct_s(C{1},C{2}, y);
                            elseif contains(x, '-')
                                C = split(x, '-');
                                obj.pointer = mp_c_construct_s(C{1},['-' C{2}], y);
                            else
                                obj.pointer = mp_c_construct_s('0',x, y);
                            end
                            obj.is_real = false;
                        else
                            if strlength(x) > 3
                                if strcmpi(x(2), 'I') || strcmpi(x(3), 'I')
                                    obj.pointer = mp_r_construct_inf(x(1),y);
                                elseif strcmpi(x(1), 'N') || strcmpi(x(2), 'N')
                                    obj.pointer = mp_r_construct_nan(y);
                                else
                                    obj.pointer = mp_r_construct_s(x, y);
                                end
                            else
                                obj.pointer = mp_r_construct_s(x, y);
                            end
                        end
                    end
                    obj.precision = y;

                elseif (isa(x,'mp') && isscalar(x))
                    if nargin==1
                        if x.is_real
                            obj.pointer = mp_r_construct_mp(x.pointer,x.precision);
                        else
                            obj.pointer = mp_c_construct_mp(x.pointer,x.precision);
                        end
                        obj.precision = x.precision;
                        obj.is_real = x.is_real;
                    else
                        if x.is_real
                            obj.pointer = mp_r_construct_mp(x.pointer,y);
                        else
                            obj.pointer = mp_c_construct_mp(x.pointer,y);
                        end
                        obj.precision = y;
                        obj.is_real = x.is_real;
                    end % if nargin==2
                elseif iscell(x)
                    obj = repmat(obj,size(x));
                    for i = 1:numel(x)
                        obj(i) = mp(x{i}, y);
                    end

                    if ~isreal(obj)
                        for i = 1:numel(obj)
                            if isreal(obj(i))
                                obj(i) = complex(obj(i));
                            end
                        end
                    end
                elseif ~isscalar(x)
                    obj = repmat(obj,size(x));
                    for i = 1:numel(x)
                        obj(i) =mp(x(i),y);
                    end

                    if ~isreal(obj)
                        for i = 1:numel(obj)
                            if isreal(obj(i))
                                obj(i) = complex(obj(i));
                            end
                        end
                    end
                end
            end
        end % constructor
    end
    methods (Static)
        function obj = arrayCreation(funcName, varargin)
            fh = str2func(funcName);

            if numel(varargin) == 0
                % For funcName('mp')
                obj = mp(fh());
            elseif any([varargin{:}] <= 0)
                % For funcName with any dimension <= 0
                obj = mp.empty(varargin{:});
            else
                % For funcName(m,n,...,'mp')
                y = ones(numel(varargin) +1,1);
                y(end) = mp.getDefaultPrecision;
                for i = 1: length(varargin)
                    if isa(varargin{i}, 'mp')
                        y(i) = varargin{i}.precision;
                    end
                end

                y = max(y);
                obj = mp(fh(double([varargin{:}])), y);
            end
        end % arrayCreation

        function obj = arrayCreationLike(objIn, funcName, varargin)
            if isempty(objIn)
                p = which('mp');
                p = extractBefore(p,'mp.m');
                p = [p 'precision.bin'];
                fileID = fopen(p,'r');
                if(fileID == -1)
                    precision = mp.defaultPrecision;
                else
                    precision = fread(fileID,[1 1],'double');
                    if(fclose(fileID))
                        error('Error closing default precision file!');
                    end
                end
            else
                precision = objIn(1).precision;
            end

            fh = str2func(funcName);

            if nargin == 1  || isempty(varargin)
                % For funcName('like',obj)
                obj = mp(fh(), precision);
            elseif  any([varargin{:}] <= 0)
                % For funcName with any dimension <= 0
                obj = mp.empty(varargin{:});
            else
                % For funcName(m,n,...,'like',obj)
                obj = mp(fh(double([varargin{:}])), precision);
            end
        end % arrayCreationLike

        function obj = ones(varargin)
            st = dbstack;
            funcName = st(1).name(4:end);
            obj = mp.arrayCreation(funcName, varargin{:});
        end % ones

        function obj = zeros(varargin)
            st = dbstack;
            funcName = st(1).name(4:end);
            obj = mp.arrayCreation(funcName, varargin{:});
        end % zeros

        function obj = eye(varargin)
            st = dbstack;
            funcName = st(1).name(4:end);
            obj = mp.arrayCreation(funcName, varargin{:});
        end % eye

        function obj = nan(varargin)
            st = dbstack;
            funcName = st(1).name(4:end);
            obj = mp.arrayCreation(funcName, varargin{:});
        end % nan

        function obj = inf(varargin)
            st = dbstack;
            funcName = st(1).name(4:end);
            obj = mp.arrayCreation(funcName, varargin{:});
        end % inf

        function B = cast(A)
            B = mp(A);
        end % cast

        function obj = rand(varargin)
            st = dbstack;
            funcName = st(1).name(4:end);
            obj = mp.arrayCreation(funcName, varargin{:});
        end % rand

        function obj = randn(varargin)
            st = dbstack;
            funcName = st(1).name(4:end);
            obj = mp.arrayCreation(funcName, varargin{:});
        end % randn

        function obj = randi(varargin)
            st = dbstack;
            funcName = st(1).name(4:end);
            obj = mp.arrayCreation(funcName, varargin{:});
        end % randi

        function out = eulergamma(precision)
            if nargin == 0
                precision = mp.defaultPrecision;
            end

            out = mp(zeros(1), precision);
            out.rval = mpfr_euler(precision);
        end % eulergamma

        function out = pi(precision)
            if nargin == 0
                precision = mp.defaultPrecision;
            end

            out = mp(zeros(1), precision);
            out.rval = mpfr_pi(precision);
        end % pi

        function out = Log2(precision)
            if nargin == 0
                precision = mp.defaultPrecision;
            end

            out = mp(zeros(1), precision);
            out.rval = mpfr_const_log2(precision);
        end % log2

    end % methods (Static)

    methods (Hidden)
        function mpOut = onesLike(obj,varargin)
            st = dbstack;
            funcName = st(1).name(4:end-4);
            mpOut = mp.arrayCreationLike(obj, funcName, varargin{:});
        end % onesLike

        function mpOut = zerosLike(obj,varargin)
            st = dbstack;
            funcName = st(1).name(4:end-4);
            mpOut = mp.arrayCreationLike(obj, funcName, varargin{:});
        end % zerosLike

        function mpOut = eyeLike(obj, varargin)
            st = dbstack;
            funcName = st(1).name(4:end-4);
            mpOut = mp.arrayCreationLike(obj, funcName, varargin{:});
        end %eyeLike

        function mpOut = nanLike(obj, varargin)
            st = dbstack;
            funcName = st(1).name(4:end-4);
            mpOut = mp.arrayCreationLike(obj, funcName, varargin{:});
        end % nanLike

        function mpOut = infLike(obj, varargin)
            st = dbstack;
            funcName = st(1).name(4:end-4);
            mpOut = mp.arrayCreationLike(obj, funcName, varargin{:});
        end % infLike

        function B = castLike(obj, A)
            if isempty(obj)
                B = mp(A);
            else
                B = mp(A, obj(1).precision);
            end
        end % castLike

        function mpOut = randLike(obj, varargin)
            st = dbstack;
            funcName = st(1).name(4:end-4);
            mpOut = mp.arrayCreationLike(obj, funcName, varargin{:});
        end % randLike

        function mpOut = randnLike(obj, varargin)
            st = dbstack;
            funcName = st(1).name(4:end-4);
            mpOut = mp.arrayCreationLike(obj, funcName, varargin{:});
        end % randnLike

        function mpOut = randiLike(obj, varargin)
            st = dbstack;
            funcName = st(1).name(4:end-4);
            mpOut = mp.arrayCreationLike(obj, funcName, varargin{:});
        end % randiLike
    end % methods (Hidden)
end
