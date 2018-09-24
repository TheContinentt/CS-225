/**
 * @file mosaiccanvas.h
 */

#include <iostream>
#include <sys/stat.h>
#include <errno.h>
#include <cstdlib>

#include "mosaiccanvas.h"
#include "util/util.h"

using namespace std;
using namespace util;

bool MosaicCanvas::enableOutput = false;

/**
 * Constructor.
 *
 * @param theRows Number of rows to divide the canvas into
 * @param theColumns Number of columns to divide the canvas into
 */
MosaicCanvas::MosaicCanvas(int theRows, int theColumns)
    : rows(theRows), columns(theColumns)
{
    if ((theRows < 1) || (theColumns < 1)) {
        cerr << "Error: Cannot set non-positive rows or columns" << endl;
        exit(-1);
    }

    myImages.resize(rows * columns);
}

/**
 * Retrieve the number of rows of images
 *
 * @return The number or rows in the mosaic, or -1 on error
 */
int MosaicCanvas::getRows() const
{
    return rows;
}

/**
 * Retrieve the number of columns of images
 *
 * @return The number of columns in the mosaic, or -1 or error
 */
int MosaicCanvas::getColumns() const
{
    return columns;
}

void MosaicCanvas::setTile(int row, int column, TileImage& i)
{
    if (enableOutput) {
        cerr << "\rPopulating Mosaic: setting tile ("
             << row << ", " << column
             << ")" << string(20, ' ') << "\r";
        cerr.flush();
    }
    myImages[row * columns + column] = &i;
}

const TileImage& MosaicCanvas::getTile(int row, int column) const
{
    return *(images(row, column));
}

PNG MosaicCanvas::drawMosaic(int pixelsPerTile) const
{
    if (pixelsPerTile <= 0) {
        cerr << "ERROR: pixelsPerTile must be > 0" << endl;
        exit(-1);
    }

    int width = columns * pixelsPerTile;
    int height = rows * pixelsPerTile;

    // Create the image
    PNG mosaic(width, height);
	uint16_t *storex = new uint16_t[rows * columns];// = {0};
	uint16_t *storey = new uint16_t[rows * columns];// = {0};
	uint16_t *storeendx = new uint16_t[rows * columns];// = {0};
	uint16_t *storerow = new uint16_t[rows * columns];// = {0};
	uint16_t *storecol = new uint16_t[rows * columns];// = {0};
	uint32_t index = 0;
	/*int storex[300000] = {0};
	int storey[300000] = {0};
	int storeendx[300000] = {0};
	int storerow[300000] = {0};
	int storecol[300000] = {0};
	int index = 0;*/
    // Create list of drawable tiles
    for (int row = 0; row < rows; row++) {
        if (enableOutput) {
            cerr << "\rDrawing Mosaic: resizing tiles ("
                 << (row * columns + /*col*/ 0 + 1) << "/" << (rows * columns)
                 << ")" << string(20, ' ') << "\r";
            cerr.flush();
        }
        for (int col = 0; col < columns; col++) {
            int startX = divide(width  * col,       getColumns());
            int endX   = divide(width  * (col + 1), getColumns());
            int startY = divide(height * row,       getRows());
            int endY   = divide(height * (row + 1), getRows());

            if (endX - startX != endY - startY)
                cerr << "Error: resolution not constant: x: " << (endX - startX)
                     << " y: " << (endY - startY) << endl;

            //images(row, col)->paste(mosaic, startX, startY, endX - startX);
	    storex[index] = startX;
	    storey[index] = startY;
	    storerow[index] = row;
	    storecol[index] = col;
	    storeendx[index] = endX - startX;
	    index++;
        }
    }
	for (int j = 0; j < rows * columns; j++)
	{
		images(storerow[j], storecol[j])->paste(mosaic, storex[j], storey[j], storeendx[j]);
		//cout << j << endl;
	}
	/*for (int j = 0; j < index; j++)
	{
		myImages[storerow[j] * columns + storecol[j]]->paste(mosaic, storex[j], storey[j], storeendx[j]);
		//cout << j << endl;
	}*/
	/*delete [] storex;
	delete [] storey;
	delete [] storeendx;
	delete [] storerow;
	delete [] storecol;*/
    if (enableOutput) {
        cerr << "\r" << string(60, ' ');
        cerr << "\rDrawing Mosaic: resizing tiles ("
             << (rows * columns) << "/" << (rows * columns) << ")" << endl;
        cerr.flush();
    }

    return mosaic;
}
