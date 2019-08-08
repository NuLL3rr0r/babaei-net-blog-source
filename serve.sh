#!/usr/bin/env sh

BASE_DIRECTORY=`$(dirname $(realpath "$0"))`

killall -9 hugo

cd "${BASE_DIRECTORY}" \
    && GIT_COMMIT_SHA=`git rev-parse --verify HEAD` \
        GIT_COMMIT_SHA_SHORT=`git rev-parse --short HEAD` \
        hugo server --bind 0.0.0.0 --port 1001 --buildDrafts
