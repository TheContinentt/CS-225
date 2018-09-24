/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

/* mapTiles;
 * Description: The function used to plot the mosaic effect of original picture.
 * Input: theSource: the source picture.
 *	  theTiles: the tile that we need to find nearest neighbor from.
 * Output: none.
 * Return Value: retval: a MosaicCanvas type pointer.
 * SideEffect: plot the mosaic picture.
 */
MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    /**
     * @todo Implement this function!
     */
	int sourcerow = theSource.getRows();
	int sourcecol = theSource.getColumns();
	int i = 0, j = 0, index = 0;
	MosaicCanvas* retval = new MosaicCanvas(sourcerow, sourcecol);
	int size = theTiles.size();
	vector<Point<3>> store;
	for (i = 0; i < size; i++)
	{
		HSLAPixel tempcolor = theTiles[i].getAverageColor();
		Point<3> target(tempcolor.h, tempcolor.s, tempcolor.l);
		store.push_back(target);
	}
	KDTree<3> pixeltree(store);
	for (i = 0; i < sourcerow; i++)
	{
		for (j = 0; j < sourcecol; j++)
		{
			HSLAPixel sourcecolor = theSource.getRegionColor(i, j);
			Point<3> sourcepixel(sourcecolor.h, sourcecolor.s, sourcecolor.l);
			Point<3> temppoint;
			temppoint = pixeltree.findNearestNeighbor(sourcepixel);
			double th = temppoint[0];
			double ts = temppoint[1];
			double tl = temppoint[2];
			for (index = 0; index < size; index++)
			{
				if (th == store[index][0] && ts == store[index][1] && tl == store[index][2])
					break;
			}
			TileImage findout;
			findout = theTiles[index];
			retval->setTile(i, j, findout);
		}
	}
    return retval;
}

