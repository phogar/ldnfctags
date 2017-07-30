
#include "legodimensions_characters.h"
#include "legodimensions_ntag.h"
#include <glib.h>

#define LD_MAX_KNOWN_CID ( (int)sizeof(ld_characters)/sizeof(ld_characters[0]) -2 )


/* List characters by ID */
const ntag_t ld_characters[] = {
/* 00 */ { NTAG_UNKNOWN         ,NTAG_UNKNOWN }, /* ID 0 - unused */
/* 01 */ {"Batman"              ,WORLD_DC_COMICS},
/* 02 */ {"Gandalf"             ,WORLD_LORD_OF_THE_RINGS},
/* 03 */ {"Wyldstyle"           ,WORLD_THE_LEGO_MOVIE},
/* 04 */ {"Aquaman"             ,WORLD_DC_COMICS},       /* verified - DC Comics */
/* 05 */ {"Bad Cop"             ,WORLD_THE_LEGO_MOVIE},
/* 06 */ {"Bane"                ,WORLD_DC_COMICS},
/* 07 */ {"Bart Simpson"        ,WORLD_THE_SIMPSONS},
/* 08 */ {"Benny"               ,WORLD_THE_LEGO_MOVIE},
/* 09 */ {"Chell"               ,WORLD_PORTAL2},         /* verified - Portal 2 */

/* 10 */ {"Cole"                ,WORLD_LEGO_NINJAGO},
/* 11 */ {"Cragger"             ,WORLD_LEGO_LEGENDS_OF_CHIMA},
/* 12 */ {"Cyborg"              ,WORLD_DC_COMICS},
/* 13 */ {"Cyberman"            ,WORLD_DOCTOR_WHO},
/* 14 */ {"Doc Brown"           ,WORLD_BACK_TO_THE_FUTURE},
/* 15 */ {"The Doctor"          ,WORLD_DOCTOR_WHO},
/* 16 */ {"Emmet"               ,WORLD_THE_LEGO_MOVIE},
/* 17 */ {"Eris"                ,WORLD_LEGO_LEGENDS_OF_CHIMA},
/* 18 */ {"Gimli"               ,WORLD_LORD_OF_THE_RINGS},
/* 19 */ {"Gollum"              ,WORLD_LORD_OF_THE_RINGS},

/* 20 */ {"Harley Quinn"        ,WORLD_DC_COMICS},
/* 21 */ {"Homer Simpson"       ,WORLD_THE_SIMPSONS},
/* 22 */ {"Jay"                 ,WORLD_LEGO_NINJAGO},
/* 23 */ {"Joker"               ,WORLD_DC_COMICS},
/* 24 */ {"Kai"                 ,WORLD_LEGO_NINJAGO},
/* 25 */ {"ACU Trooper"         ,WORLD_JURASSIC_WORLD},
/* 26 */ {"Gamer Kid"           ,WORLD_MIDWAY_ARCADE},
/* 27 */ {"Krusty"              ,WORLD_THE_SIMPSONS},
/* 28 */ {"Laval"               ,WORLD_LEGO_LEGENDS_OF_CHIMA},
/* 29 */ {"Leoglas"             ,WORLD_LORD_OF_THE_RINGS},

/* 30 */ {"Lloyd"               ,WORLD_LEGO_NINJAGO},
/* 31 */ {"Marty McFly"         ,WORLD_BACK_TO_THE_FUTURE},
/* 32 */ {"Nya"                 ,WORLD_LEGO_NINJAGO},
/* 33 */ {"Owen"                ,WORLD_JURASSIC_WORLD},
/* 34 */ {"Peter Venkman"       ,WORLD_GHOSTBUSTERS},
/* 35 */ {"Slimer"              ,WORLD_GHOSTBUSTERS},
/* 36 */ {"Scooby Doo"          ,WORLD_SCOOBY_DOO},
/* 37 */ {"Sensei Wu"           ,WORLD_LEGO_NINJAGO},
/* 38 */ {"Shaggy"              ,WORLD_SCOOBY_DOO},
/* 39 */ {"Stay Puft"           ,WORLD_GHOSTBUSTERS},

/* 40 */ {"Superman"            ,WORLD_DC_COMICS},             /* verified - DC Comics */
/* 41 */ {"Unikitty"            ,WORLD_THE_LEGO_MOVIE},        /* verified - LEGO Movie */
/* 42 */ {"Wicked Witch"        ,WORLD_WIZARD_OF_OZ },         /* verified - Wizard of Oz */
/* 43 */ {"Wonder Woman"        ,WORLD_DC_COMICS},             /* verified - DC Comics */
/* 44 */ {"Zane"                ,WORLD_LEGO_NINJAGO},          /* verified - Ninjago */
/* 45 */ {"Green Arrow"         ,WORLD_DC_COMICS},             /* verified - DC Comics */
/* 46 */ {"Supergirl"           ,WORLD_DC_COMICS},             /* verified - DC Comics */
/* 47 */ {"Abby Yates"          ,WORLD_GHOSTBUSTER_2016},      /* verified - Ghostbuster 2016 */
/* 48 */ {"Finn"                ,WORLD_ADVENTURE_TIME},        /* verified - Adventure Time */
/* 49 */ {"Ethan Hunt"          ,WORLD_MISSION_IMPOSSIBLE},    /* verified - Mission Impossible */

/* 50 */ {"Lumpy Space Princess",WORLD_ADVENTURE_TIME},        /* verified - Adventure Time */
/* 51 */ {"Jake the Dog"        ,WORLD_ADVENTURE_TIME},        /* verified - Adventure Time */
/* 52 */ {"Harry Potter"        ,WORLD_HARRY_POTTER},          /* verified - Harry Potter  */
/* 53 */ {"Lord Voldemort"      ,WORLD_HARRY_POTTER},          /* verified - Harry Potter */
/* 54 */ {"Michael Knight"      ,WORLD_KNIGHT_RIDER},          /* verified - Knight Rider */
/* 55 */ {"B.A.Baracus"         ,WORLD_A_TEAM},                /* verified - The A-Team */
/* 56 */ {"Newt Scamander"      ,WORLD_FANTASTIC_BEASTS},      /* verified - Fantastic Beasts */
/* 57 */ {"Sonic the Hedgehog"  ,WORLD_SONIC_THE_HEDGEHOG},    /* verified - Sonic The Hedgehog */
/* 58 */ {NTAG_UNKNOWN          ,NTAG_UNKNOWN},                /* verified - game asks for an update */
/* 59 */ {"Gizmo"               ,WORLD_GREMLINS},              /* verified - Gremlins */

/* 60 */ {"Stripe"              ,WORLD_GREMLINS},              /* verified - Gremlins */
/* 61 */ {"E.T."                ,WORLD_E_T},                   /* verified - E.T. */
/* 62 */ {"Tina Goldstein"      ,WORLD_FANTASTIC_BEASTS},      /* verified - Fantastic Beasts */
/* 63 */ {"Marceline Abadeer"   ,WORLD_ADVENTURE_TIME},        /* verified - Adventure Time */
/* 64 */ {"Batgirl"             ,WORLD_LEGO_BATMAN_MOVIE},     /* verified - The LEGO Batman Movie */
/* 65 */ {"Robin (Lego Movie)"  ,WORLD_LEGO_BATMAN_MOVIE},     /* verified - The LEGO Batman Movie */
/* 66 */ {"Sloth"               ,WORLD_THE_GOONIES},           /* verified - The Goonies */
/* 67 */ {"Hermione Granger"    ,WORLD_HARRY_POTTER},          /* verified - Harry Potter */
/* 68 */ {"Chase McCain"        ,WORLD_LEGO_CITY},             /* verified - LEGO City */
/* 69 */ {"Excalibur Batman"    ,WORLD_LEGO_BATMAN_MOVIE},     /* verified - The LEGO Batman Movie */
/* 70 */ {"Raven"               ,WORLD_TEEN_TITANS_GO},        /* verified - Teen Titans Go! */
/* 71 */ {"Beast Boy"           ,WORLD_TEEN_TITANS_GO},        /* verified - Teen Titans Go! */
/* 72 */ {"Betelgeuse"          ,WORLD_BEETLEJUISE},           /* verified - Beetlejuice */
/* 73 */ {NTAG_UNKNOWN          ,NTAG_UNKNOWN},                /* game v2.4.0 crashes  */
/* 74 */ {"Blossom"             ,WORLD_POWERPUFF_GIRLS},
/* 75 */ {"Bubbles"             ,WORLD_POWERPUFF_GIRLS},
/* 76 */ {"Buttercup"           ,WORLD_POWERPUFF_GIRLS},
/* 77 */ {"Starfire"            ,WORLD_TEEN_TITANS_GO},
/* 78 */ {NTAG_UNKNOWN          ,NTAG_UNKNOWN},                /* game v2.4.0 crashes */
/* 79 */ {NTAG_UNKNOWN          ,NTAG_UNKNOWN},                /* game v2.4.0 crashes */
/* 80 */ {NTAG_UNKNOWN          ,NTAG_UNKNOWN},                /* game v2.4.0 crashes */
    { NULL, NULL }                          /* terminate list */
};


