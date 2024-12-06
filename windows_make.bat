msbuild /m /p:Configuration=Release Code/Stratego.vcxproj
mkdir build
mkdir build\bin
mkdir build\bin\board_configs
copy Code\Release\Stratego.exe build\bin\
copy Code\Release\ascii_engine.dll build\bin\
copy board_configs\* build\bin\board_configs\
copy Stratego.bat build\
rd /s /q Code\Release