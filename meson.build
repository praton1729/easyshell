
project('easyshell', 'c',
  version: files('version'),
  meson_version: '>=1.7.0',
  default_options: ['buildtype=release']
)

executable(
  'easyshell.elf',
  ['src/main.c', 'src/util.c', 'src/builtins.c'],
  include_directories: include_directories('include'),
  dependencies: [dependency('readline')],
  install: false
)
