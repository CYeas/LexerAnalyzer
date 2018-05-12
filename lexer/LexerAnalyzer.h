#pragma once
#include "fstream"
#include<vector>
#include<map>
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
	char analyzeWord(char first);
	char analyzeNum(char first);
	char analyzeOneEle(char first);
	char analyzeColon(char first);
	char analyzeLess(char first);
	char analyzeGreater(char first);
	bool isLetter(const char & character);
	bool isNum(const char & character);
	char nextNotBlankWord();
	void initCharTable();
	char nextLetter();
	char unvisbaleChar(const char & character);
	void allocateWord(const std::string & temp);

	void errorInfo(std::string error);

	void writeError();

	std::string fileName;
	std::vector<std::string> wordArray;
	std::ifstream sourceFile;
	std::ofstream targetTable;
	std::vector<dydValue> dydMap;
	std::ofstream errorTable;
	std::vector<dydValue> errorMap;
	int nowLine;
	std::map<std::string, int> charTable;
};

