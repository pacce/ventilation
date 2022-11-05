rapidcheck  = dependency('rapidcheck')
gtest       = dependency('gtest')

dependencies  = [gtest, rapidcheck, ventilation_dep]

pressure  = executable('test-pressure', 'test-pressure.cpp', dependencies: dependencies)
flow      = executable(    'test-flow',     'test-flow.cpp', dependencies: dependencies)

test(    'test-flow',     flow)
test('test-pressure', pressure)
