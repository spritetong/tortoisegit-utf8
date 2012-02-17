@echo off
setlocal

set TGIT_HOME=%~dp0..\..

if "%~1" == "" (
	call :move_msi x86
	call :move_msi x64
) else (
	call :move_msi %~1
)
goto :EOF

:move_msi
for /f %%i in ('date /t') do set BUILD_DATE=%%i
set BUILD_DATE=%BUILD_DATE:/=%
set BUILD_DATE=%BUILD_DATE:-=%
for /f "tokens=2,3*" %%i in (%TGIT_HOME%\src\version.h) do (
	if "%%i" == "FILEVER" set BUILD_VER=%%j
)
set BUILD_VER=%BUILD_VER:,=.%
move /y "%TGIT_HOME%\bin\setup\%1\TortoiseGit.msi" "%TGIT_HOME%\..\TortoiseGit-utf8-%BUILD_VER%-%1-%BUILD_DATE%.msi" >nul
goto :EOF
