//Developer: Cameron Peeters
//Project: traversalTypes
//Abstract: to show how different traversal types work i.e.(recusion and dijsktras)
//In progress: implement dijsktras algorithm 
//Compiler: g++ -std=c++11 -g -Wall traversalTypes.cpp

// Header files
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <unordered_map>
#include <fstream>

// namespaces
using namespace std;

// Robot class to traverse the maze
class Robot
{
private:
	vector<char> _path;
	int steps = 0;
	int xStart = 0;
	int yStart = 0;

public:
	bool mazeTraverse(vector<string> &, int xLoc, int yLoc, char facing);
	void savePath();
	void loadPath();
	void clearPath();
	void displayStats();
	int getSteps();
};

// Traverse through the maze using recusion to check each direction
bool Robot::mazeTraverse(vector<string> &maze, int xLoc, int yLoc, char facing)
{
	bool success = false;
	maze[xLoc][yLoc] = 'R';   // current location in the maze

	while (success == false)	// while the end char ['f'] is not found
	{
		// faceing north(forward)
		if (facing == 'N')
		{
			// check for valid symbols in y++ direction
			if (maze[xLoc][yLoc+1] == '*' || maze[xLoc][yLoc+1] == 'f' || maze[xLoc][yLoc+1] == 'b' )
			{
				_path.push_back('E');
				steps++;

				// if 'f' return
				if (maze[xLoc][yLoc+1] == 'f')
				{
					yLoc++;
					maze[xLoc][yLoc] = 'R';
					success = true;	
					return success;

				}
				success = mazeTraverse(maze, xLoc, yLoc+1, 'E');
			}
			else if (maze[xLoc-1][yLoc] == '*' || maze[xLoc-1][yLoc] == 'f' || maze[xLoc-1][yLoc] == 'b')
			{
				_path.push_back('N');
				steps++;

				if (maze[xLoc-1][yLoc] == 'f')	
				{
					xLoc--;
					maze[xLoc][yLoc] = 'R';
					success = true;
					return success;

				}
				success = mazeTraverse(maze, xLoc-1, yLoc, 'N');
			}
			else if (maze[xLoc][yLoc-1] == '*' || maze[xLoc][yLoc-1] == 'f' || maze[xLoc][yLoc-1] == 'b')	
			{
				_path.push_back('W');
				steps++;

				if (maze[xLoc][yLoc-1] == 'f')	
				{
					yLoc--;
					maze[xLoc][yLoc] = 'R';
					success = true;	
					return success;

				}
				success = mazeTraverse(maze, xLoc, yLoc-1, 'W');	
			}
			else
			{	
				if (success == false)
						_path.erase(_path.end()-1);
				steps++;
				maze[xLoc][yLoc] = 'X';
				return false;	
			}
		}
		else if (facing == 'E')	
		{
			if (maze[xLoc+1][yLoc] == '*' || maze[xLoc+1][yLoc] == 'f' || maze[xLoc+1][yLoc] == 'b' )	
			{
				_path.push_back('S');
				steps++;

				if (maze[xLoc+1][yLoc] == 'f')
				{
					xLoc++;
					maze[xLoc][yLoc] = 'R';
					success = true;	
					return success;

				}

				success = mazeTraverse(maze, xLoc+1, yLoc, 'S');	
			}
			else if (maze[xLoc][yLoc+1] == '*' || maze[xLoc][yLoc+1] == 'f' || maze[xLoc][yLoc+1] == 'b')
			{
				_path.push_back('E');
				steps++;

				if (maze[xLoc][yLoc+1] == 'f')	
				{
					yLoc++;
					maze[xLoc][yLoc] = 'R';
					success = true;
					return success;

				}

				success = mazeTraverse(maze, xLoc, yLoc+1, 'E');	
			}
			else if (maze[xLoc-1][yLoc] == '*' || maze[xLoc-1][yLoc] == 'f' || maze[xLoc-1][yLoc] == 'b')	
			{
				_path.push_back('N');
				steps++;

				if (maze[xLoc-1][yLoc] == 'f')	
				{
					xLoc--;
					maze[xLoc][yLoc] = 'R';
					success = true;	
					return success;

				}

				success = mazeTraverse(maze, xLoc-1, yLoc, 'N');	
			}
			else
			{
				if (success == false)
						_path.erase(_path.end()-1);
				maze[xLoc][yLoc] = 'X';
				steps++;
				return false;	
			}

		}
		else if (facing == 'S')
		{
			if (maze[xLoc][yLoc-1] == '*' || maze[xLoc][yLoc-1] == 'f' || maze[xLoc][yLoc-1] == 'b')	
			{
				_path.push_back('W');
				steps++;

				if (maze[xLoc][yLoc-1] == 'f')	
				{
					yLoc--;
					maze[xLoc][yLoc] = 'R';					
					success = true;
					return success;

				}

				success = mazeTraverse(maze, xLoc, yLoc-1, 'W');	
			}
			else if (maze[xLoc+1][yLoc] == '*' || maze[xLoc+1][yLoc] == 'f' || maze[xLoc+1][yLoc] == 'b')	
			{
				_path.push_back('S');
				steps++;

				if (maze[xLoc+1][yLoc] == 'f')	
				{
					xLoc++;
					maze[xLoc][yLoc] = 'R';
					success = true;	
					return success;

				}

				success = mazeTraverse(maze, xLoc+1, yLoc, 'S');	
			}
			else if (maze[xLoc][yLoc+1] == '*' || maze[xLoc][yLoc+1] == 'f' || maze[xLoc][yLoc+1] == 'b')	
			{
				_path.push_back('E');
				steps++;

				if (maze[xLoc][yLoc+1] == 'f')	
				{
					yLoc++;
					maze[xLoc][yLoc] = 'R';
					success = true;	
					return success;

				}

				success = mazeTraverse(maze, xLoc, yLoc+1, 'E');
			}
			else
			{
				if (success == false)
						_path.erase(_path.end()-1);
				maze[xLoc][yLoc] = 'X';
				steps++;
				return false;
			}
		}
		else if (facing == 'W')
		{
			if (maze[xLoc-1][yLoc] == '*' || maze[xLoc-1][yLoc] == 'f' || maze[xLoc-1][yLoc] == 'b')
			{
				_path.push_back('N');
				steps++;

				if (maze[xLoc-1][yLoc] == 'f')
				{
					xLoc--;
					maze[xLoc][yLoc] = 'R';
					success = true;	
					return success;

				}
				success = mazeTraverse(maze, xLoc-1, yLoc, 'N');	
			}
			else if (maze[xLoc][yLoc-1] == '*' || maze[xLoc][yLoc-1] == 'f' || maze[xLoc][yLoc-1] == 'b')
			{
				_path.push_back('W');
				steps++;

				if (maze[xLoc][yLoc-1] == 'f')	
				{
					yLoc--;
					maze[xLoc][yLoc] = 'R';
					success = true;	
					return success;

				}

				success = mazeTraverse(maze, xLoc, yLoc-1, 'W');
			}
			else if (maze[xLoc+1][yLoc] == '*' || maze[xLoc+1][yLoc] == 'f' || maze[xLoc+1][yLoc] == 'b')
			{
				_path.push_back('S');
				steps++;

				if (maze[xLoc+1][yLoc] == 'f')
				{
					xLoc++;
					maze[xLoc++][yLoc] = 'R';
					success = true;	
					return success;

				}

				success = mazeTraverse(maze, xLoc+1, yLoc, 'S');
			}
			else	
			{
				if (success == false)
						_path.erase(_path.end()-1);
				maze[xLoc][yLoc] = 'X';
				steps++;
				return false;	
			}
		}
	}	

	savePath();
	return success;	
}
void Robot::savePath()
{

	ofstream outputFile;
	outputFile.open("path.txt");

	for (unsigned int i = 0; i < _path.size(); i++)
	{
		outputFile << _path[i] << "\t\r\n";

	}

	outputFile.close();
}
void Robot::loadPath() 
{
	char pathChar;

	//cout << "Loading Data: " << endl;
	ifstream inFile;
	inFile.open("path.txt");

	if (inFile.is_open())
  	{
  		_path.clear();

  	  while (!inFile.eof())
    	{
    		inFile >> pathChar;
    		_path.push_back(pathChar);
    	}

    	_path.erase(_path.end()-1);

   	 inFile.close();
  	}
  	else
  	{
  		cout << "No data found.\n";
  	}
}
void Robot::displayStats()
{
	//displays the path
	cout << "Best Path: ";
	for (unsigned int i = 0; i < _path.size(); i++)
	{
		cout << _path[i] << " ";
	}
	cout << endl;

	//displays steps
	cout << "Steps: " << steps << endl;

}
int Robot::getSteps()
{
	return steps;
}
void Robot::clearPath()
{
	_path.clear();
	savePath();
}

