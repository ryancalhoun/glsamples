#ifndef SOLVE_H
#define SOLVE_H

#define SOLVE_SIZE 8
#define SOLVE_NQUEENS 8

void solve_init();
void solve_queen_at(int q, int* i, int* j);
int solve_next_move();
int solve_nmessages();
char* solve_message(int i);

#endif
