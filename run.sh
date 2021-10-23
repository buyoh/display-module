#!/bin/bash

cd `dirname $0`

python3 -m http.server 8000 --bind 127.0.0.1 --directory ./web &
PID_WEB=$!
trap "kill $PID_WEB" 2 9 15
bundle exec ruby screen.rb | src/out/epdisplay
kill $PID_WEB
