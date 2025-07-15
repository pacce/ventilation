cmake     = import('cmake')
options   = cmake.subproject_options()
options.add_cmake_defines({'RC_ENABLE_GTEST':'ON'})

gtest               = dependency('gtest')
rapidcheck_project  = cmake.subproject('rapidcheck', options: options)
rapidcheck          = rapidcheck_project.dependency('rapidcheck')
rapidcheck_gtest    = rapidcheck_project.dependency('rapidcheck_gtest')

dependencies  = [gtest, rapidcheck, rapidcheck_gtest, ventilation_dep]

test('compliance', executable('compliance', 'compliance.cpp', dependencies: dependencies))
test(      'flow', executable(      'flow',       'flow.cpp', dependencies: dependencies))
test(  'pressure', executable(  'pressure',   'pressure.cpp', dependencies: dependencies))
test('resistance', executable('resistance', 'resistance.cpp', dependencies: dependencies))
test(    'volume', executable(    'volume',     'volume.cpp', dependencies: dependencies))
