all_headers = [
  'util/util.h',
  'brute/brute.h',
  'permutation/util.h',
  'interval/interval.h',
]

cxx_library(
  name = 'fvs-algorithms',
  srcs = [
    'util/util.cpp',
    'brute/brute.cpp',
    'permutation/util.cpp',
    'interval/interval.cpp',
    
  ],
  headers = all_headers,
  exported_headers = all_headers,
  link_style = 'static',
  deps = [
  ],
  visibility = [
    'PUBLIC',
  ],
  compiler_flags = [
    '-std=c++17',
    '-Wall',
    '-pthread',
  ],
)
