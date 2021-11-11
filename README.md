# About

A lightweight implementation of a physically based shading model for an OpenGL renderer derived from models outlined by Walt Disney’s Animation Studio in 2012 and Unreal Engine 4 in 2013. The main goal of this project is to explore widely adopted, modern rendering techniques for realistic graphics. The ideal features of the project are outlined below.

✔️ - Completed

🚧 - In progress

🛑 - Yet to be implemented

**Basic Features**

- Layer and Overlay System ✔️
- OpenGL primitive abstraction ✔️
- Basic Camera controls ✔️
- Event loop for user input, window events (resize, etc), and application events (Update, etc) ✔️ 
- Load from disk obj/blend files containing mesh data ✔️
- GLSL fragment and vertex shader compilation, linking, and execution ✔️
- A PBR compliant material system capable of loading in albedo, normal, metallic, & roughness textures 🚧
- PBR rendering Pipeline 🚧

**Advanced Features (time permitting)**

- Load in HDR images to create environment cubemaps for IBL 🛑
- Ambient occlusion 🛑
- GUI for basic scene manipulation renderer setting controls ✔️
- Shadow Mapping 🛑
- Tone Mapping for ture HDR 🛑
- Gamma Correction 🛑

An additional goal (time permitting) would be to benchmark the performance of different
BDRF implementations, i.e, alternative normal distribution functions, geometry functions, etc. So, an ideal feature would be for the user to be able to hot swap different implementations during runtime.

# Internal Dependencies

This is a list of all dependancies which are internal to the source code. You don't need to install any packages for these dependencies, since I have included the source code and wrote platform agnostic makefiles to compile. 

## [GLFW](https://github.com/glfw/glfw) - Open Source, multi-platform library for OpenGL

GLFW is a modern library suited for modern OpenGL. GLFW offers much finer control over context creation and window attributes. FreeGLUT necessitates an inversion of control to handle it's event loop, whereas GLFW allows for us to define our own event loop; leading to more precise timing and lower latency.

## [GLM](https://github.com/g-truc/glm) - Header only C++ mathematics

An objective of this project is to achieve high performance rendering HD assets. A large bottleneck for performance will be the efficiency of our calculations, particularly floating point operations. I could roll my own math library similar to the exercise in assignment 1. However doing this would significantly impacted performance since it would not be utilizing SIMD (single instruction, multiple data) parallel processing. GLM offers OpenGL Shader Language compliant SIMD mathematics for blazing fast computations.


## [GLAD](https://glad.dav1d.de/) - Multi-Language GL/GLES/EGL/GLX/WGL Loader-Generator

This project is built using modern OpenGL (shader-based rendering). Most platforms do not provide OpenGL libraries to link against. For example windows OpenGL library libopengl32 only supports OpenGL up to version 2.x. Therefore it is necessary to use a wrangler like GLAD to obtain the function pointers and macros for the Modern OpenGL code implemented by graphics card manufacturers.

## [imgui](https://github.com/ocornut/imgui) - Immediate-mode, bloat-free GUI

The purpose of this project is to showcase the results of physically based rendering techniques. Spending time rolling my own GUI library would only be counter productive to this purpose. It is better to not reinvent the wheel and take advantage of this open-sourced MIT licensed GUI library so I can spend more time perfecting the graphics pipeline.

# External Dependancies 

This is a list of dependancies which are external to the codebase. **You will need to install these packages in order to build this project**. I've included the bash commands for Windows, Ubuntu, and Debian platforms below. These packages are external due to their complexity and size.

## [ASSIMP](https://github.com/assimp/assimp) - Open Asset Import Library

High quality, HD models and meshes will be required to truly test the performance of this renderer and showcase it's capabilities. ASSIMP can import a wide range of mesh file formats, normalize them into a standard internal format for us to process for rendering.

### Installing ASSIMP

*Windows MSYS2* 
```bash
pacman -S mingw-w64-x86_64-assimp
```
*Debian*
```bash
pacman -S assimp
```
*Ubuntu*
```bash
sudo apt-get install assimp
```

# Build

run `make debug` to build the project in debug mode, or run `make`/`make production` to build the project in production mode. The build artifacts will be in the `build` directory.
