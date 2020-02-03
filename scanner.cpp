#include "scanner.h"
#include "Token.h"

using namespace std;
    

Scanner::Scanner(string filename) {}
Scanner::~Scanner() {
    infile.close();
}
bool Scanner::Scan(string filename) {
    infile.open(filename);
    if(infile) {
        while(infile.get(c)) {
            ScanToken();
        }
        MakeToken(Eof, value, lineNum);
        cout << "Total Tokens = " << tokVector.size() << endl;
        return true;
    }
    else {
        cout << "File failed to open." << endl;
        return false;
    }
}
void Scanner::ScanToken() {
    while(isspace(c)) {
        if(c == '\n') {
            lineNum++;
        }
        infile.get(c);
        if(infile.eof()) {
            break;
        }
    }
    switch (c) {
        case ',':
            value = ",";
            MakeToken(Comma, value, lineNum);
            break;
        case '.':
            value = ".";
            MakeToken(Period, value, lineNum);
            break;
        case '?':
            value = "?";
            MakeToken(Q_mark, value, lineNum);
            break;
        case '(':
            value = "(";
            MakeToken(Left_paren, value, lineNum);
            break;
        case ')':
            value = ")";
            MakeToken(Right_paren, value, lineNum);
            break;
        case '*':
            value = "*";
            MakeToken(Multiply, value, lineNum);
            break;
        case '+':
            value = "+";
            MakeToken(Add, value, lineNum);
            break;
        case ':':
            value = ":";
            next = infile.peek();
            if(next == '-') {
                value = ":-";
                MakeToken(Colon_dash, value, lineNum);
                infile.get(c);
            }
            else {
                MakeToken(Colon, value, lineNum);
            }
            break;
        case '\'':
            ScanStr();
            break;
        case '#':
            ScanCom();
            break;
        default:
            if (isalpha(c)) {
                ScanID();
            }
            else if(!infile.eof()) {
                value += c;
                MakeToken(Undefined, value, lineNum);
            }
            break;
    }
    
}
void Scanner::ScanID() {
    value += c;
    infile.get(c);
    while(isalnum(c)) {
        value += c;
        infile.get(c);
    }
    if (value == "Schemes") {
        MakeToken(Schemes, value, lineNum);
    }
    else if(value == "Facts"){
        MakeToken(Facts, value, lineNum);
    }
    else if(value == "Rules"){
        MakeToken(Rules, value, lineNum);
    }
    else if(value == "Queries"){
        MakeToken(Queries, value, lineNum);
    }
    else {
        MakeToken(Id, value, lineNum);
    }
    ScanToken();
}
void Scanner::ScanStr() {
    value += c;
    startLine = lineNum;
    bool endOfString = false;
    while(endOfString == false) {
        if (infile.peek() == -1) {
            MakeToken(Undefined, value, startLine);
            endOfString = true;
        }
        else {
            infile.get(c);
            switch (c) {
                case '\n':
                    lineNum++;
                    value += c;
                    break;
                case '\'':
                    value += c;
                    next = infile.peek();
                    if(next != '\'') {
                        MakeToken(String, value, startLine);
                        endOfString = true;
                    }
                    else {
                        infile.get(c);
                        value += c;
                    }
                    break;
                default:
                    value += c;
                    break;
            }
        }
    }
}
void Scanner::ScanCom() {
    value += c;
    startLine = lineNum;
    next = infile.peek();
    if (next != '|') {
        infile.get(c);
        while (c != '\n') {
            value += c;
            infile.get(c);
        }
        if (c == '\n') {
            lineNum++;
        }
        //MakeToken(Comment, value, startLine);
    }
    else {
        infile.get(c);
        value += c;
        infile.get(c);
        next = infile.peek();
        while ((c != '|' || next != '#') && next != -1) {
            if (c == '\n') {
                lineNum++;
            }
            value += c;
            infile.get(c);
            next = infile.peek();
        }
        if (c == '|' && next == '#') {
            value += c;
            infile.get(c);
            value += c;
            //MakeToken(Comment, value, startLine);
        }
        else if (infile.eof()) {
            value += c;
            lineNum++;
            //MakeToken(Undefined, value, startLine);
        }
    }
}
void Scanner::MakeToken(tokenType t, string s, int lineNum) {
    Token tok(t, s, lineNum);
    tokVector.push_back(tok);
    cout << tok.ToString(t, s, lineNum) << endl;
    value = "";
}
vector<Token> Scanner::getVector() {
    return tokVector;
}
