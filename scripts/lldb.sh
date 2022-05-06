#!/bin/sh

set -o errexit
set -o nounset

if [ $# -lt 2 ]
then
  echo "Usage: $0 <preset> <test-name>" 1>&2
  exit 1
fi

COMMANDS_JSON="$(ctest --preset "$1" --tests-regex "$2" --show-only=json-v1 \
  | jq '.tests[0].command')"
COMMAND="$(echo "$COMMANDS_JSON" | jq --raw-output '.[0]')"
OPTIONS="$(echo "$COMMANDS_JSON" | jq --raw-output '.[1:] | join ("\n")')"

# shellcheck disable=SC2086
exec lldb "$COMMAND" -- $OPTIONS
