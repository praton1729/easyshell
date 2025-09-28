
project('easyshell', 'c',
  version: files('version'),
  meson_version: '>=1.7.0',
  default_options: ['buildtype=release']
)

ss = import('sourceset')

srcs = ss.source_set()

subdir('src')

executable(
  'easyshell.elf',
  sources: srcs.all_sources(),
  include_directories: include_directories('include'),
  dependencies: [dependency('readline')],
  install: false
)
