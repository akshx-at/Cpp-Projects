/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
     // so the function takes in individual pixels, finds the clsest tiles that represent sit LUV values, replaces it and and maps it out
     //converts tiles to Mosaic
     // maps based on if avg color of the tile is closest to the avg color of the region in the originalimage
     int col = theSource.getColumns();
     int row = theSource.getRows();
    MosaicCanvas * newCanvas = new MosaicCanvas(row,col);
    // vector<Point<3>> changedpoints;
    // std::map<Point<3>, TileImage*> mapnode;
    // for (auto Iterate = theTiles.begin(); Iterate != theTiles.end(); Iterate++) {
    // 	LUVAPixel tilepixel = Iterate->getAverageColor(); // Get average pixel in Point form
    // 	Point<3> pointnode = convertToXYZ(tilepixel);
    // 	changedpoints.push_back(pointnode); 
    // 	mapnode[pointnode] = &*Iterate;  // Map that average pixel to its tile

    vector<Point<3>> Color(theTiles.size());
    map<Point<3>, int> sourceMap;
    for (size_t i = 0; i < theTiles.size(); i++) {
      Color[i] = convertToXYZ(theTiles[i].getAverageColor());
      sourceMap[Color[i]] = i;
    }

    KDTree<3> treeavgcolor(Color);  // Make a kd tree of all average points
    for (int i = 0; i < row; i++) {
    	for (int j = 0; j < col; j++) {
    		Point<3> avg_ = convertToXYZ(theSource.getRegionColor(i, j));
    		Point<3> near_ = treeavgcolor.findNearestNeighbor(avg_);
    		int newcorrecttile = sourceMap[near_];  
    		newCanvas->setTile(i, j, &theTiles[newcorrecttile]);
    	}
    }
        return newCanvas;
}


