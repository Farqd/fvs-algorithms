all_headers = [
  'util/util.h',
  'brute/brute.h',
  'permutation/util.h',
  'interval/interval.h',
  'bipartite_permutation/bipartite_permutation.h',
]

cxx_library(
  name = 'fvs-algorithms',
  srcs = [
    'util/util.cpp',
    'brute/brute.cpp',
    'permutation/util.cpp',
    'interval/interval.cpp',
    'bipartite_permutation/bipartite_permutation.cpp',
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
    '-O3',
  ],
)

cxx_binary(
  name = 'main',
  srcs = [
    'main.cpp',
  ],
  link_style = 'static',
  deps = [
    '//:fvs-algorithms',
  ],
  visibility = [
    'PUBLIC',
  ],
  compiler_flags = [
    '-std=c++17',
    '-Wall',
    '-pthread',
    '-O3',
  ],
)
