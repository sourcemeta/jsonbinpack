#!/bin/sh

set -o errexit
set -o nounset

if [ $# -lt 4 ]
then
  echo "Usage: $0 <stdin> <program> <exit code> <expected string> [args...]" 1>&2
  exit 1
fi

STDIN="$1"
shift 1

CDPATH='' cd -- "$(dirname -- "$0")"
SCRIPT_DIRECTORY="$(pwd -P)"
cd - > /dev/null

echo "Stubbing stdin using $STDIN" 1>&2
exec "$SCRIPT_DIRECTORY/runner.sh" "$@" < "$STDIN"
