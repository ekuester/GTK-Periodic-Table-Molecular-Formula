/* gtkmm example Copyright (C) 2006 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef GTKMM_PRINT_FORM_OPERATION_H
#define GTKMM_PRINT_FORM_OPERATION_H

#include <algorithm>
#include <glibmm/i18n.h>
#include <gtkmm.h>
#include <iostream>

//We derive our own class from PrintOperation,
//so we can put the actual print implementation here.
class PrintFormOperation : public Gtk::PrintOperation
{
 public:
  static Glib::RefPtr<PrintFormOperation> create();
  virtual ~PrintFormOperation();

  void set_pixbuf(const Glib::RefPtr<Gdk::Pixbuf> pixbuf) { m_refPixbuf = pixbuf; }

 protected:
  PrintFormOperation();

  //PrintOperation default signal handler overrides:
  void on_begin_print(const Glib::RefPtr<Gtk::PrintContext>& context) override;
  void on_draw_page(const Glib::RefPtr<Gtk::PrintContext>& context, int page_nr) override;

  Glib::RefPtr<Gdk::Pixbuf> m_refPixbuf;
};

#endif // GTKMM_PRINT_FORM_OPERATION_H
