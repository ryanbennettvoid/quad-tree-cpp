
#include <iostream>
#include "./QuadTree.h"

// Coordinate

Coordinate::Coordinate( double _x, double _y )
: x(_x), y(_y)
{
}

// Node

template<typename T>
Node<T>::Node( Coordinate &_point, T &_data )
: point(_point), data(_data)
{
}

// BoundaryBox

BoundaryBox::BoundaryBox( Coordinate &_center, double _halfSize )
: center(_center), halfSize(_halfSize)
{
}

// Quad Tree

// template<typename T>
// QuadTree<T>::QuadTree( BoundaryBox &_boundaryBox )
// : boundaryBox(_boundaryBox)
// {
//   std::cout << "init qt\n";
// }

// template<typename T>
// bool QuadTree<T>::insert( Node<T> &_node )
// :
// {
//   return false;
// }

// void QuadTree<T>::subdivide()
// {
// }

// template<typename T>
// std::vector< Node<T> > QuadTree<T>::queryRange( BoundaryBox &_boundaryBox )
// {
//   std::vector< Node<T> > results;
//   return results;
// }
