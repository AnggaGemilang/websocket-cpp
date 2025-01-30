# Use base image (Ubuntu 22.04) as BUILD STAGE
FROM ubuntu:22.04 as build

RUN apt-get update -y && \
    apt-get upgrade -y && \
    apt-get install -y \
    ca-certificates \
    wget \
    tar \
    curl \
    zip \
    libssl-dev \
    libuv1-dev \
    zlib1g-dev \    
    pkg-config \
    autoconf \
    python3 \
    flex \
    bison \
    git \
    build-essential \
    ninja-build \
    g++ \
    gcc \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Install CMAKE
RUN wget https://github.com/Kitware/CMake/releases/download/v3.31.3/cmake-3.31.3.tar.gz && \
    tar -xvf cmake-3.31.3.tar.gz && cd cmake-3.31.3 && ./configure && make && make install

# Install vcpkg package manager
WORKDIR /home
RUN git clone https://github.com/microsoft/vcpkg && \
    cd vcpkg && git checkout f7423ee180c4b7f40d43402c2feb3859161ef625 && \
    cd .. && vcpkg/bootstrap-vcpkg.sh

# Install vcpkg packages
RUN ./vcpkg/vcpkg install boost-asio && \
    ./vcpkg/vcpkg install boost-thread && \
    ./vcpkg/vcpkg install uwebsockets && \
    ./vcpkg/vcpkg install gtest

# Copy files from local directory to container
COPY ./src /home/project/src
COPY ./docker/CMakeLists.txt /home/project/CMakeLists.txt

# Build project
RUN cmake --no-warn-unused-cli \
    -DCMAKE_BUILD_TYPE:STRING=Release \
    -DCMAKE_TOOLCHAIN_FILE:STRING=/home/vcpkg/scripts/buildsystems/vcpkg.cmake \
    -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE \
    -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc \
    -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++ \
    "-S/home/project" "-B/home/project/build" -G "Unix Makefiles" \
    && cmake --build "/home/project/build" --config Release --target all -j 18 --

# Start a new stage, this stage will run programs from the build stage
FROM ubuntu:22.04

# Define working directory from container
WORKDIR /home/project/build

# Copy files from the build stage
COPY --from=build /home/project/build /home/project/build

# Set exposed ports
EXPOSE 8000
EXPOSE 8001
EXPOSE 8002
EXPOSE 8003
EXPOSE 8004
EXPOSE 8005
EXPOSE 8006
EXPOSE 8007
EXPOSE 8008
EXPOSE 8009
EXPOSE 8010
EXPOSE 8011
EXPOSE 8012
EXPOSE 8013
EXPOSE 8014
EXPOSE 8015
EXPOSE 8016
EXPOSE 8017
EXPOSE 8018
EXPOSE 8019
EXPOSE 8020
EXPOSE 8021
EXPOSE 8022
EXPOSE 8023
EXPOSE 8024
EXPOSE 8025
EXPOSE 8026
EXPOSE 8027
EXPOSE 8028
EXPOSE 8029
EXPOSE 8030
EXPOSE 8031
EXPOSE 8032
EXPOSE 8033
EXPOSE 8034
EXPOSE 8035
EXPOSE 8036
EXPOSE 8037
EXPOSE 8038
EXPOSE 8039
EXPOSE 8040
EXPOSE 8041
EXPOSE 8042
EXPOSE 8043
EXPOSE 8044
EXPOSE 8045
EXPOSE 8046
EXPOSE 8047
EXPOSE 8048
EXPOSE 8049
EXPOSE 8050
EXPOSE 8051
EXPOSE 8052
EXPOSE 8053
EXPOSE 8054
EXPOSE 8055
EXPOSE 8056
EXPOSE 8057
EXPOSE 8058
EXPOSE 8059
EXPOSE 8060
EXPOSE 8061
EXPOSE 8062
EXPOSE 8063
EXPOSE 8064
EXPOSE 8065
EXPOSE 8066
EXPOSE 8067
EXPOSE 8068
EXPOSE 8069
EXPOSE 8070
EXPOSE 8071
EXPOSE 8072
EXPOSE 8073
EXPOSE 8074
EXPOSE 8075
EXPOSE 8076
EXPOSE 8077
EXPOSE 8078
EXPOSE 8079
EXPOSE 8080
EXPOSE 8081
EXPOSE 8082
EXPOSE 8083
EXPOSE 8084
EXPOSE 8085
EXPOSE 8086
EXPOSE 8087
EXPOSE 8088
EXPOSE 8089
EXPOSE 8090
EXPOSE 8091
EXPOSE 8092
EXPOSE 8093
EXPOSE 8094
EXPOSE 8095
EXPOSE 8096
EXPOSE 8097
EXPOSE 8098
EXPOSE 8099

# Run the app
CMD ["./1-1-ws"]
