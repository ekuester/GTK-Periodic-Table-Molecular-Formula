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
//  File:   molecularformula.cpp
//          Summenformel V 1.5.2
//       1993 initially command line version
// 15.12.1993 Englische Version mit defines
// 20.03.1995 V 1.3.3  Eingabepuffer größer
// 26.06.1995 V 1.3.31 Puffer noch groesser
//      Version for Windows with Borland-C
// 24.09.1998 V 1.3.4  Edit Controls without Dialog
//      Version ohne Stockhausen-Bindung
//  1.03.2006 V 1.3.5 Microsoft Visual C# 2005
//       command line version in C#
//   ported to Apple PC Mac OSX ab 10.6
// 31.01.2012 V 1.3.6 Mono Framework 2.10.88 with MonoDevelop
//     command line version in Objective-C
// 10.03.2012 V 1.3.7 mit XCode 4.2.1
//        GUI-Version in Objective-C
//  7.11.2012 V 1.3.8 mit XCode 4.5.1
//     last revised on 2012-11-07
//        GUI-Version in Swift
// 17.07.2014 V 1.4.0 IDE Xcode 6.0 Beta
// 16.09.2014 V 1.4.1 IDE XCode 6.0 GM
// 28.12.2015 V 1.4.2 IDE XCode 7.2 und Swift 2.1
//        GUI-Version in C++
// 27.09.2018 V 1.4.3 IDE Netbeans 8.2, GTK+ mit gtkmm wrapper
// 30.10.2018 V 1.5.1 completed with Periodic Table in a window
// 28.02.2019 V 1.5.2 some translations and switch-over to autotools
//  Created by Erich Kuester, Krefeld, Germany
//    Copyright © 2014 - 2019 Erich Kuester.
//            All rights reserved.
//
//  for bonds: "-" ":" "=" "." ""
//  for complex formulas "[" "]" "(" ")"
//  for hydration water, Eisenheptahydrate = FeSO4.[H2O]7
//
//  renewed on September 27, 2018 at 18:36
//  Copyright © 2014 - 2019 Erich Kuester.
//      All rights reserved.
//  Last changes on October 31, 2018
 */

#include "molecularformula.h"

