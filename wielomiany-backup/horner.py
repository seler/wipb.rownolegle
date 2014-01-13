r1 = (6 * 5 ** 5) + (5 * 5 ** 4) + (4 * 5 ** 3) + (3 * 5 ** 2) + (2 * 5 ** 1) + (1 * 5 ** 0)


def horner(x, *polynomial):
    """A function that implements the Horner Scheme for evaluating a
    polynomial of coefficients *polynomial in x."""
    result = 0
    for coefficient in polynomial:
        result = result * x + coefficient
    return result

r2 = horner(5, 6, 5, 4, 3, 2, 1)


print r1, r2
