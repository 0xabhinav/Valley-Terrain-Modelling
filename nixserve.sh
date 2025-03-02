#!/bin/sh

echo "Serving files from output/ directory on port 8000"
miniserve --index valley_terrain.html -p 8000 output/
