#ifndef QUADTREE_H
#define QUADTREE_H

#include <string>
#include <vector>

#include "./Printable.h"
#include "./BoundaryBox.h"
#include "./Node.h"

class QuadTree : Printable
{

  private:

    static const unsigned int NODE_CAPACITY = 4;

  public:

    BoundaryBox mBoundaryBox;
    std::vector<Node> mNodes;

    QuadTree* mNorthWest;
    QuadTree* mNorthEast;
    QuadTree* mSouthWest;
    QuadTree* mSouthEast;

    // nw---ne
    // |     |
    // |     |
    // sw---se

    QuadTree( BoundaryBox boundaryBox );
    // ~QuadTree();
    bool insert( Node node );
    void subdivide(); // divide into 4 children
    std::vector<Node> queryRange( BoundaryBox boundaryBox );

    // Printable
    std::string toString();

};

#endif
