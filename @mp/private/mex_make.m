libPath = pwd;
iPath = ['-I' libPath];
lPath = ['-L' libPath];

headerList = dir('*.h');
dllList = dir('*.dll');
libList = dir('*.lib');
dependenciesList = [headerList; dllList; libList];
lastLibModified = max(cell2mat({dependenciesList(:).datenum}'));

fileList = dir('*.cpp');
for i = 1 : length(fileList)
    func_name = fileList(i).name;
    mexFileDir = dir([func_name(1:end-3) 'mexw64']);
    if isempty(mexFileDir) || ...
       fileList(i).datenum > mexFileDir.datenum || ...
       lastLibModified > mexFileDir.datenum

        disp(['MEX: ' func_name])
        mex(func_name, '-g', '-O', iPath, lPath, '-lmpfr.dll', '-lmpc.dll', '-lmplapack_mpfr.dll', '-lmpblas_mpfr.dll', "CXXFLAGS=$CXXFLAGS -fpermissive")
    end
end

disp('MEX script finished.');