MolecularFormula::MolecularFormula()
: m_VBox(Gtk::ORIENTATION_VERTICAL),
  m_InputLabel(_("Formula:")),
  m_FormulaLabel(_("Overall formula:")),
  m_WeightLabel(_("Molar mass:")),
  m_TextWindow(),
  m_TextFrame(_(" Elementary Analysis:"))
{
    set_border_width(5);
    set_default_size(160, 320);
    // set background image
    set_name("window_azure");
    Glib::RefPtr<Gtk::CssProvider> windowCssProvider = Gtk::CssProvider::create();
    windowCssProvider->load_from_data(window_css);
    get_style_context()->add_provider(\
        windowCssProvider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    set_title(_("Gtk+: Calculator - Molecular Formula"));
    // if you want this window always on top
    set_type_hint(Gdk::WindowTypeHint::WINDOW_TYPE_HINT_DIALOG);
    move(274, 64);
    // add vertical box
    add(m_VBox);
    // add grid with labels and entries
    m_VBox.pack_start(m_Grid);
    m_Grid.set_border_width(6);
    //Arrange the widgets inside the grid
    m_Grid.set_row_spacing(16);
    m_Grid.set_column_spacing(10);

    m_InputLabel.set_hexpand(true);
    m_InputLabel.set_vexpand(false);
    m_InputLabel.set_halign(Gtk::ALIGN_START); // left justified
    m_Grid.attach(m_InputLabel, 0, 0, 1, 1); // column 0, row 0
    m_Grid.attach(m_InputEntry, 1, 0, 1, 1); // column 1, row 0

    m_FormulaLabel.set_hexpand(true);
    m_FormulaLabel.set_vexpand(false);
    m_FormulaLabel.set_halign(Gtk::ALIGN_START);
    m_Grid.attach(m_FormulaLabel, 0, 1, 1, 1); // column 0, row 1
    m_FormulaEntry.set_editable(false);
    m_Grid.attach(m_FormulaEntry, 1, 1, 1, 1); // column 1, row 1

    m_WeightLabel.set_vexpand(false);
    m_WeightLabel.set_hexpand(true);
    m_WeightLabel.set_halign(Gtk::ALIGN_START);
    m_Grid.attach(m_WeightLabel, 0, 2, 1, 1); // column 0, row 2
    m_WeightEntry.set_editable(false);
    m_Grid.attach(m_WeightEntry, 1, 2, 1, 1); // column 1, row 2

    m_InputEntry.signal_activate().connect(sigc::mem_fun(*this,
        &MolecularFormula::on_activated));

    //Create the Text Buffer
    m_refTextBuffer = Gtk::TextBuffer::create();
    m_TextView.set_buffer(m_refTextBuffer);
    // set background image
    m_TextView.set_name("textview_azure");
    m_TextView.override_background_color(Gdk::RGBA("rgb(193, 227, 255, 1.0)"),\
        Gtk::StateFlags::STATE_FLAG_NORMAL);
    m_TextView.set_editable(false);
    m_TextView.set_left_margin(8);
    m_TextWindow.set_size_request(-1, 112);
    m_TextView.set_wrap_mode(Gtk::WRAP_WORD);
    
    //Add the TextView to a Frame, inside a ScrolledWindow
    m_TextWindow.add(m_TextView);
    //Only show the scrollbars when they are necessary:
    m_TextWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    m_TextFrame.add(m_TextWindow);
    m_VBox.pack_start(m_TextFrame, Gtk::PACK_EXPAND_WIDGET);
    m_VBox.set_border_width(6);

    show_all_children();
}

MolecularFormula::MolecularFormula(const MolecularFormula& orig) {
}

MolecularFormula::~MolecularFormula() {
}

int MolecularFormula::errorAlert(int messageNumber) {
    Gtk::MessageDialog dialog(*this,\
        _("Error: Check input"),\
        false,\
        Gtk::MESSAGE_ERROR,\
        Gtk::BUTTONS_OK, // Gtk::BUTTONS_OK, Gtk::BUTTONS_NONE,
        true);
	// intermediate step to translate the status message
	const char* message = _(m_StatusMessages[messageNumber].data());
    dialog.set_secondary_text(message);
    return dialog.run();
}

// handles "ENTER" pressed
void MolecularFormula::on_activated() {
    string inputString = m_InputEntry.get_text();
    // check input
    if (inputString.empty()) {
        auto result = errorAlert(1);
    }
    else {
        // erase text buffer
        Gtk::TextBuffer::iterator iter_begin = 
            m_refTextBuffer->get_iter_at_offset(0);
        Gtk::TextBuffer::iterator iter_end = 
            m_refTextBuffer->get_iter_at_offset(m_refTextBuffer->get_char_count());
        m_refTextBuffer->erase(iter_begin, iter_end);
        // begin the formula parsing
        ElementSchema overallFormula = ElementSchema();
        FormulaParser* formulaParser = new FormulaParser(inputString);
        std:vector<ElementSchema::FormulaItem> elementArray;
        do {
            // run through at least once
            try {
                auto partialFormula = overallFormula.parseElements(formulaParser);
                //if (partialFormula.size() == 0) break;
                for (auto partial : partialFormula) {
                    elementArray.push_back(partial);
                }
            }
            catch (const int number) {
                auto result = errorAlert(number);
                break;
            }
        } while (!formulaParser->endOfString);
        for (auto element : elementArray) {
            auto symbol = element.elementSymbol;
            auto index = element.indexSum;
            // fill formula
            overallFormula.formulaTable[symbol].indexSum += index;
        }
        m_FormulaEntry.set_text(overallFormula.finalFormula());
        stringstream totalStream;
        // use momentan valid locale
        totalStream.imbue(std::locale(""));
        totalStream << setprecision(3) << fixed << overallFormula.totalMass;
        m_WeightEntry.set_text(totalStream.str());
        //output values for elementary analysis
        Gtk::TextBuffer::iterator iter_start = 
            m_refTextBuffer->get_iter_at_offset(m_refTextBuffer->get_char_count());
        auto iter = m_refTextBuffer->insert(iter_start, overallFormula.analytics());
    }
}
