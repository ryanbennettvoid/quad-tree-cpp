
#include <iostream>
#include <string>

#include "./Coordinate.h"
#include "./BoundaryBox.h"
#include "./Node.h"
#include "./Data.h"
#include "./QuadTree.h"

const int WORLD_SIZE = 1000;

int main() {

  Coordinate worldCenter = Coordinate( 5, 3 );
  std::cout << "created worldCenter: " << worldCenter.toString() << std::endl;

  BoundaryBox worldBounds = BoundaryBox( worldCenter, WORLD_SIZE/2 );
  std::cout << "created worldBounds: " << worldBounds.toString() << std::endl;
  
  QuadTree qt = QuadTree( worldBounds );
  std::cout << "create qt: " << qt.toString() << std::endl;

  for ( int i = 0; i < 15; i++ ) {

    double randX = ( double )( rand() % WORLD_SIZE ) * 0.9;
    double randY = ( double )( rand() % WORLD_SIZE ) * 0.9;
    
    Coordinate nodeOrigin = Coordinate( randX, randY );
    Data nodeData = Data();
    Node node = Node( nodeOrigin, nodeData );
    std::cout << "created node: " << i+1 << ", " << node.toString() << std::endl;

    qt.insert( node );

  }

  std::vector<Node> queryItems = qt.queryRange( worldBounds );

  std::cout << "num items in query: " << queryItems.size() << std::endl;

  for ( unsigned int i = 0; i < queryItems.size(); i++ ) {
    std::cout << "query item: " << queryItems[ i ].toString() << std::endl;
  }

  return 0;

}
