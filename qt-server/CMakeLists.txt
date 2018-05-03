
cmake_minimum_required( VERSION 3.5 )

add_compile_options( -Wall -Wextra -Wpedantic -std=c++0x )

add_executable( 
  quadtree 
  src/main.cpp 
  src/QuadTree/Coordinate.cpp
  src/QuadTree/BoundaryBox.cpp
  src/QuadTree/Node.cpp
  src/QuadTree/Data.cpp
  src/QuadTree/QuadTree.cpp
  src/QuadTree/Renderer.cpp
  src/Misc/Printable.cpp
  src/Server/Server.cpp
  src/QTServerHandler.cpp
)