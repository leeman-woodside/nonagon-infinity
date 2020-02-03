#ifndef SCANNER_H
#define SCANNER_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "Token.h"

using namespace std;

class Scanner{
    
    public:
    Scanner(string filename);
    ~Scanner();
    bool Scan(string filename);
    void ScanToken();
    void ScanID();
    void ScanStr();
    void ScanCom();
    void MakeToken(tokenType t, string s, int lineNum);
    vector<Token> getVector();
    vector<Token> tokVector;
    
    private:
    ifstream infile;
    string filename;
    string value = "";
    int lineNum = 1;
    int startLine = 0;
    char c;
    char next;
    
};
#endif
