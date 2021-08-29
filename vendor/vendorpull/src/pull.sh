#!/bin/sh

set -o errexit
PATTERN="$1"
set -o nounset

%include "assert.sh"
%include "vcs/git.sh"
%include "masker.sh"
%include "patcher.sh"
%include "tmpdir.sh"
%include "dependencies.sh"

# @params [string] Base directory
# @params [string] Dependency definition
vendorpull_command_pull() {
  NAME="$(vendorpull_dependencies_name "$2")"
  REPOSITORY="$(vendorpull_dependencies_repository "$2")"
  REVISION="$(vendorpull_dependencies_revision "$2")"

  echo "Updating $NAME..."

  GIT_REPOSITORY_DIRECTORY="$TEMPORARY_DIRECTORY/$NAME"
  vendorpull_clone_git "$REPOSITORY" "$GIT_REPOSITORY_DIRECTORY" "$REVISION"
  vendorpull_patch "$GIT_REPOSITORY_DIRECTORY" "$1/patches/$NAME"
  vendorpull_clean_git "$GIT_REPOSITORY_DIRECTORY"
  vendorpull_mask_directory "$GIT_REPOSITORY_DIRECTORY" "$1/vendor/$NAME.mask"

  # Atomically move the new dependency into the vendor directory
  OUTPUT_DIRECTORY="$1/vendor/$NAME"
  rm -rf "$OUTPUT_DIRECTORY"
  mkdir -p "$(dirname "$OUTPUT_DIRECTORY")"
  mv "$TEMPORARY_DIRECTORY/$NAME" "$OUTPUT_DIRECTORY"
}

vendorpull_assert_command 'git'

# Get the root directory of the current git repository
BASE_DIRECTORY="$(git rev-parse --show-toplevel)"
DEPENDENCIES_FILE="$BASE_DIRECTORY/DEPENDENCIES"
vendorpull_assert_file "$DEPENDENCIES_FILE"

if [ -n "$PATTERN" ]
then
  DEFINITION="$(vendorpull_dependencies_safe_find "$DEPENDENCIES_FILE" "$PATTERN")"
  vendorpull_command_pull "$BASE_DIRECTORY" "$DEFINITION"
else
  echo "Reading DEPENDENCIES files..."
  while read -r dependency
  do
    vendorpull_command_pull "$BASE_DIRECTORY" "$dependency"
  done < "$DEPENDENCIES_FILE"
fi
