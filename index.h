#ifndef index_h
#define index_h

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

class index
{
	public:

		index();

		void print_Maze_Terminal(string);

		void Maze_to_array(string, int, string[35][35]);

		void Change_icons(string, string, string, string, string, string, int);

		void Write_Difficulty(string, int);

};

#endif //index_h

