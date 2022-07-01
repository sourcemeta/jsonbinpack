#!/bin/sh

set -o errexit
set -o nounset

if [ $# -lt 3 ]
then
  echo "Usage: $0 <program> <exit code> <expected string> [args...]" 1>&2
  exit 1
fi

PROGRAM="$1"
EXPECTED_EXIT_CODE="$2"
EXPECTED_STRING="$3"
shift 3

echo "Running: $PROGRAM $*" 1>&2
set +e
OUTPUT="$("$PROGRAM" "$@" 2>&1)"
EXIT_CODE="$?"
set -e

if [ "$EXIT_CODE" != "$EXPECTED_EXIT_CODE" ]
then
  echo "ERROR: Expected exit code $EXPECTED_EXIT_CODE but got $EXIT_CODE" 1>&2
  exit 1
fi

if ! echo "$OUTPUT" | grep --quiet "$EXPECTED_STRING"
then
  echo "ERROR: Expected string not found in command output: $EXPECTED_STRING" 1>&2
  echo "$OUTPUT" 1>&2
  exit 1
fi
