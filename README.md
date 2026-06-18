# raytracer

A compact portfolio-quality ray tracer written in modern C++.

## Overview

This project renders configurable sphere scenes into a binary PPM image using a plain-text scene description. The renderer supports:

- camera settings from input
- 24-bit palette colors in `0xRRGGBB` format
- diffuse lighting with hard shadows
- 3x3 supersampling anti-aliasing
- multiple sample scene files in `inputs/`

## Files

- `src/` - source code for the ray tracer
- `Makefile` - build and run commands
- `inputs/` - sample scene files
- `outputs/` - recommended destination for rendered images
 - `outputs/README.txt` - quick notes on viewing and converting generated PPM images

## Build & Run

This project provides both a `Makefile` for Unix-like environments (Linux, macOS, MSYS2) and direct compiler commands for Windows users who do not have `make` installed.

Linux / macOS / MSYS2 (recommended)

Build with:

```bash
make
```

Or compile directly with `g++`:

```bash
g++ -std=c++17 -Wall -O2 -o raytracer src/main.cpp src/sphere.cpp src/world.cpp src/camera.cpp src/vec3.cpp
```

Run a sample (writes into `outputs/`):

```bash
make example1
make example2
make example3
```

Windows (PowerShell / cmd)

If you use MSYS2 / MinGW with `make`, run the same `make` targets inside the MinGW shell. If you don't have `make`, compile and run directly from PowerShell or cmd:

```powershell
g++ -std=c++17 -Wall -O2 -o raytracer.exe src\main.cpp src\sphere.cpp src\world.cpp src\camera.cpp src\vec3.cpp
.\raytracer.exe inputs\example1.txt outputs\example1.ppm
```

If your MinGW installation provides `mingw32-make`, you can run:

```powershell
mingw32-make example1
```

Notes

- `make` simplifies repeated tasks (build, example runs, clean) but is not required to use the project.
- The `Makefile` targets write output PPM files to the `outputs/` folder; use ImageMagick (`magick convert`) or an image viewer that supports PPM to view or convert them.

Performance note

- High-resolution renders (e.g., 1920x1080) are significantly slower because the renderer traces 9 rays per pixel. Estimated total rays = width * height * 9. For 1920x1080 that's ~18.7 million rays. Expect render times of minutes to hours depending on CPU.
- To speed up: compile with `-O3`, reduce samples (change 3x3 sampling to 2x2 in `src/main.cpp`), or add multithreading (OpenMP / std::thread).

## Input format

Each scene file uses this order:

1. `image_width image_height`
2. `viewport_height`
3. `focal_length`
4. `light_x light_y light_z light_brightness`
5. `color_count`
6. `color_hex[0] ... color_hex[n-1]` (use `0xRRGGBB` format)
7. `background_color_index`
8. `sphere_count`
9. sphere definitions:
   `center_x center_y center_z radius color_index`

## Sample scenes

- `inputs/example1.txt` - three spheres over a sky background
- `inputs/example2.txt` - four spheres with a darker blue background
- `inputs/example3.txt` - two spheres with a tall 800x600 render
 - `inputs/example_1920x1080.txt` - HD 1920x1080 example
 - `inputs/example_1280x720.txt` - HD 1280x720 example

## Clean

Remove the compiled executable and generated images with:

```bash
make clean
```
