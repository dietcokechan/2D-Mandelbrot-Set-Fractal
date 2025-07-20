# Mandelbrot Set Visualizer

A fast and minimal fractal renderer using **C++** and **SDL2**, showcasing the beauty and complexity of the **Mandelbrot set**.

Built as part of my graphics and math exploration series, this project balances low-level rendering, performance, and visual aesthetics — no frameworks, just raw power and pixels.

## Features

- Renders the Mandelbrot Set in real time  
- Zoom and explore the fractal's infinite detail  
- Clean implementation of complex number math  
- Built using SDL2 and C++, no third-party game engines  
- Organized, beginner-friendly code with comments  

## Demo

![](./resources/192219296-1f72a9c5-d0bc-412d-b6e2-56e4fa76ec34.gif)

## How to Build (MSYS2 on Windows)

Make sure you're using the **ucrt64 shell** in MSYS2.

### Install dependencies:

```bash
pacman -Syu
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-SDL2
```

### Compile:
```bash
g++ main.cpp -o fractal.exe -lSDL2main -lSDL2
```

### Run:
```bash
./fractal.exe
```

## How It Works
The Mandelbrot set is a set of complex numbers c for which the function:

```bash
z = z^2 + c
```
...does not diverge when iterated from z = 0.

Each pixel on the screen maps to a point on the complex plane. The number of iterations before divergence determines the color. Points that do not diverge are inside the Mandelbrot set and are rendered as solid color (usually black).

## Future Improvements
- Mouse controls for zoom and pan
- Dynamic color palettes
- Real-time shader version using OpenGL or DirectX 12
- Julia Set toggle mode

## License
MIT License.
