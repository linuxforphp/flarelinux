@echo off
rem echo Exiting the server, please wait...

rem Get unique file name 
:uniqLoop
set "uniqueFileName=%tmp%\bat~%RANDOM%.tmp"
if exist "%uniqueFileName%" goto :uniqLoop

docker stop my_flare_server > "%uniqueFileName%"
exit %ERRORLEVEL%
