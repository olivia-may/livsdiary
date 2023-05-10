project('livsdiary', 'c', 'cpp', version : '3.0.0')

srcs = [
    'src/converters.c',
    'src/filesystem.c',
    'src/main.cpp',
    'src/time.c'
]
deps = [
    dependency('threads')
]
inc = [
    include_directories('.'),
]

conf_data = configuration_data()
conf_data.set('version', meson.project_version())
configure_file(
    input : 'config.h.in',
    output : 'config.h',
    configuration: conf_data
)

executable(
    'livsdiary.o', 
    srcs, 
    dependencies: deps, 
    include_directories: inc
)
