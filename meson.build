project('myproject', 'cpp',
  version : '1.0.0',
  default_options : ['cpp_std=c++20', 'warning_level=2']
)

inc = include_directories('include')

sources = files(
  'src/main.cpp',
  'src/chess.cpp',
  'src/functions.cpp',
)

executable('myapp',
  sources,
  include_directories : inc,
  install : true
)