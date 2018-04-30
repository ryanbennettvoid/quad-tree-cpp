
#include <iostream>
#include <string>
#include <vector>
#include "assert.h"

#include "./QuadTree.h"
#include "./BoundaryBox.h"
#include "./Node.h"

QuadTree::QuadTree( BoundaryBox boundaryBox )
: mBoundaryBox(boundaryBox), mNorthWest(NULL), mNorthEast(NULL), mSouthWest(NULL), mSouthEast(NULL)
{
  // this->mNodes = std::vector<Node>();
}

// QuadTree::~QuadTree()
// {
//    if ( this->mNorthWest != NULL ) delete this->mNorthWest;
//    if ( this->mNorthEast != NULL ) delete this->mNorthEast;
//    if ( this->mSouthWest != NULL ) delete this->mSouthWest;
//    if ( this->mSouthEast != NULL ) delete this->mSouthEast;
// }

bool QuadTree::insert( Node node )
{

  // ensure correct bounds
  if ( !this->mBoundaryBox.containsCoordinate( node.mOrigin ) ) {
    // std::cout << "not contained: " << node.toString() << std::endl;
    return false;
  }

  // if space available here, add it
  if ( this->mNodes.size() < this->NODE_CAPACITY ) {
    this->mNodes.push_back( node );
    // std::cout << "added node: " << node.toString() << std::endl;
    return true;
  }

  // create child quads
  if ( this->mNorthWest == NULL ) this->subdivide();

  // otherwise subdivide and add to first available quad
  if ( this->mNorthWest->insert( node ) ) return true;
  if ( this->mNorthEast->insert( node ) ) return true;
  if ( this->mSouthWest->insert( node ) ) return true;
  if ( this->mSouthEast->insert( node ) ) return true;

  return false;
}

void QuadTree::subdivide()
{

  std::cout << "subd start" << std::endl;

  double newHalfSize = this->mBoundaryBox.mHalfSize / 2;

  Coordinate nwCenter = Coordinate( this->mBoundaryBox.mOrigin.mX - newHalfSize, this->mBoundaryBox.mOrigin.mY + newHalfSize );
  Coordinate neCenter = Coordinate( this->mBoundaryBox.mOrigin.mX + newHalfSize, this->mBoundaryBox.mOrigin.mY + newHalfSize );
  Coordinate swCenter = Coordinate( this->mBoundaryBox.mOrigin.mX - newHalfSize, this->mBoundaryBox.mOrigin.mY - newHalfSize );
  Coordinate seCenter = Coordinate( this->mBoundaryBox.mOrigin.mX + newHalfSize, this->mBoundaryBox.mOrigin.mY - newHalfSize );

  BoundaryBox bbNw = BoundaryBox( nwCenter, newHalfSize );
  BoundaryBox bbNe = BoundaryBox( neCenter, newHalfSize );
  BoundaryBox bbSw = BoundaryBox( swCenter, newHalfSize );
  BoundaryBox bbSe = BoundaryBox( seCenter, newHalfSize );

  this->mNorthWest = new QuadTree( bbNw );
  this->mNorthEast = new QuadTree( bbNe );
  this->mSouthWest = new QuadTree( bbSw );
  this->mSouthEast = new QuadTree( bbSe );

  // move nodes from this quad to child quads

  for ( unsigned int i = 0; i < this->mNodes.size(); i++ ) {

    Node node = this->mNodes.at( i );

    if ( this->mNorthWest->insert( node ) ) std::cout << "inserted " << &node << " into northWest" << std::endl;
    else if ( this->mNorthEast->insert( node ) ) std::cout << "inserted " << &node << " into northEast" << std::endl;
    else if ( this->mSouthWest->insert( node ) ) std::cout << "inserted " << &node << " into mSouthWest" << std::endl;
    else if ( this->mSouthEast->insert( node ) ) std::cout << "inserted " << &node << " into mSouthEast" << std::endl;

  }

  this->mNodes.clear();

  assert( this->mNodes.empty() );

  std::cout << "subd end" << std::endl;

}

std::vector<Node> QuadTree::queryRange( BoundaryBox boundaryBox )
{

  std::vector<Node> results = std::vector<Node>();

  if ( !this->mBoundaryBox.intersectsBoundaryBox( boundaryBox ) ) return results;

  for ( unsigned int i = 0; i < this->mNodes.size(); i++ ) {

    Node node = this->mNodes.at( i );

    if ( boundaryBox.containsCoordinate( node.mOrigin ) ) {
      results.push_back( node );
    }

  }

  return results;
}

// Printable
std::string QuadTree::toString()
{
  return std::string( "QuadTree(mBoundaryBox:" + this->mBoundaryBox.toString() + ")" );
}
