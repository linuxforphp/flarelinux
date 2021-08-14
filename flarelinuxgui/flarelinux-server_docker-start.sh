#!/usr/bin/env sh
docker run -it --rm -p 9650:9650 --name my_flare_server asclinux/flarelinux:1.0.0-rc1 flare --coston
echo "\nFlare server successfully exited\n"
exit 0