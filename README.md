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

## Build

From the repository root, build the executable using:

```bash
make
```

This Makefile uses `g++` with `-std=c++17`, so it works on machines with a C++17 compiler installed. It is compatible with MSYS2 on Windows and standard Unix-like environments.

## Run

Render the first sample scene with:

```powershell
make example1
```

For the other scenes:

```powershell
make example2
make example3
```

Each command writes a PPM file into `outputs/`:

- `outputs/example1.ppm`
- `outputs/example2.ppm`
- `outputs/example3.ppm`

You can also run a custom file directly:

```powershell
.\raytracer.exe inputs\example2.txt outputs\custom.ppm
```

Or on macOS/Linux:

```bash
./raytracer inputs/example2.txt outputs/custom.ppm
```

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

## Clean

Remove the compiled executable and generated images with:

```bash
make clean
```
