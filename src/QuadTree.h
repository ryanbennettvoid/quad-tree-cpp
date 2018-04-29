#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>

class Coordinate
{

  public:

    double x;
    double y;

    Coordinate( double _x, double _y );

};

template<typename T>
class Node
{

  public:

    Coordinate* point;
    T* data;

    Node( Coordinate* _point, T* _data );

};

class BoundaryBox
{

  public:

    Coordinate* center;
    double halfSize;

    BoundaryBox( Coordinate* _center, double _halfSize );
    bool containsCoordinate( Coordinate* _point );
    bool intersectsBoundaryBox( BoundaryBox* _boundaryBox );

};

template<typename T>
class QuadTree
{

  private:

    static const unsigned int NODE_CAPACITY = 4;

  public:

    BoundaryBox* boundaryBox;
    std::vector< Node<T>* >* nodes;

    QuadTree<T>* northWest;
    QuadTree<T>* northEast;
    QuadTree<T>* southWest;
    QuadTree<T>* southEast;

    // nw---ne
    // |     |
    // |     |
    // sw---se

    QuadTree( BoundaryBox* _boundaryBox );
    ~QuadTree();
    bool insert( Node<T>* _node );
    void subdivide(); // divide into 4 children
    std::vector< Node<T>* >* queryRange( BoundaryBox* _boundaryBox );

};

#endif