// Holds the room for the Robot to traverse
class Room
{
private:
	int xLoc, yLoc;

public:
	vector<string> maze;

	void printMaze();
	void loadMaze(string);
	void setLocations();
	int getXLoc();
	int getYLoc();

};

// print the current state of the maze
void Room::printMaze()
{
	cout << "Room:" << endl;
	for (unsigned int i = 0; i < maze.size(); i++)
	{
		cout << maze[i] << endl;
	}
} // end function printMaze
void Room::setLocations()
{
	for (unsigned int i = 0; i < maze.size(); i++) // sets the starting position of the robot
	{
		for (unsigned int j = 0; j < maze[0].length(); j++)
		{
			if (maze[i][j] == 's')
			{
				xLoc = i;
				yLoc = j;
			}
		}
	}
}
void Room::loadMaze(string mazeName)
{
	string line;

	//cout << "Loading Data: " << endl;
	ifstream inFile;
	inFile.open(mazeName);

	if (inFile.is_open())
  	{
  		maze.clear();

  	  while (!inFile.eof())
    	{
    		inFile >> line;
    		maze.push_back(line);
    	}

    	maze.erase(maze.end()-1);

   	 inFile.close();
  	}
  	else
  	{
  		cout << "No data found.\n";
  	}
}
int Room::getXLoc()
{
	return xLoc;
}
int Room::getYLoc()
{
	return yLoc;
}
int main()
{
	Room room;
	Robot robot;

	//init room;
	room.loadMaze("room.txt");
	room.setLocations();
	room.loadMaze("room.txt");
	room.printMaze();

	//recursion method
	cout << "\nTraversal Method: Recursion "<< endl;
	robot.mazeTraverse(room.maze, room.getXLoc(), room.getYLoc(),'N');
	robot.displayStats();
	room.printMaze();
}

