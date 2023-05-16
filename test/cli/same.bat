@echo off
setlocal

set "PROGRAM=%1"
set "EXPECTED_FILE=%2"
shift
shift

set "TEMP_OUTPUT=test-same-%RANDOM%-%RANDOM%.stdout"
echo Running %PROGRAM% %1 %2 %3 ^>%TEMP_OUTPUT% 1>&2
"%PROGRAM%" %1 %2 %3 >"%TEMP_OUTPUT%" || exit /b 1

fc "%TEMP_OUTPUT%" "%EXPECTED_FILE%" > nul
if errorlevel 1 (
  echo Got 1>&2
  type "%TEMP_OUTPUT%"
  del "%TEMP_OUTPUT%"
  echo Expected 1>&2
  type "%EXPECTED%"
  exit /b 1
) else (
  del "%TEMP_OUTPUT%"
)
