
#include <iostream>

#include "../external/bitmap/bitmap_image.hpp"

#include "./Renderer.h"
#include "./Coordinate.h"
#include "./BoundaryBox.h"

Renderer::Renderer( std::string filepath, int w, int h )
: _mFilepath(filepath)
{
  this->_mBitmapImage = bitmap_image( w, h );
  this->_mBitmapImage.set_all_channels( 255, 255, 255 ); // set to white
  this->_mDrawer = new image_drawer( this->_mBitmapImage );
}

Renderer::~Renderer()
{
  if ( this->_mDrawer != NULL ) delete this->_mDrawer;
}

void Renderer::drawCoordinate( Coordinate& coordinate )
{
  if ( this->_mDrawer == NULL ) return;
  int xOffset = this->_mBitmapImage.width() / 2;
  int yOffset = this->_mBitmapImage.height() / 2;
  this->_mDrawer->circle( coordinate.mX + xOffset, coordinate.mY + yOffset, 3 );
}

void Renderer::drawBoundaryBox( BoundaryBox& boundaryBox )
{
  if ( this->_mDrawer == NULL ) return;
  int xOffset = this->_mBitmapImage.width() / 2;
  int yOffset = this->_mBitmapImage.height() / 2;
  int x1 = boundaryBox.getLeft();
  int y1 = boundaryBox.getTop();
  int x2 = boundaryBox.getRight();
  int y2 = boundaryBox.getBottom();
  this->_mDrawer->rectangle( x1 + xOffset, y1 + yOffset, x2 + xOffset, y2 + yOffset );
}

void Renderer::save()
{
  this->_mBitmapImage.save_image( this->_mFilepath );
}