const ntag_t *
ld_get_character_by_id(guint cid_, GError **error_){

    /* Out of Range */
    if (!LD_CID_VALID(cid_)) {
        g_set_error(error_, G_OPTION_ERROR, 9, "Character id(%d) is out of range ("
                    G_STRINGIFY(LD_MIN_CID)".."G_STRINGIFY(LD_MAX_CID)").\n", cid_);
        return NULL;
    }

    return cid_>LD_MAX_KNOWN_CID?ld_characters:ld_characters+cid_;

} // ld_get_character_by_id

void
ld_print_characters(){
    guint cid;
    for (cid = 1; ld_characters[cid].name; cid++){
        const ntag_t *chr;
        chr = ld_characters+cid;
        g_print("c%02d: %s: %s\n", cid, chr->name, chr->world);
    }
} /* ld_print_characters */


void
ld_print_character_by_id(guint cid_){
    const ntag_t *c = ld_get_character_by_id(cid_, NULL);
    if(c)
        g_print("c%02d: %s: %s\n", cid_, c->name, c->world);
} /* ld_print_character_by_id */


const gchar *
ld_get_character_name_by_id(guint cid_, GError **error_){
    const ntag_t *c = ld_get_character_by_id(cid_, error_);
    return c?c->name:NULL;
} /* ld_get_character_name_by_id */


const gchar *
ld_get_character_world_by_id(guint cid_, GError **error_){
    const ntag_t * c= ld_get_character_by_id(cid_, error_);
    return c?c->world:NULL;
} /* ld_get_character_world_by_id */
