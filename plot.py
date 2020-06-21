import os
import numpy as np
import matplotlib.pyplot as plt
from decimal import Decimal

linkrate = [0.01, 0.06, 0.11, 0.16, 0.21, 0.26, 0.31, 0.36, 0.41, 0.46, 0.51, 0.53, 0.55]
latency = [18.76, 18.78, 19.14, 19.67, 20.48, 21.56, 22.43, 23.70, 25.92, 28.39, 32.40, 33.83, 61.21]
traffic = [0.01, 0.06, 0.11, 0.16, 0.21, 0.26, 0.31, 0.36, 0.41, 0.46, 0.51, 0.53, 0.30]
# plt.plot(linkrate, latency)
# plt.ylabel("Average packet delay (cycles)")
# plt.xlabel("Packet injection rate [packet/cycle/node]")
# plt.show()

plt.plot(linkrate, traffic)
plt.ylabel("Throughput [flits/cycle/node]")
plt.xlabel("Packet injection rate [packet/cycle/node]")
plt.show()