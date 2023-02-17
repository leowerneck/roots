test_bisection = executable('test_bisection',
                            sources : 'test_bisection.c',
                            dependencies : [dep_roots])

test_secant = executable('test_secant',
                         sources : 'test_secant.c',
                         dependencies : [dep_roots])

test_dekker = executable('test_dekker',
                         sources : 'test_dekker.c',
                         dependencies : [dep_roots])

test('Bisection method test', test_bisection)
test('Secant method test', test_secant)
test('Dekker\'s method test', test_dekker)
