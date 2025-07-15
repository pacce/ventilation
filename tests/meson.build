cmake     = import('cmake')
options   = cmake.subproject_options()
options.add_cmake_defines({'RC_ENABLE_GTEST':'ON'})

gtest               = dependency('gtest')
rapidcheck_project  = cmake.subproject('rapidcheck', options: options)
rapidcheck          = rapidcheck_project.dependency('rapidcheck')
rapidcheck_gtest    = rapidcheck_project.dependency('rapidcheck_gtest')

dependencies  = [gtest, rapidcheck, rapidcheck_gtest, ventilation_dep]

test('flow', executable('flow', 'flow.cpp', dependencies: dependencies))
