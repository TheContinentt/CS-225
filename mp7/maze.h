/* Your code here! */
#ifndef _MAZE_H_
#define _MAZE_H_
#include <vector>
#include "cs225/PNG.h"
#include "dsets.h"
#include <cstdlib>
#include <queue>
#include <stdlib.h>

using namespace cs225;

class SquareMaze
{
	public:
		SquareMaze();
		/* This function makes maze.*/
		void makeMaze(int width, int height);
		/*This function checks whether this direction in able to travel.*/
		bool canTravel(int x, int y, int dir) const;
		/* This function set wall between two squares.*/
		void setWall(int x, int y, int dir, bool exists);
		/* Thif function returns the path that we solved the maze.*/
		vector<int> solveMaze();
		/* THis is the helper function for solvemaze.*/
		int solveMazehelper(int x, int y, int counter, vector<int> &result);
		/* THis is the function in order to draw maze.*/
		PNG* drawMaze() const;
		/*This is the helper function to set black color.*/
		void setblackcolor(int x, int y, PNG* draw) const;
		/*This is the helper function to set red color.*/
		void setredcolor(int x, int y, PNG* draw) const;
		/*This is the helper function to set white color.*/
		void setwhitecolor(int x, int y, PNG* draw) const;
		/* THis is the function in order to draw solved maze.*/
		PNG* drawMazeWithSolution();
	private:
		DisjointSets storedset;
		int w;
		int h;
		//vector<int> rightwall;
		//vector<int> downwall;
		bool* rightwall;
		bool* downwall;
		int exit;
};
	
#endif


