@echo off

title BABAEI.NET HEXO CLI

cd %~dp0

set LANG=en_US.UTF-8
set MM_CHARSET=UTF-8
set LC_ALL=en_US.UTF-8
chcp 65001

set PATH=%~dp0..\_tools\cwRsync;%~dp0..\_tools\Git\bin;%PATH%

echo %PATH% & echo. & echo %LANG% & echo %MM_CHARSET% & echo %LC_ALL% & echo.

%comspec% /k 

