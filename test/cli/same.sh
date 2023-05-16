#!/bin/sh

set -o errexit
set -o nounset

if [ $# -lt 2 ]
then
  echo "Usage: $0 <program> <expected-file> [args...]" 1>&2
  exit 1
fi

PROGRAM="$1"
EXPECTED_FILE="$2"
shift 2

RANDOM_STRING="$(LC_ALL=C tr -dc 'A-Za-z0-9' < /dev/urandom | head -c 13)"
OUTPUT="test-same-$RANDOM_STRING.stdout"
echo "Running: $PROGRAM $* > $OUTPUT" 1>&2
"$PROGRAM" "$@" > "$OUTPUT"
cmp --verbose "$OUTPUT" "$EXPECTED_FILE"
rm "$OUTPUT"
