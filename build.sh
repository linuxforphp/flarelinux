#!/usr/bin/env sh
cd flarelinux-image &&
docker build . -t localhost:5000/flarelinux:1.2.0-1.11.13