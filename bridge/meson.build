
rootdir = '..'
currentdir = '.'
rootinc = join_paths(rootdir, 'include/')
currentinc = join_paths(currentdir, 'include/')
bridge_inc = include_directories(currentinc)
bridge_main = ['src/main.cpp']
# bridge_simple = ['src/user_simple.cpp']
bridge_src = [
    'src/lib.cpp',
]

bridge_exe = executable(
    'bridge_opt',
    [bridge_main, bridge_src],
    include_directories: [bridge_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
    objects: [common_inc_opt_o],
)

bridge_exe_no_opt = executable(
    'bridge_no_opt',
    [bridge_main, bridge_src],
    include_directories: [bridge_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
    cpp_args: ['-O0', '-g'],
    objects: [common_inc_no_opt_o],
)

bridge_inc_opt_o = bridge_exe.extract_objects(
    bridge_src,
)

bridge_main_opt_o = bridge_exe.extract_objects(
    bridge_main,
)

bridge_inc_o = bridge_inc_opt_o

bridge_inc_no_opt_o = bridge_exe_no_opt.extract_objects(
    bridge_src,
)

bridge_main_no_opt_o = bridge_exe_no_opt.extract_objects(
    bridge_main,
)

asandep = cpp.find_library('asan', dirs: '/usr/lib/x86_64-linux-gnu')

bridge_exe_sanitize = executable(
    'bridge_opt_sanitize',
    include_directories: [bridge_inc, common_inc],
    install: true,
    cpp_args: ['-O3', '-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    objects: [
        bridge_main_opt_o, 
        bridge_inc_opt_o, 
        common_inc_opt_o
    ],
)

bridge_exe_no_opt_sanitize = executable(
    'bridge_no_opt_sanitize',
    include_directories: [bridge_inc, common_inc],
    install: true,
    cpp_args: ['-O0', '-g', '-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    objects: [
        bridge_main_no_opt_o, 
        bridge_inc_no_opt_o, 
        common_inc_no_opt_o
    ],
)

if bench.found()
    bridge_benchmark_test = ['bench.cpp']

    bridge_benchmark_google_opt_exe = executable(
        'bridge_benchmark_google_opt',
        [bridge_benchmark_test],
        objects: [bridge_inc_opt_o, common_inc_opt_o],
        include_directories: [bridge_inc, common_inc],
        dependencies: [bench, thread],
    )

    benchmark(
        'bridge_benchmark_google_opt',
        bridge_benchmark_google_opt_exe,
        suite: 'bridge',
        timeout: 0,
    )

    bridge_benchmark_google_no_opt_exe = executable(
        'bridge_benchmark_google_no_opt',
        [bridge_benchmark_test],
        objects: [bridge_inc_no_opt_o, common_inc_no_opt_o],
        include_directories: [bridge_inc, common_inc],
        dependencies: [bench, thread],
        cpp_args: ['-O0', '-g'],
    )

    benchmark(
        'bridge_benchmark_google_no_opt',
        bridge_benchmark_google_no_opt_exe,
        suite: 'bridge',
        timeout: 0,
    )

    custom_target(
        'bench_bridge',
        command: [
            'sh',
            '-c', 'meson test --benchmark -C @BUILD_ROOT@ --suite bridge && cat @BUILD_ROOT@/meson-logs/testlog.txt',
        ],
        depends: [
            bridge_benchmark_google_no_opt_exe,
            bridge_benchmark_google_opt_exe,
        ],
        output: 'dummy_output.txt',
    )
endif

gen_asm = custom_target(
    'gen_asm_no_opt',
    input: bridge_main,
    output: 'bridge_main_no_opt.s',
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
    input: bridge_main,
    output: 'bridge_main_opt.s',
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
    input: bridge_src,
    output: 'bridge_lib_no_opt.s',
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
    input: bridge_src,
    output: 'bridge_lib_opt.s',
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
