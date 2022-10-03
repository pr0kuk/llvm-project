# llvm-project Lloyd Relaxation
# Requirements
* GCC 9.3.0 *or newer*
* CMAKE 3.16.3 *or newer*
* CLANG 10.0.0 *or newer*
* LLVM 10.0.0 *or newer*
* FREEGLUTD 3.0.0 *or newer*
* OPENGL 3.0 *or newer*
# Description
## Algorithm Description
A canvas of points with the size `HEIGHT x WIDTH` is initialized. Then the coordinates of the `NUMBER_OF_POINTS` points - centers of Voronoi cells are randomly generated. After that, a Voronoi diagram is constructed for each frame and the Voronoi centers are shifted to the mass centers of its cells. After some time, the diagrams converge and the rendering of new frames is suspended.
## Files Description
`logic.cpp` - main() and logic functions  
`graphic.cpp` - OpenGL (freeglut) functions  
`logloop.cpp` - general loop based on while()  
`glutloop.cpp` - general loop based on glutMainLoop()  
`point.cpp` - methods of Point class  
`point.hpp` - description of Point class  
`libs.hpp` - list of includes and defines
# Build
## Unix
    cmake ./
    make
## Windows
    cmake .
    cmake --build .
### Remark
Sometimes for Windows it is better to compile manually by:

    g++ logic.cpp graphic.cpp point.cpp logloop.cpp -o build/launcher.exe -lfreeglutd -lopengl32
## CMake options
`glut` = 1 - using glutloop.cpp *(default value)* 
`glut` = 0 - using logloop.cpp  

example:  

    cmake . -Dglut=0
    cmake --build .
# Run
    build/launcher

## Control keys
* `ESC` - exit program
* `SPACE` - pause/resume rendering
* `R` - reset Voronoi diagram