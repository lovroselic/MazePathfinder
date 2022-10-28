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

vector<vector<vector<string>>> Traverse(vector<vector<string>>& map, int W, int H);
string Resolve(vector<string>& cell);

int main() {
	//
	cout << "MazePathfinder v" << VERSION << "!\n\n";
	//string path = "Test.txt";
	string path = "Try.txt";
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
	//print2DVector(data);

	vector<vector<vector<string>>> SolvedPath = Traverse(data, WIDTH, HEIGHT);
	//print3DVector(SolvedPath);
	cout << "Solution: ";
	cout << Resolve(SolvedPath[0][WIDTH - 1]) << " ";
	cout << Resolve(SolvedPath[HEIGHT - 1][0]) << " ";
	cout << Resolve(SolvedPath[HEIGHT - 1][WIDTH - 1]) << endl;
}

string Resolve(vector<string>& cell) {
	reverse(cell.begin(), cell.end());
	string compacted = "";
	string pchar = "";
	int count = 0;
	for (auto& c : cell) {
		if (c == pchar) {
			count++;
		}
		else {
			if (count > 0) {
				compacted += to_string(count);
				compacted += pchar;
			}
			pchar = c;
			count = 1;
		}

	}
	compacted += to_string(count);
	compacted += pchar;

	return compacted;
}

vector<vector<vector<string>>> Traverse(vector<vector<string>>& map, int W, int H) {
	vector<vector<vector<string>>> path(H, vector<vector<string>>(W, vector<string>()));
	vector<vector<int>> stack;
	vector<vector<bool>> mark(H, vector<bool>(W, false));

	stack.push_back({ 0,0 });
	mark[0][0] = true;

	while (stack.size() > 0) {
		vector<int> coord = stack.rbegin()[0];
		stack.pop_back();
		int x = coord[0];
		int y = coord[1];

		//left
		if (x + 1 < W) {
			if (!mark[y][x + 1] && map[y][x + 1] == "1") {
				path[y][x + 1] = path[y][x];
				path[y][x + 1].push_back("L");
				stack.push_back({ x + 1, y });
				mark[y][x + 1] = true;
			}
		}
		//right
		if (x - 1 >= 0) {
			if (!mark[y][x - 1] && map[y][x - 1] == "1") {
				path[y][x - 1] = path[y][x];
				path[y][x - 1].push_back("R");
				stack.push_back({ x - 1, y });
				mark[y][x - 1] = true;
			}
		}
		//up
		if (y + 1 < H) {
			if (!mark[y + 1][x] && map[y + 1][x] == "1") {
				path[y + 1][x] = path[y][x];
				path[y + 1][x].push_back("U");
				stack.push_back({ x, y + 1 });
				mark[y + 1][x] = true;
			}
		}
		//down
		if (y - 1 >= 0) {
			if (y - 1 >= 0 && !mark[y - 1][x] && map[y - 1][x] == "1") {
				path[y - 1][x] = path[y][x];
				path[y - 1][x].push_back("D");
				stack.push_back({ x, y - 1 });
				mark[y - 1][x] = true;
			}
		}
	}
	return path;
}
