#pragma once
#include "grid.h"
#include "blocks.cpp"
#include <vector>

class Game
{
public:
	Game();
	Block GetRandomBlock();
	std::vector<Block> GetAllBlocks();
	void Draw();
	void HandleInput();
	void MoveBlockLeft();
	void MoveBlockRight();
	void MoveBlockDown();
	Grid grid;
	bool gameOver = false;

private:
	bool IsBlockOutside();
	void RotateBlock();
	void LockBlock();
	bool BlockFits();
	void Reset();
	std::vector<Block> blocks;
	Block currentBlock;
	Block nextBlock;
};