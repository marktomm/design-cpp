
rootdir = '..'
currentdir = '.'
rootinc = join_paths(rootdir, 'include/')
currentinc = join_paths(currentdir, 'include/')
alt_bridge_inc = include_directories(currentinc)
alt_bridge_main = ['src/main.cpp']
# alt_bridge_simple = ['src/user_simple.cpp']
alt_bridge_src = [
    'src/lib.cpp',
]

alt_bridge_exe = executable(
    'alt_bridge_opt',
    [alt_bridge_main, alt_bridge_src],
    include_directories: [alt_bridge_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
    objects: [common_inc_opt_o],
)

alt_bridge_exe_no_opt = executable(
    'alt_bridge_no_opt',
    [alt_bridge_main, alt_bridge_src],
    include_directories: [alt_bridge_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
    cpp_args: ['-O0', '-g'],
    objects: [common_inc_no_opt_o],
)

alt_bridge_inc_opt_o = alt_bridge_exe.extract_objects(
    alt_bridge_src,
)

alt_bridge_main_opt_o = alt_bridge_exe.extract_objects(
    alt_bridge_main,
)

alt_bridge_inc_o = alt_bridge_inc_opt_o

alt_bridge_inc_no_opt_o = alt_bridge_exe_no_opt.extract_objects(
    alt_bridge_src,
)

alt_bridge_main_no_opt_o = alt_bridge_exe_no_opt.extract_objects(
    alt_bridge_main,
)

asandep = cpp.find_library('asan', dirs: '/usr/lib/x86_64-linux-gnu')

alt_bridge_exe_sanitize = executable(
    'alt_bridge_opt_sanitize',
    include_directories: [alt_bridge_inc, common_inc],
    install: true,
    cpp_args: ['-O3', '-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    objects: [
        alt_bridge_main_opt_o, 
        alt_bridge_inc_opt_o, 
        common_inc_opt_o
    ],
)

alt_bridge_exe_no_opt_sanitize = executable(
    'alt_bridge_no_opt_sanitize',
    include_directories: [alt_bridge_inc, common_inc],
    install: true,
    cpp_args: ['-O0', '-g', '-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    objects: [
        alt_bridge_main_no_opt_o, 
        alt_bridge_inc_no_opt_o, 
        common_inc_no_opt_o
    ],
)

if bench.found()
    alt_bridge_benchmark_test = ['bench.cpp']

    alt_bridge_benchmark_google_opt_exe = executable(
        'alt_bridge_benchmark_google_opt',
        [alt_bridge_benchmark_test],
        objects: [alt_bridge_inc_opt_o, common_inc_opt_o],
        include_directories: [alt_bridge_inc, common_inc],
        dependencies: [bench, thread],
    )

    benchmark(
        'alt_bridge_benchmark_google_opt',
        alt_bridge_benchmark_google_opt_exe,
        suite: 'alt_bridge',
        timeout: 0,
    )

    alt_bridge_benchmark_google_no_opt_exe = executable(
        'alt_bridge_benchmark_google_no_opt',
        [alt_bridge_benchmark_test],
        objects: [alt_bridge_inc_no_opt_o, common_inc_no_opt_o],
        include_directories: [alt_bridge_inc, common_inc],
        dependencies: [bench, thread],
        cpp_args: ['-O0', '-g'],
    )

    benchmark(
        'alt_bridge_benchmark_google_no_opt',
        alt_bridge_benchmark_google_no_opt_exe,
        suite: 'alt_bridge',
        timeout: 0,
    )

    custom_target(
        'bench_alt_bridge',
        command: [
            'sh',
            '-c', 'meson test --benchmark -C @BUILD_ROOT@ --suite alt_bridge && cat @BUILD_ROOT@/meson-logs/testlog.txt',
        ],
        depends: [
            alt_bridge_benchmark_google_no_opt_exe,
            alt_bridge_benchmark_google_opt_exe,
        ],
        output: 'dummy_output.txt',
    )
endif

gen_asm = custom_target(
    'gen_asm_no_opt',
    input: alt_bridge_main,
    output: 'alt_bridge_main_no_opt.s',
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
    input: alt_bridge_main,
    output: 'alt_bridge_main_opt.s',
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
    input: alt_bridge_src,
    output: 'alt_bridge_lib_no_opt.s',
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
    input: alt_bridge_src,
    output: 'alt_bridge_lib_opt.s',
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
