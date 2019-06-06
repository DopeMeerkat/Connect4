#ifndef BOARD_H_
#define BOARD_H_

#include <cstring>
#define CLS(b) memset(b, 0, sizeof(b))
#define MAX_SIZE 12

//X and Y are reversed in this code because it's more intuitive
//X - Horizontal, Y - Vertical

class Board
{
	int N, M, noX, noY;
	int top[MAX_SIZE];
	int vert[MAX_SIZE];
	int horiz[MAX_SIZE];
	int bSlash[2 * MAX_SIZE - 1];
	int slash[2 * MAX_SIZE - 1];
	bool connected(const int &a);
public:
	void init(const int _N, const int _M, const int _noX, const int _noY, const int* _top, const int* _board);
	void place(const int &X, const int &player);
	void remove(const int &X, const int &player);
	bool connect4(const int &X);
	int getTop(const int &X);
};
#endif