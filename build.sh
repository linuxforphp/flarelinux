#!/usr/bin/env sh
cd flarelinux-image &&
docker build . -t localhost:5000/flarelinux:1.1.6-1.10.0-testnet