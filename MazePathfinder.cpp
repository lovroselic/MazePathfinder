// https://www.codeabbey.com/index/task_view/maze-pathfinder
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "Console.h"
#include "CodeAbbey.h"
#include "LS_library.h"
#define VERSION "0.3"

using namespace std;

vector<vector<vector<string>>> Traverse(vector<vector<string>>& map, int W, int H);

int main() {
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
		vector<string> row = splitString(raw_data[r]);
		data.at(r - 1) = row;
	}
	print2DVector(data);

	vector<vector<vector<string>>> SolvedPath = Traverse(data, WIDTH, HEIGHT);
	print3DVector(SolvedPath);
}

vector<vector<vector<string>>> Traverse(vector<vector<string>>& map, int W, int H) {
	vector<vector<vector<string>>> path(H, vector<vector<string>>(W, vector<string>()));
	vector<vector<int>> stack;
	vector<vector<bool>> mark(H, vector<bool>(W, false));

	//cout << "*****************************" << endl;
	//print2DVector(map);
	//cout << "*****************************" << endl;
	stack.push_back({ 0,0 });
	mark[0][0] = true;
	//path[0][0].push_back("*");

	while (stack.size() > 0) {
		vector<int> coord = stack.rbegin()[0];
		stack.pop_back();
		int x = coord[0];
		int y = coord[1];
		//cout << "\nx: " << x << " y: " << y << endl;

		//left
		//cout << ".right " << x + 1 << " " << y << endl;
		if (x + 1 < W) {
			if (!mark[y][x + 1] && map[y][x + 1] == "1") {
				path[y][x + 1] = path[y][x];
				path[y][x + 1].push_back("L");
				stack.push_back({ x + 1, y });
				mark[y][x + 1] = true;
				//cout << "...*" << endl;
			}
		}
		//
		//break;
		//right
		//cout << ".left " << x - 1 << " " << y << endl;
		if (x - 1 >= 0) {
			if (!mark[y][x - 1] && map[y][x - 1] == "1") {
				path[y][x - 1] = path[y][x];
				path[y][x - 1].push_back("R");
				stack.push_back({ x - 1, y });
				mark[y][x - 1] = true;
				//cout << "...*" << endl;
			}
		}
		//up
		//cout << ".down " << x << " " << y + 1 << endl;
		if (y + 1 < H) {
			if (!mark[y + 1][x] && map[y + 1][x] == "1") {
				path[y + 1][x] = path[y][x];
				path[y + 1][x].push_back("U");
				stack.push_back({ x, y + 1 });
				mark[y + 1][x] = true;
				//cout << "...*" << endl;
			}
		}
		//down
		//cout << ".up " << x << " " << y - 1 << endl;
		if (y - 1 >= 0) {
			if (y - 1 >= 0 && !mark[y - 1][x] && map[y - 1][x] == "1") {
				path[y - 1][x] = path[y][x];
				path[y - 1][x].push_back("D");
				stack.push_back({ x, y - 1 });
				mark[y - 1][x] = true;
				//cout << "...*" << endl;
			}
		}
	}

	//cout << "*****************************" << endl;
	//print2DVector(mark);
	//cout << "*****************************\n" << endl;
	return path;
}
