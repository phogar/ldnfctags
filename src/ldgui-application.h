#ifndef LDGUI_APPLICATION_H_
#define LDGUI_APPLICATION_H_

#include <gtkmm.h>

class LegoDimensionsGuiMainWindow;

class LegoDimensionsGuiApplication: public Gtk::Application
{
protected:
  LegoDimensionsGuiApplication();

public:
  static Glib::RefPtr<LegoDimensionsGuiApplication> create();

protected:
  // Override default signal handlers:
  void on_activate() override;
  void on_open(const Gio::Application::type_vec_files& files,
    const Glib::ustring& hint) override;

private:
//  PopulatingWindowWindow* create_appwindow();
  void on_hide_window(Gtk::Window* window);
};

#endif /* LDGUI_APPLICATION_H */
