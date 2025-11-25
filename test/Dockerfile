FROM alpine:latest

RUN apk update && \
    apk add --no-cache \
    build-base \
    valgrind \
    check-dev \
    git \
    make \
    gcovr \
    clang \
    cppcheck \
    clang18-extra-tools \
    python3 && \
    ln -s /usr/lib/llvm18/bin/clang-format /usr/bin/clang-format

WORKDIR /app

COPY . .

WORKDIR /app