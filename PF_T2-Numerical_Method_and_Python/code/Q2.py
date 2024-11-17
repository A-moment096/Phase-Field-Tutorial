import numpy as np
from typing import Callable


def Ex2(x):
    return np.exp(-(x**2))


N: float = 100000.0
dx: float = 1.0
Exact_Result: float = np.sqrt(np.pi)

def RiemannIntegral(
    f: Callable[[float], float], x_start: float, x_end: float, dx: float
) -> float:
    sum = 0
    x = x_start
    while x < x_end:
        sum += f(x)
        x += dx
    return sum * dx


def QuadratureIntegral(
    f: Callable[[float], float], x_start: float, x_end: float, dx: float
) -> float:
    sum = 0
    x = x_start
    while x < x_end:
        sum += f(x)
        x += dx
    sum -= (f(x_start) + f(x_end)) / 2
    return sum * dx


def SimpsonIntegral(
    f: Callable[[float], float], x_start: float, x_end: float, dx: float
) -> float:
    sum = 0
    x = x_start
    while x < x_end:
        sum += 4 * f(x + dx / 2)
        sum += 2 * f(x)
        x += dx
    sum -= f(x_start) + f(x_end)
    return sum * dx / 6


def N_C_Integral(
    f: Callable[[float], float], x_start: float, x_end: float, dx: float
) -> float:
    sum = 0
    x = x_start
    while x < x_end:
        sum += 32 * f(x + dx / 4)
        sum += 12 * f(x + dx / 2)
        sum += 32 * f(x + 3 * dx / 4)
        sum += 14 * f(x)
        x += dx
    sum -= 7 * (f(x_start) + f(x_end))
    return sum * dx / 90


I_1 = RiemannIntegral(Ex2, -N, N, dx)
I_2 = QuadratureIntegral(Ex2, -N, N, dx)
I_3 = SimpsonIntegral(Ex2, -N, N, dx)
I_4 = N_C_Integral(Ex2, -N, N, dx)

print(
    f"""
Riemann Integral :      {I_1:.8f};   Absolute Error: {I_1-Exact_Result:.9f};    Relative Error: {(I_1-Exact_Result)/Exact_Result:.3e}
Quadrature Integral :   {I_2:.8f};   Absolute Error: {I_2-Exact_Result:.9f};    Relative Error: {(I_2-Exact_Result)/Exact_Result:.3e}
Simpson Integral :      {I_3:.8f};   Absolute Error: {I_3-Exact_Result:.9f};    Relative Error: {(I_3-Exact_Result)/Exact_Result:.3e}
Newton-Cotes Integral : {I_4:.8f};   Absolute Error: {I_4-Exact_Result:.9f};    Relative Error: {(I_4-Exact_Result)/Exact_Result:.3e}
"""
)
