#!/usr/bin/env sh

BASE_DIRECTORY=`$(dirname $(realpath "$0"))`

killall -9 hugo

cd "${BASE_DIRECTORY}" \
    && rm -rf public \
    && GIT_COMMIT_SHA=`git rev-parse --verify HEAD` \
        GIT_COMMIT_SHA_SHORT=`git rev-parse --short HEAD` \
        hugo \
    && rsync -avze 'ssh -p 1317' --perms --chmod=u+rwx,g+rx,o+rx,g-w,o-wx\
        --delete public/en/ wrs@199.48.133.134:~/babaei.net/wen \
    && rsync -avze 'ssh -p 1317' --perms --chmod=u+rwx,g+rx,o+rx,g-w,o-wx\
        --delete public/fa/ wrs@199.48.133.134:~/babaei.net/wfa
