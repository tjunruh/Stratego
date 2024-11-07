msbuild /m /p:Configuration=Release Code/Stratego.vcxproj
mkdir build
mkdir build\board_configs
copy Code\Release\Stratego.exe build
copy Code\Release\ascii_engine.dll build
copy board_configs\* build\board_configs\
rd /s /q Code\Release