cmake_minimum_required(VERSION 3.13)

#Project setup
project(Orchid)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)

# Désactiver les warnings comme erreurs pour les dépendances externes
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=dangling-reference")
elseif(MSVC)
    # For MSVC, disable the dangling reference warning (C4172)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4172")
endif()

#Subdirectories for libraries that use CMakeLists.txt on their own
add_subdirectory("libs/ASSIMP/assimp-5.3.1")
#add_subdirectory("libs/GLM/glm-0.9.9.8/glm")

message(STATUS "path du repertoire actuel : ${CMAKE_CURRENT_SOURCE_DIR}")

# Pour GLM - approche alternative
set(GLM_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libs/GLM/glm-0.9.9.8")
if(EXISTS "${GLM_PATH}")
    message(STATUS "GLM found at: ${GLM_PATH}")
else()
    message(WARNING "GLM not found at: ${GLM_PATH}")
endif()

#Executable
add_executable(Orchid "src/main.cpp")

#Include all the .cpp files in src and subdirectories and all these sources to the target
file(GLOB_RECURSE SOURCES "src/*.cpp")
target_sources(Orchid PRIVATE ${SOURCES})

#Libraries that required .cpp to be compiled
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
target_sources(Orchid PRIVATE ${IMGUI_SOURCES})
target_sources(Orchid PRIVATE ${IMPLOT_SOURCES})

#Include directories
target_include_directories(Orchid SYSTEM
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include/" #My custom headers
#        "${CMAKE_CURRENT_SOURCE_DIR}/libs/ASSIMP/assimp-5.3.1/include" #ASSIMP headers
        "${CMAKE_CURRENT_SOURCE_DIR}/libs/GLEW/glew-2.1.0-win32/glew-2.1.0/include/" #GLEW headers
        "${CMAKE_CURRENT_SOURCE_DIR}/libs/GLFW/glfw-3.3.8.bin.WIN64/glfw-3.3.8.bin.WIN64/include/" #GLFW headers
        "${CMAKE_CURRENT_SOURCE_DIR}/libs/GLM/glm-0.9.9.8/glm/glm" #GLM headers
        "${CMAKE_CURRENT_SOURCE_DIR}/libs/IMGUI/imgui-docking" #IMGUI headers (docking branch only, some imgui files include other and need the direct file name)
        "${CMAKE_CURRENT_SOURCE_DIR}/libs/IMGUI/imgui-docking/backends" #IMGUI backends
#        "${CMAKE_CURRENT_SOURCE_DIR}/libs/IMPLOT" #IMPLOT headers
        "${CMAKE_CURRENT_SOURCE_DIR}/libs/IMPLOT/implot-master" #IMPLOT headers
        "${CMAKE_CURRENT_SOURCE_DIR}/libs/STB" #STB headers
)

#Pour les includes systèmes (qui utilisent les <>)
target_include_directories(Orchid SYSTEM
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/libs/IMGUI/imgui-docking"
)

#Link libraries
target_link_libraries(Orchid
    PRIVATE
#        "${CMAKE_CURRENT_SOURCE_DIR}/libs/ASSIMP/assimp-5.3.1/lib/Debug/assimp-vc143-mtd.lib" #ASSIMP test
        assimp #ASSIMP
        "${CMAKE_CURRENT_SOURCE_DIR}/libs/GLEW/glew-2.1.0-win32/glew-2.1.0/lib/Release/x64/glew32s.lib" #GLEW
        "${CMAKE_CURRENT_SOURCE_DIR}/libs/GLFW/glfw-3.3.8.bin.WIN64/glfw-3.3.8.bin.WIN64/lib-vc2022/glfw3.lib" #GLFW
        opengl32 #OpenGL
)
target_compile_definitions(Orchid PRIVATE GLEW_STATIC) #Linking GLEW in static way (no .dll) as the program will be slightly faster

#This will link the assimp .dll during the build of the executable
add_custom_command(TARGET Orchid POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        #Depending if it's x64-Debug or x64-Release, it builds with the corresponding .dll
        "$<IF:$<CONFIG:Debug>,${CMAKE_CURRENT_SOURCE_DIR}/libs/ASSIMP/assimp-5.3.1/build/bin/Debug/assimp-vc143-mtd.dll,${CMAKE_CURRENT_SOURCE_DIR}/libs/ASSIMP/assimp-5.3.1/build/bin/Release/assimp-vc143-mt.dll>"
        "$<TARGET_FILE_DIR:Orchid>"
)