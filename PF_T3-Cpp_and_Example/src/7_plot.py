import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.axes3d import Axes3D
from matplotlib.cm import coolwarm
import pandas
import os

dir = os.path.dirname(__file__)

filename = ["vals", "gradx", "grady", "laps"]
filelist = [
    pandas.read_csv(os.path.join(dir, "./results/" + fname + ".csv"))
    for fname in filename
]


def array_to_matrix(array: np.array, size: int):
    matrix = []
    for i in range(len(array)):
        row = []
        row.append(array[i])
        if i % size == size - 1:
            row = np.array(row)
            matrix.append(row)
            row = []
    return np.array(matrix)


fcount = 0
for file in filelist:

    fig, ax = plt.subplots(1, 1, subplot_kw=dict(projection="3d"))
    fig.set_layout_engine("constrained")
    this_axis = ax

    x_axis = [i for i in range(100)]
    y_axis = [i for i in range(100)]
    z = file["val"].values
    z = [np.nan if val > 4.0 or val < -4.0 else val for val in z]
    z = array_to_matrix(z, 100)
    x, y = np.meshgrid(x_axis, y_axis)

    p = this_axis.plot_surface(
        x, y, z, rstride=1, cstride=1, cmap=coolwarm, linewidth=0, antialiased=False
    )
    this_axis.set_title(filename[fcount])
    fcount += 1
    fig.show()
input()
