# Configures the development container for the project
# syntax=docker/dockerfile:1

# Start from a given base image with CPU architecture 'amd64'
ARG ARCHITECTURE=linux/amd64
ARG BASE_IMG=ubuntu:latest
FROM --platform=${ARCHITECTURE} ${BASE_IMG}

# Ensure that the system is up to date, and the prerequisites are installed
# RUN apt update && \
#     apt install -y \
#         lsb-release \
#         ca-certificates \
#         sudo \
#         gnupg \
#         software-properties-common \
#         curl \
#         wget \
#         apt-transport-https \
#         zip \
#         unzip \
#         tzdata \
#         build-essential \
#         debconf-utils \
#         gdb \
#         ninja-build \
#         git \
#         manpages-dev \
#         python3-pip \
#         python-is-python3 \
#         pylint \
#         python3-autopep8 \  
#         gcovr && \
#     apt-get purge --yes --auto-remove cmake

# Create a non-root user to use if preferred - see https://aka.ms/vscode-remote/containers/non-root-user
ARG TARGET_USER
RUN useradd -s /bin/bash -m ${TARGET_USER} \
    && echo ${TARGET_USER} ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/${TARGET_USER} \
    && chmod 0440 /etc/sudoers.d/${TARGET_USER}

# Switch to the non-root user    
USER ${TARGET_USER}

# Set the default locale to UTF-8
ENV LANG=C.UTF-8
ENV LANGUAGE=C.UTF-8
ENV LC_ALL=C.UTF-8

# Set the timezone to Europe/Berlin
ENV TZ=Europe/Berlin

# Set Docker to use BuildKit
ENV DOCKER_HIDE_LEGACY_COMMANDS=ON
ENV DOCKER_BUILDKIT=1
ENV COMPOSE_DOCKER_CLI_BUILD=1

# Install Conan C++ package manager and CMake
# RUN pip install --break-system-packages --upgrade pip
# RUN pip install --break-system-packages conan cmake coloredlogs cmake_format
# RUN $HOME/.local/bin/conan profile detect

# Set the default shell to bash rather than sh
ENV SHELL=/bin/bash

# Switch back to dialog for any ad-hoc use of apt-get
ENV DEBIAN_FRONTEND=dialog