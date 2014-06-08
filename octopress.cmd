@echo off

cd %~dp0

set LANG=en_US.UTF-8
set MM_CHARSET=UTF-8
set LC_ALL=en_US.UTF-8
chcp 65001

set PATH=%~dp0Ruby\bin;%~dp0RubyDevKit\bin;%~dp0Python;%~dp0nginx;%~dp0cwRsync;%~dp0Git\bin;%PATH%

echo %PATH% & echo. & echo %LANG% & echo %MM_CHARSET% & echo %LC_ALL% & echo.

%comspec% /k 

