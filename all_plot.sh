#!/bin/bash

set -e

while IFS= read -r line; do
    ./rplot.sh ${line} ${1}
done <<< "$(./design_list.sh)"
./rplot.sh ${line} benchmarks ${1}
