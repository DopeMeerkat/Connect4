#include "Board.h"
#include <assert.h>
void Board::init(const int _N, const int _M, const int _noX, const int _noY, const int* _top, const int* _board)
{
	CLS(vert);
	CLS(horiz);
	CLS(bSlash);
	CLS(slash);
	N = _N, M = _M, noX = _noX, noY = _noY;
	for (int i = 0; i < N; i++) top[i] = M;
	if (noY == M - 1) top[noX] = M - 1;
	for (int i = 0; i < N; i++)
	{
		for (int j = M - 1; j >= 0; j--)
		{
			if (_board[j*N + i]) place(i, _board[j*N + i]);
		}
	}
}

void Board::place(const int &X, const int &player)
{
	int Y = top[X] - 1;
	vert[X] |= (1 << (Y * 2 + player));
	horiz[Y] |= (1 << (X * 2 + player));
	bSlash[X + M - Y] |= (1 << (X * 2 + player));
	slash[X + Y] |= (1 << (X * 2 + player));
	top[X]--;
	if (X == noX && top[X] - 1 == noY) top[X]--;
}

void Board::remove(const int &X, const int &player)
{
	if (X == noX && top[X] == noY) top[X]++;
	int Y = top[X];
	vert[X] -= (1 << (Y * 2 + player));
	horiz[Y] -= (1 << (X * 2 + player));
	bSlash[X + M - Y] -= (1 << (X * 2 + player));
	slash[X + Y] -= (1 << (X * 2 + player));
	top[X]++;
}

bool Board::connect4(const int &X)
{
	int Y = top[X];
	if (X == noX && Y == noY) Y++;
	if (Y == M) return false;
	return (connected(vert[X]) || connected(horiz[Y]) ||
			connected(bSlash[X - Y + M]) || connected(slash[X + Y]));
}

bool Board::connected(const int &a)
{
	return (a & (a >> 2) & (a >> 4) & (a >> 6));
}

int Board::getTop(const int &X)
{
	assert(X >= 0 && X <= MAX_SIZE);
	return top[X];
}