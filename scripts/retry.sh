#!/bin/sh

set -o errexit
set -o nounset

if [ $# -lt 1 ]
then
  echo "Usage: $0 <command...>" 1>&2
  exit 1
fi

RETRIES=5
EXIT_CODE=1
while [ "$RETRIES" -gt 0 ] && [ "$EXIT_CODE" != "0" ]
do
  echo "(pending retries: $RETRIES)" 1>&2
  "$@" && EXIT_CODE="$?" || EXIT_CODE="$?"
  RETRIES="$((RETRIES-1))"
done
if [ "$EXIT_CODE" != "0" ]
then
  exit "$EXIT_CODE"
fi
