# Use the official GCC image as the base image
FROM gcc:latest

RUN apt-get update
RUN apt-get install -y clang-format cmake cmake-format cpputest cppcheck clang-tidy valgrind

# Set git global variables
RUN git config --global user.email "lminvernizzi@gmail.com"
RUN git config --global user.name "Leonardo Invernizzi"

# Set the working directory inside the container
WORKDIR /http_server

# Copy the .bashrc file to the home directory of the root user
COPY _bashrc /root/.bashrc

# Declare the mount point as a volume
VOLUME ["/http_server"]
