import numpy as np
from matplotlib import pyplot as plt
from typing import Callable

u = [2.0]
t_0 = 0.0
t_N = 5.0
N = 10000
h = (t_N - t_0) / N
t_list = [i * h for i in range(N + 1)]


def f(t: float) -> float:
    return 0.5 * t**3 - 5 * t**2 + 10 * t


# By rearrange equation from the Euler Backward Method, we got:
# $$ u_n = \frac{f_{n-1} h + u_{n-1}}{1-\lambda h} $$
# where h is defined as above.


def RHS(
    u: list[float], i: int, t: list[float], f: Callable[[float], float], h: float
) -> float:
    return (f(t[i] + h) * h + u[i]) / (1.0 + 5.0 * h)


for i in range(N):
    u.append(RHS(u, i, t_list, f, h))

t = np.linspace(0, 5, 10000)

plt.plot(
    t,
    (3106 * np.exp(-5 * t) + 125 * t**3 - 1325 * t**2 + 3030 * t - 606) / 1250,
    "-b",
    label="Exact solution",
)  # plot exact solution

plt.plot(
    np.array(t_list), np.array(u), "--r", label="Numerical solution"
)  # plot Numerical solution

plt.xlabel("t")
plt.ylabel("u(t)")
plt.legend(loc=1, borderaxespad=0.0)
# plot legend
plt.show()
