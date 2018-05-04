#ifndef RENDERER_H
#define RENDERER_H

#include "../../external/bitmap/bitmap_image.hpp"

#include "./Coordinate.h"
#include "./BoundaryBox.h"

class Renderer
{

  private:

    std::string _mFilepath;
    bitmap_image _mBitmapImage;
    image_drawer* _mDrawer;

  public:

    Renderer( std::string filepath, int w, int h );
    ~Renderer();
    void drawCoordinate( Coordinate& point );
    void drawBoundaryBox( BoundaryBox& boundaryBox );
    void save();

};

#endif
