
#include <iostream>
#include "./QuadTree.h"

// Coordinate

Coordinate::Coordinate( double _x, double _y )
: x(_x), y(_y)
{
}

// Node

template<typename T>
Node<T>::Node( Coordinate &_point, T _data )
: point(_point), data(_data)
{
}

// BoundaryBox

BoundaryBox::BoundaryBox( Coordinate &_center, double _halfSize )
: center(_center), halfSize(_halfSize)
{
}

bool BoundaryBox::containsCoordinate( Coordinate& _coordinate )
{

  double left = this->center.x - this->halfSize;
  double right = this->center.x + this->halfSize;
  double top = this->center.y + this->halfSize;
  double bottom = this->center.y - this->halfSize;

  double x = _coordinate.x;
  double y = _coordinate.y;

  if (
    left < x && x < right &&
    bottom < y && y < top
  ) {
    return true;
  }

  return false;
}

// https://stackoverflow.com/questions/306316/determine-if-two-rectangles-overlap-each-other
bool BoundaryBox::intersectsBoundaryBox( BoundaryBox& _boundaryBox )
{

  double leftA = this->center.x - this->halfSize;
  double rightA = this->center.x + this->halfSize;
  double topA = this->center.y + this->halfSize;
  double bottomA = this->center.y - this->halfSize;

  double leftB = _boundaryBox.center.x - _boundaryBox.halfSize;
  double rightB = _boundaryBox.center.x + _boundaryBox.halfSize;
  double topB = _boundaryBox.center.y + _boundaryBox.halfSize;
  double bottomB = _boundaryBox.center.y - _boundaryBox.halfSize;

  return !(
    leftA > rightB ||
    rightA < leftB ||
    topA < bottomB ||
    bottomA > topB
  );
}

// Quad Tree

template<typename T>
QuadTree<T>::QuadTree( BoundaryBox &_boundaryBox )
: boundaryBox(_boundaryBox)
{
  std::cout << "init qt\n";
}

template<typename T>
bool QuadTree<T>::insert( Node<T> &_node )
{

  // ensure correct bounds
  if ( !this->boundaryBox.containsCoordinate( _node.point ) ) {
    return false;
  }

  // if space available here, add it
  if ( this->nodes.size() < this->NODE_CAPACITY ) {
    this->nodes.push_back( _node );
    return true;
  }

  // otherwise subdivide and add to first available node
  if ( this->northWest->insert( _node ) ) return true;
  if ( this->northEast->insert( _node ) ) return true;
  if ( this->southWest->insert( _node ) ) return true;
  if ( this->southEast->insert( _node ) ) return true;

  return false;
}

template<typename T>
void QuadTree<T>::subdivide()
{
}

template<typename T>
std::vector< Node<T> > QuadTree<T>::queryRange( BoundaryBox &_boundaryBox )
{
  std::vector< Node<T> > results;
  return results;
}
