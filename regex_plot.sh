#!/bin/bash

set -e

trimFwdSlashes() {
  a1="${1#/}"       # Remove leading /
  a1="${a1%/}"     # Remove preceding /
  echo "${a1}"
}

ARG1=${1}
ARG1=$(trimFwdSlashes ${ARG1})
ARG2=${2}
EARG2=$(printf '%q' "$ARG2")
ARG3=${3}

line=${ARG1}
./builddir/${line}/${line}_benchmark_google_$( [[ -n "${ARG3}" && "${ARG3}" == 'opt' ]] && echo "" || echo "no_" )opt --benchmark_filter="${ARG2}" --benchmark_format=csv 2>&1  | ./plot.sh ${line} && mv ${line}/bench.png ${line}/${line}_${ARG3}_${EARG2}.png || echo "${line}/${line}_${ARG3}_${EARG2}.png skip"

