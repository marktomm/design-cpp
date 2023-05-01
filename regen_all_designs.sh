#!/bin/bash

set -e

# other_script_output=$(./designs_list.sh)

while IFS= read -r line; do
    ./new_design.sh ${line} regen_meson
done <<< "$(./designs_list.sh)"