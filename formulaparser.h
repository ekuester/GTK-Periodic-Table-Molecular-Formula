/* 
 * File:   formulaparser.h
 * Author: kuestere
 *
 * Created on 29. September 2018, 16:04
 */

#ifndef FORMULAPARSER_H
#define FORMULAPARSER_H

#include <cstdlib>
#include <glibmm.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class FormulaParser {
public:
    FormulaParser(Glib::ustring input);
    FormulaParser(const FormulaParser& orig);
    virtual ~FormulaParser();

    Glib::ustring formulaString;
    int length = 0;
    Glib::ustring::iterator pointer;
    bool endOfString = false;

    void advance();
    gunichar fetch();
    Glib::ustring scanForBond();
    bool isDigit(gunichar c);
    int scanForIndex();
    gunichar scanForOpeningBracket();
    bool isCharClosingBracket(gunichar closing);
    bool followsClosingBracket();
    string scanForElement();

private:

protected:

};

#endif /* FORMULAPARSER_H */

