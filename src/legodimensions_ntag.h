#ifndef HAVE_LEGODIMENSIONS_NTAG
#define HAVE_LEGODIMENSIONS_NTAG

#include <glib.h>

#define NTAG_UNKNOWN                "UNKOWN"

#define WORLD_DC_COMICS             "DC Comics"
#define WORLD_LORD_OF_THE_RINGS     "Lord of the Rings"
#define WORLD_THE_LEGO_MOVIE        "The Lego Movie"
#define WORLD_THE_SIMPSONS          "The Simpsons"
#define WORLD_PORTAL2               "Portal 2"
#define WORLD_LEGO_NINJAGO          "Lego Ninjago"
#define WORLD_LEGO_LEGENDS_OF_CHIMA "Lego Legends of Chima"
#define WORLD_DOCTOR_WHO            "Doctor Who"
#define WORLD_BACK_TO_THE_FUTURE    "Back to the Future"
#define WORLD_JURASSIC_WORLD        "Jurassic World"
#define WORLD_MIDWAY_ARCADE         "Midway Arcade"
#define WORLD_GHOSTBUSTERS          "Ghostbusters"
#define WORLD_SCOOBY_DOO            "Scooby-Doo"
#define WORLD_WIZARD_OF_OZ          "Wizard of Oz"

/* wave 6 */
#define WORLD_FANTASTIC_BEASTS      "Fantastic Beasts and Where to Find Them"
#define WORLD_ADVENTURE_TIME        "Adventure Time"
#define WORLD_MISSION_IMPOSSIBLE    "Mission: Impossible"
#define WORLD_HARRY_POTTER          "Harry Potter"
#define WORLD_GREMLINS              "Gremlins"
#define WORLD_THE_A_TEAM            "The A-Team"

/* wave 7 */
#define WORLD_SONIC_THE_HEDGEHOG    "Sonic the Hedgehog"
#define WORLD_E_T                   "E.T. the Extra-Terrestrial"
#define WORLD_THE_LEGO_BATMAN_MOVIE "The Lego Batman Movie"
#define WORLD_KNIGHT_RIDER          "Knight Rider"
#define WORLD_GHOSTBUSTER_2016      "Ghostbusters 2016"

/* wave 7.5 */
#define WORLD_LEGO_BATMAN_MOVIE     "The LEGO Batman Movie"
#define WORLD_KNIGHT_RIDER          "Knight Rider"


typedef struct  {
    const gchar *name;
    const gchar *world;
} ntag_t ;

extern const ntag_t ld_unknown_ntag;

#endif
