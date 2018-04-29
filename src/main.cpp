
#include <iostream>
#include "./QuadTree.cpp"

const int MAX_BOUND = 1000;

int main() {

  Coordinate* bbCenter = new Coordinate( 0, 0 );
  BoundaryBox* bb = new BoundaryBox( bbCenter, MAX_BOUND );
  QuadTree<std::string>* qt = new QuadTree<std::string>( bb );

  for ( int i = 0; i < 15; i++ ) {

    double randX = ( double )( rand() % MAX_BOUND ) * 0.9;
    double randY = ( double )( rand() % MAX_BOUND ) * 0.9;
    Coordinate* c = new Coordinate( randX, randY );

    std::string* str = new std::string( "yo!" );

    Node<std::string>* node = new Node<std::string>( c, str );

    qt->insert( node );

  }

  std::vector< Node<std::string>* >* queryItems = qt->queryRange( bb );

  std::cout << "num items in query: " << queryItems->size() << std::endl;

  // delete qt;

  return 0;
}
