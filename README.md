## Computer Graphics HW8 Q1 - 202011378 차현준

# 🐇 OpenGL Stanford Bunny Renderer

This program renders the Stanford Bunny mesh using OpenGL’s fixed-function pipeline and immediate mode. It performs real-time rendering with per-frame FPS calculation.

---

## ✅ Features

### 1. Mesh Loading

- Loads a `.obj` file (`bunny.obj`) via a custom parser.
- Parses:
  - Vertex positions (`gPositions`)
  - Vertex normals (`gNormals`)
  - Triangle indices (`gTriangles`)
- Assumes `v//vn` format where vertex and normal indices match.

---

### 2. Scene Setup

- Uniformly scales the model by a factor of **20**:
  ```cpp
  glScalef(20.0f, 20.0f, 20.0f);
Translates the model downward and backward:

cpp
glTranslatef(0.0f, -1.0f, -1.0f);
Camera is placed at (0, 0, 5) and looks toward the origin:

cpp
gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
3. Projection
Perspective projection with glFrustum():

cpp
glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 1000);
Viewport size: 1280 × 1280

4. Lighting and Materials
Uses OpenGL fixed-function lighting.

Light:

Direction: (-1, -1, -1, 0)

Diffuse color: (1, 1, 1)

No ambient or specular

Material:

Ambient & Diffuse: (1, 1, 1)

No specular

5. Depth and Rendering
Depth testing enabled.

Backface culling disabled.

Normals are automatically normalized with:

cpp
glEnable(GL_NORMALIZE);
Geometry is rendered using immediate mode (glBegin(GL_TRIANGLES)).

6. FPS Measurement
Uses GL_TIME_ELAPSED query to measure per-frame rendering time.

FPS is computed and displayed in the window title:

yaml
OpenGL Bunny: 59.82 FPS
🔧 Source Files
File	Purpose
main.cpp	Initialization, scene setup, bunny draw logic
frame_timer.cpp	FPS measurement and display() function
load_mesh.cpp	.obj file loader for mesh data
bunny.obj	69,451 triangle Stanford Bunny mesh

🖼️ Result
The bunny is displayed in the center of the window at a proper scale.

Lighting highlights the geometry accurately.

Performance is tracked in real-time via FPS measurement.

