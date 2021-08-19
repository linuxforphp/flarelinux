@echo off
setlocal EnableDelayedExpansion
setlocal EnableExtensions

if "%1" == "" ( set flaremode="--coston" ) else ( set flaremode="%1" )

rem Get unique file name 
:uniqLoop
set "uniqueFileName=%tmp%\bat~%RANDOM%.tmp"
if exist "%uniqueFileName%" goto :uniqLoop

rem THE NEXT LINE IS TO BE REMOVED IN THE FINAL VERSION OF THIS SCRIPT
set processstatus=412

rem start "dockerflarelinuxstartscript" /B docker run -dit --rm -p 9650:9650 --name my_flare_server asclinux/flarelinux:1.0.0-rc1 flare %flaremode% > "%uniqueFileName%"

rem for /F "tokens=2" %%K in ('
rem    tasklist /FI "ImageName eq dockerflarelinuxstartscript" /FI "Status eq Running" /FO LIST ^| findstr /B "PID:"
rem ') do (
rem    set processstatus=%%K
rem )

echo Docker process started as PID #%processstatus%...

set /A checkcount=0
set /A checkcountincrement=1

:loop

if %checkcount% equ 0 (
   set /A checkcount+=20
   
   echo !checkcount!
)

set /A checkcountincrementtemp5=%checkcountincrement% %% 5

if %checkcountincrementtemp5% equ 0 echo .

set /A checkcountincrementtemp30=%checkcountincrement% %% 30

if %checkcountincrementtemp30% equ 0 ( 
   if %checkcount% neq 100 (
      set /a checkcount+=20
      echo %checkcount%
   )
)

set /A timeoutcounter=0

:timeoutloop
if %timeoutcounter% leq 60 (
   set /A timeoutcounter+=1
   goto timeoutloop
)

rem for /F "tokens=* USEBACKQ" %%F in (`docker inspect -f "{{.State.Running}}" my_flare_server`) do (
rem    set dockercontainerstatus=%%F
rem )

rem for /F "tokens=2" %%K in ('
rem    tasklist /FI "ImageName eq dockerflarelinuxstartscript" /FI "Status eq Running" /FO LIST ^| findstr /B "PID:"
rem ') do (
rem    set processstatus=%%K
rem )

rem if %dockercontainerstatus% equ "false" ( if "%processstatus%" neq "dockerflarelinuxstartscript" goto error )

set /A checkcountincrement+=1

rem The next line will be replaced with a check to see if the Docker container has been started of not (docker inspect command)
if %checkcountincrement% equ 60 goto done

goto loop

:error
exit 1

:done
