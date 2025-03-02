# Valley-Terrain-Modelling
An opengl minor project for Computer Graphics Course (CS 352)


## WASM Build and Run

### Using Nix

```bash
nix-shell
./build-wasm.sh
./nixserve.sh
```

### Using Docker (build) + run via python server

```bash
# Build using docker
docker build -t valley-terrain-modelling-wasm wasm.Dockerfile
docker run -v $(pwd):/app valley-terrain-modelling-wasm
# Run locally
python3 -m http.server 8000

```
