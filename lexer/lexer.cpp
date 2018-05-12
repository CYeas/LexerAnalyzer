// lexer.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "LexerAnalyzer.h"


int main()
{

	LexerAnalyzer* lex = new LexerAnalyzer("source");
	lex->start();
	system("pause");
    return 0;
}

