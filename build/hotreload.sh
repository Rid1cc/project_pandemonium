#!/bin/bash

while true; do
    fswatch -1 ../Game/ # -1 oznacza pojedyncze wyzwolenie
    make
done