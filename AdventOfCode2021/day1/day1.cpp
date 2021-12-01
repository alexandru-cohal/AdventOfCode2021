#include "day1.h"

vector<int> readInputDay1()
{
	vector<int> measurements;

	string filename = "day1/day1Input.txt";
	ifstream inFile(filename);

	if (inFile.is_open())
	{
		long long currentMeasurement;
		while (!inFile.eof())
		{
			inFile >> currentMeasurement;
			measurements.push_back(currentMeasurement);
		}
	}

	inFile.close();

	return measurements;
}

int solveDay1Part1()
{
	vector<int> measurements = readInputDay1();
	int numIncreases = 0;

	for (int index = 1; index < measurements.size(); ++index)
	{
		if (measurements[index] > measurements[index - 1])
		{
			numIncreases++;
		}
	}

	return numIncreases;
}

int solveDay1Part2()
{
	vector<int> measurements = readInputDay1();
	int numIncreases = 0;
	int sumLastWindow, sumCurrentWindow;

	if (measurements.size() >= 3)
	{
		sumLastWindow = measurements[0] + measurements[1] + measurements[2];
	}
	else
	{
		return 0;
	}

	for (int indexLast = 3; indexLast < measurements.size(); ++indexLast)
	{
		sumCurrentWindow = sumLastWindow - measurements[indexLast - 3] + measurements[indexLast];

		if (sumCurrentWindow > sumLastWindow)
		{
			numIncreases++;
		}
	}

	return numIncreases;
}