#!/usr/bin/env bash
echo "Exiting the server, please wait..."
STD_OUTPUT=$( docker rm -f my_flare_server 2>&1 )
if [[ "$STD_OUTPUT" =~ "Error" ]]; then
  EXIT_CODE=1
else
  EXIT_CODE=0
fi
exit $EXIT_CODE