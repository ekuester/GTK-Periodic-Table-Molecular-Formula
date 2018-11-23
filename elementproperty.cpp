/* 
 * File:   ElementPropertyWindow.cpp
 * Author: kuestere
 * 
 * Created on 7. November 2018, 22:31
 */

#include "elementproperty.h"

using namespace std;

ElementProperty::ElementProperty()
: m_VBox(Gtk::ORIENTATION_VERTICAL),
  m_TitleLabel(),
  m_TableWindow(),
  m_Grid(),
  m_Move_HBox(Gtk::Orientation::ORIENTATION_HORIZONTAL),
  m_LeftRight_HBox(Gtk::Orientation::ORIENTATION_HORIZONTAL)
{
    // set background color
    set_name("window_azure");
    Glib::RefPtr<Gtk::CssProvider> windowCssProvider = Gtk::CssProvider::create();
    windowCssProvider->load_from_data(window_css);
    get_style_context()->add_provider(\
        windowCssProvider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    set_title(_("Gtk+: Application - Element Properties"));
    set_border_width(4);
    set_default_size(392, 496);
    set_type_hint(Gdk::WindowTypeHint::WINDOW_TYPE_HINT_DIALOG);
    move(512, 64);
    m_VBox.pack_start(m_TitleLabel, Gtk::PackOptions::PACK_SHRINK);
    m_Grid.set_column_spacing(8);
    // Add the Grid, inside a ScrolledWindow
    m_TableWindow.add(m_Grid);
    // Only show the scrollbars when they are necessary:
    m_TableWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    m_VBox.pack_start(m_TableWindow);
    m_VBox.set_border_width(8);
    m_go_left_Button.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,\
        &ElementProperty::on_button_clicked), -1));
    m_go_right_Button.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,\
        &ElementProperty::on_button_clicked), 1));
    m_LeftRight_HBox.pack_start(m_go_left_Button, Gtk::PackOptions::PACK_SHRINK);
    m_LeftRight_HBox.pack_start(m_go_right_Button, Gtk::PackOptions::PACK_SHRINK);
    // style
    m_LeftRight_HBox.get_style_context()->add_class("raised");
    m_LeftRight_HBox.get_style_context()->add_class("linked");
    // Buttons
    m_go_left_Button.set_image_from_icon_name("go-previous-symbolic", Gtk::ICON_SIZE_BUTTON, true);
    m_go_right_Button.set_image_from_icon_name("go-next-symbolic", Gtk::ICON_SIZE_BUTTON, true);
    m_Move_HBox.pack_start(m_LeftRight_HBox, Gtk::PackOptions::PACK_EXPAND_PADDING);
    m_VBox.pack_start(m_Move_HBox, Gtk::PackOptions::PACK_SHRINK);
    // build first column with names of properties
    int row = 0;
    for (auto name : property_names) {
        Gtk::Label* left = new Gtk::Label(_(name), Gtk::ALIGN_START);
        left->set_hexpand_set(true);
        left->set_margin_right(8);
        left->set_margin_right(8);
        left->set_vexpand(false);
        m_Grid.attach(*left, 0, row, 1, 1); // column 0, row row
        row++;
    }
}

ElementProperty::ElementProperty(const ElementProperty& orig) {
}

ElementProperty::~ElementProperty() {
}

void ElementProperty::on_element_clicked(int index) {
    // place to give more information about the specific element
    if (m_ElementIndex >= 0) {
        remove();
        m_Grid.remove_column(1);
    }
    m_ElementIndex = index;
    auto element = elements[index];
    stringstream title;
    title << "<b>" << element[2] << "</b>";
    m_TitleLabel.set_markup(title.str());
    int row = 0;
    // iterator over vector of strings
    auto value = element.begin();
    while (value != element.end()) {
        Gtk::Label* right = Gtk::manage(new Gtk::Label());
        right->set_alignment(Gtk::ALIGN_START);
        auto markup = *value;
        if (std::next(value) == element.end()) {
            stringstream markup_url;
            markup_url << _("see <a href=\"") << *value << "\" title=\""
                << *value << _("\">Wikipedia</a> article");
            markup = markup_url.str();
        }
        right->set_markup(markup);
        right->set_vexpand(false);
        m_Grid.attach(*right, 1, row, 1, 1); // column 1, row row
        row++;
        value++;
    }
    add(m_VBox);
    show_all_children();
    present();
}

void ElementProperty::on_button_clicked(int advance) {
    int index = m_ElementIndex + advance;
    if ((index >= 0) || (index < elements.size()))
        on_element_clicked(index);
}