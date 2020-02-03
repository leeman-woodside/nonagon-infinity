#include <string>
#include <vector>

#include "Parser.h"
#include "Token.h"

using namespace std;

Parser::Parser() {}
Parser::~Parser() {}

void Parser::parse(vector<Token> myTokens) {
    if(myTokens.at(myIndex).type == Schemes){
        match(Schemes);
        match(Colon);
        scheme();
        schemeList();
        match(Colon);
        factList();
        match(Colon);
        ruleList();
        match(Colon);
        query();
        queryList();
    }
    else {
        throw myTokens.at(myIndex);
    }
    
}
void Parser::match(tokenType t) {
    if(t == myTokens.at(myIndex).type) {
        myIndex++;
    }
    else {
        throw myTokens.at(myIndex);
    }
}

void Parser::schemeList() {
    if(myTokens.at(myIndex+1).type == Id) {
        scheme();
        schemeList();
    }
    //lambda
}
void Parser::factList() {
    if(myTokens.at(myIndex+1).type == Id) {
        fact();
        factList();
    }
    //lambda
}
void Parser::ruleList() {
    if(myTokens.at(myIndex+1).type == Id) {
        rule();
        ruleList();
    }
    //lambda
}
void Parser::queryList() {
    if(myTokens.at(myIndex+1).type == Id) {
        query();
        queryList();
    }
    //lambda
}

void Parser::scheme() {
    match(Id);
    match(Left_paren);
    match(Id);
    idList();
    match(Right_paren);
}
void Parser::fact() {
    match(Id);
    match(Left_paren);
    match(String);
    stringList();
    match(Right_paren);
    match(Period);
}
void Parser::rule() {
    headPredicate();
    match(Colon_dash);
    predicate();
    predicateList();
    match(Period);
}
void Parser::query() {
    predicate();
    match(Q_mark);
}

void Parser::headPredicate() {
    match(Id);
    match(Left_paren);
    match(Id);
    idList();
    match(Right_paren);
}
void Parser::predicate() {
    match(Id);
    match(Left_paren);
    parameter();
    parameterList();
    match(Right_paren);
}

void Parser::predicateList() {
    match(Comma);
    if(myTokens.at(myIndex+1).type == Id) {
        predicate();
        predicateList();
    }
    //lambda
}
void Parser::parameterList() {
    match(Comma);
    if(myTokens.at(myIndex+1).type == String) {
        parameter();
        parameterList();
    }
    //lambda
}
void Parser::stringList() {
    if(myTokens.at(myIndex+1).type == Comma) {
        match(Comma);
        match(String);
        stringList();
    }
    //lambda
}
void Parser::idList() {
    if(myTokens.at(myIndex+1).type == Comma) {
        match(Comma);
        match(Id);
        idList();
    }
    //lambda
}

void Parser::parameter() {
    if (myTokens.at(myIndex).type == String) {
       match(String);
    }
    else if (myTokens.at(myIndex).type == Id) {
        match(Id);
    }
    else if (myTokens.at(myIndex+1).type == Left_paren){
        expression();
    }
    else {
        throw myTokens.at(myIndex);
    }
}
void Parser::expression() {
    match(Left_paren);
    parameter();
    parseOperator();
    parameter();
    match(Right_paren);
}
void Parser::parseOperator() {
    if (myTokens.at(myIndex).type == Add) {
        match(Add);
    }
    else if (myTokens.at(myIndex).type == Multiply){
        match(Multiply);
    }
    else {
        throw myTokens.at(myIndex);
    }
}
