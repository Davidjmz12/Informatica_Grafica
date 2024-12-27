from PIL import Image
import numpy as np
import cv2
def compute_mse(ppm_path1, ppm_path2):
    # Open the images
    img1 = Image.open(ppm_path1)
    img2 = Image.open(ppm_path2)
    
    # Convert images to numpy arrays
    arr1 = np.array(img1)
    arr2 = np.array(img2)
    
    # Ensure the images have the same dimensions
    if arr1.shape != arr2.shape:
        raise ValueError("Images must have the same dimensions")
    
    # Compute the Mean Squared Error
    mse = np.mean((arr1 - arr2) ** 2)
    
    return mse

def apply_laplace_and_compute_stats(ppm_path, output_png_path):

    # Open the image
    img = Image.open(ppm_path)
    
    # Convert image to grayscale
    img_gray = img.convert('L')
    
    # Convert image to numpy array
    arr = np.array(img_gray)
    
    # Apply Laplace kernel
    laplacian = cv2.Laplacian(arr, cv2.CV_64F)
    
    # Normalize the Laplacian image
    laplace_arr = cv2.normalize(laplacian, None, 0, 255, cv2.NORM_MINMAX)
    laplace_arr = laplace_arr.astype(np.uint8)
    
    # Save the image as PNG
    Image.fromarray(laplace_arr).save(output_png_path)
    
    # Compute mean luminance and standard deviation
    mean_luminance = np.mean(laplace_arr)
    std_deviation = np.std(laplace_arr)
    
    return mean_luminance, std_deviation

def compute_mse_images(ppm_paths, comparison_png_path, output_file):
    with open(output_file, "w") as f:
        f.write("SPP, MSE\n")
        for (ppm_path,spp) in ppm_paths:
            mse = compute_mse(ppm_path, comparison_png_path)
            f.write(f"{spp}, {mse}\n")

def compute_laplace_images(ppm_paths, ppm_output_paths, output_file):
    with open(output_file, "w") as f:
        f.write("SPP, Mean Luminance, Standard Deviation\n")
        for (ppm_path, ppm_output_path, spp) in zip(ppm_paths, ppm_output_paths, [2,8,32,128,512]):
            mean_luminance, std_deviation = apply_laplace_and_compute_stats(ppm_path, ppm_output_path)
            f.write(f"{spp}, {mean_luminance}, {std_deviation}\n")

if __name__ == '__main__':
    compute_mse_images([(f"assets/out/scenes_spp_2/scene_spp_{i}.ppm", i) for i in [2,8,32,128, 512]], 
    "assets/out/scenes_spp_2/scene_spp_512.png", 
    "assets/out/results/mse_results_scene1.txt")
    compute_laplace_images([f"assets/out/scenes_spp_2/scene_spp_{i}.ppm" for i in [2,8,32,128, 512]],
    [f"assets/out/results/scene_spp_{i}_laplace.png" for i in [2,8,32,128, 512]],
    "assets/out/results/laplace_results_scene1.txt")