/* Your code here! */
#include "maze.h"
#include <vector>
#include <iostream>
#include <queue>
#include <stdlib.h>
#include <cstdlib>

SquareMaze::SquareMaze()
{
	DisjointSets dset = DisjointSets();
	storedset = dset;
	w = 0;
	h = 0;
	exit = 0;
//	std::vector<int> t;
//	rightwall = t;
//	std::vector<int> tt;
//	downwall = tt;
}

void SquareMaze::makeMaze(int width, int height)
{
	int counter = 0;
	int tempcell = 0;
	int tempdir = 0;
	int nextcell = 0;
	w = width;
	h = height;
	int cellnumber = width * height;
	rightwall = new bool[cellnumber];
	downwall = new bool[cellnumber];
	vector<int> checkr;
	for (int i = 0; i < w * h; i++)
		checkr.push_back(0);
	vector<int> checkd;
	for (int i = 0; i < w * h; i++)
		checkd.push_back(0);
	storedset.addelements(cellnumber);
	int wallnumber = width * (height - 1) + height * (width - 1);
	int keepnumber = (height - 1) * (width - 1);
	int maxnumber = wallnumber - keepnumber - 1;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			setWall(j, i, 0, 1);
			setWall(j, i, 1, 1);
		}
	}
	while (counter <= maxnumber)
	{
		tempcell = rand() % cellnumber;
		tempdir = rand() % 2;
		if (((tempcell + 1) % width == 0) && tempdir == 0)
			continue;
		if ((tempcell / width == (height - 1)) && tempdir == 1)
			continue;
		if (tempdir == 0)
		{
			nextcell = tempcell + 1;
			if (storedset.find(tempcell) == storedset.find(nextcell))
				continue;
			else if (checkr[tempcell] == 0)
			{
				checkr[tempcell] = 1;
				storedset.setunion(tempcell, nextcell);
				setWall(tempcell % width, tempcell / width, 0, 0);
				counter++;
			}
		}
		else if (tempdir == 1)
		{
			nextcell = tempcell + width;
			if (storedset.find(tempcell) == storedset.find(nextcell))
				continue;
			else if (checkd[tempcell] == 0)
			{
				checkd[tempcell] = 1;
				storedset.setunion(tempcell, nextcell);
				setWall(tempcell % width, tempcell / width, 1, 0);
				counter++;
			}
		}
		//std::cout << counter << "\n" << std::endl;
	}
}

bool SquareMaze::canTravel(int x, int y, int dir) const
{
	int cellindex = y * w + x;
	int nextcell = 0;
	/*if ((y >= h - 1) && dir == 1)
		return false;
	if ((x >= w - 1) && dir == 0)
		return false;*/
	if (dir == 0)
	{
		if (x >= w - 1)
			return false;
		nextcell = cellindex + 1;
		if (rightwall[cellindex] == 1)
			return false;
		return true;
	}
	else if (dir == 1)
	{
		if (y >= h - 1)
			return false;
		nextcell = cellindex + w;
		if (downwall[cellindex] == 1)
			return false;
		return true;
	}
	else if (dir == 2)
	{
		nextcell = cellindex - 1;
		if (nextcell < 0)
			return false;
		if (rightwall[nextcell] == 1)
			return false;
		return true;
	}
	else if (dir == 3)
	{
		nextcell = cellindex - w;
		if (nextcell < 0)
			return false;
		if (downwall[nextcell] == 1)
			return false;
		return true;
	}
	return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
	int index = x + y * w;
	int flag = 0;
	if (dir == 0 && (x + 1) % w == 0)
	{
		rightwall[index] = 1;
		flag = 1;
	}
	else if (dir == 1 && ((y + 1) == h))
	{
		downwall[index] = 1;
		flag = 1;
	}
	if (flag == 1)
		return;
	if (dir == 0)
		rightwall[index] = exists;
	else if (dir == 1)
		downwall[index] = exists;
}

