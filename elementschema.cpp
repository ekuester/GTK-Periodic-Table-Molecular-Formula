/* 
 * File:   elementschema.cpp
 * Author: kuestere
 * 
 * Created on 1. Oktober 2018, 19:28
 */

#include "elementschema.h"

ElementSchema::ElementSchema() {
    for (auto element : elements) {
        double mass;
        stringstream massStream(element[3]);
        massStream >> mass; 
        FormulaItem formulaItem = {element[1], mass, 0};
        formulaTable[element[1]] = formulaItem;
    }
}

ElementSchema::ElementSchema(const ElementSchema& orig) {
}

ElementSchema::~ElementSchema() {
}

std::vector<ElementSchema::FormulaItem> ElementSchema::parseElements(FormulaParser* inputParser) {
    std::vector<ElementSchema::FormulaItem> outputElements;
    auto closingBracket = inputParser->scanForOpeningBracket();
    if (closingBracket == 'q') {
        throw(2);
    }
    if (closingBracket != u'?') {
        // found opening bracket
        std::vector<ElementSchema::FormulaItem> bracketElements;
        do {
            // run through at least once
            auto partialElements = parseElements(inputParser);
            if (partialElements.size() == 0) break;
            for (auto partial : partialElements) {
                bracketElements.push_back(partial);
            }
            if (inputParser->endOfString) {
                switch (closingBracket) {
                    // no closing bracket
                    case ')':
                        throw(6);
                    default:
                        throw(7);
                }
                break;
            }
        } while (!inputParser->isCharClosingBracket(closingBracket));
        // scan for integer index, if no integer found, index is one
        int index = inputParser->scanForIndex();
        if (index < 0) {
            //  index 0 not allowed
            //ErrorAlert(message: 8).show()
            throw(8);
            return {};
        }
        for (auto element : bracketElements) {
            element.indexSum *= index;
            outputElements.push_back(element);
        }
    } else {
        string symbol = inputParser->scanForElement();
        //found an element?
        if (symbol.empty()) {
            throw(2);
            return {};
        }
        // now identify the element symbol
        if (formulaTable.find(symbol) == formulaTable.end()) {
            //no suitable element symbol found
            throw(3);
            return {};
        }
        // scan for integer index, if no integer found, index is one
        int index = inputParser->scanForIndex();
        if (index < 0) {
            //index 0 not allowed
            throw(8);
            return {};
        }
        int indexsum = 1;
        indexsum *= index;
        FormulaItem formulaItem = {symbol, 0.0, indexsum};
        outputElements.push_back(formulaItem);
    }
    // scan for bond sign, result is not evaluated at the moment
    auto bondSign = inputParser->scanForBond();
    if (!bondSign.empty()) {
        //after bound must follow a formula element
        if ((inputParser->followsClosingBracket()) || (inputParser->endOfString)) {
            throw(5);
        }
    }
    return outputElements;
}

string ElementSchema::analytics() {
    stringstream analyticStream;
    // use momentan valid locale
    analyticStream.imbue(std::locale(""));
    for ( auto const& pair : formulaTable ) {
        auto symbol = pair.first;
        FormulaItem formulaItem = formulaTable[symbol];
        auto indexSum = formulaItem.indexSum;
        if (indexSum > 0) {
            double percentage = formulaItem.mass / totalMass * 100;
            analyticStream << symbol << "\t"
                << setprecision(3) << fixed << percentage << " %" << endl;
        }
    }
    return analyticStream.str();
}

string ElementSchema::finalFormula() {
    stringstream formulaStream;
    totalMass = 0.0;
    for ( auto const& pair : formulaTable ) {
        auto symbol = pair.first;
        FormulaItem formulaItem = formulaTable[symbol];
        auto indexSum = formulaItem.indexSum;
        if (indexSum > 0) {
            formulaStream << symbol;
            double massMultiple = formulaItem.mass;
            if (indexSum > 1) {
                formulaStream << indexSum;
                massMultiple *= indexSum;
            }
            formulaTable[symbol].mass = massMultiple;
            totalMass += massMultiple;
        }
    }
    return formulaStream.str();
}
