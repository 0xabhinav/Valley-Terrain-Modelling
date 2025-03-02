FROM emscripten/emsdk:latest

# Install git and other useful tools
RUN apt-get update && apt-get install -y \
    git \
    wget \
    unzip \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Set GLM version
ENV GLM_VERSION=0.9.9.8

# Download and install GLM (OpenGL Mathematics)
RUN wget https://github.com/g-truc/glm/archive/${GLM_VERSION}.zip \
    && unzip ${GLM_VERSION}.zip \
    && cp -r glm-${GLM_VERSION}/glm /usr/local/include/ \
    && rm -rf ${GLM_VERSION}.zip glm-${GLM_VERSION}

# Set GLM include path environment variable
ENV GLM_INCLUDE_PATH=/usr/local/include

# Set the default command
CMD ["/app/build-wasm.sh"]
