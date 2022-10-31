# [![Flare Linux Banner](data/logo.png)](https://flarelinux.xyz/)
# Flare Linux Docker Images

The Official Flare Linux Repository.

Website: https://flarelinux.xyz

Flare Linux is a lightweight version of Linux to run Flare Networks server nodes.

## Getting Started

To begin with, you will need to clone the repository and change your current directory
to the newly cloned project on your computer, like so:

```
git clone https://github.com/linuxforphp/flarelinux.git
cd flarelinux
```

## Build the Flare Linux image

In order to build the image, you must first have `docker` on your computer (https://www.docker.com/get-started).

Then, you have many options to build the Flare Linux image:

### Option 1 - Docker Compose (build the image and run a container)

If you have `docker-compose` installed on your computer, please enter the following command:

```
docker-compose up -d --build
```

To stop the container once you are done with it, please type the following command:

```
docker-compose down -v
```

### Option 2 - Linux for Composer (build the image and run a container)

If you have `composer` and `linuxforcomposer` (https://packagist.org/packages/linuxforphp/linuxforcomposer) on your computer, you can build the image, and start the container with the following command:

```
cd flarelinux-image
composer require linuxforphp/linuxforcomposer
vendor/bin/linuxforcomposer.phar docker:run start
```

To stop the container, simply enter the following command:

```
vendor/bin/linuxforcomposer.phar docker:run stop-force
```

### Option 3 - Build manually (build the image only)

To build the main Docker image without `docker-compose` or `linuxforcomposer`, please run the main `build.sh` script.

```
./build.sh
```

## Run the Flare Linux image manually (run a container only)

If you have built the Flare Linux image using one of the previous options,
you can also start testing the new image manually. To start a container only,
run the following command:

```
docker run -it --rm -e FLARE_BIND_ADDRESS=0.0.0.0 -p 9650:9650 -p 9651:9651 --name my_flare_server localhost:5000/flarelinux:1.1.2 flare
```

You can stop the container by typing the `Ctrl+C` keys on your keyboard, or by stopping the Docker container with the `docker stop my_flare_server` command.

Have a lot of fun! :)
