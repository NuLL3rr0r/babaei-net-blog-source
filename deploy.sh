#!/usr/bin/env bash

source ~/.config/babaei.net

BASE_DIRECTORY=$(dirname $(realpath "$0"))

killall -9 hugo

cd "${BASE_DIRECTORY}" \
    && rm -rf public \
    && GIT_COMMIT_SHA=`git rev-parse --verify HEAD` \
        GIT_COMMIT_SHA_SHORT=`git rev-parse --short HEAD` \
        hugo \
    && rsync -avze "ssh -p ${BABAEI_NET_SSH_PORT}" --perms --chmod=u+rwx,g+rx,o+rx,g-w,o-wx\
        --delete public/en/ ${BABAEI_NET_SSH_USER}@${BABAEI_NET_SSH_HOST}:${BABAEI_NET_EN_SSH_REMOTE_DIR}