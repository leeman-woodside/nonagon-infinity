#include <sstream>
#include <string>
using namespace std;

#include "Token.h"

Token::Token(tokenType t, string s, int l){}
Token::Token() {}
Token::~Token() {}

string Token::ToString(tokenType t, string s, int l) {
    stringValue = s;
    lineNum = l;
    string output;
    output.append("(");
    output.append(printType(t));
    output.append(",\"");
    output.append(s);
    output.append("\",");
    output += to_string(l);
    output.append(")");
    return output;
}
string Token::printType(tokenType t) {
    switch (t) {
        case (Comma): return "COMMA"; break;
        case (Period): return "PERIOD"; break;
        case (Q_mark): return "Q_MARK"; break;
        case (Left_paren): return "LEFT_PAREN"; break;
        case (Right_paren): return "RIGHT_PAREN"; break;
        case (Colon): return "COLON"; break;
        case (Colon_dash): return "COLON_DASH"; break;
        case (Multiply): return "MULTIPLY"; break;
        case (Add): return "ADD"; break;
        case (Schemes): return "SCHEMES"; break;
        case (Facts): return "FACTS"; break;
        case (Rules): return "RULES"; break;
        case (Queries): return "QUERIES"; break;
        case (Id): return "ID"; break;
        case (String): return "STRING"; break;
        case (Comment): return "COMMENT"; break;
        case (Undefined): return "UNDEFINED"; break;
        case (Eof): return "EOF"; break;
    }
    return "error";
}

string Token::GetValue() {
    return stringValue;
}
int Token::GetLineNum() {
    return lineNum;
}
