#pragma once
#include "fstream"
#include<vector>
class LexerAnalyzer
{
public:
	LexerAnalyzer(char* fileName);
	~LexerAnalyzer();
	void start();
private:
	struct dydValue {
		std::string word;
		int type;
	};
	void readFile(char * _fileName, std::string &fileString);
	void writeTable();
	void analyze();
	void splitToWords();
	void analyzeWord();

	std::string fileName;
	std::vector<std::string> wordArray;
	std::ifstream sourceFile;
	std::ofstream targetTable;
	std::vector<dydValue> dydMap;
};

