/*
 *
 *  iteratively solve the eight-queens problem
 *
 */
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "solve.h"

#define MOVE_WRAP 100
#define LINE_LEN 50

static char move_buff[MOVE_WRAP][LINE_LEN];
static int move_count = 0;
static int mn = -1;

static int queen;
static struct
{
	int i, j;
	int di, dj;
} stack[SOLVE_NQUEENS];
int board[SOLVE_SIZE][SOLVE_SIZE];

#define Si(q) ((stack[q].i + stack[q].di)%SOLVE_SIZE)
#define Sj(q) ((stack[q].j + stack[q].dj)%SOLVE_SIZE)

static int queen_on(int q);

/*
 *  1 if the board spot is open, 0 if not. 
 */
static int solve_spot_open(int i, int j)
{
	return board[i][j] == 0;
}


/*
 *  set the board to either add or remove queen q
 */
static int sr_queen(int q, int inc)
{
	int i, j;
	int qi = Si(q);
	int qj = Sj(q);

	if(!queen_on(q))
		return -1;

	// spot
	board[qi][qj] += inc;

	// row
	for(j = 0; j < SOLVE_SIZE; ++j)
		if(j != qj)
			board[qi][j] += inc;

	// col
	for(i = 0; i < SOLVE_SIZE; ++i)
		if(i != qi)
			board[i][qj] += inc;

	// diag - right & down
	for(i = qi + 1, j = qj + 1; i < SOLVE_SIZE && j < SOLVE_SIZE; ++i, ++j)
		board[i][j] += inc;

	// diag - right & up
	for(i = qi - 1, j = qj + 1; i >= 0 && j < SOLVE_SIZE; --i, ++j)
		board[i][j] += inc;

	// diag - left & down
	for(i = qi + 1, j = qj - 1; i < SOLVE_SIZE && j >= 0; ++i, --j)
		board[i][j] += inc;

	// diag - left & up
	for(i = qi - 1, j = qj - 1; i >= 0 && j >= 0; --i, --j)
		board[i][j] += inc;

	return 0;
}


/*
 *  set the queen at (i,j) to q. return 0 if success
 */
static int set_queen(int q)
{
	return sr_queen(q, 1);
}


/*
 *  remove the queen from (i,j). return 0 if success
 */
static int remove_queen(int q)
{
	return sr_queen(q, -1);
}


/*
 *  true if queen q is already on the board
 */
static int queen_on(int q)
{
	return stack[q].i > -1 && stack[q].j > -1;
}

/*
 *  initialize the board
 */
void solve_init()
{
	int i, j;
	queen = 0;

	srand(time(0));

	for(i = 0; i < SOLVE_NQUEENS; ++i)
	{
		stack[i].i = stack[i].j = -1;
	}
	for(i = 0; i < SOLVE_SIZE; ++i)
	{
		for(j = 0; j < SOLVE_SIZE; ++j)
		{
			board[i][j] = 0;
		}
	}

	mn = 0;
	move_count = 1;
	sprintf(move_buff[0], "Start.");
}


/*
 *  find the location of queen q
 */
void solve_queen_at(int q, int* i, int* j)
{
	if(q < 0 || q >= SOLVE_NQUEENS || !queen_on(q))
		*i = *j = -1;
	else
	{
		*i = Si(q);
		*j = Sj(q);
	}
}


/*
 *  make the next solve move
 */
int solve_next_move()
{
	int moved = 0;
	int on; 

	// done - found solution
	if(queen == SOLVE_NQUEENS)
	{
		sprintf(move_buff[(move_count++)%MOVE_WRAP], "Complete!!!");
		return 1;
	} 
	// done - did not find solution
	if(queen < 0)
	{
		sprintf(move_buff[(move_count++)%MOVE_WRAP], "Failed.");
		return -1;
	}

	// should only run once or twice
	while(!moved)
	{
		on = queen_on(queen);
		moved = 1;
		// from last time
		if(on)
		{
			remove_queen(queen); 
		}
		// add to board
		else
		{
			stack[queen].di = rand()%SOLVE_SIZE;
			stack[queen].dj = rand()%SOLVE_SIZE;
			stack[queen].i = 0;
		}

		// find open spot
		do
		{
			// increment position
			++stack[queen].j;
			if(stack[queen].j == SOLVE_SIZE){
				stack[queen].j = 0;
				++stack[queen].i;

				// exhausted - backtrack
				if(stack[queen].i == SOLVE_SIZE)
				{
					stack[queen].i = stack[queen].j = -1;
					--queen;
					if(on){
						mn = 0;
						sprintf(move_buff[(move_count++)%MOVE_WRAP],
								"...Exhausted spaces for Queen %d.", queen+2);
						return 0;
					}
					mn = 1;
					sprintf(move_buff[(move_count++)%MOVE_WRAP],
							"...No place for Queen %d.", queen+2);

					moved = 0;
					break;
				}
			}
		} while(!solve_spot_open(Si(queen), Sj(queen)));
	}
	mn = 0;
	sprintf(move_buff[(move_count++)%MOVE_WRAP], 
			"Move Queen %d to %c%d.", queen+1, Si(queen)+'A', Sj(queen)+1);

	// place queen
	set_queen(queen);

	// get next queen
	++queen;

	return 0;
}


/*
 *
 */
int solve_nmessages()
{
	if(move_count >= MOVE_WRAP)
		return MOVE_WRAP - mn -1;
	return move_count - mn; 
}


/*

    MOVE_WRAP = 100
    move_count = 101
    i = 0 --> 2

 *
 */
char* solve_message(int i)
{
	if(move_count > MOVE_WRAP)
		return move_buff[(move_count - MOVE_WRAP + i + 1)%MOVE_WRAP];

	return move_buff[i];
}



