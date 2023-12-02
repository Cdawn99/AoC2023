#!/usr/bin/bash

if [[ $# -eq 0 ]]; then
    echo "Usage: $0 [file(s)] -o [outfile]"
    exit 1
fi

set -xe

gcc -Wall -Werror -Wextra -pedantic -pedantic-errors -std=c17 $@

