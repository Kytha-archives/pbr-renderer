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
- Super basic directional lighting (ambient and diffuse) ✔️
- A PBR compliant material system capable of loading in albedo, normal, metallic, & roughness textures 🚧
- PBR pipeline & shader programs 🚧

**Advanced Features (time permitting)**

- Load in HDR images to create environment cubemaps for IBL 🛑
- Ambient occlusion 🛑
- GUI for basic scene manipulation renderer setting controls ✔️
- Shadow Mapping 🛑
- Tone Mapping for true HDR 🛑
- Gamma Correction 🛑

An additional goal (time permitting) would be to benchmark the performance of different
BDRF implementations, i.e, alternative normal distribution functions, geometry functions, etc. So, an ideal feature would be for the user to be able to hot swap different implementations during runtime.

# Internal Dependencies

This is a list of all dependancies which are internal to the source code. You don't need to install any packages for these dependencies, since I have included the source code and wrote platform agnostic makefiles to compile.

## [GLM](https://github.com/g-truc/glm) - Header only C++ mathematics

An objective of this project is to achieve high performance rendering HD assets. A large bottleneck for performance will be the efficiency of our calculations, particularly floating point operations. I could roll my own math library similar to the exercise in assignment 1. However doing this would significantly impacted performance since it would not be utilizing SIMD (single instruction, multiple data) parallel processing. GLM offers OpenGL Shader Language compliant SIMD mathematics for blazing fast computations.

## [GLAD](https://glad.dav1d.de/) - Multi-Language GL/GLES/EGL/GLX/WGL Loader-Generator

This project is built using modern OpenGL (shader-based rendering). Most platforms do not provide OpenGL libraries to link against. For example windows OpenGL library libopengl32 only supports OpenGL up to version 2.x. Therefore it is necessary to use a wrangler like GLAD to obtain the function pointers and macros for the Modern OpenGL code implemented by graphics card manufacturers.

## [imgui](https://github.com/ocornut/imgui) - Immediate-mode, bloat-free GUI

The purpose of this project is to showcase the results of physically based rendering techniques. Spending time rolling my own GUI library would only be counter productive to this purpose. It is better to not reinvent the wheel and take advantage of this open-sourced MIT licensed GUI library so I can spend more time perfecting the graphics pipeline.

# External Dependancies

This is a list of dependancies which are external to the codebase. **You will need to install these packages in order to build this project**. I've included the bash commands for Windows, Ubuntu, and Debian platforms below. These packages are external because they interface with platform-specific APIs and thus have platform-specific dependencies themselves.

## [GLFW](https://github.com/glfw/glfw) - Open Source, multi-platform library for OpenGL

GLFW is a modern library suited for modern OpenGL. GLFW offers much finer control over context creation and window attributes. FreeGLUT necessitates an inversion of control to handle it's event loop, whereas GLFW allows for us to define our own event loop; leading to more precise timing and lower latency.

### Installing GLFW

_Windows MSYS2_

```bash
pacman -S mingw-w64-x86_64-glfw
```

_Linux_

```bash
sudo apt-get install libglfw3
sudo apt-get install libglfw3-dev
```

## [ASSIMP](https://github.com/assimp/assimp) - Open Asset Import Library

High quality, HD models and meshes will be required to truly test the performance of this renderer and showcase it's capabilities. ASSIMP can import a wide range of mesh file formats, normalize them into a standard internal format for us to process for rendering.

### Installing ASSIMP

_Windows MSYS2_

```bash
pacman -S mingw-w64-x86_64-assimp
```

_Linux_

```bash
sudo apt-get install assimp
```

# Build

run `make debug` to build the project in debug mode, or run `make`/`make production` to build the project in production mode. The build artifacts will be in the `build` directory.

Note: The first build will take longer because the dependencies need to be compiled. Subsequent builds will not take as long.

⚠️ I did my development on Windows. I've tested compiling and linking on Linux so their shouldn't be any problems  
to that effect in a linux environment. However depending on your setup, there is a possibility that the shaders I have written are not compatible with your version of OpenGL. If this is a the case (the model of Emperor Trajan does not appear) consider switching to a windows environment. Hopefully this issue will be fixed soon.

# Architecture

The codebase is quite large and very flat, which does not help convey the relationships between objects and the system they create. This section is intended to help convey the system as a whole and explain the "how" of the engine. The next section- "Design Designs", focuses more on the "why".

## Application System Relational Diagram

This diagram shows the general structure of the main components in the application flow. The Application is a singleton object, so it can only be instantiated once, and by doing so creates and owns a member Window. The Application also houses the main event loop where each layer in the layer stack is sequentially updated/rendered to the window.

The window object handles the OpenGL context, amongst other window properties (width, height, vsync, etc). This is where the engine interfaces with GLFW and GLAD to load in an OpenGL 4 context. By setting up callback functions, GLFW events are routed into the application where they are dispatched to the layer stack and polled by the input system.

Each layer has the ability to poll inputs, update game/application logic, and render scenes via the Renderer. The Renderer is another singleton which any layer can interface with. A layer can upload an environment to the renderer (camera, lights, etc) and then submit any models to be rendered.

The Renderer also houses a library of shaders. These shaders get loaded, compiled, and linked at the beginning of run-time and are avalible for use by other modules.

This is a general overview. More granular explanations can be found in the comments documenting the code.

![image](https://user-images.githubusercontent.com/33584092/141251749-74959b11-774a-4e18-baad-570fdcb0307e.png)

## Model & Material System Relational Diagram

The diagram below depicts the architecture of the model / mesh / material system.

![image](https://user-images.githubusercontent.com/33584092/141251215-83b1e876-6381-4b3e-98cd-393ec0a3963f.png)

There are quite a few parts to this system. When instantiated, the model object will load in a assimp scene from a file on disk. It then processes this into multiple meshes. All vertex data for each mesh is processed into a vertex buffer with an opinionated layout. At the minimum, the mesh must specify position and normal data for each vertex. The vertex buffer layout also accommodates for tangent, binormal, and texture coordinate data. The indices are also processed into an index buffer. These buffers are grouped together to form a vertex array. In addition, Each mesh is capable of having it's own material (in future these materials would be in a shared library owned by the Model). Each material will be capable of storing multiple texture maps (albedo, normal, metallic, roughness).

The structure for the renderer was explained in the previous section, but this diagram demonstrates how the renderer relates to the model system.

## End-to-end Renderer Pipeline

This diagram show's the end-to-end process of rendering a model, from program start-up, to the first frame rendering. This is a general overview of how models are loaded and rendered.
![image](https://user-images.githubusercontent.com/33584092/141259777-33f69470-b0da-4692-a851-5210aafcd11f.png)
