/* 
// File:   periodictablewindow.cpp
// Author: kuestere
//
//  Created by Erich Kuester, Krefeld, Germany
//    Copyright © 2014 - 2018 Erich Kuester.
//            All rights reserved.
//  Last changes on November 16, 2018
 */

#include "periodictablewindow.h"
#include "about.xpm"

const char* app_title \
= N_("Gtk+: Chemistry Application - Periodic Table · Element Properties · Molecular Weight");

PeriodicTableWindow::PeriodicTableWindow(const Glib::RefPtr<Gtk::Application>& app)
:
m_VBox(Gtk::ORIENTATION_VERTICAL, 3),
  m_HBox(Gtk::ORIENTATION_HORIZONTAL),
  m_MenuBar(),
  s_MenuTable(),
  //s_MenuItemLine(),
  s_MenuItemQuit(),
  s_MenuCalc(),
  s_MenuItemOpen(),
  s_MenuItemClose(),
  s_MenuItemAbout(),
  m_TableWindow(),
  m_Grid(),
  m_Dialog(),
  m_FormulaWindow(),
  m_PropertyWindow()
{
    //Set up window and the top-level container:
    set_title(_(app_title));
    set_border_width(4);
    set_default_size(1072, 564);
    m_FormulaWindow.signal_hide().connect(sigc::mem_fun(*this,\
        &PeriodicTableWindow::on_calc_close));
    // menu "Table"
    m_MenuTable = Gtk::MenuItem(_("Table"));
    s_MenuItemQuit.add_pixlabel("16x16/application-exit.png", _("Exit"), Gtk::Align::ALIGN_START);
    s_MenuItemQuit.signal_activate().connect(sigc::mem_fun(*this,\
        &PeriodicTableWindow::on_action_quit));

    //s_MenuTable.append(s_MenuItemLine);
    s_MenuTable.append(s_MenuItemQuit);

    m_MenuTable.set_submenu(s_MenuTable);
    // menu "Calc"
    m_MenuCalc = Gtk::MenuItem(_("Calc"));
    m_MenuCalc.set_submenu(s_MenuCalc);
    s_MenuItemOpen.add_pixlabel("16x16/document-open.png", _("Open"), Gtk::Align::ALIGN_START);
    s_MenuItemOpen.signal_activate().connect(sigc::mem_fun(*this,\
        &PeriodicTableWindow::on_calc_open));
    s_MenuItemClose.add_pixlabel("16x16/window-close.png", _("Close"), Gtk::Align::ALIGN_START);
    s_MenuItemClose.set_sensitive(false);
    s_MenuItemClose.signal_activate().connect(sigc::mem_fun(*this,\
        &PeriodicTableWindow::on_calc_close));
    s_MenuCalc.append(s_MenuItemOpen);
    s_MenuCalc.append(s_MenuItemClose);
    // menu "Help"
    m_MenuHelp = Gtk::MenuItem(_("Help"));
    s_MenuItemAbout.add_pixlabel("16x16/help-about.png", _("Info"), Gtk::Align::ALIGN_START);
    s_MenuItemAbout.signal_activate().connect(sigc::mem_fun(*this,\
        &PeriodicTableWindow::on_help_about));
    s_MenuHelp.append(s_MenuItemAbout);
    m_MenuHelp.set_submenu(s_MenuHelp);
    // set menu bar
    m_MenuBar.set_margin_bottom(4);
    m_MenuBar.append(m_MenuTable);
    m_MenuBar.append(m_MenuCalc);
    m_MenuBar.append(m_MenuHelp);
    m_VBox.pack_start(m_MenuBar, Gtk::PACK_SHRINK);

    add(m_VBox);
    Glib::RefPtr<Gtk::CssProvider> m_LabelCssProvider = Gtk::CssProvider::create();
    m_LabelCssProvider->load_from_data(label_css);
    int i = 0;
    int p = 0;
    for (auto period : table_blueprint) {
        int g = 0;
        for (auto group : period) {
            switch (group.first) {
                case 1:
                {
                    auto element = elements[i];
                    std::stringstream text;
                    // use momentan valid locale
                    text.imbue(std::locale(""));
                    auto element_ordinal = element[0];
                    double mass;
                    stringstream massStream(element[3]);
                    massStream >> mass; 
                    text << "<span size=\"x-small\">" << element_ordinal << "</span>"
                        << std::endl << "<b>" << element[1] << "</b>" << std::endl
                        << "<span size=\"x-small\">"
                        << std::setprecision(3) << std::fixed << mass << "</span>";
                    //Tooltip Window:
                    Gtk::Window* tooltip_window = new Gtk::Window(Gtk::WINDOW_POPUP);
                    tooltip_window->set_default_size(144, 24);
                    //Label:
                    Gtk::Label* element_label = Gtk::manage(new Gtk::Label());
                    element_label->set_justify(Gtk::Justification::JUSTIFY_CENTER);
                    element_label->set_markup(text.str());
                    //Button:
                    Gtk::Button* element_button = Gtk::manage(new Gtk::Button());
                    element_button->set_size_request(48, 48);
                    element_button->add(*element_label);
                    // set_tooltip_window(), like set_tooltip_text()
                    // will call set_has_tooltip() for us.
                    element_button->set_tooltip_window(*tooltip_window);
                    std::string button_name = colors[group.second];
                    element_button->set_name(button_name);
                    Glib::RefPtr<Gtk::CssProvider> buttonCssProvider = Gtk::CssProvider::create();
                    buttonCssProvider->load_from_data(button_css);
                    element_button->get_style_context()->add_provider(\
                        buttonCssProvider, GTK_STYLE_PROVIDER_PRIORITY_USER);
                    //Button's custom tooltip window:
                    Gtk::Label* label = Gtk::manage(new Gtk::Label(element[2]));
                    label->get_style_context()->add_provider(\
                        m_LabelCssProvider, GTK_STYLE_PROVIDER_PRIORITY_USER);
                    label->show();
                    tooltip_window->add(*label);
                    element_button->signal_query_tooltip().connect(sigc::mem_fun(*this,\
                        &PeriodicTableWindow::on_button_query_tooltip));
                    element_button->signal_clicked().connect(\
                        sigc::bind<int>(sigc::mem_fun(&m_PropertyWindow,\
                            &ElementProperty::on_element_clicked), i));
                    m_Grid.attach(*element_button, g, p, 1, 1); // column g, row p
                    g++;
                    i++;
                    break;
                }
                case 0:
                {
                    Gtk::Label* space = Gtk::manage(new Gtk::Label(Glib::ustring()));
                    space->set_size_request(48, 48);
                    m_Grid.attach(*space, g, p, 1, 1); // column g, row p
                    g++;
                    break;
                }
                case -1: {
                    // space for lanthanoides and actinoids
                    Gtk::Label* space = new Gtk::Label(Glib::ustring());
                    space->set_size_request(48, 48);
                    m_Grid.attach(*space, g, p, 1, 1); // column g, row p
                    g++;
                    i += 15;
                    break;
                }
                case -2: {
                    Gtk::Label* space = new Gtk::Label(Glib::ustring());
                    space->set_size_request(48, 48);
                    m_Grid.attach(*space, g, p, 1, 1); // column g, row p
                    g++;
                    i -=62;
                    break;
                }
                case -3: {
                    Gtk::Label* space = new Gtk::Label(Glib::ustring());
                    space->set_size_request(48, 48);
                    m_Grid.attach(*space, g, p, 1, 1); // column g, row p
                    g++;
                    i += 17;
                    break;
                }
                case -4: {
                    // empty space before extra lanthanoide resp. actinoide period
                    Gtk::Label* space = new Gtk::Label(Glib::ustring());
                    space->set_size_request(48, 12);
                    m_Grid.attach(*space, g, p, 1, 1); // column g, row p
                    g++;
                    break;
                }
                default:
                    break;
            }
        }
        p++;
    }
    m_Grid.set_column_homogeneous(true);
    m_TableWindow.add(m_Grid);
    m_VBox.pack_start(m_TableWindow);

    m_Dialog.set_transient_for(*this);
    m_Dialog.set_logo(Gdk::Pixbuf::create_from_xpm_data(about));
    m_Dialog.set_program_name(_(app_title));
    m_Dialog.set_version(_("Version 1.5.1"));
    m_Dialog.set_copyright(_("Copyright © 2018 Erich Küster. All rights reserved."));
    m_Dialog.set_comments(_("Periodic Table and Molecular Formula for Chemists"));
    std::ifstream licenseFile("LICENSE");
    std::stringstream licenseStream;
    licenseStream << licenseFile.rdbuf();
    m_Dialog.set_license(licenseStream.str());
    std::ifstream commentsFile(_("COMMENTS"));
    std::stringstream commentsStream;
    commentsStream << commentsFile.rdbuf();
    m_Dialog.set_comments(commentsStream.str());

    m_Dialog.set_website("http://www.gtkmm.org");
    m_Dialog.set_website_label(_("gtkmm Website - C++ Interfaces for GTK+ and GNOME"));

    std::vector<Glib::ustring> list_authors;
    list_authors.push_back("Erich Küster, Krefeld/Germany");
    list_authors.push_back(_("Dmitri Ivanovich Mendeleev, Saint Petersburg/Russia"));
    list_authors.push_back(_("IUPAC, International Union of Pure and Applied Chemistry"));
    m_Dialog.set_authors(list_authors);

    m_Dialog.signal_response().connect(sigc::mem_fun(*this,\
        &PeriodicTableWindow::on_about_dialog_response));

    show_all_children();
}

