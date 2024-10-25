import numpy as np
import matplotlib.pyplot as plt

# Define the wave range
wave = np.linspace(380, 780, 1000)

# Define the functions
y1 = 0.398 * np.exp(-1250 * np.power(np.log((wave + 570.1) / 1014), 2)) + 1.132 * np.exp(-234 * np.power(np.log((1338 - wave) / 743.5), 2))
y2 = 1.011 * np.exp(-0.5 * np.power((wave - 556.1) / 46.14, 2))
y3 = 2.060 * np.exp(-32 * np.power(np.log((wave - 265.8) / 180.4), 2))

# Plot the functions
plt.plot(wave, y1, label='Function 1')
plt.plot(wave, y2, label='Function 2')
plt.plot(wave, y3, label='Function 3')

plt.xlabel('Wave')
plt.ylabel('Function Value')
plt.title('Plot of the Functions')
plt.legend()
plt.grid(True)
plt.show()
