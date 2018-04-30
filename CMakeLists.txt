
cmake_minimum_required( VERSION 3.5 )

add_compile_options( -Wall -Wextra -Wpedantic )

add_executable( 
  quadtree 
  src/main.cpp 
  src/Printable.cpp
  src/Coordinate.cpp
  src/BoundaryBox.cpp
  src/Node.cpp
  src/Data.cpp
  src/QuadTree.cpp
)