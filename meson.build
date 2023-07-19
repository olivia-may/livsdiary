project('livsdiary', 'c', version : '3.3.0')

srcs = [
    'src/commands.c',
    'src/editor.c',
    'src/filesystem.c',
    'src/main.c',
]

deps = [
    dependency('curses'),
    dependency('threads')
]

link_args = [
    '-lm'
]

subdir('src/')

executable(
    'livsdiary', 
    srcs, 
    link_args : link_args,
    dependencies : deps, 
    include_directories: 'src/',
    install : true
)
