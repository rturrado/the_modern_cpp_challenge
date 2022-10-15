FROM ubuntu:22.04

RUN apt-get -qq update \
    && apt-get -qq upgrade \
    && apt-get -qq -y install netbase \
    && apt-get -qq -y install --reinstall ca-certificates

WORKDIR /tmcppc

COPY /tmcppc/ .
