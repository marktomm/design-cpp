#!/bin/bash

set -e

# other_script_output=$(./design_list.sh)

while IFS= read -r line; do
    ./new_design.sh ${line} regen_meson
done <<< "$(./design_list.sh)"