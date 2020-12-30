# Particle Simulations 

Simple application developed to utilise Cinder: (https://github.com/cinder/Cinder)

## Usage
Spawn particles with the right click button on your mouse and set up a gravity sink with the left click, particles will collide and lose energy. When they collide they tend to stick together.

Collision detection utilises quadtrees for efficent spatial partioning and collision identification.


## Compilation
If you edited the source code and want to recompile then simply open up the folder and type
```bash
sh build.sh
```
Note that the application is built on top of libcinder and installation instructions for libcinder can be found at the github link provided.

## Usage
A binary is provided and can be executed through:
```
./out/app
```
Alternatively if you compiled the application yourself then the binary will be outputted to: `build/Debug/Debug`
