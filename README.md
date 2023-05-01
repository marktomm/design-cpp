# design-cpp

Design patterns related to poly-cpp

build requirements: meson, gcc, binutils (objdump), libasan

```shell
meson setup builddir
./start.sh
```

formatting requirements: clang-format, muon

documentation requirements: doxygen, graphviz,

profiling nice-to-haves: heaptrack, valgrind (massif)

# ouput: join.sh

Create one file code listing for design main code

```shell
./join.sh <design_name>
ls <design_name>/amalgamation.cpp
```

# output: asm_prettify.sh

Get assmebly with numbered lines and no meta data

```shell
./asm_prettify.sh <design_name> lib opt
./asm_prettify.sh <design_name> main opt
```

To get 25 lines after main

```shell
./asm_prettify.sh <design_name> main | grep '^[0-9]* main' -A25
```

# output: bench_prettify.sh

Output benchmark info in real time using default google benchmark output method but without iterations count.

```shell
./bench_prettify.sh <design_name>
./bench_prettify.sh <design_name> opt
```

# dev: new_design.sh

Add new design dir and code boilerplate

```shell
./new_design.sh design_name
# creates dir design_name
# running ./start.sh will build it
```

```shell
./new_design.sh design_name regen_meson
# regenerates meson.build file in design subdir
# this is required only after changes in new_feaure.sh

# to rebuild meson.build for all designs run
./regen_all_designs.sh
```

# dev: meson_fmt.sh

Syntax check and format meson.build files

# output: parsing for docs

```shell
# note: this is automatically done in ./bench_prettify <design name>
sort bench_output.txt | sed -E 's/(^.*[^0-9])[0-9]*$/\1/'
```

# heaptrack

```shell
./_build.sh && heaptrack ./builddir/lambda_fns/lambda_fns_no_opt
```

# output: google benchmark compare two bechmark runs

required: pip3

```shell
cd benchmark/tools
pip3 install -r requirements.txt
./compare.py benchmarks  ../../builddir/<design_name>/<design_name>_benchmark_google_no_opt ../../builddir/<design_name>/<design_name>_benchmark_google_no_opt
```
