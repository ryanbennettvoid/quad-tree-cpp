
#include <iostream>
#include "./QuadTree.cpp"

const int MAX_BOUND = 1000;

int main() {

  Coordinate bbCenter = Coordinate( 0, 0 );
  BoundaryBox bb = BoundaryBox( bbCenter, MAX_BOUND );
  QuadTree<int>* qt = new QuadTree<int>( bb );

  for ( int i = 0; i < 50; i++ ) {

    double randX = ( double )( rand() % MAX_BOUND ) * 0.9;
    double randY = ( double )( rand() % MAX_BOUND ) * 0.9;

    Coordinate c = Coordinate( randX, randY );

    Node<int> n = Node<int>( c, 777 );

    qt->insert( n );

    std::cout << randX << "," << randY << std::endl;

  }

  delete qt;

  return 0;
}
