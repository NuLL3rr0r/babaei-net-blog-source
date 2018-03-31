#!/bin/sh
cd ./fa.babaei.net/ \
    && rm -rf public \
    && hugo build \
    && rsync -avze 'ssh -p 1317' --perms --chmod=u+rwx,g+rx,o+rx,g-w,o-wx --delete public/ wrs@199.48.133.134:~/babaei.net/wfa
