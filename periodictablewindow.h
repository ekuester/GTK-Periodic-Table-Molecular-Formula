#ifndef GTKMM_PERIODICTABLEWINDOW_H
#define GTKMM_PERIODICTABLEWINDOW_H

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
#include <vector>
#include "elementproperty.h"
#include "elementschema.h"
#include "formulaparser.h"
#include "molecularformula.h"

class ElementProperty;
class ElementSchema;
class FormulaParser;
class MolecularFormula;

using namespace std;

class PeriodicTableWindow : public Gtk::Window {
public:

    PeriodicTableWindow(const Glib::RefPtr<Gtk::Application>& app);
    PeriodicTableWindow(const PeriodicTableWindow& orig);
    virtual ~PeriodicTableWindow();

protected:
    //Methods:

    //Signal handlers:
    void on_about_dialog_response(int response_id);
    void on_action_quit();
    bool on_button_query_tooltip(int x, int y, bool keyboard_tooltip, const Glib::RefPtr<Gtk::Tooltip>& tooltip);
    void on_calc_open();
    void on_calc_close();
    void on_help_about();

    //Child widgets:
    Gtk::Box m_VBox;
    Gtk::Box m_HBox;
    Gtk::MenuBar m_MenuBar;
    Gtk::MenuItem m_MenuTable;
    //Gtk::SeparatorMenuItem s_MenuItemLine;
    Gtk::MenuItem s_MenuItemQuit;
    Gtk::Menu s_MenuTable;
    Gtk::MenuItem m_MenuCalc;
    Gtk::Menu s_MenuCalc;
    Gtk::MenuItem s_MenuItemOpen;    
    Gtk::MenuItem s_MenuItemClose;    
    Gtk::MenuItem m_MenuHelp;
    Gtk::Menu s_MenuHelp;
    Gtk::MenuItem s_MenuItemAbout;
    Gtk::ScrolledWindow m_TableWindow;
    Gtk::Grid m_Grid;

   std::string button_css = "\
#element_yellow {\
   border-radius: 4px;\
   background-color: palegoldenrod;\
   background-image: none;\
}\
#element_salmon {\
   border-radius: 4px;\
   background-image: image(salmon);\
}\
#element_coral {\
   border-radius: 4px;\
   background-image: image(coral);\
}\
#element_brown {\
   border-radius: 4px;\
   background-image: image(sandybrown);\
}\
#element_green {\
   border-radius: 4px;\
   background-image: image(lightgreen);\
}\
#element_blue {\
   border-radius: 4px;\
   background-image: image(lightblue);\
}\
#element_violet {\
   border-radius: 4px;\
   background-image: image(lavender);\
}\
@define-color paleazure rgb(178, 220, 255);\
#element_azure {\
   border-radius: 4px;\
   background-image: image(@paleazure);\
}\
#element_yellow:hover,\
#element_salmon:hover,\
#element_coral:hover,\
#element_brown:hover,\
#element_green:hover,\
#element_blue:hover,\
#element_violet:hover,\
#element_azure:hover {\
   background-image: image(firebrick);\
   color: white;\
}\
#element_yellow:active,\
#element_salmon:active,\
#element_coral:active,\
#element_brown:active,\
#element_green:active,\
#element_blue:active,\
#element_violet:active,\
#element_azure:active {\
   background-image: image(OrangeRed);\
}";
    Glib::RefPtr<Gtk::CssProvider> m_LabelCssProvider;
    std::string label_css = "\
label {\
  border-radius: 4px;\
  background-color: firebrick;\
  color: white;\
}";

    Gtk::AboutDialog m_Dialog;
    // child windows
    MolecularFormula m_FormulaWindow;
    ElementProperty m_PropertyWindow;

private:
    std::vector< std::string > colors = {
        "element_green",
        "element_coral",
        "element_salmon",
        "element_yellow",
        "element_violet",
        "element_blue",
        "element_brown",
        "element_azure"
    };
    std::vector< std::vector< std::pair<int,int> > > table_blueprint = {
        {{ 1,0},{ 0,0},{ 0,0},{ 0,0},{ 0,0},{ 0,0},{ 0,0},{ 0,0},{ 0,0},
         { 0,0},{ 0,0},{ 0,0},{ 0,0},{ 0,0},{ 0,0},{ 0,0},{ 0,0},{ 1,4}},
        {{ 1,1},{ 1,2},{ 0,0},{ 0,0},{ 0,0},{ 0,0},{ 0,0},{ 0,0},{ 0,0},
         { 0,0},{ 0,0},{ 0,0},{ 1,7},{ 1,0},{ 1,0},{ 1,0},{ 1,3},{ 1,4}},
        {{ 1,1},{ 1,2},{ 0,0},{ 0,0},{ 0,0},{ 0,0},{ 0,0},{ 0,0},{ 0,0},
         { 0,0},{ 0,0},{ 0,0},{ 1,7},{ 1,7},{ 1,0},{ 1,0},{ 1,3},{ 1,4}},
        {{ 1,1},{ 1,2},{ 1,5},{ 1,5},{ 1,5},{ 1,5},{ 1,5},{ 1,5},{ 1,5},
         { 1,5},{ 1,5},{ 1,5},{ 1,7},{ 1,7},{ 1,7},{ 1,0},{ 1,3},{ 1,4}},
        {{ 1,1},{ 1,2},{ 1,5},{ 1,5},{ 1,5},{ 1,5},{ 1,5},{ 1,5},{ 1,5},
         { 1,5},{ 1,5},{ 1,5},{ 1,7},{ 1,7},{ 1,7},{ 1,7},{ 1,3},{ 1,4}},
        {{ 1,1},{ 1,2},{-1,0},{ 1,5},{ 1,5},{ 1,5},{ 1,5},{ 1,5},{ 1,5},
         { 1,5},{ 1,5},{ 1,5},{ 1,7},{ 1,7},{ 1,7},{ 1,7},{ 1,3},{ 1,4}},
        {{ 1,1},{ 1,2},{-1,0},{ 1,5},{ 1,5},{ 1,5},{ 1,5},{ 1,5},{ 1,5},
         { 1,5},{ 1,5},{ 1,5},{ 1,7},{ 1,7},{ 1,7},{ 1,7},{ 1,3},{ 1,4}},
        {{-4,0}},
        {{ 0,0},{-2,0},{ 1,5},{ 1,6},{ 1,6},{ 1,6},{ 1,6},{ 1,6},{ 1,6},
         { 1,6},{ 1,6},{ 1,6},{ 1,6},{ 1,6},{ 1,6},{ 1,6},{ 1,6},{ 0,0}},
        {{ 0,0},{-3,0},{ 1,5},{ 1,6},{ 1,6},{ 1,6},{ 1,6},{ 1,6},{ 1,6},
         { 1,6},{ 1,6},{ 1,6},{ 1,6},{ 1,6},{ 1,6},{ 1,6},{ 1,6},{ 0,0}}
    };
};

#endif // GTKMM_PERIODICTABLEWINDOW_H
