FROM ubuntu:22.04

RUN apt-get -qq update \
    && apt-get -qq upgrade \
    && apt-get -qq -y install netbase \
    && apt-get -qq -y install --reinstall ca-certificates

WORKDIR /tmcppc

COPY /tmcppc/the_modern_c++_challenge_benchmark .
COPY /tmcppc/out/build/unixlike-gcc-debug-github/_deps/freeimage-build/Debug/libFreeImage.so .
COPY /tmcppc/out/build/unixlike-gcc-debug-github/src/Debug/the_modern_c++_challenge .
COPY /tmcppc/out/build/unixlike-gcc-debug-github/test/Debug/the_modern_c++_challenge_test .
COPY /tmcppc/Dockerfile .
