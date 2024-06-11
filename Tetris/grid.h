#pragma once
#include <vector>
#include <raylib.h>

class Grid
{
public:
	Grid();
	void Initialize();
	void Print();
	void Draw();
	bool IsCellEmpty(int row, int column);
	bool IsCellOutside(int row, int column);
	int grid[20][10];
private:
	int numRows;
	int numCols;
	int cellSize;
	std::vector<Color> colors;
};