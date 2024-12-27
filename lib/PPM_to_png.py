import os
import sys
from PIL import Image

def ppm_to_png(file_path):
    img = Image.open(file_path)
    png_file_path = file_path.rsplit('.', 1)[0] + '.png'
    img.save(png_file_path, 'PNG')

def convert_directory(directory_path):
    for file_name in os.listdir(directory_path):
        if file_name.endswith('.ppm'):
            file_path = os.path.join(directory_path, file_name)
            ppm_to_png(file_path)

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Usage: python PPM_to_png.py <directory_path>")
    else:
        directory_path = sys.argv[1]
        convert_directory(directory_path)