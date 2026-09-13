# OrchidEngine

Orchid Engine is a game engine made in C++/OpenGL.

First time configuration:

Create (if not already done) the following environment variable VCPKG_ROOT which roots to {USER}\vcpkg.
Then, also add {VCPKG_ROOT} to your PATH.

Install the following vcpkg packages for MinGW (dynamic version) via cmd
- vcpkg install glfw3:x64-mingw-dynamic
- vcpkg install glew:x64-mingw-dynamic
- vcpkg install glm:x64-mingw-dynamic
- vcpkg install assimp:x64-mingw-dynamic

Then use CMake with the MinGW toolchain
You will have to put your {mingw\bin} path into your PATH