vector<int> SquareMaze::solveMaze()
{
	vector<int> retval;
	vector<int> direction;
	for (int i = 0; i < w * h; i++)
		direction.push_back(0);
	vector<int> counter;
	for (int i = 0; i < w * h; i++)
		counter.push_back(0);
	queue<int> step;
	vector<bool> check;
	for (int i = 0; i < w * h; i++)
		check.push_back(0);
	step.push(0);
	int col = 0;
	int row = 0;
	int curr;
	while (!step.empty())
	{
		curr = step.front();
		step.pop();
		row = curr / w;
		col = curr % w;
		if (check[curr + 1] == 0 && canTravel(col, row, 0))
		{
			check[curr + 1] = 1;
			step.push(curr + 1);
			direction[curr + 1] = 0;
			counter[curr + 1] = counter[curr] + 1;
		}
		if (check[curr + w] == 0 && canTravel(col, row, 1))
		{
			check[curr + w] = 1;
			step.push(curr + w);
			direction[curr + w] = 1;
			counter[curr + w] = counter[curr] + 1;
		}
		if (curr - 1 >= 0)
		{
			if (check[curr - 1] == 0 && canTravel(col, row, 2))
			{
				check[curr - 1] = 1;
				step.push(curr - 1);
				direction[curr - 1] = 2;
				counter[curr - 1] = counter[curr] + 1;
			}
		}
		if (curr - w >= 0)
		{
			if (curr - w >= 0 && check[curr - w] == 0 && canTravel(col, row, 3))
			{
				check[curr - w] = 1;
				step.push(curr - w);
				direction[curr - w] = 3;
				counter[curr - w] = counter[curr] + 1;
			}
		}
	}
	/*for (int i = 0; i < w * h; i++)
		std::cout << counter[i] << "\n" << std::endl;*/
	//std::cout << counter.size() << "\n" << std::endl;
	int maxend = 0;
	int maxindex;
	for (int i = w * (h - 1); i < w * h; i++)
	{
		if (counter[i] > maxend)
		{
			maxend = counter[i];
			maxindex = i;
		}
	}
	int count = 0;
	count = counter[maxindex];
	int i = maxindex;
	exit = maxindex;
	while (count > 0)
	{
		count--;
		retval.push_back(direction[i]);
		if (direction[i] == 3)
			i = i + w;
		else if (direction[i] == 2)
			i = i + 1;
		else if (direction[i] == 1)
			i = i - w;
		else if (direction[i] == 0)
			i = i - 1;
	}
	reverse(retval.begin(), retval.end());
	return retval;
}


PNG* SquareMaze::drawMaze() const
{
	int index = 0;
	PNG* draw = new PNG(w * 10 + 1, h * 10 + 1);
	for (int i = 10; i < w * 10 + 1; i++)
		setblackcolor(i, 0, draw);
	for (int i = 0; i < h * 10 + 1; i++)
		setblackcolor(0, i, draw);
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			index = i * w + j;
			if (rightwall[index] == 1)
			{
				for (int k = 0; k <= 10; k++)
					setblackcolor((j + 1) * 10, i * 10 + k, draw);
			}
			if (downwall[index] == 1)
			{
				for (int k = 0; k <= 10; k++)
					setblackcolor(j * 10 + k, (i + 1) * 10, draw);
			}
		}
	}
	return draw;
}

PNG* SquareMaze::drawMazeWithSolution()
{
	PNG* draw = drawMaze();
	vector<int> retval = solveMaze();
	int size = retval.size();
	int curr;
	int currx = 5;
	int curry = 5;
	int counter = 10;
	for (int i = 0; i < size; i++)
	{
		counter = 10;
		curr = retval[i];
		if (curr == 0)
		{
			while (counter >= 0)
			{
				setredcolor(currx, curry, draw);
				currx++;
				counter--;
			}
			currx--;
		}
		else if (curr == 1)
		{
			while (counter >= 0)
			{
				setredcolor(currx, curry, draw);
				curry++;
				counter--;
			}
			curry--;
		}
		else if (curr == 2)
		{
			while (counter >= 0)
			{
				setredcolor(currx, curry, draw);
				currx--;
				counter--;
			}
			currx++;
		}
		else if (curr == 3)
		{
			while (counter >= 0)
			{
				setredcolor(currx, curry, draw);
				curry--;
				counter--;
			}
			curry++;
		}
	}
	int row = h - 1;
	int col = exit % w;
	for (int j = 1; j <= 9; j++)
	{
		setwhitecolor(col * 10 + j, (row + 1) * 10, draw);
	}
	return draw;
}

/* helper function for blacken the pixel. */
void SquareMaze::setblackcolor(int x, int y, PNG* draw) const
{
	HSLAPixel *curr = draw->getPixel(x, y);
	curr->h = 0;
	curr->l = 0;
	curr->s = 0.5;
}

void SquareMaze::setredcolor(int x, int y, PNG* draw) const
{
	HSLAPixel *curr = draw->getPixel(x, y);
	curr->h = 0.1;
	curr->l = 0.5;
	curr->s = 1;
}

void SquareMaze::setwhitecolor(int x, int y, PNG* draw) const
{
	HSLAPixel *curr = draw->getPixel(x, y);
	curr->h = 0;
	curr->l = 1;
	curr->s = 1;
}
