import numpy as np
import matplotlib.pyplot as plt
import os

dir = os.path.dirname(__file__)

# bc_type = "periodic"
bc_type = "fixed"

step_interval = 200

file_count = 0
file_list = []

for i in range(4):
    file_count = i * step_interval
    file_list.append(
        np.loadtxt(
            os.path.join(dir, "results", bc_type + "_step_" + str(file_count) + ".csv"),
            delimiter=",",
            skiprows=1,
        )
    )
fig, axs = plt.subplots(2, 2)
i = 0

for file in file_list:
    ax_this = axs[int(i / 2), i % 2]
    x = file[:, 0]
    y = file[:, 1]
    ax_this.plot(x, y)
    ax_this.set_ylim(-0.05, 1.05)
    ax_this.set_xlim(0, 128)
    ax_this.set_title("Step " + str(i * step_interval))
    ax_this.set_xlabel("x")
    ax_this.set_ylabel("T")
    ax_this.margins(0)
    i += 1
fig.set_layout_engine("constrained")
plt.show()