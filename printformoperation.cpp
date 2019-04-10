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

#include "printformoperation.h"
#include "gdkmm-2.4/gdkmm/pixbuf.h"

PrintFormOperation::PrintFormOperation()
{
}

PrintFormOperation::~PrintFormOperation()
{
}

Glib::RefPtr<PrintFormOperation> PrintFormOperation::create()
{
  return Glib::RefPtr<PrintFormOperation>(new PrintFormOperation());
}

void PrintFormOperation::on_begin_print(
        const Glib::RefPtr<Gtk::PrintContext>& print_context) {
}

void PrintFormOperation::on_draw_page(
        const Glib::RefPtr<Gtk::PrintContext>& print_context, int page_nr) {
    //Get a Cairo Context, which is used as a drawing board
    Cairo::RefPtr<Cairo::Context> cairo_ctx = print_context->get_cairo_context();
    // calculate proportional scaling
    const double height = print_context->get_height();
    const double width = print_context->get_width()-20;
    const int img_height = m_refPixbuf->get_height();
    const int img_width = m_refPixbuf->get_width();
    double height_ratio = height / double(img_height);
    double width_ratio =  width / double(img_width);
    double scale_xy = std::min(height_ratio, width_ratio);
    // shift start point for painting
    cairo_ctx->translate(10, 20);
    // scale image and add it
    cairo_ctx->scale(scale_xy, scale_xy);
    Gdk::Cairo::set_source_pixbuf(cairo_ctx, m_refPixbuf, 0, 0);
    cairo_ctx->paint();
}
