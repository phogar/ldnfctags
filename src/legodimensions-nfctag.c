/*
 *
 */


#include "legodimensions-nfctag.h"

/* Private structure definition */
typedef struct _LegodimensionsNfctagPrivate {
    gchar *charactername;
    //GInputStream *input_stream;
} LegodimensionsNfctagPrivate;

struct _LegodimensionsNfctag
{
  GObject parent_instance;
  /* Other members, including private data */
};

/*
 * forward defintions
 */

G_DEFINE_TYPE_WITH_PRIVATE (LegodimensionsNfctag, legodimensions_nfctag, G_TYPE_OBJECT)



static void
legodimensions_nfctag_class_new(LegodimensionsNfctagClass *klass){
}


static void
legodimensions_nfctag_new(LegodimensionsNfctag *self){
    LegodimensionsNfctagPrivate *priv = legodimensions_nfctag_get_instance_private(self);

    /* initialize all public and private members to reasonable default values.
     * They are all automatically initialized to 0 to begin with. */
}


static void
legodimensions_nfctag_dispose(GObject *gobject){
    LegodimensionsNfctagPrivate *priv = legodimensions_nfctag_get_instance_private(LEGODIMENSIONS_NFCTAG(gobject));

  /* In dispose(), you are supposed to free all types referenced from this
   * object which might themselves hold a reference to self. Generally,
   * the most simple solution is to unref all members on which you own a
   * reference.
   */

  /* dispose() might be called multiple times, so we must guard against
   * calling g_object_unref() on an invalid GObject by setting the member
   * NULL; g_clear_object() does this for us.
   */
   //g_clear_object( &priv->input_stream);

   /* Always chain up to the parent class; there is no need to check if
    * the parent class implements the dispose() virtual function: it is
    * always guaranteed to do so
    */
    G_OBJECT_CLASS(legodimensions_nfctag_parent_class)->dispose (gobject);
}

static void
legodimensions_nfctag_class_init(LegodimensionsNfctagClass *klass){
    GObjectClass *object_class = G_OBJECT_CLASS(klass);

    object_class->dispose = legodimensions_nfctag_dispose;
}



static void
legodimensions_nfctag_init(LegodimensionsNfctag *self){
    LegodimensionsNfctagPrivate *priv = legodimensions_nfctag_get_instance_private(self);

    priv->charactername = "";
}
