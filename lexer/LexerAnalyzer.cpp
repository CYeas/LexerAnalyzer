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
	readFile();
	analyze();
	writeTable();
}

void LexerAnalyzer::readFile()
{
	std::cout << "open file start" << std::endl;
	sourceFile.open(fileName);
	std::cout << "open file done" << std::endl;
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
	scan();
	std::cout << "analyze done" << std::endl;
}

void LexerAnalyzer::scan()
{
	std::cout << "scan ---------" << std::endl;
	char temp;
	while (temp = nextNotBlankWord())
	{
		if (isLetter(temp))
		{

		}
	}
	std::cout << "scan --------- done" << std::endl;
}



bool LexerAnalyzer::isLetter(const char & character)
{
	return (('A' <= character && character <= 'Z') || ('a' <= character && character <= 'z'));
}

bool LexerAnalyzer::isNum(const char & character)
{
	return '0' <= character && character <= '9';
}

char LexerAnalyzer::nextNotBlankWord()
{
	char temp = NULL;
	while (!sourceFile.eof())
	{
		temp = sourceFile.get();
		if (temp != ' ')
		{
			break;
		}
	}
	return temp;
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


