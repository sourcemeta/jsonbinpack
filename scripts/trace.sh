#!/bin/sh

set -o errexit
set -o nounset

COMMANDS="$(jq --raw-output '.tests[0].command | join(" ")')"

CDPATH='' cd -- "$(dirname -- "$0")"
SCRIPT_DIRECTORY="$(pwd -P)"
PROJECT_DIRECTORY="$(dirname "$SCRIPT_DIRECTORY")"
cd "$PROJECT_DIRECTORY"

OUTPUT="$PROJECT_DIRECTORY/build/tracing/$1.trace"
rm -rf "$OUTPUT"
mkdir -p "$(dirname "$OUTPUT")"
# shellcheck disable=SC2086
xcrun xctrace record --template Logging --output "$OUTPUT" \
  --target-stdin - --target-stdout - --launch -- $COMMANDS
open "$OUTPUT"
