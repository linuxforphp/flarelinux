@ECHO OFF
docker run -it --rm -p 9650:9650 --name my_flare_server asclinux/flarelinux:1.0.0-rc1 flare --coston
ECHO Flare server successfully exited
pause