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
EXPOSE 7000
EXPOSE 7001
EXPOSE 7002
EXPOSE 7003
EXPOSE 7004
EXPOSE 7005
EXPOSE 7006
EXPOSE 7007
EXPOSE 7008
EXPOSE 7009
EXPOSE 7010
EXPOSE 7011
EXPOSE 7012
EXPOSE 7013
EXPOSE 7014
EXPOSE 7015
EXPOSE 7016
EXPOSE 7017
EXPOSE 7018
EXPOSE 7019
EXPOSE 7020
EXPOSE 7021
EXPOSE 7022
EXPOSE 7023
EXPOSE 7024
EXPOSE 7025
EXPOSE 7026
EXPOSE 7027
EXPOSE 7028
EXPOSE 7029
EXPOSE 7030
EXPOSE 7031
EXPOSE 7032
EXPOSE 7033
EXPOSE 7034
EXPOSE 7035
EXPOSE 7036
EXPOSE 7037
EXPOSE 7038
EXPOSE 7039
EXPOSE 7040
EXPOSE 7041
EXPOSE 7042
EXPOSE 7043
EXPOSE 7044
EXPOSE 7045
EXPOSE 7046
EXPOSE 7047
EXPOSE 7048
EXPOSE 7049
EXPOSE 7050
EXPOSE 7051
EXPOSE 7052
EXPOSE 7053
EXPOSE 7054
EXPOSE 7055
EXPOSE 7056
EXPOSE 7057
EXPOSE 7058
EXPOSE 7059
EXPOSE 7060
EXPOSE 7061
EXPOSE 7062
EXPOSE 7063
EXPOSE 7064
EXPOSE 7065
EXPOSE 7066
EXPOSE 7067
EXPOSE 7068
EXPOSE 7069
EXPOSE 7070
EXPOSE 7071
EXPOSE 7072
EXPOSE 7073
EXPOSE 7074
EXPOSE 7075
EXPOSE 7076
EXPOSE 7077
EXPOSE 7078
EXPOSE 7079
EXPOSE 7080
EXPOSE 7081
EXPOSE 7082
EXPOSE 7083
EXPOSE 7084
EXPOSE 7085
EXPOSE 7086
EXPOSE 7087
EXPOSE 7088
EXPOSE 7089
EXPOSE 7090
EXPOSE 7091
EXPOSE 7092
EXPOSE 7093
EXPOSE 7094
EXPOSE 7095
EXPOSE 7096
EXPOSE 7097
EXPOSE 7098
EXPOSE 7099

# Run the app
CMD ["./1-1-grouping-ws"]
