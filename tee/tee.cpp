// This source code is release under the CMU License.

#include <fstream>
#include <iterator>
#include <iostream>
#include <signal.h>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>

void signal_handler(int signal);

bool appendFlag = false, ignoreSignalFlag = false;

using namespace std;
int main(int argc, char *argv[])
{
	std::vector<std::ofstream*> fileList;

	/* register the signal handler */
	/* why won't SIG_IGN work?	*/
	signal(SIGINT, signal_handler);

      int c;
	/* start parsing options */
      while ((c = getopt (argc, argv, "ai")) != -1)
     	{
            switch (c)
            {
                  case 'a':
                        appendFlag = true;
                        break;
                  case 'i':
                        ignoreSignalFlag = true;
				break;
			default:
				break;
		}
	}
	// lets make sure we have enouph room for all the CLI options.  We may not use it all but it should be minimal.
	fileList.reserve (argc - 1);
	/* since the CLI index includes options we want to maintain a count of files */
	int fileCount = 0;
	/* add files to fileList; */
	for (int i = optind; i < argc; ++i )
	{
		//I need to find a better way to do this?  Is there a way to keep a pointer to the "mode"?
            if (appendFlag)
            {
            	//fileList.push_back(new std::ofstream(argv[i],ios::app | ios::binary));
                  fileList.push_back (new std::ofstream(argv[i], ios::app | ios::binary));
            }
            else
            {
            	//fileList.push_back(new std::ofstream(argv[i],ios::out | ios::binary));
                  fileList.push_back (new std::ofstream(argv[i], ios::out | ios::binary));
            }
		printf ("argument %s with file count of %d with i of %d\n", argv[i], fileCount, i);
		++fileCount;
	}
	cout << fileList.size() << endl;
	/* start reading input */
	string line;
	while ( ! cin.eof() )
	{
		getline(cin, line);
		/* only write to files if we have files....*/
		if (fileCount > 0)
		{
			for (unsigned int i = 0; i < fileList.size(); ++i)
			{
				cout << "trying to write to file" << i << endl;
				cout << fileList.at(i) << endl;
				//  don't use .at() becauyse we know we are in bounds
				*fileList.at(i) << line << endl;
				//fileList[i]->write(line.c_str(), line.length() + 1);
			}

			/*
			for (std::vector<std::ofstream*>::iterator it = fileList.begin(); it != fileList.end(); ++it)
			{
				(*it)->write(line.c_str(),line.length() + 1);
			}*/

		}
		cout << line << endl;
	}
	return 0;
}

/**********************************************
 * Name:    singal_handler                    *
 * Purpose: handle signals; ignore sigint     *
 * Returns: nothing                           *
 * Parameters: int - which signal did we get  *
 * compatibility: tee -i	                *
 *********************************************/

void signal_handler(int signal)
{
	/* if we are  SIGINT and -i has been set ignore it else: */
	if (! (signal == SIGINT && ignoreSignalFlag) )
	{
		exit(0);
	}
}
