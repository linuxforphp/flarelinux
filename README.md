# [![Flare Linux Banner](tools/logo.png)](https://flarelinux.xyz/)
# Flare Linux Docker Images

The official Flare Linux repository.

https://flarelinux.xyz

Flare Linux is a lightweight version of Linux to run Flare Networks server nodes.

## Build the Flare Linux image

You must have `docker` and `docker-compose` installed on your computer.

To build the main Docker image, please run the main `build.sh` script.

```
git clone https://github.com/linuxforphp/flarelinux.git
cd flarelinux
./build
```

## Run the Flare Linux image

You will then be able to start testing the new image. To start a container, run the following command:

```
docker run -it --rm -p 9650:9650 -p 9651:9651 --name my_flare_server localhost:5000/flarelinux:1.0.0 flare
```

You can stop the container by typing the `Ctrl+C` keys on your keyboard, or by stopping and removing the Docker container with the `docker stop my_flare_server` and `docker rm my_flare_server` commands.

If you have `Linux for Composer` (https://github.com/linuxforphp/linuxforcomposer) on your computer, you can start the container with the following command:

```
linuxforcomposer docker:run start
```

To stop the container, simply enter the following command:

```
linuxforcomposer docker:run stop-force
```

Have a lot of fun! :)
