import matplotlib.pyplot as plt

# Data from MSE_RESULTS_SCENE1.TXT
data = {"SPP": [], "MEAN": [], "STD": []}
with open('assets/out/results/laplace_results_scene1.txt', 'r') as file:
    next(file)  # Skip the header
    for line in file:
        spp, mean,std = line.strip().split(',')
        data["SPP"].append(int(spp))
        data["MEAN"].append(float(mean))
        data["STD"].append(float(std))

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(10, 8))

# Plot Mean
ax1.plot(data["SPP"], data["MEAN"], marker='o', linestyle='-', color='b')
ax1.set_title('Mean vs SPP')
ax1.set_xlabel('SPP')
ax1.set_ylabel('Mean')
ax1.grid(True)

# Plot STD
ax2.plot(data["SPP"], data["STD"], marker='o', linestyle='-', color='r')
ax2.set_title('STD vs SPP')
ax2.set_xlabel('SPP')
ax2.set_ylabel('STD')
ax2.grid(True)

plt.tight_layout()
plt.show()