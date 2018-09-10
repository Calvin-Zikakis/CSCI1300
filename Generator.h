#ifndef Generator_h
#define Generator_h

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
//Not sure what needs to be defined yet.

using namespace std;



struct Cell
{
	bool visited;
	bool wall_bot;
	bool wall_top;
	bool wall_left;
	bool wall_right;
	int display;
};
// create an object called Cell. This will house all info we need to know about the cell.
// It contains info on if we have visted the cell, the walls still avaliable and the integer to display. (One = wall)

class Generator
{
	public:
		Generator();
		//Constructor

		Generator(int);

		//~Generator();
		//Destructor

		bool setSize(int);
		//Set the number of rows wanted for the maze (must be odd)

		void Intialize_Matrix();
		// initializes the matrix. ie sets the borders and the cells

		void CreateMatrix();
		//Creates a matrix with the specified row and column amount

		void GenerateMaze();
		//uses depth first algorithm to generate maze, returns the matrix

		void Set_Start_Finish();
		//This function sets the start and finish position.

		void Print_Matrix();
		//Converts the maze to a standard matrix

		void Save_Maze(string);

		int area;

		Cell maze_matrix[35][35];
		// Maximum size for our matrix is 75 x 75


};

#endif //Generator_h

