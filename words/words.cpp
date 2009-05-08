#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <utility>

int main (void)
{
	typedef std::map<const std::string, const int> cmdListMapType;
	std::string mainWord;
	std::string cmdIn;
 	cmdListMapType cmdIntMap;
	int counter = 1;
	cmdIntMap.insert(std::make_pair("list", counter));
	counter++;
	cmdIntMap.insert(std::make_pair("word", counter));
	counter++;
	cmdIntMap.insert(std::make_pair("help", counter));
	counter++;
	cmdIntMap.insert(std::make_pair("bucket", counter));
	counter++;


	std::cout << "Please enter the main word: ";
	std::cin >> mainWord;

	int i;
	cmdListMapType::iterator cmdListIter;

	std::vector<std::string> wordList;
	while (true)
	{
		std::cout << "Enter a command: ";
		std::cin >> cmdIn;
		if (cmdIn[0]=='?')
		{
			for(i = 1; i < cmdIn.size(); ++i)
			{
				cmdIn[i - 1] = cmdIn [ i ];
			}
			/*
				we remove the last char of the string so the length matches up - we should remove whitespace instead.
			*/
			cmdIn.erase(cmdIn.size() - 1, 1) ;
			cmdListIter = cmdIntMap.find(cmdIn);
			if (cmdListIter != cmdIntMap.end())
			{
				std::cout << "we have what we need";
				int val = cmdListIter->second;
				std::cout << val << std::endl;
				switch (val)
				{
					case 1:
						for (std::vector<std::string>::iterator it = wordList.begin(); it != wordList.end(); ++it)
						{
							std::cout << *it << std::endl;
						}
						break;
					case 2:
						std::cout << mainWord << std::endl;
						break;
					case 3:
						std::cout << "help text here" << std::endl;
						break;
					case 4:
						int bucket[26];
						for (int j = 0; j <26; ++j)
						{
							bucket[j] = 0;
						}
						for(i = 0; i < mainWord.length(); ++i)
						{
							char c = mainWord[i];
							if (isalpha(c))
							{
								c = tolower(c);
								int cVal = (int)(c - 'a');
								bucket[cVal]++;
								std::cout << c << cVal << std::endl;
								for (int j = 0; j <26; ++j)
								{
									std::cout << bucket[j] << " ";
								}
							}
							std::cout << std::endl;
						}
						break;
						default:
							std::cout << "No such command" << std::endl;
							break;
				}
			}
		}
		else
		{
			std::cout << "added!";
			wordList.push_back(cmdIn);
		}
	}
	return 0;
}

void generateBucket(std::string str, char *bucket[26])
{
	/* clear the bucket and add new values; no real return value - perhaps I should work with a vector and return it instead? */
	for (int j = 0; j <26; ++j)
	{
		bucket[j] = 0;
	}
}