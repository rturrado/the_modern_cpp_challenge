FROM ubuntu:22.04

RUN apt-get -qq update \
    && apt-get -qq upgrade \
    && apt-get -qq -y install netbase \
    && apt-get -qq -y install --reinstall ca-certificates

WORKDIR /tmcppc

COPY ./Dockerfile .
COPY ./out/build/unixlike-gcc-release-docker/benchmark/Release/the_modern_c++_challenge_benchmark .
COPY ./out/build/unixlike-gcc-release-docker/src/Release/the_modern_c++_challenge .
COPY ./out/build/unixlike-gcc-release-docker/test/Release/the_modern_c++_challenge_test .
COPY ./out/build/unixlike-gcc-release-docker/_deps/freeimage-build/Release/libFreeImage.so .
ADD ./res /tmcppc/res
