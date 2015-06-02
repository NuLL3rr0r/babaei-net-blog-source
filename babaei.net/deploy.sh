#!/bin/sh
rm -rf public/*
hexo generate && rsync -avze 'ssh -p 1317' --perms --chmod=u+rwx,g+rx,o+rx,g-w,o-wx --delete public/ wrs@199.48.133.134:~/babaei.net/wen
