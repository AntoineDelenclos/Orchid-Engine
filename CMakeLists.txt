cmake_minimum_required(VERSION 3.20)

# vcpkg config
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()
set(VCPKG_TARGET_TRIPLET x64-mingw-static CACHE STRING "")

project(OrchidEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dependances via vcpkg
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)


file(GLOB_RECURSE ENGINE_SOURCES "src/*.cpp")

file(GLOB IMGUI_SOURCES
        "libs/IMGUI/imgui-docking/imgui.cpp"
        "libs/IMGUI/imgui-docking/imgui_demo.cpp"
        "libs/IMGUI/imgui-docking/imgui_draw.cpp"
        "libs/IMGUI/imgui-docking/backends/imgui_impl_glfw.cpp"
        "libs/IMGUI/imgui-docking/backends/imgui_impl_opengl3.cpp"
        "libs/IMGUI/imgui-docking/misc/cpp/imgui_stdlib.cpp"
        "libs/IMGUI/imgui-docking/imgui_tables.cpp"
        "libs/IMGUI/imgui-docking/imgui_widgets.cpp"
)

file(GLOB IMPLOT_SOURCES
        "libs/IMPLOT/implot-master/implot.cpp"
        "libs/IMPLOT/implot-master/implot_items.cpp"
)

add_executable(Orchid
        ${ENGINE_SOURCES}
        ${IMGUI_SOURCES}
        ${IMPLOT_SOURCES}
)

target_include_directories(Orchid PRIVATE
        "include"
        "libs/STB"
        "libs/IMGUI/imgui-docking"
        "libs/IMGUI/imgui-docking/backends"
        "libs/IMPLOT/implot-master"
)

target_link_libraries(Orchid PRIVATE
        OpenGL::GL
        glfw
        GLEW::GLEW
        glm::glm
        assimp::assimp
)

if(MINGW)
    # Bundled MinGW's libwinpthread.a needs __intrinsic_setjmpex, which only
    # exists in libucrt.a (the default link spec pulls in libmsvcrt instead).
    # Must be appended after the implicit -lwinpthread the compiler adds, so
    # it goes on CMAKE_CXX_STANDARD_LIBRARIES (linked last) rather than via
    # target_link_libraries (linked before the implicit libs).
    string(APPEND CMAKE_CXX_STANDARD_LIBRARIES " -lucrt")
endif()

target_compile_definitions(Orchid PRIVATE)