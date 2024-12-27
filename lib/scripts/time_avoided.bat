.\build\src\main.exe --threads 12 --rays 1 -metrics --task-size 256 --bounces 5 --max-depth 7 --file-in in/scene_geometries_2.txt --file-out out/avoided/bb_1.ppm
.\build\src\main.exe --threads 12 --rays 2 -metrics --task-size 256 --bounces 5 --max-depth 7 --file-in in/scene_geometries_2.txt --file-out out/avoided/bb_2.ppm
.\build\src\main.exe --threads 12 --rays 4 -metrics --task-size 256 --bounces 5 --max-depth 7 --file-in in/scene_geometries_2.txt --file-out out/avoided/bb_4.ppm
.\build\src\main.exe --threads 12 --rays 8 -metrics --task-size 256 --bounces 5 --max-depth 7 --file-in in/scene_geometries_2.txt --file-out out/avoided/bb_8.ppm
.\build\src\main.exe --threads 12 --rays 16 -metrics --task-size 256 --bounces 5 --max-depth 7 --file-in in/scene_geometries_2.txt --file-out out/avoided/bb_16.ppm
.\build\src\main.exe --threads 12 --rays 32 -metrics --task-size 256 --bounces 5 --max-depth 7 --file-in in/scene_geometries_2.txt --file-out out/avoided/bb_32.ppm