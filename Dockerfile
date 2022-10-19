FROM ubuntu:22.04

# netbase and ca-certificates are needed to run /tmcppc/the_modern_c++_challenge* binaries
RUN apt-get -qq update \
    && apt-get -qq upgrade \
    && apt-get -qq -y install netbase \
    && apt-get -qq -y install --reinstall ca-certificates

# artifact folder lives at the root of the GitHub workspace. It has the following structure:
#
#    Dockerfile
#    out/
#    \- build/
#       |- unixlike-gcc-release-docker/
#          |- _deps/freeimage-build/Release/libFreeImage.so
#          |- benchmark/Release/the_modern_c++_challenge_benchmark
#          |- src/Release/the_modern_c++_challenge
#          \- test/Release/the_modern_c++_challenge_test
#    res/
#
# tmcppc folder lives at the root of the docker. It has the following structure:
#
#    Dockerfile
#    libFreeImage.so
#    the_modern_c++_challenge
#    the_modern_c++_challenge_benchmark
#    the_modern_c++_challenge_test
#    res/
#
WORKDIR /tmcppc

COPY ./artifact/Dockerfile .
COPY ./artifact/out/build/unixlike-gcc-release-docker/benchmark/Release/the_modern_c++_challenge_benchmark .
COPY ./artifact/out/build/unixlike-gcc-release-docker/src/Release/the_modern_c++_challenge .
COPY ./artifact/out/build/unixlike-gcc-release-docker/test/Release/the_modern_c++_challenge_test .
COPY ./artifact/out/build/unixlike-gcc-release-docker/_deps/freeimage-build/Release/libFreeImage.so .
ADD ./artifact/res /tmcppc/res
