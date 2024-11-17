import numpy as np
from typing import Callable
from matplotlib import pyplot as plt
from matplotlib.cm import coolwarm


class Mesh:
    def __init__(
        self,
        x_length: float,
        dx: float,
        y_length: float = None,
        f: Callable[[float, float], float] = None,
    ):

        self.x_length = x_length
        self.dx = dx
        if y_length is None:
            self.y_length = x_length
        else:
            self.y_length = y_length

        self.Nx = int(self.x_length / self.dx)
        self.Ny = int(self.y_length / self.dx)

        self.vals: list[list[float]] = []
        self.assign_values(f)

        self.bounds: dict[str, list[float]] = {
            "x-": [self.vals[-1][i] for i in range(self.Ny)],  # x = 0
            "x+": [self.vals[+0][i] for i in range(self.Ny)],  # x = Nx-1
            "y-": [self.vals[i][-1] for i in range(self.Nx)],  # y = 0
            "y+": [self.vals[i][+0] for i in range(self.Nx)],  # y = Ny-1
        }
        self.grad_x: list[list[float]] = [
            [0.0 for i in range(self.Ny)] for j in range(self.Nx)
        ]
        self.grad_y: list[list[float]] = [
            [0.0 for i in range(self.Ny)] for j in range(self.Nx)
        ]
        self.lap: list[list[float]] = [
            [0.0 for i in range(self.Ny)] for j in range(self.Nx)
        ]

        self.calc_grad()
        self.calc_lap()

    def assign_values(self, f: Callable[[float, float], float] = None):
        if f is None:
            self.vals = [[0.0 for i in range(self.Ny)] for j in range(self.Nx)]
            print("Mesh is 0 initialized")
        else:
            self.vals = [
                [f(i * self.dx, j * self.dx) for i in range(self.Ny)]
                for j in range(self.Nx)
            ]
            print(f"Evalued with {f.__name__}")

    def calc_grad(self):
        Nx = len(self.vals)
        Ny = len(self.vals[0])
        for i in range(Nx):
            for j in range(Ny):
                v_l = self.vals[i - 1][j] if i != 0 else self.bounds["x-"][j]
                v_r = self.vals[i + 1][j] if i != Nx - 1 else self.bounds["x+"][j]
                v_d = self.vals[i][j - 1] if j != 0 else self.bounds["y-"][i]
                v_u = self.vals[i][j + 1] if j != Nx - 1 else self.bounds["y+"][i]
                self.grad_x[i][j] = (v_r - v_l) / (2 * self.dx)
                self.grad_y[i][j] = (v_u - v_d) / (2 * self.dx)

    def calc_lap(self):
        Nx = len(self.vals)
        Ny = len(self.vals[0])
        for i in range(Nx):
            for j in range(Ny):
                v_c = self.vals[i][j]
                v_l = self.vals[i - 1][j] if i != 0 else self.bounds["x-"][j]
                v_r = self.vals[i + 1][j] if i != Nx - 1 else self.bounds["x+"][j]
                v_d = self.vals[i][j - 1] if j != 0 else self.bounds["y-"][i]
                v_u = self.vals[i][j + 1] if j != Nx - 1 else self.bounds["y+"][i]
                self.lap[i][j] = (v_l + v_d + v_r + v_u - 4 * v_c) / (self.dx * self.dx)

    def assign_bound(self, bound_type: str = "Periodic"):
        if bound_type == "Periodic":
            self.bounds["x-"] = [self.vals[-1][i] for i in range(self.Ny)]
            self.bounds["x+"] = [self.vals[+0][i] for i in range(self.Ny)]
            self.bounds["y-"] = [self.vals[i][-1] for i in range(self.Nx)]
            self.bounds["y+"] = [self.vals[i][+0] for i in range(self.Nx)]
        elif bound_type == "Const":
            print("Not implemented, use Periodic Boundary")
        elif bound_type == "Adiabtic":
            self.bounds["x-"] = [self.vals[+0][i] for i in range(self.Ny)]
            self.bounds["x+"] = [self.vals[-1][i] for i in range(self.Ny)]
            self.bounds["y-"] = [self.vals[i][+0] for i in range(self.Nx)]
            self.bounds["y+"] = [self.vals[i][-1] for i in range(self.Nx)]
        else:
            print("Wrong Boundary Type, use Periodic Boundary")
        pass


def Cos_2D(x: float, y: float) -> float:
    return np.cos(x) + np.cos(y)


def Sin_2D(x: float, y: float) -> float:
    return np.sin(x) + np.sin(y)


mesh = Mesh(x_length=4 * np.pi, dx=0.1, f=Sin_2D)

x_axis = np.linspace(0, mesh.x_length, mesh.Nx)
y_axis = np.linspace(0, mesh.y_length, mesh.Ny)
X, Y = np.meshgrid(x_axis, y_axis)
## Here I use list comprehension to extract the property 'val' I need, and use one-liner if else statement.
Z_1 = np.array([[val for val in row] for row in mesh.vals])

fig = plt.figure()
# surface_plot with color grading and color bar
ax = fig.add_subplot(2, 2, 1, projection="3d")
p = ax.plot_surface(
    X, Y, Z_1, rstride=1, cstride=1, cmap=coolwarm, linewidth=0, antialiased=False
)
cb = fig.colorbar(p, shrink=0.5)

Z_2_x = np.array([[val for val in row] for row in mesh.grad_x])
Z_2_y = np.array([[val for val in row] for row in mesh.grad_y])

ax = fig.add_subplot(2, 2, 2, projection="3d")
p = ax.plot_surface(
    X, Y, Z_2_x, rstride=1, cstride=1, cmap=coolwarm, linewidth=0, antialiased=False
)
cb = fig.colorbar(p, shrink=0.5)

ax = fig.add_subplot(2, 2, 3, projection="3d")
p = ax.plot_surface(
    X, Y, Z_2_y, rstride=1, cstride=1, cmap=coolwarm, linewidth=0, antialiased=False
)
cb = fig.colorbar(p, shrink=0.5)

Z_3 = np.array([[val for val in row] for row in mesh.lap])
ax = fig.add_subplot(2, 2, 4, projection="3d")
p = ax.plot_surface(
    X, Y, Z_3, rstride=1, cstride=1, cmap=coolwarm, linewidth=0, antialiased=False
)
cb = fig.colorbar(p, shrink=0.5)
plt.show()
