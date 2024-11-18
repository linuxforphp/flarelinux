@ECHO OFF
docker run -it --rm -e FLARE_BIND_ADDRESS=0.0.0.0 -p 9650:9650 --name my_flare_server asclinux/flarelinux:1.1.5-1.9.0-0.7.0 flare --flare-coston2
ECHO Flare server successfully exited
pause