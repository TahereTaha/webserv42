FROM ubuntu:22.04

RUN apt-get update && \
    apt-get install -y build-essential entr python3 && \
    apt-get clean

WORKDIR /app
COPY . .

