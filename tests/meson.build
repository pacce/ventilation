rapidcheck    = dependency('rapidcheck')
gtest         = dependency('gtest')
dependencies  = [gtest, rapidcheck, ventilation_dep]

compliance  = executable('test-compliance', 'test-compliance.cpp', dependencies: dependencies)
elastance   = executable( 'test-elastance',  'test-elastance.cpp', dependencies: dependencies)
flow        = executable(      'test-flow',       'test-flow.cpp', dependencies: dependencies)
pressure    = executable(  'test-pressure',   'test-pressure.cpp', dependencies: dependencies)
volume      = executable(    'test-volume',     'test-volume.cpp', dependencies: dependencies)

test('test-compliance', compliance)
test( 'test-elastance',  elastance)
test(      'test-flow',       flow)
test(  'test-pressure',   pressure)
test(    'test-volume',     volume)
