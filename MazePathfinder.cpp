// https://www.codeabbey.com/index/task_view/maze-pathfinder
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "Console.h"
#include "CodeAbbey.h"
#include "LS_library.h"
#define VERSION "1.0"

using namespace std;
int main()
{
	//
	cout << "MazePathfinder v" << VERSION << "!\n\n";
	string path = "Test.txt";
	//string path = "Try.txt";
	vector<string> raw_data = loadData(path);
	//printVector(raw_data);
	//
	vector<int> WH = splitToInt(raw_data[0], " ");
	const int WIDTH = WH[0];
	const int HEIGHT = WH[1];
	vector<vector<string>> data(HEIGHT, vector<string>(WIDTH, ""));

	for (int r = 1; r < raw_data.size(); r++) {
		vector<string> row = splitString(raw_data[r], " ");
		data.at(r - 1) = row;
	}
	print2DVector(data);
}


