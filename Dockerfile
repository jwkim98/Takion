FROM ubuntu:18.04
LABEL maintainer "Jaewoo Kim <jwkimrhkgkr@gmail.com>"

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    --no-install-recommends \
    && rm -rf /var/lib/apt/lists/*

COPY . /app

WORKDIR /app/build
RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y git
RUN  git submodule update  --init
RUN cmake .. && \
    make  && \
    make install