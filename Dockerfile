FROM ubuntu:22.04

RUN apt-get update
RUN apt-get -y install gcc-11 g++-11
RUN apt-get -y install cmake gdb clang-format
