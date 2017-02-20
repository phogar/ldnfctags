#include "lddb-model.h"
#include "legodimensions_characters.h"
void
LdTagModelColumns::loadCharacters(Glib::RefPtr<Gtk::TreeStore> &refTreeModel_ )
{
  Gtk::TreeModel::Row row;
  int cid;
  const ntag_t *ntag;

  for ( cid = 1; ntag = ld_get_character_by_id(cid, NULL); cid++){
    if( Glib::ustring(ntag->name) == Glib::ustring(NTAG_UNKNOWN)) continue;
    row = *(refTreeModel_->append());
    row[m_tag_id]     = cid;
    row[m_tag_name]   = ntag->name;
    row[m_world_name] = ntag->world;
  }
} // loadCharacters
