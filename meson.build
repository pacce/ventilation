project('ventilation', 'cpp', version: '0.1.0', default_options : ['cpp_std=c++20'])

headers       = include_directories('include')
sources       = ['sources/ventilation.cpp']
dependencies  = []

ventilation = library(
  'ventilation'
  , sources
  , include_directories : headers
  , dependencies        : dependencies
  )

ventilation_dep = declare_dependency(
  include_directories : headers
  , dependencies      : dependencies
  , link_with         : ventilation
  )

if not meson.is_subproject()
    subdir('tests')
endif