PeriodicTableWindow::~PeriodicTableWindow() {
}

bool PeriodicTableWindow::on_button_query_tooltip(int, int, bool, const Glib::RefPtr<Gtk::Tooltip>&) {
    //we already have a custom window ready, just return true to show it:
    return true;
}

void PeriodicTableWindow::on_action_quit() {
    hide();
}

void PeriodicTableWindow::on_calc_open() {
    s_MenuItemClose.set_sensitive(true);
    s_MenuItemOpen.set_sensitive(false);
    m_FormulaWindow.present();
}

void PeriodicTableWindow::on_calc_close() {
    s_MenuItemClose.set_sensitive(false);
    s_MenuItemOpen.set_sensitive(true);
    m_FormulaWindow.hide();
}

void PeriodicTableWindow::on_help_about() {
    m_Dialog.show();
    //bring it to the front, in case it was already shown:
    m_Dialog.present();
}

void PeriodicTableWindow::on_about_dialog_response(int response_id) {
    switch (response_id) {
        case Gtk::RESPONSE_CLOSE:
        case Gtk::RESPONSE_CANCEL:
        case Gtk::RESPONSE_DELETE_EVENT:
            m_Dialog.hide();
            break;
        default:
            std::cout << _("Unexpected response!") << std::endl;
            break;
    }
}
