#!/bin/env bash

# directories to exclude from the find command
EXCLUDE=("build" \
         "deps"  \
         "CMake")

# exit codes
EXIT_SUCCESS=0
EXIT_NONEXISTANT=1
EXIT_NO_CLANGFMT=2

# usage help heredoc
function usage () {
    cat << HELP_USAGE
    $0 <pathname>

    DESCRIPTION
        clang-format-all - recursively invoke clang-format from a C
        project's root directory on all it's header and source files
        while excluding the configured directories

    RETURN VALUE
        0 - on success
        1 - directory doesn't exist or path isn't a directory
        2 - no '.clang_format' file found in the project root directory
            path
HELP_USAGE
}

# log to stderr
function log () { >&2 echo "LOG[$USER]:" "$@"; }

# check if there's exactly one positional argument
if [ "$#" -ne 1 ]
then
    usage
    exit $EXIT_SUCCESS
fi

# resolve relative paths
PROJROOTDIR=$(readlink -f $1)
log "configured project root directory: '$PROJROOTDIR'"

# check if the pathname refers to a directory
if [ ! -d "$PROJROOTDIR" ]
then
    log "directory: '$PROJROOTDIR' does not exist or isn't a directory"
    exit $EXIT_NONEXISTANT
fi

# search for a '.clang_format' file  only in the provided directory,
# don't descend
if [ -z "$(find "$PROJROOTDIR" -maxdepth 1 -type f -name '.clang-format')" ]
then
    log "no '.clang_format' found in: '$PROJROOTDIR'"
    exit $EXIT_NO_CLANGFMT
fi

log "found '.clang_format' in: '$PROJROOTDIR'"

# build the prune part of the find command
LEN_EXCLUDE=${#EXCLUDE[@]}
FIND_PRUNE_OPTS=""
if [ "$LEN_EXCLUDE" -eq 0 ]; then
    log "no directories to exclude"
else
    # if there is only one element in the array, 
    # disable printf entries
    FMTS=("" " -o -name %s")
    # shellcheck disable=SC2059 
    # intentional format string selection
    FIND_PRUNE_OPTS="-type d ( -name ${EXCLUDE[0]}      \
                     $(printf "${FMTS[LEN_EXCLUDE!=1]}" \
                              "${EXCLUDE[@]:1}")        \
                     ) -prune -o"
    log "excluding directories:" "${EXCLUDE[@]}"
fi

# clang format all C files with '.h' or '.c' extensions
log "recursively clang formatting all '.h' and '.c' files"
# shellcheck disable=SC2086
# intentional split on spaces due to command building
find "$PROJROOTDIR"   $FIND_PRUNE_OPTS                         \
                      -type f \( -iname \*.h -o -iname \*.c \) \
                      -exec                                    \
                       clang-format -i -Werror --verbose {} +
