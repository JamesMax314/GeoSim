# TODO
- [x] Add lighting;
- [ ] Add realistic sky;
- [ ] Have one shader programme for everything in the scene with if statements to controll the rendering algorithm;
- [ ] Restructure classes to allow lights etc to effect model rendering;
- [ ] Make a UI class;
- [ ] Use mesh size when defining the mountains.
## Lighting
- [x] Impliment Phong lighting model;
    - [x] Add ambiant lighting;
    - [x] Add diffuse;
    - [x] Add specular;
- [ ] Add shadows;
- [ ] Add ray marched lighting;
## Realistic sky
- [ ] Use raymarched rayleigh scattering;

## Restructure
- [x] World should do rendering;
- [ ] World stores an array of lighting objects, drawables and a camera;
- [ ] World passes the lighting parameters to the drawable shader along with its own uniforms;

# Alpha 0.1

```Mermaid
classDiagram
    class Drawable {
        -vector Mesh
        -GLuint VBO;
        +void getMesh()
        +void getVertBuff()
        +void addMesh()
    }

    class Light {
        +vec3 lightColour
        +vec3 location
    }

    class Terrain {
        +Terrain(as before)
    }

    Drawable <|-- ThreeDMesh
    Drawable <|-- TwoDMesh
    TwoDMesh <|-- Atmosphere
    ThreeDMesh <|-- PhysicsObj
    ThreeDMesh <|-- Terrain
    ThreeDMesh <|-- Light

    class Window {
        -GLFWwindow* window
        -ShaderManager shaderMan
        -vector<Light> lights
        -vector<Drawable> meshes
        -Camera cam
        +void addLight(&Light)
        +void removeLight(&Light)
        +GLFWwindow* getWindow()
        +void renderFrame()
    }
```
