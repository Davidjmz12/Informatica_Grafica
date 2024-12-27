import matplotlib.pyplot as plt

data = {"THREADS": [1,2,4,8,16,32], "TIME": [35.60, 21.41, 13.84, 11.27, 8.37, 8.24]}

fig, (ax1) = plt.subplots(1, 1)

# Plot Mean
ax1.plot(data["THREADS"], data["TIME"], marker='o', linestyle='-', color='b')
ax1.set_title('Execution time vs number of threads')
ax1.set_xlabel('THREADS')
ax1.set_ylabel('TIME (s)')
ax1.grid(True)

plt.tight_layout()
plt.show()