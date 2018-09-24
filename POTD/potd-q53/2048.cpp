
void run2048(int puzzle[4][4], int dir) {

    // your code here
	if (dir == 0)
	{
		for (int row = 0; row < 4; row++)
		{
			for (int col = 1; col < 4; col++)
			{
				if ((puzzle[row][col] == puzzle[row][col - 1]) && (puzzle[row][col] != 0))
				{
					puzzle[row][col - 1] = 2 * puzzle[row][col - 1];
					puzzle[row][col] = 0;
					continue;
				}
				else if (puzzle[row][col - 1] == 0 && puzzle[row][col] != 0)
				{
					int index = col - 1;
					while (index >= 0)
					{
						if (puzzle[row][index] != 0)
							break;
						index--;
					}
					if (puzzle[row][index] == puzzle[row][col])
					{
						puzzle[row][index] = 2 * puzzle[row][index];
						index--;
					}
					else
					{
						puzzle[row][index + 1] = puzzle[row][col];
					}
					while (index <= col - 2)
					{
						puzzle[row][index + 2] = 0;
						index++;
					}
				}
			}
		}
	}
	if (dir == 2)
	{
		for (int row = 0; row < 4; row++)
		{
			for (int col = 2; col >= 0; col--)
			{
				if ((puzzle[row][col] == puzzle[row][col + 1]) && (puzzle[row][col] != 0))
				{
					puzzle[row][col + 1] = 2 * puzzle[row][col + 1];
					puzzle[row][col] = 0;
					continue;
				}
				else if (puzzle[row][col + 1] == 0 && puzzle[row][col] != 0)
				{
					int index = col + 1;
					while (index <= 3)
					{
						if (puzzle[row][index] != 0)
							break;
						index++;
					}
					if (puzzle[row][index] == puzzle[row][col])
					{
						puzzle[row][index] = 2 * puzzle[row][index];
						index--;
					}
					else
					{
						puzzle[row][index - 1] = puzzle[row][col];
					}
					while (index <= col + 2)
					{
						puzzle[row][index - 2] = 0;
						index++;
					}
				}
			}
		}
	}
	if (dir == 2)
	{
		for (int row = 0; row < 4; row++)
		{
			for (int col = 2; col >= 0; col--)
			{
				if ((puzzle[row][col] == puzzle[row][col + 1]) && (puzzle[row][col] != 0))
				{
					puzzle[row][col + 1] = 2 * puzzle[row][col + 1];
					puzzle[row][col] = 0;
					continue;
				}
				else if (puzzle[row][col + 1] == 0 && puzzle[row][col] != 0)
				{
					int index = col + 1;
					while (index <= 3)
					{
						if (puzzle[row][index] != 0)
							break;
						index++;
					}
					if (puzzle[row][index] == puzzle[row][col])
					{
						puzzle[row][index] = 2 * puzzle[row][index];
						puzzle[row][col] = 0;
					}
					else
					{
						puzzle[row][index - 1] = puzzle[row][col];
					}
					while (index <= col + 2)
					{
						puzzle[row][index - 2] = 0;
						index++;
					}
				}
			}
		}
	}
}
