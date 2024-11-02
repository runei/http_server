# Use the official Ubuntu image as the base image
FROM ubuntu:latest

RUN apt-get update
RUN apt-get update && apt-get install -y \
    build-essential \
    clang-format \
    cmake \
    cmake-format \
    cpputest \
    cppcheck \
    clang-tidy \
    valgrind \
    lcov \
    git

# Set git global variables
RUN git config --global user.email "lminvernizzi@gmail.com"
RUN git config --global user.name "Leonardo Invernizzi"

# Set the working directory inside the container
WORKDIR /http_server

# Copy the .bashrc file to the home directory of the root user
COPY _bashrc /root/.bashrc

# Declare the mount point as a volume
VOLUME ["/http_server"]
