#include "day4.h"

void readInputDay4(vector<int> &drawnNumbers, 
					vector<map<int, location>> &boards,
					int &boardNumRows,
					int &boardNumCols)
{
	string filename = "day4/day4Input.txt";
	ifstream inFile(filename);
	string line;
	
	// Get the drawn numbers
	getline(inFile, line); // Read the drawn numbers
	
	smatch number;
	while (regex_search(line, number, regex("[0-9]+")))
	{
		drawnNumbers.push_back(stoi(number[0]));
		line = number.suffix();
	}

	getline(inFile, line); // Read the empty line after the drawn numbers

	// Get the boards 
	int indexBoard = 0, indexRow = -1, indexCol = 0;
	map<int, location> boardCurrent;
	if (inFile.is_open())
	{
		while (getline(inFile, line))
		{
			if (line == "")
			{
				// End of the board
				boards.push_back(boardCurrent);
				boardCurrent.clear();
				indexBoard++;
				indexRow = -1;
			}
			else
			{
				// New line of the board
				indexRow++;
				indexCol = -1;
				while (regex_search(line, number, regex("[0-9]+")))
				{
					indexCol++;
					location loc = { indexRow, indexCol };
					boardCurrent[stoi(number[0])] = loc;
					line = number.suffix();
				}
			}
		}
		boards.push_back(boardCurrent);
	}

	boardNumRows = indexRow + 1;
	boardNumCols = indexCol + 1;

	inFile.close();
}

void markDrawNumber(int drawnNumber, 
					vector<map<int, location>> boards, 
					vector<vector<int>> &numDrawnNumbersPerRow,
					vector<vector<int>> &numDrawnNumbersPerCol,
					set<int> indicesCompletedBoards)
{
	for (int indexBoard = 0; indexBoard < boards.size(); ++indexBoard)
	{
		if (indicesCompletedBoards.find(indexBoard) == indicesCompletedBoards.end())
		{
			if (boards[indexBoard].find(drawnNumber) != boards[indexBoard].end())
			{
				// Drawn number present on the board
				numDrawnNumbersPerRow[indexBoard][boards[indexBoard][drawnNumber].row]++;
				numDrawnNumbersPerCol[indexBoard][boards[indexBoard][drawnNumber].col]++;
			}
		}
	}
}

vector<int> checkBoards(vector<vector<int>> numDrawnNumbersPerRow,
						vector<vector<int>> numDrawnNumbersPerCol,
						int boardNumRows, 
						int boardNumCols,
						set<int> indicesCompletedBoards)
{
	vector<int> completedBoards;

	for (int indexBoard = 0; indexBoard < numDrawnNumbersPerRow.size(); ++indexBoard)
	{
		if (indicesCompletedBoards.find(indexBoard) == indicesCompletedBoards.end())
		{
			for (int indexRow = 0; indexRow < numDrawnNumbersPerRow[indexBoard].size(); ++indexRow)
			{
				if (numDrawnNumbersPerRow[indexBoard][indexRow] == boardNumRows)
				{
					// Line complete
					completedBoards.push_back(indexBoard);
				}
			}
		}

		for (int indexCol = 0; indexCol < numDrawnNumbersPerCol[indexBoard].size(); ++indexCol)
		{
			if (numDrawnNumbersPerCol[indexBoard][indexCol] == boardNumCols)
			{
				// Column complete
				completedBoards.push_back(indexBoard);
			}
		}
	}

	return completedBoards;
}

int getFinalScore(map<int, location> board, 
				  vector<int> drawnNumbers)
{
	int finalScore = 0;

	for (int indexNumber = 0; indexNumber < drawnNumbers.size(); ++indexNumber)
	{
		board.erase(drawnNumbers[indexNumber]);
	}

	for (map<int, location>::iterator it = board.begin(); it != board.end(); ++it)
	{
		finalScore += it->first;
	}

	return finalScore * drawnNumbers.back();
}

int solveDay4Part1()
{
	vector<int> drawnNumbers;
	vector<map<int, location>> boards;
	int boardNumRows, boardNumCols;
	readInputDay4(drawnNumbers, boards, boardNumRows, boardNumCols);

	vector<vector<int>> numDrawnNumbersPerRow(boards.size(), vector<int>(boardNumRows));
	vector<vector<int>> numDrawnNumbersPerCol(boards.size(), vector<int>(boardNumCols));
	vector<int> completedBoards;
	set<int> indicesCompletedBoards;
	for (int indexNumber = 0; indexNumber < drawnNumbers.size(); ++indexNumber)
	{
		int drawNumber = drawnNumbers[indexNumber];

		markDrawNumber(drawNumber, boards, numDrawnNumbersPerRow, numDrawnNumbersPerCol, indicesCompletedBoards);
		completedBoards = checkBoards(numDrawnNumbersPerRow, numDrawnNumbersPerCol, boardNumRows, boardNumCols, indicesCompletedBoards);
		if (completedBoards.size() > 0)
		{
			return getFinalScore(boards[completedBoards[0]], { drawnNumbers.begin(), drawnNumbers.begin() + indexNumber + 1 });
		}
	}

	return -1; // It shouldn't get here
}

int solveDay4Part2()
{
	vector<int> drawnNumbers;
	vector<map<int, location>> boards;
	int boardNumRows, boardNumCols;
	readInputDay4(drawnNumbers, boards, boardNumRows, boardNumCols);

	vector<vector<int>> numDrawnNumbersPerRow(boards.size(), vector<int>(boardNumRows));
	vector<vector<int>> numDrawnNumbersPerCol(boards.size(), vector<int>(boardNumCols));
	set<int> indicesCompletedBoards;
	for (int indexNumber = 0; indexNumber < drawnNumbers.size(); ++indexNumber)
	{
		int drawNumber = drawnNumbers[indexNumber];

		markDrawNumber(drawNumber, boards, numDrawnNumbersPerRow, numDrawnNumbersPerCol, indicesCompletedBoards);
		vector<int> completedBoards = checkBoards(numDrawnNumbersPerRow, numDrawnNumbersPerCol, boardNumRows, boardNumCols, indicesCompletedBoards);
		
		int lastCompletedBoard;
		for (int indexCompletedBoard = 0; indexCompletedBoard < completedBoards.size(); ++indexCompletedBoard)
		{
			lastCompletedBoard = completedBoards[indexCompletedBoard];
			indicesCompletedBoards.insert(completedBoards[indexCompletedBoard]);
		}

		if (indicesCompletedBoards.size() == boards.size())
		{
			return getFinalScore(boards[lastCompletedBoard], { drawnNumbers.begin(), drawnNumbers.begin() + indexNumber + 1 });
		}
	}

	return -1; // It shouldn't get here
}