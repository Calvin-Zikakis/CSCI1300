#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <stdlib.h> 
#include <stack>
#include <ctime>


#include "Generator.h"
#include "index.h"

using namespace std;

int main()
{
	srand((unsigned)time(0));

	Generator test;

	int r = 35;

	Generator test1(r);

	test1.setSize(r);

	test1.Intialize_Matrix();

	test1.GenerateMaze();

	test1.Set_Start_Finish();

	test1.Print_Matrix();

	test1.Save_Maze("Calvin_Random_Maze");

/*	cout << "Test 2" <<endl;

	index test2;

	test2.print_Maze_Terminal("Calvin_Random_Maze");

	string maze[35][35];

	int size = 35;

	string filename = "Calvin_Random_Maze";

	cout << "Test 3" << endl;

	test2.Maze_to_array(filename, size, maze);

	for (int i = 0; i < 35; i++)
	{
		for (int j = 0; j < 35; j++)
		{
			cout << maze[i][j];
		}
		cout << endl;
	}

	string start = "B";
	string finish = "E";
	string wall = "X";
	string path = "O";

	string output = "Different Icons";

	test2.Change_icons(filename, start, finish, wall, path, output, size);
*/
	test2.Write_Difficulty("Calvin_Random_Maze", 6);


}

