#include "day3.h"

vector<string> readInputDay3()
{
	vector<string> numbers;
	string filename = "day3/day3Input.txt";
	ifstream inFile(filename);

	if (inFile.is_open())
	{
		string line;
		while (getline(inFile, line))
		{
			numbers.push_back(line);
		}
	}

	inFile.close();

	return numbers;
}

long long solveDay3Part1()
{
	vector<string> numbers = readInputDay3();
	vector<int> countBits1;
	long long epsilonRate = 0, gammaRate = 0;

	for (int indexNumber = 0; indexNumber < numbers.size(); ++indexNumber)
	{
		for (int indexBit = 0; indexBit < numbers[indexNumber].size(); ++indexBit)
		{
			if (indexNumber == 0)
			{
				if (numbers[indexNumber][indexBit] == '0')
				{
					countBits1.push_back(0);
				}
				else
				{
					countBits1.push_back(1);
				}
			}
			else
			{
				if (numbers[indexNumber][indexBit] == '1')
				{
					countBits1[indexBit]++;
				}
			}
		}
	}

	for (int indexBit = 0; indexBit < numbers[0].size(); ++indexBit)
	{
		epsilonRate *= 2;

		if (countBits1[indexBit] >= (numbers.size() / 2))
		{
			epsilonRate++;
		}
	}

	gammaRate = ((1 << (long long)numbers[0].size()) - 1) - epsilonRate;

	return epsilonRate * gammaRate;
}

long long solveDay3Part2()
{
	vector<string> numbers = readInputDay3();
	vector<string> numbersWithBit0;
	vector<string> numbersWithBit1;
	int oxygenRating = 0, co2Rating = 0;

	// Oxygen Rating
	for (int indexBit = 0; indexBit < numbers[0].size(); ++indexBit)
	{
		for (int indexNumber = 0; indexNumber < numbers.size(); ++indexNumber)
		{
			if (numbers[indexNumber][indexBit] == '1')
			{
				numbersWithBit1.push_back(numbers[indexNumber]);
			}
			else
			{
				numbersWithBit0.push_back(numbers[indexNumber]);
			}
		}

		if (numbersWithBit1.size() >= numbersWithBit0.size())
		{
			numbers = numbersWithBit1;
		}
		else
		{
			numbers = numbersWithBit0;
		}

		numbersWithBit0.clear();
		numbersWithBit1.clear();


		if (numbers.size() == 1)
		{
			break;
		}
	}

	for (int indexBit = 0; indexBit < numbers[0].size(); ++indexBit)
	{
		oxygenRating = oxygenRating * 2 + (numbers[0][indexBit] - '0');
	}

	// CO2 Rating
	numbers = readInputDay3();

	for (int indexBit = 0; indexBit < numbers[0].size(); ++indexBit)
	{
		for (int indexNumber = 0; indexNumber < numbers.size(); ++indexNumber)
		{
			if (numbers[indexNumber][indexBit] == '1')
			{
				numbersWithBit1.push_back(numbers[indexNumber]);
			}
			else
			{
				numbersWithBit0.push_back(numbers[indexNumber]);
			}
		}

		if (numbersWithBit1.size() < numbersWithBit0.size())
		{
			numbers = numbersWithBit1;
		}
		else
		{
			numbers = numbersWithBit0;
		}

		numbersWithBit0.clear();
		numbersWithBit1.clear();


		if (numbers.size() == 1)
		{
			break;
		}
	}

	for (int indexBit = 0; indexBit < numbers[0].size(); ++indexBit)
	{
		co2Rating = co2Rating * 2 + (numbers[0][indexBit] - '0');
	}

	return (long long)oxygenRating * co2Rating;
}