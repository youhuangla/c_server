#!/bin/bash
git config --global --unset http.proxy 
git config --global --unset https.proxy
if [[ $# -ne 1 ]];then
    echo "Usage: $0 msg"
    exit
fi
git add .
git commit -m $1
git push origin main