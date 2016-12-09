@echo off

cd %~dp0

set LANG=en_US.UTF-8
set MM_CHARSET=UTF-8
set LC_ALL=en_US.UTF-8

set GOROOT=E:\OPT\Go\

set PATH=E:\OPT\Python27\Scripts;%PATH%
set PATH=E:\OPT\Python27;%PATH%
set PATH=E:\OPT\Go\bin;%PATH%
set PATH=E:\OPT\cwRsync;%PATH%
set PATH=E:\OPT\Git\bin;%PATH%
set PATH=E:\OPT\Hugo;%PATH%

echo.
echo %LANG%
echo %MM_CHARSET%
echo %LC_ALL%
echo.
echo %PATH%
echo.

%comspec% /k