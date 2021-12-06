#ifndef DAY4_H
#define DAY4_H

#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <map>
#include <set>
using namespace std;

typedef struct location
{
	int row;
	int col;
} location;

void readInputDay4(vector<int>& drawnNumbers, vector<map<int, location>>& board);
int solveDay4Part1();
int solveDay4Part2();

#endif