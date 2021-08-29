# Clone a git repository
# @params [string] Git URL
# @params [string] Clone location
# @params [string] Revision
vendorpull_clone_git() {
  git clone --recurse-submodules --jobs 8 "$1" "$2"
  if [ "$3" != "HEAD" ]
  then
    git -C "$2" reset --hard "$3"
  fi
}

# Un-git the repository and its dependencies (if any)
# @params [string] Repository directory
vendorpull_clean_git() {
  GIT_FILES=".git .gitignore .github .gitmodules"
  git -C "$1" submodule foreach "rm -rf $GIT_FILES"
  for file in $GIT_FILES
  do
    rm -rf "$1/${file:?}"
  done
}

# @params [string] Repository directory
# @params [string] Patch file
vendorpull_patch_git() {
  git -C "$1" apply --3way "$2"
}
