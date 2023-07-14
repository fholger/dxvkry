rem call "%ProgramFiles%\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat" -arch=x86

meson setup --prefix="%~dp0." --buildtype=release --backend vs build
