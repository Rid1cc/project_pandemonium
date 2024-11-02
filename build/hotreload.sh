#!/bin/bash

while true; do
    inotifywait -e modify ../Game/
    make
done