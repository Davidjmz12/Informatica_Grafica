.\build\src\main.exe --threads 8 --rays 2  --task-size 10 --bounces 5 --max-depth 1 --file-in in/scene_convergence_area_light.txt --file-out out/convergence_al/scene_2_2.ppm
.\build\src\main.exe --threads 8 --rays 8  --task-size 10 --bounces 5 --max-depth 1 --file-in in/scene_convergence_area_light.txt --file-out out/convergence_al/scene_2_8.ppm
.\build\src\main.exe --threads 8 --rays 32  --task-size 10 --bounces 5 --max-depth 1 --file-in in/scene_convergence_area_light.txt --file-out out/convergence_al/scene_2_32.ppm
.\build\src\main.exe --threads 8 --rays 128  --task-size 10 --bounces 5 --max-depth 1 --file-in in/scene_convergence_area_light.txt --file-out out/convergence_al/scene_2_128.ppm
.\build\src\main.exe --threads 8 --rays 512  --task-size 10 --bounces 5 --max-depth 1 --file-in in/scene_convergence_area_light.txt --file-out out/convergence_al/scene_2_512.ppm