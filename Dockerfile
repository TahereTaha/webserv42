FROM ubuntu:22.04

RUN apt-get update && \
    apt-get install -y build-essential entr && \
    apt-get clean

WORKDIR /app
COPY . .

