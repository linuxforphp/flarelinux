#!/usr/bin/env bash
if [[ -z "$1" ]]; then
    FLARE_MODE="--coston"
else
    FLARE_MODE="$1"
fi

$( docker run -dit --rm -p 9650:9650 --name my_flare_server asclinux/flarelinux:1.0.0-rc1 flare "$FLARE_MODE" > /dev/null 2>&1 & )
PID_NUMBER=$( ps aux | grep 9650:9650 | awk '{print $2}' | head -n 1 )
echo "Docker process started as PID #$PID_NUMBER..."
DOCKER_CONTAINER_STATUS=$( docker inspect -f "{{.State.Running}}" my_flare_server  2> /dev/null )
CHECK_COUNT=0
CHECK_COUNT_INCREMENT=1
EXIT_CODE=0
while [[ ! $DOCKER_CONTAINER_STATUS ]]; do
     if [[ $CHECK_COUNT == 0 ]]; then
       CHECK_COUNT=$(( CHECK_COUNT + 20 ))

       echo -e $CHECK_COUNT
     fi

     if ! (( CHECK_COUNT_INCREMENT % 5 )); then
       echo -e .
     fi

     if ! (( CHECK_COUNT_INCREMENT % 30 )); then
       if [[ $CHECK_COUNT != 100 ]]; then
         CHECK_COUNT=$(( CHECK_COUNT + 20 ));

         echo -e $CHECK_COUNT
       fi
     fi

     sleep 1

     DOCKER_CONTAINER_STATUS=$( docker inspect -f "{{.State.Running}}" my_flare_server 2> /dev/null )

     PROCESS_STATUS=$( ps -p "$PID_NUMBER" > /dev/null 2>&1 && echo $? )

     if [[ ! $DOCKER_CONTAINER_STATUS && -z "$PROCESS_STATUS" ]]; then
       EXIT_CODE=1
       break
     fi

     CHECK_COUNT_INCREMENT=$(( CHECK_COUNT_INCREMENT + 1 ))
done

exit $EXIT_CODE
