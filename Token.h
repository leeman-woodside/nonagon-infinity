#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

enum tokenType {Comma, Period, Q_mark, Left_paren, Right_paren, Colon, Colon_dash, Multiply, Add, Schemes, Facts, Rules, Queries, Id, String, Comment, Undefined, Eof };


class Token{
    public:
    Token(tokenType t, string s, int l = 0);
    Token();
    ~Token();
    int line();
    string ToString(tokenType t, string s, int l);
    string printType(tokenType t);
    string GetValue();
    int GetLineNum();
    
    tokenType type;
    
    private:
    int lineNum = 1;
    string stringValue;
    
};

#endif
