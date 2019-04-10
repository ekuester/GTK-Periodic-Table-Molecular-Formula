/*
//  Part of GTKPeriodicTable - Periodic Table of the Elements
//  Copyright (C) 2018  Erich Küster
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
//  File:   formulaparser.cpp
//  Created on September, 29 2018, 16:04
 */

#include "formulaparser.h"

FormulaParser::FormulaParser(Glib::ustring input) {
    formulaString = input; //std::vector<gunichar>(input.begin(), input.end());
    // number of input characters
    length = formulaString.size();
    // iterator into the string
    pointer = formulaString.begin();
    endOfString = (pointer == formulaString.end());
}

FormulaParser::FormulaParser(const FormulaParser& orig) {
}

FormulaParser::~FormulaParser() {
}

void FormulaParser::advance() {
    pointer++;
    endOfString = (pointer == formulaString.end());
}

gunichar FormulaParser::fetch() {
    return *pointer;
}

Glib::ustring FormulaParser::scanForBond() {
    // scan for bond sign
    if (!endOfString) {
        gunichar bondChar = fetch();
        switch (bondChar) {
            case '-':
            case '.':
            case ':':
            case '=':
            case u'·':
                // found bond sign
                advance();
                return Glib::ustring(1, bondChar);
            default:
                break;
        }
    }
    return Glib::ustring();
}

bool FormulaParser::isDigit(gunichar c) {
    switch (c) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return true;
        default:
            break;
    }
    return false;
}

int FormulaParser::scanForIndex() {
    // scan for integer index, if no integer found, index is one
    Glib::ustring indexString = Glib::ustring();
    while (!endOfString) {
        gunichar formulaChar = fetch();
        if (isDigit(formulaChar)) {
            indexString.append(1, formulaChar);
            advance();
        } else {
            break;
        }
    }
    if (!indexString.empty()) {
        int index = stoi(indexString);

        if (index > 0) {
            return index;
        }
        // index 0 not allowed
        return -1;
    }
    // no index means 1
    return 1;
}

gunichar FormulaParser::scanForOpeningBracket() {
    gunichar bracketChar = fetch();
    switch (bracketChar) {
        case '[':
        case '(':
            advance();
            if (endOfString) {
                //ErrorAlert(message: 2).show()
                return 'q';
            }
            if (bracketChar == '[') {
                return ']';
            } else {
                return ')';
            }
        default:
            break;
    }
    return u'?';
}

bool FormulaParser::isCharClosingBracket(gunichar closing) {
    if (!endOfString) {
        gunichar bracketChar = fetch();
        if (bracketChar == closing) {
            advance();
            return true;
        }
    }
    return false;
}

bool FormulaParser::followsClosingBracket() {
    gunichar bracketChar = fetch();
    if ((bracketChar == u')') || (bracketChar == u']')) {
        return true;
    }
    return false;
}

string FormulaParser::scanForElement() {
    if (!endOfString) {
        // parse one formula element containing an atomic symbol, index is set to one
        string symbol = string();
        gunichar upperChar = fetch();
        switch (upperChar) {
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
            case 'G':
            case 'H':
            case 'I':
            case 'K':
            case 'L':
            case 'M':
            case 'N':
            case 'O':
            case 'P':
            case 'R':
            case 'S':
            case 'T':
            case 'U':
            case 'V':
            case 'W':
            case 'X':
            case 'Y':
            case 'Z':
                advance();
                symbol.append(1, upperChar);
                break;
            default:
                return string();
        }
        // advance pointer but only if characters left
        if (!endOfString) {
            // now scan for one lowercase letter
            gunichar lowerChar = fetch();
            switch (lowerChar) {
                case 'a':
                case 'b':
                case 'c':
                case 'd':
                case 'e':
                case 'f':
                case 'g':
                case 'h':
                case 'i':
                case 'k':
                case 'l':
                case 'm':
                case 'n':
                case 'o':
                case 'p':
                case 'r':
                case 's':
                case 't':
                case 'u':
                case 'w':
                case 'y':
                    // found element symbol with upper and lower case letter
                    advance();
                    symbol.append(1, lowerChar);
                    break;
                default:
                    break;
            }
        }
        return {symbol};
    }
    return string();
}
