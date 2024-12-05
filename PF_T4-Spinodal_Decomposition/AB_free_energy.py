from matplotlib import pyplot as plt
import numpy as np
import os

path = os.path.dirname(__file__)
print()

x = np.linspace(-0.1, 1.1, 1000000)
y = x**2 * (1 - x) ** 2

plt.plot(x, y)
plt.xlabel("Concentration, $c(A)$")
plt.ylabel("Chemical Energy, $G$")

ticks = ("B", "0.2", "0.4", "0.6", "0.8", "A")
plt.xticks([0, 0.2, 0.4, 0.6, 0.8, 1.0], ticks)
plt.tight_layout()

plt.savefig(os.path.join(path, "pic", "AB_free_energy"))
plt.show()
