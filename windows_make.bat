status=0
msbuild /m /p:Configuration=Release Code/windows_msbuild/Stratego.vcxproj
IF %ERRORLEVEL% NEQ 0 (
  set status=1
)
mkdir build
mkdir build\bin
mkdir build\bin\board_configs
copy Code\windows_msbuild\Release\Stratego.exe build\bin\
copy Code\windows_msbuild\Release\ascii_engine.dll build\bin\
copy board_configs\* build\bin\board_configs\
copy Stratego.bat build\
FOR /D %%p IN ("Code\windows_msbuild\*.*") DO rmdir "%%p" /s /q

EXIT /b %status%