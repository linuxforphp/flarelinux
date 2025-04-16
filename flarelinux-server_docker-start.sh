#!/usr/bin/env sh
docker run -it --rm -e FLARE_BIND_ADDRESS=0.0.0.0 -p 9650:9650 --name my_flare_server asclinux/flarelinux:1.1.6-1.10.0 flare --flare-coston2
echo "\nFlare server successfully exited\n"
exit 0