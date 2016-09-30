@echo off

cd %~dp0

set LANG=en_US.UTF-8
set MM_CHARSET=UTF-8
set LC_ALL=en_US.UTF-8
chcp 65001

set PATH=%~dp0..\_deps\cwRsync;%~dp0..\_deps\Git\bin;%~dp0..\_deps\nodejs;%PATH%

echo %PATH% & echo. & echo %LANG% & echo %MM_CHARSET% & echo %LC_ALL% & echo.

echo Removing public dir...
rmdir /S /Q public

echo.

echo Starting Hexo generation process...
hexo generate && rsync -avze 'ssh -p 1317' --perms --chmod=u+rwx,g+rx,o+rx,g-w,o-wx --delete public/ wrs@199.48.133.134:~/babaei.net/wfa

pause

