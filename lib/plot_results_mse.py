import matplotlib.pyplot as plt

# Data from MSE_RESULTS_SCENE1.TXT
data = {"SPP": [], "MSE": []}
with open('assets/out/results/mse_results_scene1.txt', 'r') as file:
    next(file)  # Skip the header
    for line in file:
        spp, mse = line.strip().split(',')
        data["SPP"].append(int(spp))
        data["MSE"].append(float(mse))
    
# Plotting the data
plt.figure(figsize=(10, 6))
plt.plot(data["SPP"], data["MSE"], marker='o', linestyle='-', color='b')

# Adding titles and labels
plt.title('MSE vs SPP')
plt.xlabel('Samples Per Pixel (SPP)')
plt.ylabel('Mean Squared Error (MSE)')
plt.grid(True)

# Show the plot
plt.show()