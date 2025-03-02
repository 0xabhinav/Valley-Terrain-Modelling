#!/bin/sh

echo "Serving files from output/ directory on port 8000"
miniserve --index index.html -p 8000 output/
