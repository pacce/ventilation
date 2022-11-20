project('ventilation', 'cpp', version : '0.1.0', default_options : ['warning_level=3', 'cpp_std=c++20'])

includes      = include_directories('include')
dependencies  = [dependency('boost')]

ventilation = library(
  meson.project_name()
  , []
  , include_directories : includes
  , dependencies        : dependencies
  , install             : true
  )

ventilation_dep = declare_dependency(
    link_with           : ventilation
  , include_directories : includes
  )

if not meson.is_subproject()
  subdir('example')
  subdir('tests')
endif
