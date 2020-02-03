#include <iostream>
#include <vector>
#include <string>

#include "scanner.h"
#include "Token.h"
#include "Parser.h"


using namespace std;

int main (int argc, char* argv[]) {
    if (argc < 2) {
        cout << "incorrect number of arguments";
        exit(1);
    }
    vector<Token> myTokens;
    
    //convert filename to string and create tokens through the scanner
    string filename = argv[1];
    Scanner myScanner(filename);
    myScanner.Scan(filename);
    
    /*for (int i = 0; i < myScanner.getVector().size(); i++) {
        myTokens.push_back(myScanner.getVector().at(i));
    }*/
    myTokens = myScanner.getVector();
    for (int i = 0; i < myScanner.getVector().size(); i++) {
        cout << myScanner.getVector().at(i).type << endl;
    }
    //create Paarser object
    Parser myParser;
    //parse the vector of tokens
    try {
        myParser.parse(myTokens);
    }
    catch(Token t) {
        cout << "Failure!" << endl;
        cout << t.ToString(t.type, t.GetValue(), t.GetLineNum()) << endl;
    }
    
    return 0;
}
