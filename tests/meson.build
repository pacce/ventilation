rapidcheck  = dependency('rapidcheck')
gtest       = dependency('gtest')

pressure = executable('test-pressure', 'test-pressure.cpp', dependencies  : [gtest, rapidcheck, ventilation_dep])
test('test-pressure', pressure)
