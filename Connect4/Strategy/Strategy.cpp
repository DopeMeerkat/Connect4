#include <iostream>
#include <ctime>
#include <conio.h>
#include <atlstr.h>

#include "Point.h"
#include "Board.h"
#include "Strategy.h"

#define MAX_TIME 2.9
#define LIMIT 6000000
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define OPP 3 - player

using namespace std;

int N, M;
int W[3];
Board board;

int total = 0;
int following[LIMIT][MAX_SIZE];
int wins[LIMIT][MAX_SIZE];
int simulations[LIMIT][MAX_SIZE];
int totalSim[LIMIT];
int prevAct;

extern "C" __declspec(dllexport) Point *getPoint(const int _M, const int _N, const int *_top, const int *_board,
												 const int _lastX, const int _lastY, const int _noX, const int _noY)
{
	/*int x = -1, y = -1;
	int **board = new int *[M];
	for (int i = 0; i < M; i++)
	{
		board[i] = new int[N];
		for (int j = 0; j < N; j++)
		{
			board[i][j] = _board[i * N + j];
		}
	}
	clearArray(M, N, board);
	return new Point(x, y);*/
	N = _N, M = _M;
	board.init(N, M, _noY, _noX, _top, _board);
	return MCTS();
}

extern "C" __declspec(dllexport) void clearPoint(Point *p)
{
	delete p;
	return;
}
/*
void clearArray(int M, int N, int **board)
{
	for (int i = 0; i < M; i++)
	{
		delete[] board[i];
	}
	delete[] board;
}
*/

#pragma region Monte Carlo Tree Search
Point* MCTS()
{
	clock_t start = clock();
	for (int i = 0; i <= total; i++) //reset
	{
		CLS(following[i]);
		CLS(wins[i]);
		CLS(simulations[i]);
		totalSim[i] = 0;
	}
	total = 0;

	while ((double)(clock() - start) / CLOCKS_PER_SEC < MAX_TIME) select(0, 2); //total will never surpass the upper limit unless the limit is changed or more time is allotted

	double prob = -1;
	int act;
	for (int i = 0; i < N; i++)
	{
		if (board.getTop(i) != 0)
		{
			double avg = (double)wins[0][i] / MAX(1, simulations[0][i]);
			if (prob < avg)
			{
				prob = avg;
				act = i;
			}
		}
	}
#ifdef DEBUG
	_cprintf("total: %d\ntime: %f\n", total, (double)(clock() - start) / CLOCKS_PER_SEC);
	_cprintf("X = %d, Y = %d\n", act, board.getTop(act) - 1);
#endif
	return new Point(board.getTop(act) - 1, act);
}

int select(const int current, const int player)
{
	if (current && board.connect4(prevAct)) return 0; //wins ++

	int act = explore(current);
	if (act == -1) return rand() & 1; //no action chosen

	compWin();
	if (W[player]) act = W[player] % (N + 1) - 1;
	else if (W[OPP] >= N + 1) return 0;
	else if (W[OPP]) act = W[OPP] - 1;

	board.place(act, player);

	simulations[current][act]++;
	totalSim[current]++;

	if (following[current][act] == 0) following[current][act] = ++total;
	int wl = select(following[current][act], OPP); 
	if (wl == 0) wins[current][act]++;

	board.remove(act, player);
	prevAct = act;
	return (1 - wl);
}

int explore(const int current)
{
	for (int i = 0; i < N; i++)
	{
		if (board.getTop(i) != 0 && simulations[current][i] == 0)
		{
			int x;
			do { x = rand() % N; } while (board.getTop(x) == 0);
			return x;
		}
	}
	double prob = -1;
	int act = - 1;
	for (int i = 0; i < N; i++)
	{
		if (board.getTop(i) != 0)
		{
			double Si = (double)wins[current][i] / simulations[current][i] + sqrt(2) * sqrt(log(totalSim[current]) / simulations[current][i]); //UCT value
			if (prob < Si)
			{
				prob = Si;
				act = i;
			}
		}
	}
	return act;
}

void compWin()
{
	for (int player = 1; player <= 2; player++)
	{
		W[player] = 0;
		for (int i = 0; i < N; i++)
		{
			if (board.getTop(i) != 0)
			{
				board.place(i, player);
				if (board.connect4(i)) W[player] = W[player] * (N + 1) + i + 1;
				board.remove(i, player);
			}
		}
	}
}
#pragma endregion