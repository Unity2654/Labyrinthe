cmake_minimum_required(VERSION 3.10)

project(Labyrinthe
  VERSION 0.1.0
  LANGUAGES CXX C
)

include(GNUInstallDirs)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

file(GLOB SPNG "spng/*.c")

add_executable(Labyrinthe
  Src/IGTemplate.cpp
  Src/GlOOPLib/Maths/Vector.cpp
  Src/GlOOPLib/Objects/Entity3D.h
  Src/GlOOPLib/Objects/Object3D.cpp
  Src/GlOOPLib/Scenes/Scenes.cpp
  Src/GlOOPLib/Lights/Lights.h
  Src/GlOOPLib/Lights/Colors.h

  ${SPNG}
)

add_dependencies(Labyrinthe
  OpenGL::OpenGL
)

target_include_directories(Labyrinthe
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Src"
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(Labyrinthe
  PRIVATE
    OpenGL::OpenGL
    GLUT::GLUT
)

target_compile_options(Labyrinthe
  PRIVATE
    "-Wall"
)


set_target_properties(Labyrinthe
  PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
)
