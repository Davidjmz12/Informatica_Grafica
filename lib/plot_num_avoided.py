import matplotlib.pyplot as plt

# Data from MSE_RESULTS_SCENE1.TXT
data = {"SPP": [1,2,4,8,16,32], "TIME_BB": [8.95, 16.71, 37.54, 104.171, 227.84, 365.98], "TIME": [140.60, 350, None, None, None, None]}
data_avoided = {"SPP": [1,2,4,8,16,32], "AVOIDED": [1681324, 3359505, 6709860, 13429322, 26915477, 53718018]}

fig, (ax1, ax2) = plt.subplots(1, 2)

# Plot Mean
ax1.plot(data["SPP"], data["TIME_BB"], marker='o', linestyle='-', color='b', label='With BB')
ax1.plot(data["SPP"], data["TIME"], marker='o', linestyle='-', color='g', label='Without BB')
ax1.set_title('Execution time with and without bounding box')
ax1.set_xlabel('SPP')
ax1.set_ylabel('TIME (s)')
ax1.grid(True)
ax1.legend()

# Plot STD
ax2.plot(data_avoided["SPP"], data_avoided["AVOIDED"], marker='o', linestyle='-', color='r')
ax2.set_title('Number of avoided intersections')
ax2.set_xlabel('SPP')
ax2.set_ylabel('AVOIDED')
ax2.grid(True)

plt.tight_layout()
plt.show()