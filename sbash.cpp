#include <iostream>
#include <string.h>
#include<sys/types.h>
#include<dirent.h>
#include<unistd.h>

using namespace std;

int main()
{

	bool q = true; // Program flag
	string raw; // Raw input from user

	while(q)
	{

		char buf[FILENAME_MAX];
    	cout << getcwd(buf, FILENAME_MAX);
		cout << " >>> ";
		getline(cin, raw);
		int cursor = 0; // Cursor for building char arrays
		int argc = 0; // Index of char arrays
		char* argsv[10][100]; // 2D Method

		/* Loads all arguments into custom argv buffer with argc as well! */
		for (int i = 0; i < raw.length(); i++)
		{
			argsv[argc][cursor] = &raw[i]; // Points to address of character in the raw input
			cursor++;

			if (raw[i] == ' ' || i == raw.length() - 1)
			{
				cursor = 0;
				argc++; // Increment argc upon blank space detection
			}
		}



		/* Logic */
		// Print current working directory
		if (strcmp(*argsv[0], "cwd") == 0)
		{
			char buf[FILENAME_MAX];
    		cout << getcwd(buf, FILENAME_MAX) << endl;
		}

		// Change directory
		else if (raw.substr(0, 3) == "chd")
		{
			chdir(*argsv[1]);
		}

		// List files
		else if (raw.substr(0, 3) == "lst")
		{
			char buf[FILENAME_MAX];
			struct dirent *entry;
			DIR *dir = opendir(getcwd(buf, FILENAME_MAX));

			if (dir == NULL) 
			{
				cout << "Directory existence error." << endl;
			}

			while ((entry = readdir(dir)) != NULL) 
			{
				cout << entry->d_name << endl;
			}

			closedir(dir);
		}

		// Quit the sbash terminal
		else if (strcmp(*argsv[0], "q") == 0)
		{
			q = !q;
		}

	}

	

	return 0;
}