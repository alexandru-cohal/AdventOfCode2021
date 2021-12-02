#include "day2.h"

void readInputDay2(vector<string> &directions, vector<int> &steps)
{
	string filename = "day2/day2Input.txt";
	ifstream inFile(filename);

	if (inFile.is_open())
	{
		string line;
		while (getline(inFile, line))
		{
			smatch directionCurrent, stepCurrent;
			
			regex_search(line, directionCurrent, regex("[a-z]+"));
			regex_search(line, stepCurrent, regex("[0-9]+"));

			directions.push_back(directionCurrent[0]);
			steps.push_back(stoi(stepCurrent[0]));
		}
	}

	inFile.close();
}

long long solveDay2Part1()
{
	vector<string> directions;
	vector<int> steps;
	int horizontal = 0, depth = 0;

	readInputDay2(directions, steps);

	for (int index = 0; index < directions.size(); ++index)
	{
		if (directions[index] == "forward")
		{
			horizontal += steps[index];
		}
		else if (directions[index] == "down")
		{
			depth += steps[index];
		}
		else if (directions[index] == "up")
		{
			depth -= steps[index];
		}
	}

	return (long long)horizontal * (long long)depth;
}

int solveDay2Part2()
{
	vector<string> directions;
	vector<int> steps;
	int horizontal = 0, depth = 0, aim = 0;

	readInputDay2(directions, steps);

	for (int index = 0; index < directions.size(); ++index)
	{
		if (directions[index] == "forward")
		{
			horizontal += steps[index];
			depth += aim * steps[index];
		}
		else if (directions[index] == "down")
		{
			aim += steps[index];
		}
		else if (directions[index] == "up")
		{
			aim -= steps[index];
		}
	}

	return (long long)horizontal * (long long)depth;
}