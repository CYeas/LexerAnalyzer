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
	void readFile();
	void writeTable();
	void analyze();
	void scan();
	bool isLetter(const char & character);
	bool isNum(const char & character);
	char nextNotBlankWord();
	void analyzeWord();

	std::string fileName;
	std::vector<std::string> wordArray;
	std::ifstream sourceFile;
	std::ofstream targetTable;
	std::vector<dydValue> dydMap;
};

