/*
	wc -- word, line, character, and byte count
*/
// This source code is release under the CMU License.
/* change in behavior with -bn */
#include <fstream>
#include <getopt.h>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;

bool wcFile(const char *file);
void doWcFile (istream &toWc);

/* make these flags default to false */
bool wordFlag = false, lineFlag = false, charFlag = false, byteFlag = false, longestLineFlag = false;

int main(int argc, char *argv[])
{
	int c;
	int toReturn = 0;
	/*
		Lets see which command line options we have.
	*/
      while ((c = getopt (argc, argv, "Lclmw")) != -1)
	{
      	switch (c)
		{
			case 'L':
				longestLineFlag = true;
				break;
			case 'c':
				charFlag = true;
				break;
			case 'l':
				lineFlag = true;
				break;
			case 'm':
				byteFlag = true;
				break;
			case 'w':
				wordFlag = true;
				break;
			default:
				break;
		}

	}
	/* if no flags are set; make the default flags true */
	if (! (charFlag || lineFlag || byteFlag || wordFlag || longestLineFlag) )
	{
		charFlag = lineFlag = byteFlag = wordFlag = true;
	}
	/* If we have files on command line - display them; else just display cin once.*/
	if (argc > 1)
	{
	      for (int i = optind; i < argc; ++i)
		{
			/* if what we have is not stdin deal with it as a file */
			if ( strcmp(argv[i] , "-") != 0 )
			{
				if ( ! wcFile(argv[i]) )
				{
					/* exact message produced by BSD wc */
	      			cerr << "wc: " << argv[i] << ": open: No such file or directory" << endl;
					toReturn = 1;
				}
				else
				{
					/* we don't pass the filename so print it here */
					cout << argv[i] << endl;
				}
			}
			else
			{
				/* we have stdin so go directly to "wc" */
				doWcFile(cin);
			}
		}
	}
	else
	{
		doWcFile(cin);
	}
      return toReturn;
}
/**********************************************
 * Name:    doWcFile                          *
 * Purpose: perform the "wc" action to file   *
 * Returns: nothing	 		          *
 * Parameters: istream - open isstream to file*
 * Known bugs: many unworking features;       *
 * compatibility: very limited                *
 * notes: keep some kind of pointer to an     *
 *	array of the const data that main()     *
 *	could use later? something else?	    *
 *********************************************/

void doWcFile (istream &toWc)
{
	/* store some kind of const to generate total */
	unsigned long int lineNums = 0;
	unsigned long int charNums = 0;
	unsigned long int words = 1; /* begin at one because we look for spaces; not words */
	unsigned long int longestLine = 0;
	/* the static content - used for 'total' */
	static unsigned long int sLineNums = 0;
	static unsigned long int sCharNums = 0;
	static unsigned long int sWords = 1;
	static unsigned long int sLongestLine = 0;
	bool lastSpace = false; /* use so double spaces are not counted as words */
	bool curCharIsSpace = false;
	string line;

	while (! toWc.eof() )
	{
		getline(toWc, line);
		/* does not deal with -c vs -m yet! */
		unsigned int lineLen = line.size();
		charNums += lineLen;
		++lineNums;
		if (lineLen > longestLine)
		{
			longestLine = lineLen;
		}
		//longestLine = max(lineLen, longestLine);

		for(unsigned int i = 0; i < lineLen; ++i)
		{
			/* use iswspace? */
			/* we are not going to use .at() because we know we are in range */
			curCharIsSpace = iswspace(line[i]);
			if (curCharIsSpace && !lastSpace)
			{
				++words;
			}
			else
			{
				if (!curCharIsSpace)
				{
					lastSpace = false;
				}
			}
		}
	}
	sLineNums += lineNums;
	sCharNums += charNums;
	sWords += words;
	sLongestLine = max (longestLine, sLongestLine);

	cout << "\t";
	if (lineFlag)
	{
		cout << lineNums << "\t";
	}
	if (wordFlag)
	{
		cout << words << "\t";
	}
	if (charFlag)
	{
		cout << charNums << "\t";
	}
	if (longestLineFlag)
	{
		cout << longestLine << " ";
	}
	/*  filename printed by calling function */
}

/**********************************************
 * Name:    wcFile                            *
 * Purpose: perform the error checking        *
 * Returns: nothing                           *
 * Parameters: char* - string to file name    *
 *********************************************/

bool wcFile(const char *file)
{
      ifstream toWc;
      toWc.open(file, ios::in);
	if ( ! toWc)
      {
		return false;
	}
	doWcFile(toWc);
      toWc.close();
	return true;
}
