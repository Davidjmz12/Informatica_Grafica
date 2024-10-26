import colour
import math
import numpy as np
from colour import SpectralDistribution

wavelengths = list(range(380,781,10))
values = np.zeros_like(wavelengths)      # Initialize all wavelengths to 0


# Assign higher values in the red range
for i, wl in enumerate(wavelengths):
    if 620 <= wl <= 750:
        values[i] = 100.0  # You can adjust this to represent intensity

# Create the SpectralDistribution for red
red_spectral = SpectralDistribution(domain=wavelengths, data=values)

XYZ = colour.sd_to_XYZ(red_spectral)
RGB = colour.XYZ_to_sRGB(XYZ)

print(XYZ)
print(RGB)