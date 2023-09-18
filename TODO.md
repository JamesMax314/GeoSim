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
- [ ] World should do rendering;
- [ ] World stores an array of lighting objects, drawables and a camera;
- [ ] World passes the lighting parameters to the drawable shader along with its own uniforms;
