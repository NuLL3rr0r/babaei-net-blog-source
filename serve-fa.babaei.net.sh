#!/bin/sh
cd ./fa.babaei.net/ \
    && GIT_COMMIT_SHA=`git rev-parse --verify HEAD` GIT_COMMIT_SHA_SHORT=`git rev-parse --short HEAD` \
    hugo server --bind 0.0.0.0 --port 1002 --buildDrafts
