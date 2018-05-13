#include "stdafx.h"
#include "LexerAnalyzer.h"
#include "map"
#include "string"
#include "vector"
#include<iostream>


LexerAnalyzer::LexerAnalyzer(char* _fileName) 
{
	initCharTable();
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
	writeError();
}

void LexerAnalyzer::initCharTable()
{
	charTable["begin"] = 1;
	charTable["end"] = 2;
	charTable["integer"] = 3;
	charTable["if"] = 4;
	charTable["then"] = 5;
	charTable["else"] = 6;
	charTable["function"] = 7;
	charTable["read"] = 8;
	charTable["="] = 12;
	charTable["<>"] = 13;
	charTable["<="] = 14;
	charTable["<"] = 15;
	charTable[">="] = 16;
	charTable[">"] = 17;
	charTable["-"] = 18;
	charTable["*"] = 19;
	charTable[":="] = 20;
	charTable["("] = 21;
	charTable[")"] = 22;
	charTable[";"] = 23;
}

void LexerAnalyzer::readFile()
{
	std::cout << "open file start" << std::endl;
	sourceFile.open(fileName);
	nowLine = 1;
	std::cout << "open file done" << std::endl;
}

void LexerAnalyzer::writeTable()
{
	std::cout << "write result file ---------" << std::endl;
	targetTable.open(fileName + ".dyd", std::ios::trunc);
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
	temp = nextNotBlankWord();
	while (true)
	{
		if(sourceFile.eof())
		{
			unvisbaleChar(NULL);
			return;
		}
		if (temp == ' ')
		{
			temp = sourceFile.get();
			continue;
		}
		else if (isLetter(temp))
		{
			temp = analyzeWord(temp);
		}
		else if (isNum(temp))
		{
			temp = analyzeNum(temp);
		}
		else
		{
			switch (temp)
			{
			case '=': ;
			case '-': ;
			case '*': ;
			case '(': ;
			case ')': ;
			case ';':temp = analyzeOneEle(temp); break;
			case'<':temp = analyzeLess(temp); break;
			case'>':temp = analyzeGreater(temp); break;
			case':':temp = analyzeColon(temp); break;
			case '\n':temp = unvisbaleChar(temp); break;
			default:errorInfo("no such sign");break;
			}
		}
	}
	std::cout << "scan --------- done" << std::endl;
}

char LexerAnalyzer::analyzeWord(char first)
{
	std::string word = "";
	word += first;
	char temp;
	while (true)
	{
		temp = nextLetter();
		if (isLetter(temp) || isNum(temp))
		{
			word += temp;
		}
		else
		{
			if (word.length > 16)
			{
				errorInfo("character is too long");
			}
			else
			{
				allocateWord(word);
			}
			return temp;
		}
	}
}

char LexerAnalyzer::analyzeNum(char first)
{
	std::string word = "";
	word += first;
	char temp;
	while (true)
	{
		temp = nextLetter();
		if (isNum(temp))
		{
			word += temp;
		}
		else
		{
			dydValue tempValue = { word , 11 };
			dydMap.push_back(tempValue);
			return temp;
		}
	}
}

char LexerAnalyzer::analyzeOneEle(char first)
{
	std::string word = "";
	word += first;
	allocateWord(word);
	return ' ';
}

char LexerAnalyzer::analyzeColon(char first)
{
	std::string word = "";
	word += first;
	char temp = sourceFile.get();
	if (temp == '=') {
		word += '=';
	}
	else
	{
		errorInfo("expected =");
	}
	allocateWord(word);
	return temp;
}

char LexerAnalyzer::analyzeLess(char first)
{
	std::string word = "";
	word += first;
	char temp = sourceFile.get();
	switch (temp)
	{
	case'=':
	case'>':word += temp; break;
	default:break;
	}
	allocateWord(word);
	return temp;
}

char LexerAnalyzer::analyzeGreater(char first)
{
	std::string word = "";
	word += first;
	char temp = sourceFile.get();
	if (temp == '=') {
		word += '=';
	}
	allocateWord(word);
	return temp;
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

char LexerAnalyzer::nextLetter()
{
	char temp = NULL;
	if (!sourceFile.eof())
	{
		temp = sourceFile.get();
	}
	return temp;
}

char LexerAnalyzer::unvisbaleChar(const char & character)
{
	dydValue tempValue;
	switch (character)
	{
		
	case '\n':tempValue = { "EOLN" , 24 }; nowLine++; break;
	case NULL:tempValue = { "EOF" , 25 }; break;
	default:tempValue = { "EOF" , 25 }; break;
	}
	std::cout << tempValue.word;
	dydMap.push_back(tempValue);
	return ' ';
}

void LexerAnalyzer::allocateWord(const std::string & temp)
{
	std::cout << "analyze word --------- " + temp << std::endl;
	int type = charTable[temp];
	if (type == 0)
		type = 10;
	dydValue tempValue = { temp , type };
	dydMap.push_back(tempValue);
	std::cout << "analyze word --------- "+ temp +" done" << std::endl;
}

void LexerAnalyzer::errorInfo(std::string error)
{
	dydValue tempValue = { error , nowLine };
	dydMap.push_back(tempValue);
}

void LexerAnalyzer::writeError()
{
	std::cout << "write err file ---------" << std::endl;
	errorTable.open(fileName + ".err", std::ios::trunc);
	std::vector<dydValue>::iterator it;
	std::string temp = "";
	for (it = errorMap.begin(); it != errorMap.end(); it++)
	{
		temp = "LINE:" + std::to_string(it->type) + "  " + it->word + "\n";
		targetTable << temp;
	}
	errorTable.close();
	std::cout << "write err file --------- done" << std::endl;
}

