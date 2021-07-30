

call  "\\DESKTOP-6VA861N\F$\Program Files\Polyspace\R2020b\bin\win64\checkMATLABRootForDriveMap.exe" "\\DESKTOP-6VA861N\F$\Program Files\Polyspace\R2020b"  > mlEnv.txt
for /f %%a in (mlEnv.txt) do set "%%a"\n
cd .

if "%1"=="" ("F:\Program Files\Polyspace\R2020b\bin\win64\gmake" MATLAB_ROOT=%MATLAB_ROOT% ALT_MATLAB_ROOT=%ALT_MATLAB_ROOT% MATLAB_BIN=%MATLAB_BIN% ALT_MATLAB_BIN=%ALT_MATLAB_BIN%  DEPRULES=1 -j5  -f adc_oku.mk all) else ("F:\Program Files\Polyspace\R2020b\bin\win64\gmake" MATLAB_ROOT=%MATLAB_ROOT% ALT_MATLAB_ROOT=%ALT_MATLAB_ROOT% MATLAB_BIN=%MATLAB_BIN% ALT_MATLAB_BIN=%ALT_MATLAB_BIN%  DEPRULES=1 -j5  -f adc_oku.mk %1)
@if errorlevel 1 goto error_exit

exit 0

:error_exit
echo The make command returned an error of %errorlevel%
exit 1