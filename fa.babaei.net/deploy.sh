#!/bin/sh
hexo generate && rsync -avze 'ssh -p 1317' --perms --chmod=a+rwx,g+rwx,o-wx --delete public/ wrs@199.48.133.134:~/babaei.net/wfa
