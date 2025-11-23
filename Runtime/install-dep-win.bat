@echo off
cd %USERPROFILE%
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
call .\bootstrap-vcpkg.bat
.\vcpkg integrate install
.\vcpkg install libffi
pause
