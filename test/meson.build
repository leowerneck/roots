test_bisection = executable('test_bisection',
                            sources : 'test_bisection.c',
                            dependencies : [dep_roots])

test_secant = executable('test_secant',
                         sources : 'test_secant.c',
                         dependencies : [dep_roots])

test_false_position = executable('test_false_position',
                                 sources : 'test_false_position.c',
                                 dependencies : [dep_roots])

test_dekker = executable('test_dekker',
                         sources : 'test_dekker.c',
                         dependencies : [dep_roots])

test_ridder = executable('test_ridder',
                         sources : 'test_ridder.c',
                         dependencies : [dep_roots])

test('Bisection method test', test_bisection)
test('Secant method test', test_secant)
test('False-position method test', test_false_position)
test('Dekker\'s method test', test_dekker)
test('Ridder\'s method test', test_ridder)
