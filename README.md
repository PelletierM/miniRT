# miniRT (Ray Tracer)

miniRT is a basic ray tracing application coded in C which is capable of rendering spheres, cylinders, planes and triangles. It can handle various material properties such as specular and diffuse reflections, emissivity and texture maps. It also includes a camera system that replicates some of the behaviour of a real camera, allowing the user to control aperture (affecting camera blur), focal length (zoom) and exposure.

Rendering is done on the CPU, using multiple threads to increase render speeds. The application lets you move around the scene using different keybindings and also allows the selection of objects to move / scale them. As the user remains stationary, more and more samples accumulate to increase the render's quality.

**Contributors**
Emmanuel Guefif - https://github.com/eguefif
Maxime Pelletier - https://github.com/PelletierM

**Skills involved**
Linear algebra
Geometrical optics
Teamwork and communication

**Sample render**
![Sample render](https://github.com/PelletierM/miniRT/blob/master/scenes/renders/spheres.png?raw=true)
Other render samples: https://github.com/PelletierM/miniRT/blob/master/scenes/renders/
