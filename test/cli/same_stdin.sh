#!/bin/sh

set -o errexit
set -o nounset

if [ $# -lt 3 ]
then
  echo "Usage: $0 <program> <expected-file> <input-file> [args...]" 1>&2
  exit 1
fi

PROGRAM="$1"
EXPECTED_FILE="$2"
INPUT_FILE="$3"
shift 3

RANDOM_STRING="$(LC_ALL=C tr -dc 'A-Za-z0-9' < /dev/urandom | head -c 13)"
OUTPUT="test-same-stdin-$RANDOM_STRING.stdout"
echo "Running: $PROGRAM $* < $INPUT_FILE > $OUTPUT" 1>&2
"$PROGRAM" "$@" < "$INPUT_FILE" > "$OUTPUT"
cmp --verbose "$OUTPUT" "$EXPECTED_FILE"
rm "$OUTPUT"
