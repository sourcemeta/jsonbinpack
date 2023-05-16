@echo off
setlocal

set "PROGRAM=%1"
set "EXPECTED_FILE=%2"
set "INPUT_FILE=%3"
shift
shift
shift

set "TEMP_OUTPUT=test-same-stdin-%RANDOM%-%RANDOM%.stdout"
echo Running %PROGRAM% %1 %2 %3 ^< "%INPUT_FILE%" ^>%TEMP_OUTPUT% 1>&2
"%PROGRAM%" %1 %2 %3 < "%INPUT_FILE%" >"%TEMP_OUTPUT%" || exit /b 1

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
