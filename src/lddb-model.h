#ifndef LD_MODEL_H
#define LD_MODEL_H
#include <gtkmm/treemodel.h>
#include <gtkmm/treestore.h>

//Tree model columns:
class LdTagModelColumns : public Gtk::TreeModel::ColumnRecord
{
  public:

    LdTagModelColumns()
    { add(m_tag_type); add(m_tag_id); add(m_tag_name); add(m_world_name);}

    void
    loadCharacters(Glib::RefPtr<Gtk::TreeStore> &refTreeModel_ );

    typedef enum eTagType {
        LD_TAGTYPE_VEHICLE ='v',
        LD_TAGTYPE_CHARACTER = 'c'
    }tTagType;

    Gtk::TreeModelColumn<eTagType>      m_tag_type;
    Gtk::TreeModelColumn<unsigned int>  m_tag_id;
    Gtk::TreeModelColumn<Glib::ustring> m_tag_name;
    Gtk::TreeModelColumn<Glib::ustring> m_world_name;
};

#endif
