#!/bin/bash

set -e

./regen_all_design.sh 
rm -r builddir/
meson setup builddir
./_build.sh 