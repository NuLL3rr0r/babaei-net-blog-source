@echo off

title BABAEI.NET HEXO CLI

cd %~dp0

set LANG=en_US.UTF-8
set MM_CHARSET=UTF-8
set LC_ALL=en_US.UTF-8
chcp 65001

set PATH=C:\Users\Administrator\AppData\Roaming\npm;%PATH%
set PATH=E:\OPT\nodejs;%PATH%
set PATH=E:\OPT\cwRsync\bin;%PATH%
set PATH=E:\OPT\Git\bin;%PATH%
set PATH=E:\OPT\Git\cmd;%PATH%
set PATH=E:\OPT\Git\usr\bin;%PATH%

echo %PATH% & echo. & echo %LANG% & echo %MM_CHARSET% & echo %LC_ALL% & echo.

%comspec% /k 
