#include "index.h"

using namespace std;

index::index()
{

}

void index::print_Maze_Terminal(string filename)
//accepts a filename for a saved maze and outputs the maze to terminal
{
	ifstream myfile;
	myfile.open(filename);
	// open the file

	string line;

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            cout << line <<endl;
            // return the contents of the line and loop to the next one.
        }
    }
    else
    {
    	cout << "Couldn't find that file!" <<endl;
    }

}
 
void index::Maze_to_array(string filename, int size, string array[35][35])
//accepts a filename for a saved maze and outputs the maze to the array specified
{
	ifstream myfile;
	myfile.open(filename);
	// open the file

	string line;

	int count = 0;
	getline(myfile, line);
	getline(myfile, line);

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
        	// return the contents of the line
            for (int i = 0; i < size; i++)
            {
            	// Loop over that line
            	array[count][i] = line[i];
            	// store the value to the array
            }
        	count++;

        }
        cout << "Success!" << endl;
    }
    else
    {
    	cout << "Couldn't find that file!" <<endl;
    }
}

void index::Change_icons(string filename, string start, string finish, string wall, string path, string output, int size)
{
	ifstream myfile;
	myfile.open(filename);
	// open the file

	ofstream file1;
	file1.open(output);
	// for the output file

	file1 << "Maze - " << filename << " - Different Icons\n" << endl;
	// Start writing the new file

	string line;

	int count = 0;
	getline(myfile, line);
	getline(myfile, line);

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
        	// return the contents of the line
            for (int i = 0; i < size; i++)
            {
            	// Loop over that line

            	if (line[i] == 'S')
            	{
            		file1 << start;
            	}
            	else if (line[i] == ' ')
            	{
            		file1 << path;
            	}
            	else if (line[i] == '*')
            	{
            		file1 << wall;
            	}
            	else if (line[i] == 'F')
            	{
            		file1 << finish;
            	}
            	//Convert the icons
            }
        	file1 << endl;
        	count++;
        	//add one to the count and end the line

        }
        cout << "Success!" << endl;
        file1.close();
		// close the file
    }
    else
    {
    	cout << "Couldn't find that file!" <<endl;
    }


}



void index::Write_Difficulty(string filename, int difficulty)
{
	ofstream add_to(filename, ios_base::app | ios_base::out);
	add_to << "The difficulty of this maze is - " << difficulty <<"/10"<<endl;
	// Append the Difficulty to the file
}


