#ifndef QUADTREE_H
#define QUADTREE_H

struct Coordinates {

  double x;
  double y;

};

template<typename T>
struct Node {

  T *data;
  Coordinates *point;

};

struct BoundaryBox {

  Coordinates *center;
  double halfSize;

};

template<typename T>
class QuadTree {

  private:

    static const int NODE_CAPACITY = 4;

  public:

    BoundaryBox *boundary;
    Node<T> *nodes[ NODE_CAPACITY ];

    QuadTree *northWest;
    QuadTree *northEast;
    QuadTree *southWest;
    QuadTree *southEast;

    // nw---ne
    // |     |
    // |     |
    // sw---se

    QuadTree();
    // insert();
    // subdivide();

};

#endif
