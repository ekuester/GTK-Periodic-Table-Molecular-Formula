/* 
 * File:   molecularformula.h
 * Author: kuestere
 *
 * Created on 27. September 2018, 18:36
 */

#ifndef MOLECULARFORMULA_H
#define MOLECULARFORMULA_H

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <glibmm/i18n.h>
#include <gtkmm.h>
#include <iomanip>
#include <iostream>
#include <limits>
#include <locale>
#include <sstream>
#include <string>
#include "formulaparser.h"
#include "elementschema.h"

using namespace std;

class FormulaParser;
class ElementSchema;

class MolecularFormula : public Gtk::Window {
public:
    MolecularFormula();
    MolecularFormula(const MolecularFormula& orig);
    virtual ~MolecularFormula();

private:

protected:
    std::vector<Glib::ustring> m_StatusMessages = {
        N_("Place holder, no error"),
        N_("No formula entered"),
        N_("Element symbol expected"),
        N_("No valid element symbol (actual not in table)"),
        N_("Too many bond signs"),
        N_("Bond sign misplaced here"),
        N_("Closing ) missing"),
        N_("Closing ] missing"),
        N_("Index 0 not allowed"),
        N_("Molecular weight is too big")
    };
    int errorAlert(int messageNumber);

    //Signal handlers for entries and buttons
    void on_activated();

    //Child widgets:
    Gtk::Box m_VBox;
    Gtk::Grid m_Grid;

    Gtk::Label m_InputLabel;
    Gtk::Entry m_InputEntry;

    Gtk::Label m_FormulaLabel;
    Gtk::Entry m_FormulaEntry;

    Gtk::Label m_WeightLabel;
    Gtk::Entry m_WeightEntry;

    Gtk::ScrolledWindow m_TextWindow;
    Gtk::Frame m_TextFrame;
    Gtk::TextView m_TextView;
    Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;

    std::string window_css = "\
@define-color paleazure rgb(193, 227, 255);\
#window_azure {\
   border-radius: 4px;\
   background-image: image(@paleazure);\
}";

};

#endif /* MOLECULARFORMULA_H */

