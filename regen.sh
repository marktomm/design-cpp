#!/bin/bash

set -e

./regen_all_designs.sh 
rm -r builddir/
meson setup builddir
./_build.sh 