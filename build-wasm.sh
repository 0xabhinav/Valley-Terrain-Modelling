#!/bin/sh

# Make output directory if it doesn't exist
mkdir -p output

DEBUG=true
DEBUG_FLAGS="-gsource-map -O0"
RELEASE_FLAGS="-O2"

FLAGS=$([ "$DEBUG" = true ] && echo "$DEBUG_FLAGS" || echo "$RELEASE_FLAGS")

emcc -std=c++11 main.cpp \
  -o output/valley_terrain.html \
  -s USE_GLFW=3 \
  -s WASM=1 \
  -s USE_WEBGL2=1 \
  -s FULL_ES3=1 \
  -s ALLOW_MEMORY_GROWTH=1 \
  -s USE_LIBPNG=1 \
  -s USE_FREETYPE=1 \
  -s MAX_WEBGL_VERSION=2 \
  -s MIN_WEBGL_VERSION=2 \
  -s NO_EXIT_RUNTIME=1 \
  -s ASSERTIONS=1 \
  -sNO_DISABLE_EXCEPTION_CATCHING \
  -I. \
  -I$GLM_INCLUDE_PATH \
  -lglut \
  --preload-file assets \
  -o output/valley_terrain.html \
  $FLAGS && echo "Build complete. Output files: valley_terrain.html, valley_terrain.js, valley_terrain.wasm" || echo "Build failed"
