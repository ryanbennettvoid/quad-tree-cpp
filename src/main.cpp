
#include <iostream>
#include <string>

#include "./Coordinate.h"
#include "./BoundaryBox.h"
#include "./Node.h"
#include "./Data.h"
#include "./QuadTree.h"
#include "./Helpers.h"
#include "./Renderer.h"

const int HALF_WORLD_SIZE = 300;

void drawBoundaryBoxes( Renderer& renderer, QuadTree* qt ) {

  renderer.drawBoundaryBox( qt->mBoundaryBox );

  if ( qt->mNorthWest != NULL ) drawBoundaryBoxes( renderer, qt->mNorthWest );
  if ( qt->mNorthEast != NULL ) drawBoundaryBoxes( renderer, qt->mNorthEast );
  if ( qt->mSouthWest != NULL ) drawBoundaryBoxes( renderer, qt->mSouthWest );
  if ( qt->mSouthEast != NULL ) drawBoundaryBoxes( renderer, qt->mSouthEast );

}

int main() {

  Coordinate worldCenter = Coordinate( 0, 0 );
  // std::cout << "created worldCenter: " << worldCenter.toString() << std::endl;

  BoundaryBox worldBounds = BoundaryBox( worldCenter, HALF_WORLD_SIZE );
  // std::cout << "created worldBounds: " << worldBounds.toString() << std::endl;
  
  QuadTree* qt = new QuadTree( worldBounds );
  // std::cout << "create qt: " << qt->toString() << std::endl;

  int rangeNum = HALF_WORLD_SIZE * 0.65;

  std::string filename = "out.bmp";

  Renderer renderer = Renderer( filename, HALF_WORLD_SIZE*2, HALF_WORLD_SIZE*2 );

  for ( int i = 0; i < 500; i++ ) {

    double randX = Helpers::generateRandomNumberInRange( -rangeNum, rangeNum );
    double randY = Helpers::generateRandomNumberInRange( -rangeNum, rangeNum );
    
    Coordinate nodeOrigin = Coordinate( randX, randY );
    Data nodeData = Data();
    Node node = Node( nodeOrigin, nodeData );
    // std::cout << "created node: " << i+1 << ", " << node.toString() << std::endl;

    qt->insert( node );
    renderer.drawCoordinate( nodeOrigin );

  }

  std::vector<Node> queryItems = qt->queryRange( worldBounds );

  std::cout << "world query: " << queryItems.size() << std::endl;

  // for ( unsigned int i = 0; i < queryItems.size(); i++ ) {
  //   std::cout << "query item: " << queryItems[ i ].toString() << std::endl;
  // }

  drawBoundaryBoxes( renderer, qt );

  renderer.save();

  std::cout << "rendered to " << filename << std::endl;

  delete qt;

  return 0;

}
