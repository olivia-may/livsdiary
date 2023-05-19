project('livsdiary', 'c', version : '3.2.3')

srcs = [
    'src/commands.c',
    'src/converters.c',
    'src/editor.c',
    'src/filesystem.c',
    'src/main.c',
    'src/time.c'
]
deps = [
    dependency('threads')
]
inc = [
    include_directories('.'),
]

linker_flags = [
    '-lncurses',
    '-lm'
]

conf_data = configuration_data()
conf_data.set('version', meson.project_version())
configure_file(
    input : 'config.h.in',
    output : 'config.h',
    configuration: conf_data
)

add_global_arguments(linker_flags, language : 'c')

executable(
    'livsdiary', 
    srcs, 
    link_args : linker_flags,
    dependencies : deps, 
    include_directories: inc,
    install : true
)
