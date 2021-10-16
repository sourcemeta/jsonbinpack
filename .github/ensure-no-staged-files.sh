#!/bin/sh

set -o errexit
set -o nounset

STATUS="$(git status -s)"

if [ -n "$STATUS" ]
then
  echo "These unstaged changes shall not exist:" 1>&2
  echo "$STATUS" 1>&2
  git diff
  exit 1
fi
