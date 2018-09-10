#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <stdlib.h> 
#include <stack>
#include <ctime>


#include "Generator.h"

using namespace std;

Generator::Generator()
{

}

Generator::Generator(int a)
{
	area = a;
}

/*
Generator::~Generator()
{

}
*/


int Generate_Random_Direction()
{
	int random = (rand() % 4) + 1;
	return random;
	// Returns a random number between 1 - 4 to choose which wall to knock down in the generation of the maze
}

bool Generator::setSize(int s)
{
	if (35 >= s && s > 5 && s % 2 != 0)
		// Need the entered value to be under 75 and over 5. It also cannot be even
	{
		area = s;
		return true;
	}
	// if the inputed column amount is creater than 5 and odd, then set them equal
	// and return true.
	else
	{
		return false;
	}
	// otherwise return false
}

void Generator::Intialize_Matrix()
{
	for (int i = 0; i < area; i++)
	{
		for (int j = 0; j < area; j++)
		{
			maze_matrix[i][j].display = 1;
			// I want this matrix to contain 1's for non-visted cells

			maze_matrix[i][j].visited = false;
			// When I visit a cell, I need to mark that I have

			maze_matrix[i][j].wall_top = true;
			maze_matrix[i][j].wall_bot = true;
			maze_matrix[i][j].wall_left = true;
			maze_matrix[i][j].wall_right = true;
			// These specify the walls of the matrix and if they are possible to "Break Down"

			// Loop over the maze matrix and fill it full of ones
			// We are also intializing all of the cells here. each cell has bool values assosiated with whether or not they have been visted.
		}
	}
	int r = 1;
	while(r < area-1) 
	{
		for(int c = 1; c < area-1; c++)
		{
			maze_matrix[1][c].wall_top = false;
			maze_matrix[area-2][c].wall_bot = false;
			maze_matrix[r][1].wall_left = false;
			maze_matrix[r][area-2].wall_right = false;

			maze_matrix[0][c].visited = true;
			maze_matrix[area-1][c].visited = true;
			// The Cells on the borders have fewer accessible walls. We need to insure they cant be pathed through
			// We now loop through the cells again and set out border cells so that the walls cannot be broken
		}

		maze_matrix[r][0].visited = true;
		maze_matrix[r][area-1].visited = true;
		r++;
	}
}

