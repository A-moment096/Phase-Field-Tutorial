import numpy as np
from typing import Callable


class val_Mesh:
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
        self.val_list: list[list[float]] = []
        self.assign_values(f)

    def assign_values(self, f: Callable[[float, float], float] = None):
        if f is None:
            self.val_list = [[0.0 for i in range(self.Ny)] for j in range(self.Nx)]
            print("Mesh is 0 initialized")
        else:
            self.val_list = [
                [f(i * self.dx, j * self.dx) for i in range(self.Ny)]
                for j in range(self.Nx)
            ]
            print(f"Evalued with {f.__name__}")


class grad_Mesh:

    def __init__(self, mesh: val_Mesh, bound_type: str = None):
        self.vals: list[list[float]] = mesh.val_list
        self.dx = mesh.dx
        self.bounds: dict[str, list[float]] = {
            "x-": [mesh.val_list[-1][i] for i in range(mesh.Ny)],  # x = 0
            "x+": [mesh.val_list[+0][i] for i in range(mesh.Ny)],  # x = Nx-1
            "y-": [mesh.val_list[i][-1] for i in range(mesh.Nx)],  # y = 0
            "y+": [mesh.val_list[i][+0] for i in range(mesh.Nx)],  # y = Ny-1
        }
        self.grad_x: list[list[float]] = [
            [0.0 for i in range(mesh.Ny)] for j in range(mesh.Nx)
        ]
        self.grad_y: list[list[float]] = [
            [0.0 for i in range(mesh.Ny)] for j in range(mesh.Nx)
        ]
        self.assign_bound(bound_type)
        self.calc_grad()
        pass

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

    def assign_bound(self, bound_type: str = "Periodic"):
        if bound_type == "Periodic" or bound_type == None:
            self.bounds["x-"] = [mesh.val_list[-1][i] for i in range(mesh.Ny)]
            self.bounds["x+"] = [mesh.val_list[+0][i] for i in range(mesh.Ny)]
            self.bounds["y-"] = [mesh.val_list[i][-1] for i in range(mesh.Nx)]
            self.bounds["y+"] = [mesh.val_list[i][+0] for i in range(mesh.Nx)]
        elif bound_type == "Const":
            print("Not implemented, use Periodic Boundary")
        elif bound_type == "Adiabtic":
            self.bounds["x-"] = [mesh.val_list[+0][i] for i in range(mesh.Ny)]
            self.bounds["x+"] = [mesh.val_list[-1][i] for i in range(mesh.Ny)]
            self.bounds["y-"] = [mesh.val_list[i][+0] for i in range(mesh.Nx)]
            self.bounds["y+"] = [mesh.val_list[i][-1] for i in range(mesh.Nx)]
        else:
            print("Wrong Boundary Type, use Periodic Boundary")
        pass


class laplacian_Mesh:
    def __init__(self, mesh: val_Mesh, bound_type: str = None):
        self.vals: list[list[float]] = mesh.val_list
        self.dx = mesh.dx
        self.bounds: dict[str, list[float]] = {
            "x-": [mesh.val_list[-1][i] for i in range(mesh.Ny)],  # x = 0
            "x+": [mesh.val_list[+0][i] for i in range(mesh.Ny)],  # x = Nx-1
            "y-": [mesh.val_list[i][-1] for i in range(mesh.Nx)],  # y = 0
            "y+": [mesh.val_list[i][+0] for i in range(mesh.Nx)],  # y = Ny-1
        }
        self.lap: list[list[float]] = [
            [0.0 for i in range(mesh.Ny)] for j in range(mesh.Nx)
        ]
        self.assign_bound(bound_type)
        self.calc_lap()
        pass

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
        if bound_type == "Periodic" or bound_type == None:
            self.bounds["x-"] = [mesh.val_list[-1][i] for i in range(mesh.Ny)]
            self.bounds["x+"] = [mesh.val_list[+0][i] for i in range(mesh.Ny)]
            self.bounds["y-"] = [mesh.val_list[i][-1] for i in range(mesh.Nx)]
            self.bounds["y+"] = [mesh.val_list[i][+0] for i in range(mesh.Nx)]
        elif bound_type == "Const":
            print("Not implemented, use Periodic Boundary")
        elif bound_type == "Adiabtic":
            self.bounds["x-"] = [mesh.val_list[+0][i] for i in range(mesh.Ny)]
            self.bounds["x+"] = [mesh.val_list[-1][i] for i in range(mesh.Ny)]
            self.bounds["y-"] = [mesh.val_list[i][+0] for i in range(mesh.Nx)]
            self.bounds["y+"] = [mesh.val_list[i][-1] for i in range(mesh.Nx)]
        else:
            print("Wrong Boundary Type, use Periodic Boundary")
        pass


def Cos_2D(x: float, y: float) -> float:
    return np.cos(x) + np.cos(y)


mesh = val_Mesh(x_length=4 * np.pi, dx=0.1, f=Cos_2D)

from matplotlib import pyplot as plt
from matplotlib.cm import coolwarm

x_axis = np.linspace(0, mesh.x_length, mesh.Nx)
y_axis = np.linspace(0, mesh.y_length, mesh.Ny)
X, Y = np.meshgrid(x_axis, y_axis)
## Here I use list comprehension to extract the property 'val' I need, and use one-liner if else statement.
Z_1 = np.array([[val for val in row] for row in mesh.val_list])

fig = plt.figure()
# surface_plot with color grading and color bar
ax = fig.add_subplot(2, 2, 1, projection="3d")
p = ax.plot_surface(
    X, Y, Z_1, rstride=1, cstride=1, cmap=coolwarm, linewidth=0, antialiased=False
)
cb = fig.colorbar(p, shrink=0.5)

mesh_grad = grad_Mesh(mesh)
Z_2_x = np.array([[val for val in row] for row in mesh_grad.grad_x])
Z_2_y = np.array([[val for val in row] for row in mesh_grad.grad_y])

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

mesh_lap = laplacian_Mesh(mesh)
Z_3 = np.array([[val for val in row] for row in mesh_lap.lap])
ax = fig.add_subplot(2, 2, 4, projection="3d")
p = ax.plot_surface(
    X, Y, Z_3, rstride=1, cstride=1, cmap=coolwarm, linewidth=0, antialiased=False
)
cb = fig.colorbar(p, shrink=0.5)
plt.show()
