@echo off
chcp 65001 > nul
setlocal
echo @echo off > "%~dp0/deactivate_conanrunenv-debug-x86_64.bat"
echo echo Restoring environment >> "%~dp0/deactivate_conanrunenv-debug-x86_64.bat"
for %%v in (PATH) do (
    set foundenvvar=
    for /f "delims== tokens=1,2" %%a in ('set') do (
        if /I "%%a" == "%%v" (
            echo set "%%a=%%b">> "%~dp0/deactivate_conanrunenv-debug-x86_64.bat"
            set foundenvvar=1
        )
    )
    if not defined foundenvvar (
        echo set %%v=>> "%~dp0/deactivate_conanrunenv-debug-x86_64.bat"
    )
)
endlocal


set "PATH=C:\Users\Ploda\.conan2\p\b\pugixce43c74568961\p\bin;C:\Users\Ploda\.conan2\p\b\gtesta940192eb4507\p\bin;%PATH%"