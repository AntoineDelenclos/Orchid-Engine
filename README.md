# OrchidEngine

Orchid Engine is a game engine made in C++/OpenGL.

ASSIMP doesn't have the build folder. It has to be build locally to have the needed .dll (as in the CMakeLists.txt of Orchid)

For that : 
- Open a terminal and cd to assimp-5.3.1
- Then use : cmake -S . -B build
- And : cmake --build build --config Release (or Debug)

PS : This method to build ASSIMP is not needed if you use vcpkg method below

To run the project :
- cd C:\Users\antoi\CLionProjects\OrchidEngine_CPP
- mkdir build
- cd build
- cmake ..
- cmake --build .

vcpkg packages for MinGW (dynamic version)
- .\vcpkg install glfw3:x64-mingw-dynamic
- .\vcpkg install glew:x64-mingw-dynamic
- .\vcpkg install glm:x64-mingw-dynamic
- .\vcpkg install assimp:x64-mingw-dynamic

Then use CMake with the MinGW toolchain
You will have to put the mingw/bin into your PATH