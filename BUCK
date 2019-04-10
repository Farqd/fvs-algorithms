all_headers = [
  'util/util.h',
  'brute/brute.h',
  'permutation/util.h',
  'interval/interval.h',
  'bipartite_permutation/bipartite_permutation.h',
]

debug_flags = [
    '-std=c++17',
    '-Wall',
    '-pthread',
    '-g',
  ]

production_flags = [
    '-std=c++17',
    '-Wall',
    '-pthread',
    '-O3',
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
  compiler_flags = production_flags,
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
  compiler_flags = production_flags,
)

cxx_binary(
  name = 'bipartite_permutation_main',
  srcs = [
    'bipartite_permutation/main.cpp',
  ],
  link_style = 'static',
  deps = [
    '//:fvs-algorithms',
  ],
  compiler_flags = debug_flags,
)
