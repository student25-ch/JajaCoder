#!/bin/bash
cd "$(dirname "$0")/.."
./jajacoder_core &
CORE_PID=$!
sleep 0.5
cd gui_py
python3 app.py
kill $CORE_PID
