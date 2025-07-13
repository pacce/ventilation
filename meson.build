project('ventilation', 'cpp', version: '0.1.0')

headers       = include_directories('include')
sources       = ['sources/ventilation.cpp']
dependencies  = []

ventilation_dep = declare_dependency(
  include_directories : headers
  , dependencies      : dependencies
  )

ventilation = library(
  'ventilation'
  , sources
  , include_directories : headers
  , dependencies        : dependencies
  )
