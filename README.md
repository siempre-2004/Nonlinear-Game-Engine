# 🌀 Nonlinear Game Engine (NGE)

**Course:** Real-Time Graphics Programming for Games (7.5 credits)  
**University:** Uppsala University, Sweden  
**Instructor:** Mikael Fridénfalk  
**Student Implementation:** Zhehan Hu  
**Language:** C++ / OpenGL  

---

## 🎮 Overview
The **Nonlinear Game Engine (NGE)** is an educational real-time rendering framework **designed and developed by Mikael Fridénfalk**.  
This project represents my **student implementation and practice exercises** within the NGE framework during the *Real-Time Graphics Programming for Games* course.  
I implemented and extended several modules to explore advanced 3D rendering techniques such as **frustum culling**, **procedural generation**, and **primitive rendering**.

---

## 🧩 Implemented Modules

### 🔷 Frustum.cpp – View Frustum Culling
Implemented the geometric computation and visibility tests for the camera frustum.
- Converts screen to world coordinates using `gluUnProject`  
- Evaluates near/far plane normals  
- Implements `Frustum_CullObj()` for bounding-sphere culling  
- Visualizes frustum planes and test spheres

### 🔶 Prim.cpp – Primitive Renderer & Collision Physics
Handles primitive geometry and transparency sorting.
- Adds and renders quads/triangles with texture and color data  
- Implements **sphere–triangle collision** for simple physics response  
- Sorts transparent primitives using `std::sort`  
- Visualizes normals and primitive centers

### 🟢 Lsys.cpp – L-System Procedural Generation
Implements recursive 3D growth patterns using transformations.
- Recursive `FX3()` / `FX4()` functions for branching structures  
- Uses `Pitch`, `Yaw`, `Roll` rotations to simulate spatial growth  
- Integrates with the primitive system for rendering nodes and cylinders

---

## ⚙️ Technical Highlights
- Custom 3D math utilities (dot, cross, normalize, distance)  
- OpenGL fixed-pipeline rendering with lighting and blending  
- Frustum culling for rendering optimization  
- STL-based transparent sorting for alpha blending  
- Recursive L-System generation integrated in real-time graphics  

---

## 🧠 Learning Focus
- Understanding low-level graphics pipeline and 3D transformations  
- Implementing real-time frustum culling and procedural models  
- Integrating collision physics with rendering  
- Practicing clean C++ structure and memory-safe design  

---

## 🖥️ Environment
- **Language:** C++ (`/std:c++latest`)  
- **Graphics API:** OpenGL / GLU  
- **IDE:** Visual Studio 2022 / CLion  
- **Platform:**

