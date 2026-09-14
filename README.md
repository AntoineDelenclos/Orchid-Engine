# OrchidEngine

Orchid Engine is a 3D engine made in C++/OpenGL.

First time configuration:

Create (if not already done) the following environment variable VCPKG_ROOT which roots to {USER}\vcpkg.
You will have to put your {mingw\bin} path into your PATH
Then, also add {VCPKG_ROOT} to your PATH.

Install the following vcpkg packages for MinGW (static version) via cmd
- vcpkg install glfw3:x64-mingw-static glew:x64-mingw-static glm:x64-mingw-static assimp:x64-mingw-static --host-triplet=x64-mingw-static

Note: the dynamic triplet (x64-mingw-dynamic) fails to build assimp because of a known
upstream issue with poly2tri symbols (see https://github.com/assimp/assimp/issues/5688).
The --host-triplet flag is needed because vcpkg's host tools default to x64-windows (MSVC),
which isn't available when only the MinGW toolchain (e.g. CLion's bundled one) is installed.

Then use CMake with the MinGW toolchain
