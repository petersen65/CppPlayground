# Configures the development container for the project
# syntax=docker/dockerfile:1

# Start from a given base image with CPU architecture 'amd64'
ARG ARCHITECTURE=linux/amd64
ARG BASE_IMG=centos:centos7
FROM --platform=${ARCHITECTURE} ${BASE_IMG}

# Switch to the CentOS Vault Repository because the CentOS 7 repositories are no longer available
RUN sed -i "s|^mirrorlist=|#mirrorlist=|g" /etc/yum.repos.d/CentOS-*.repo && \
    sed -i "s|^#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g" /etc/yum.repos.d/CentOS-*.repo

# Ensure that the system is up to date, and the prerequisites are installed
RUN yum update --assumeyes && \
    yum install --assumeyes \
        sudo \
        ncurses \
        ca-certificates \
        gnupg2 \
        wget \
        zip \
        unzip \
        tzdata \
        make \
        automake \
        gcc \
        gcc-c++ \
        gdb \
        ninja-build \
        git \
        cmake

# Create a non-root user to use if preferred - see https://aka.ms/vscode-remote/containers/non-root-user
ARG TARGET_USER
RUN useradd -s /bin/bash -m ${TARGET_USER} && \
    echo "${TARGET_USER} ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers.d/${TARGET_USER} && \
    chmod 0440 /etc/sudoers.d/${TARGET_USER}

# Switch to the non-root user    
USER ${TARGET_USER}

# Set the timezone to Europe/Berlin
ENV TZ=Europe/Berlin

# Set Docker to use BuildKit
ENV DOCKER_HIDE_LEGACY_COMMANDS=ON
ENV DOCKER_BUILDKIT=1
ENV COMPOSE_DOCKER_CLI_BUILD=1

# Create some directories for development
RUN mkdir --parents $HOME/.local/bin $HOME/source/repos

# Set the default shell to bash rather than sh
ENV SHELL=/bin/bash