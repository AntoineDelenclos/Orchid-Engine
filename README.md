# OrchidEngine

Orchid Engine is a game engine made in C++/OpenGL.

ASSIMP doesn't have the build folder. It has to be build locally to have the needed .dll (as in the CMakeLists.txt of Orchid)

For that : 
- Open a terminal and cd to assimp-5.3.1
- Then use : cmake -S . -B build
- And : cmake --build build --config Release (or Debug)


To run the project :
- cd C:\Users\antoi\CLionProjects\OrchidEngine_CPP
- mkdir build
- cd build
- cmake ..
- cmake --build .