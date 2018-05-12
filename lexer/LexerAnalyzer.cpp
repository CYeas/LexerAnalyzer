#include "stdafx.h"
#include "LexerAnalyzer.h"
#include "map"
#include "string"
#include "vector"
#include<iostream>


LexerAnalyzer::LexerAnalyzer(char* _fileName) 
{
	fileName = _fileName;
}

LexerAnalyzer::~LexerAnalyzer()
{
	sourceFile.close();
	targetTable.close();
}

void LexerAnalyzer::start() 
{
	std::string sourceString;
	readFile(fileName, sourceString);
	analyze();
	writeTable();
}

void LexerAnalyzer::readFile(char* _fileName, std::string &fileString)
{
	std::cout << "read file start" << std::endl;
	sourceFile.open(_fileName);
	while (!sourceFile.eof()) {
		fileString += sourceFile.get();
	}
	sourceFile.close();
	std::cout << "read file done" << std::endl;
}

void LexerAnalyzer::writeTable()
{
	std::cout << "write result file ---------" << std::endl;
	targetTable.open(fileName + ".dyd", std::ios::_Noreplace);
	std::vector<dydValue>::iterator it;
	std::string temp = "";
	for (it = dydMap.begin(); it != dydMap.end(); it++)
	{
		temp = "" + it->word + " " + std::to_string(it->type) + "\n";
		targetTable << temp;
	}
	targetTable.close();
	std::cout << "write result file --------- done" << std::endl;
}

void LexerAnalyzer::analyze()
{
	std::cout << "analyze start" << std::endl;
	splitToWords();
	analyzeWord();
	std::cout << "analyze done" << std::endl;
}

void LexerAnalyzer::splitToWords()
{
	std::cout << "split word ---------" << std::endl;
	bool wordDone = false;
	bool wordStart = false;
	char temp;
	int fileLength = fileString.length();
	std::string result;
	for (int index = 0; index < fileLength; index++)
	{
		temp = fileString[index];
		if (temp == ' ') {
			if (wordStart) {
				wordDone = true;
			}
			else
			{
				continue;
			}
		}
		else 
		{
			if (!wordStart) 
			{
				wordStart = true;
				result = "";
			}
			result += temp;
		}
		if (wordDone) {
			wordArray.push_back(result);
			wordDone = false;
			wordStart = false;
		}
	}
	std::cout << "split word --------- done" << std::endl;
}

void LexerAnalyzer::analyzeWord()
{
	std::cout << "analyze word ---------" << std::endl;

	std::vector<std::string>::iterator it;
	for(it = wordArray.begin(); it != wordArray.end(); it ++)
	{
		dydValue tempValue = { *it , 1 };
		dydMap.push_back(tempValue);
	}
	std::cout << "analyze word --------- done" << std::endl;
}


