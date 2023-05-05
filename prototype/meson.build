
rootdir = '..'
currentdir = '.'
rootinc = join_paths(rootdir, 'include/')
currentinc = join_paths(currentdir, 'include/')
prototype_inc = include_directories(currentinc)
prototype_main = ['src/main.cpp']
# prototype_simple = ['src/user_simple.cpp']
prototype_src = [
    'src/lib.cpp',
]

prototype_exe = executable(
    'prototype_opt',
    [prototype_main, prototype_src],
    include_directories: [prototype_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
    objects: [common_inc_opt_o],
)

prototype_exe_no_opt = executable(
    'prototype_no_opt',
    [prototype_main, prototype_src],
    include_directories: [prototype_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
    cpp_args: ['-O0', '-g'],
    objects: [common_inc_no_opt_o],
)

prototype_inc_opt_o = prototype_exe.extract_objects(
    prototype_src,
)

prototype_main_opt_o = prototype_exe.extract_objects(
    prototype_main,
)

prototype_inc_o = prototype_inc_opt_o

prototype_inc_no_opt_o = prototype_exe_no_opt.extract_objects(
    prototype_src,
)

prototype_main_no_opt_o = prototype_exe_no_opt.extract_objects(
    prototype_main,
)

asandep = cpp.find_library('asan', dirs: '/usr/lib/x86_64-linux-gnu')

prototype_exe_sanitize = executable(
    'prototype_opt_sanitize',
    include_directories: [prototype_inc, common_inc],
    install: true,
    cpp_args: ['-O3', '-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    objects: [
        prototype_main_opt_o, 
        prototype_inc_opt_o, 
        common_inc_opt_o
    ],
)

prototype_exe_no_opt_sanitize = executable(
    'prototype_no_opt_sanitize',
    include_directories: [prototype_inc, common_inc],
    install: true,
    cpp_args: ['-O0', '-g', '-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    objects: [
        prototype_main_no_opt_o, 
        prototype_inc_no_opt_o, 
        common_inc_no_opt_o
    ],
)

if bench.found()
    prototype_benchmark_test = ['bench.cpp']

    prototype_benchmark_google_opt_exe = executable(
        'prototype_benchmark_google_opt',
        [prototype_benchmark_test],
        objects: [prototype_inc_opt_o, common_inc_opt_o],
        include_directories: [prototype_inc, common_inc],
        dependencies: [bench, thread],
    )

    benchmark(
        'prototype_benchmark_google_opt',
        prototype_benchmark_google_opt_exe,
        suite: 'prototype',
        timeout: 0,
    )

    prototype_benchmark_google_no_opt_exe = executable(
        'prototype_benchmark_google_no_opt',
        [prototype_benchmark_test],
        objects: [prototype_inc_no_opt_o, common_inc_no_opt_o],
        include_directories: [prototype_inc, common_inc],
        dependencies: [bench, thread],
        cpp_args: ['-O0', '-g'],
    )

    benchmark(
        'prototype_benchmark_google_no_opt',
        prototype_benchmark_google_no_opt_exe,
        suite: 'prototype',
        timeout: 0,
    )

    custom_target(
        'bench_prototype',
        command: [
            'sh',
            '-c', 'meson test --benchmark -C @BUILD_ROOT@ --suite prototype && cat @BUILD_ROOT@/meson-logs/testlog.txt',
        ],
        depends: [
            prototype_benchmark_google_no_opt_exe,
            prototype_benchmark_google_opt_exe,
        ],
        output: 'dummy_output.txt',
    )
endif

gen_asm = custom_target(
    'gen_asm_no_opt',
    input: prototype_main,
    output: 'prototype_main_no_opt.s',
    command: [
        cpp_prog,
        '-I' + meson.current_source_dir() + '/include/',
        '-I' + meson.current_source_dir() + '/../',
        '-S',
        '-masm=intel',
        '-o', '@OUTPUT@',
        '@INPUT@',
    ],
    build_by_default: true,
)

gen_asm_opt = custom_target(
    'gen_asm_opt',
    input: prototype_main,
    output: 'prototype_main_opt.s',
    command: [
        cpp_prog,
        '-O3', '-I' + meson.current_source_dir() + '/include/',
        '-I' + meson.current_source_dir() + '/../',
        '-S',
        '-masm=intel',
        '-o', '@OUTPUT@',
        '@INPUT@',
    ],
    build_by_default: true,
)

gen_asm_lib = custom_target(
    'gen_asm_lib_no_opt',
    input: prototype_src,
    output: 'prototype_lib_no_opt.s',
    command: [
        cpp_prog,
        '-I' + meson.current_source_dir() + '/include/',
        '-I' + meson.current_source_dir() + '/../',
        '-S',
        '-masm=intel',
        '-o', '@OUTPUT@',
        '@INPUT@',
    ],
    build_by_default: true,
)

gen_asm_lib_opt = custom_target(
    'gen_asm_lib_opt',
    input: prototype_src,
    output: 'prototype_lib_opt.s',
    command: [
        cpp_prog,
        '-O3', '-I' + meson.current_source_dir() + '/include/',
        '-I' + meson.current_source_dir() + '/../',
        '-S',
        '-masm=intel',
        '-o', '@OUTPUT@',
        '@INPUT@',
    ],
    build_by_default: true,
)
