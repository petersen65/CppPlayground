# Configures the development container for the project
# syntax=docker/dockerfile:1

# Start from a given base image with CPU architecture 'arm64'
ARG ARCHITECTURE=linux/arm64
ARG BASE_IMG=ubuntu:latest
FROM --platform=${ARCHITECTURE} ${BASE_IMG}

# Ensure that the system is up to date, and the prerequisites are installed
RUN apt-get update && \
    apt-get install -y \
        sudo \
        wget \
        curl \
        lsb-release \
        software-properties-common \
        build-essential \
        git \
        gdb \
        python3-pip \
        python-is-python3

# Install a specific version of LLVM and Clang
ARG LLVM_VERSION
RUN wget https://apt.llvm.org/llvm.sh && \
    chmod +x llvm.sh && \
    ./llvm.sh "${LLVM_VERSION}" all && \
    rm llvm.sh

# Install the latest version of 1Password CLI
RUN curl -sS https://downloads.1password.com/linux/keys/1password.asc | \
    gpg --dearmor --output /usr/share/keyrings/1password-archive-keyring.gpg && \
    echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/1password-archive-keyring.gpg] https://downloads.1password.com/linux/debian/$(dpkg --print-architecture) stable main" | \
    tee /etc/apt/sources.list.d/1password.list && \
    mkdir -p /etc/debsig/policies/AC2D62742012EA22/ && \
    curl -sS https://downloads.1password.com/linux/debian/debsig/1password.pol | \
    tee /etc/debsig/policies/AC2D62742012EA22/1password.pol && \
    mkdir -p /usr/share/debsig/keyrings/AC2D62742012EA22 && \
    curl -sS https://downloads.1password.com/linux/keys/1password.asc | \
    gpg --dearmor --output /usr/share/debsig/keyrings/AC2D62742012EA22/debsig.gpg && \
    apt update && sudo apt install 1password-cli

# Create a non-root user to use if preferred - see https://aka.ms/vscode-remote/containers/non-root-user
ARG TARGET_USER
RUN useradd -s /bin/bash -m "${TARGET_USER}" && \
    echo "${TARGET_USER} ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers.d/"${TARGET_USER}" && \
    chmod 0440 /etc/sudoers.d/"${TARGET_USER}"

# Switch to the non-root user    
ARG TARGET_USER
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

# Set the default shell to bash rather than sh
ENV SHELL=/bin/bash

# Switch back to dialog for any ad-hoc use of apt-get
ENV DEBIAN_FRONTEND=dialog

# Install Conan C++ package manager and CMake
RUN mkdir --parents $HOME/.local/bin $HOME/source/repos && \
    pip install --break-system-packages --upgrade pip && \
    pip install --break-system-packages conan cmake coloredlogs cmake_format && \
    $HOME/.local/bin/conan profile detect
