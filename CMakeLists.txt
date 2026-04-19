cmake_minimum_required(VERSION 3.10)

project(Labyrinthe
  VERSION 0.1.0
  LANGUAGES CXX C
)

include(GNUInstallDirs)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)


file(GLOB SPNG "Src/spng/*.c")

file(GLOB LABY "Src/Laby/*.c")

file(GLOB LABY3D "Src/Laby3D/*.cpp")

file(GLOB COMPO "Src/Components/*.cpp")

file(GLOB MATHS "Src/GlOOPLib/Maths/*.cpp")

file(GLOB DISPLAY "Src/GlOOPLib/Display/*.cpp")

file(GLOB OBJECTS "Src/GlOOPLib/Objects/*.cpp")

file(GLOB PHYSICS "Src/GlOOPLib/Physics/*.cpp")

file(GLOB SCENES "Src/GlOOPLib/Scenes/*.cpp")

file(GLOB TEXTURES "Src/GlOOPLib/Textures/*.cpp")

file(GLOB GUI "Src/GlOOPLib/GUI/*.cpp")

file(GLOB PROPMAN "Src/GlOOPLib/PropertyManager/*")

add_executable(Labyrinthe
  Src/Labyrinthe.cpp
  Src/GlOOPLib/Maths/Vector.cpp
  Src/GlOOPLib/Objects/Entity3D.h
  Src/GlOOPLib/Objects/Object3D.cpp
  Src/GlOOPLib/Scenes/Scenes.cpp
  Src/GlOOPLib/Lights/Lights.h
  Src/GlOOPLib/Lights/Colors.h
  Src/GlOOPLib/GUI/GUI.h

  ${PHYSICS}

  ${OBJECTS}

  ${DISPLAY}

  ${SCENES}

  ${TEXTURES}

  ${MATHS}

  ${LABY}

  ${LABY3D}

  ${SPNG}

  ${COMPO}

  ${GUI}
  
  ${PROPMAN}
)

add_dependencies(Labyrinthe
  OpenGL::OpenGL
  GLUT::GLUT
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
    OpenGL::GLU

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