void Generator::GenerateMaze()
{
	int random_Column = 0;
	int random_Row = 0;

	random_Column = (area-1)/2;
	random_Row = (area-1)/2;
	// Generate the start from the middle to avoid seg fault

	int totalCells = ((area-1)/2)*((area-1)/2);
	// Calculate the total number of useable cells

	int random;

	int visitedCells = 1;
	// lets mark the start cell as a visted cell

	maze_matrix[random_Row][random_Column].visited = true;
	// Mark the cell visited inside the object as true

	maze_matrix[random_Row][random_Column].display = 0;
	// Mark the starting cell as 0 for the array purposes.

	int direction;
	// An integer (defined later) that specifies the direction that we are going to move. We will set this equal to the direction generator to determine the direction 


	stack <int> back_row, back_column;
	// First time using stack. It can be used as a array in a sense that makes it super easy to do a depth- first search. 
	// Stack allows me to pull items out of the top of the stack and store them in the top or the bottom. This allows my
	// code to be able to back track easily inorder to fully accomplish the algorithm.


	while (visitedCells < totalCells)
	// While there are still unvisted cells
	{


		// Prepare yourself for the if statement of all if statements...
		// the if statement to rule them all...
		// the if statement of kings...
		if (((maze_matrix[random_Row-2][random_Column].visited == false) && (maze_matrix[random_Row][random_Column].wall_top == true && maze_matrix[random_Row-2][random_Column].wall_bot == true)) ||  ((maze_matrix[random_Row+2][random_Column].visited == false) && (maze_matrix[random_Row][random_Column].wall_bot == true && maze_matrix[random_Row+2][random_Column].wall_top == true)) ||  ((maze_matrix[random_Row][random_Column-2].visited == false) && (maze_matrix[random_Row][random_Column].wall_left == true && maze_matrix[random_Row][random_Column-2].wall_right == true)) ||  ((maze_matrix[random_Row][random_Column+2].visited == false) && (maze_matrix[random_Row][random_Column].wall_right == true && maze_matrix[random_Row][random_Column+2].wall_left == true)))	
		   	// wow! that was long. Okay, now to try to explain this MASSIVE if statement. Essentially, we are using this if statment to see if any of the cells around us are useable as paths. We would like to go to these cells
			// but first we need to check to see if the walls are able to be torn down and if we have visted them already.
		{

			random = Generate_Random_Direction();
			// Cool, this gives us a random direction (aka a number from 1-4)
			/* 	Each number represents the direction shown below. 
					1 = Up
					2 = Right
					3 = Down
					4 = Left
			*/
			if (random == 1 && random_Row > 1)
			// Lets start with up! If the random number is 1, lets first make sure that we are not on the top row. We cannot go past the border!
			{
					if (maze_matrix[random_Row-2][random_Column].visited == false)
					// If we have not visted the cell above us..
					{
						// Cell inbetween...
						maze_matrix[random_Row-1][random_Column].display = 0;
						// Mark the cell as visted and set the display accordingly
						maze_matrix[random_Row-1][random_Column].visited = true;
						maze_matrix[random_Row][random_Column].wall_top = false;
						//Get ride of the wall inbetween our cells



						// Cell we are moving to
						maze_matrix[random_Row-2][random_Column].display = 0;
						// Mark the cell as visted and set the display accordingly
						maze_matrix[random_Row-2][random_Column].visited = true;
						maze_matrix[random_Row-2][random_Column].wall_bot = false;
						// knock down the bottom wall

						back_row.push(random_Row);
						back_column.push(random_Column);

						random_Row -= 2;
						visitedCells++;
					}
					else
					{
						continue;
					}
			}

			else if ((random == 2) && (random_Column < area-2))
			// Let go right now! If the random number is 2, lets first make sure that we are not on the far right row. We cannot go past the border!
			{
					if (maze_matrix[random_Row][random_Column+2].visited == false)
					// If we have not visted the cell to the right of us..
					{
						// Cell inbetween...
						maze_matrix[random_Row][random_Column+1].display = 0;
						// Mark the cell as visted and set the display accordingly
						maze_matrix[random_Row][random_Column+1].visited = true;
						maze_matrix[random_Row][random_Column].wall_right = false;
						//Get rid of the wall inbetween our cells



						// Cell we are moving to
						maze_matrix[random_Row][random_Column+2].display = 0;
						// Mark the cell as visted and set the display accordingly
						maze_matrix[random_Row][random_Column+2].visited = true;
						maze_matrix[random_Row][random_Column+2].wall_left = false;
						// knock down the left wall

						back_row.push(random_Row);
						back_column.push(random_Column);

						random_Column += 2;
						visitedCells++;
					}
					else
					{
						continue;
					}
			}
			else if ((random == 3) && (area-2 > random_Row))
			// Next to down! If the random number is 3, lets first make sure that we are not on the bottom row. We cannot go past the border!
			{
					if (maze_matrix[random_Row+2][random_Column].visited == false)
					// If we have not visted the cell above us..
					{
						// Cell inbetween...
						maze_matrix[random_Row+1][random_Column].display = 0;
						// Mark the cell as visted and set the display accordingly
						maze_matrix[random_Row+1][random_Column].visited = true;
						maze_matrix[random_Row][random_Column].wall_bot = false;
						//Get ride of the wall inbetween our cells



						// Cell we are moving to
						maze_matrix[random_Row+2][random_Column].display = 0;
						// Mark the cell as visted and set the display accordingly
						maze_matrix[random_Row+2][random_Column].visited = true;
						maze_matrix[random_Row+2][random_Column].wall_top = false;
						// knock down the bottom wall

						back_row.push(random_Row);
						back_column.push(random_Column);

						random_Row += 2;
						visitedCells++;
					}
					else
					{
						continue;
					}
			}
			else if ((random == 4) && (random_Column > 1))
			// Lets finally go left now! If the random number is 4, lets first make sure that we are not on the far left row. We cannot go past the border!
			{
					if (maze_matrix[random_Row][random_Column-2].visited == false)
					// If we have not visted the cell to the right of us..
					{
						// Cell inbetween...
						maze_matrix[random_Row][random_Column-1].display = 0;
						// Mark the cell as visted and set the display accordingly
						maze_matrix[random_Row][random_Column-1].visited = true;
						maze_matrix[random_Row][random_Column].wall_left = false;
						//Get rid of the wall inbetween our cells


						// Cell we are moving to
						maze_matrix[random_Row][random_Column-2].display = 0;
						// Mark the cell as visted and set the display accordingly
						maze_matrix[random_Row][random_Column-2].visited = true;
						maze_matrix[random_Row][random_Column-2].wall_right = false;
						// knock down the left wall

						back_row.push(random_Row);
						back_column.push(random_Column);

						random_Column -= 2;
						visitedCells++;
					}
					else
					{
						continue;
					}
			}
		}
		else
		{
			random_Row = back_row.top();
			random_Column = back_column.top();
			//Sets the random row and column to the top elements in the stack

			back_column.pop();
			back_row.pop();
			//Removes the top element in the stack

		// If all the cells around are used, back track to the last location and try again. 
		}
	}
}

void Generator::Print_Matrix()
{
	cout << '\n' << endl;
	for (int i = 0; i < area; i++)
	{
		for (int j = 0; j < area; j++)
		// loop over the matrix
		{
			if (maze_matrix[i][j].display == 0)
			{
				cout << " ";
			}
			else if (maze_matrix[i][j].display == 1)
			{
				cout << "*";
			}
			else if (maze_matrix[i][j].display == 2)
			{
				cout << "S";
			}
			else if (maze_matrix[i][j].display == 3)
			{
				cout << "F";
			}
			// change what the outputs display to make the maze easier to read and understand
		}
		cout << endl;
	}
}

void Generator::Set_Start_Finish()
{
	maze_matrix[1][1].display = 2;
	// set the start in the top left

	maze_matrix[area-2][area-2].display = 3;
	// set the end in the bottom right
}

void Generator::Save_Maze(string filename)
{
	ofstream file;

	file.open(filename);
	// This section of the code simply saves the 

	file << "Maze - " << filename << "\n" << endl;

	for (int i = 0; i < area; i++)
	{
		for (int j = 0; j < area; j++)
		// loop over the matrix
		{
			if (maze_matrix[i][j].display == 0)
			{
				file << " ";
			}
			else if (maze_matrix[i][j].display == 1)
			{
				file << "*";
			}
			else if (maze_matrix[i][j].display == 2)
			{
				file << "S";
			}
			else if (maze_matrix[i][j].display == 3)
			{
				file << "F";
			}
			// Depending on what the matrix has, convert it to something easier to read and save it to a file
		}
		file << endl;
	}
	file.close();
	// close the file and return success
	cout << "Success!" <<endl;
}