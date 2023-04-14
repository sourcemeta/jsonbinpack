@echo off
setlocal

set "STDIN=%1"
set "PROGRAM=%2"
set "EXPECTED_EXIT_CODE=%3"
set "EXPECTED_STRING=%~4"
shift
shift
shift
shift

set "TEMP_OUTPUT=test-output-%RANDOM%-%RANDOM%.txt"
echo Stubbing stdin using %STDIN% 1>&2
"%PROGRAM%" %1 %2 < "%STDIN%" 1>"%TEMP_OUTPUT%" 2>&1
set "EXIT_CODE=%ERRORLEVEL%"

if not "%EXIT_CODE%"=="%EXPECTED_EXIT_CODE%" (
  echo ERROR: Expected exit code %EXPECTED_EXIT_CODE% but got %EXIT_CODE% 1>&2
  exit /b 1
)

>nul find "%EXPECTED_STRING%" "%TEMP_OUTPUT%" || (
  echo ERROR: Expected string not found in command output: %EXPECTED_STRING% 1>&2
  type "%TEMP_OUTPUT%" 1>&2
  exit /b 1
)
