/*
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

#include "lddb-window.h"

#include <iostream>
#include <gtkmm/treestore.h>
#include <gtkmm/cellrendererprogress.h>

#include "legodimensions_characters.h"

LegoDimensionsDatabaseWindow::LegoDimensionsDatabaseWindow()
: m_VBox(Gtk::ORIENTATION_VERTICAL),
  m_Button_Quit("Quit")
{
  set_title("Lego Dimensions - NFC Tag Database");
  set_border_width(5);
  set_default_size(400, 200);

  add(m_VBox);

  //Add the TreeView, inside a ScrolledWindow, with the button underneath:
  m_ScrolledWindow.add(m_TreeView);

  //Only show the scrollbars when they are necessary:
  m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

  m_VBox.pack_start(m_ScrolledWindow);
  m_VBox.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);

  m_ButtonBox.pack_start(m_Button_Quit, Gtk::PACK_SHRINK);
  m_ButtonBox.set_border_width(5);
  m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);
  m_Button_Quit.signal_clicked().connect( sigc::mem_fun(*this,
              &LegoDimensionsDatabaseWindow::on_button_quit) );

  //Create the Tree model:
  m_refTreeModel = Gtk::TreeStore::create(m_Columns);
  m_TreeView.set_model(m_refTreeModel);

  //Fill the TreeView's model
  m_Columns.loadCharacters(m_refTreeModel);

  //Add the TreeView's view columns:
  //This number will be shown with the default numeric formatting.
  m_TreeView.append_column("ID", m_Columns.m_tag_id);
  m_TreeView.append_column("Name", m_Columns.m_tag_name);
  m_TreeView.append_column("World", m_Columns.m_world_name);

  //Display a progress bar instead of a decimal number:
  //auto cell = Gtk::manage(new Gtk::CellRendererProgress);
  //int cols_count = m_TreeView.append_column("Some percentage", *cell);
  //auto pColumn = m_TreeView.get_column(cols_count - 1);
  //if(pColumn)
  //{
//    pColumn->add_attribute(cell->property_value(), m_Columns.m_col_percentage);
//  }

  //Make all the columns reorderable:
  //This is not necessary, but it's nice to show the feature.
  //You can use TreeView::set_column_drag_function() to more
  //finely control column drag and drop.
  for(guint i = 0; i < 2; i++)
  {
    auto column = m_TreeView.get_column(i);
    column->set_reorderable();
  }

  show_all_children();
}

LegoDimensionsDatabaseWindow::~LegoDimensionsDatabaseWindow()
{
}


void
LegoDimensionsDatabaseWindow::on_button_quit()
{
  hide();
}

