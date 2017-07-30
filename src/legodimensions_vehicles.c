#include "legodimensions_vehicles.h"

#include <glib.h>
#include "legodimensions_ntag.h"

#define LD_MAX_KNOWN_VID ( (int) sizeof(ld_vehicles) / sizeof(ld_vehicles[0]) -2)


// List vehicles by ID
static const ntag_t ld_vehicles[] = {
/* 000 */ {"Police Car"              ,WORLD_THE_LEGO_MOVIE },
/* 001 */ {"Aerial Squad Car"        ,WORLD_THE_LEGO_MOVIE },
/* 002 */ {"Missile Striker"         ,WORLD_THE_LEGO_MOVIE },

/* 003 */ {"Gravity Sprinter"        ,WORLD_THE_SIMPSONS},
/* 004 */ {"Street Shredder"         ,WORLD_THE_SIMPSONS},
/* 005 */ {"Sky Clobberer"           ,WORLD_THE_SIMPSONS},

/* 006 */ {"Batmobile"               ,WORLD_DC_COMICS },
/* 007 */ {"Batblaster"              ,WORLD_DC_COMICS },
/* 008 */ {"Sonic Batray"            ,WORLD_DC_COMICS },

/* 009 */ {"Benny's Spaceship"       ,WORLD_THE_LEGO_MOVIE },
/* 010 */ {"Lasercraft"              ,WORLD_THE_LEGO_MOVIE },
/* 011 */ {"The Annihilator"         ,WORLD_THE_LEGO_MOVIE },

/* 012 */ {"DeLorean Time Machine"   ,WORLD_BACK_TO_THE_FUTURE },
/* 013 */ {"Ultra Time Machine"      ,WORLD_BACK_TO_THE_FUTURE },
/* 014 */ {"Electric Time Machine"   ,WORLD_BACK_TO_THE_FUTURE },

/* 015 */ {"Hoverboard"              ,WORLD_BACK_TO_THE_FUTURE },
/* 016 */ {"Cyclone Board"           ,WORLD_BACK_TO_THE_FUTURE },
/* 017 */ {"Ultimate Hoverjet"       ,WORLD_BACK_TO_THE_FUTURE },

/* 018 */ {"Eagle Interceptor"       ,WORLD_LEGO_LEGENDS_OF_CHIMA },
/* 019 */ {"Eagle Skyblazer"         ,WORLD_LEGO_LEGENDS_OF_CHIMA },
/* 020 */ {"Eagle Swoop Diver"       ,WORLD_LEGO_LEGENDS_OF_CHIMA },

/* 021 */ {"Swamp Skimmer"           ,WORLD_LEGO_LEGENDS_OF_CHIMA },
/* 022 */ {"Croc Command Sub"        ,WORLD_LEGO_LEGENDS_OF_CHIMA },
/* 023 */ {"Cragger's Fireship"      ,WORLD_LEGO_LEGENDS_OF_CHIMA },

/* 024 */ {"Cyber Guard"             ,WORLD_DC_COMICS },
/* 025 */ {"Cyber-Wrecker"           ,WORLD_DC_COMICS },
/* 026 */ {"Laser Robot Walker"      ,WORLD_DC_COMICS },

/* 027 */ {"K9"                      ,WORLD_DOCTOR_WHO },
/* 028 */ {"K9 Ruff Rover"           ,WORLD_DOCTOR_WHO },
/* 029 */ {"K9 Laser Cutter"         ,WORLD_DOCTOR_WHO },

/* 030 */ {"TARDIS"                  ,WORLD_DOCTOR_WHO },
/* 031 */ {"Laser-Pulse TARDIS"      ,WORLD_DOCTOR_WHO },
/* 032 */ {"Energy-Burst TARDIS"     ,WORLD_DOCTOR_WHO },

/* 033 */ {"Emmet's Excavator"       ,WORLD_THE_LEGO_MOVIE },
/* 034 */ {"The Destroydozer"        ,WORLD_THE_LEGO_MOVIE },
/* 035 */ {"Destruct-o-Mech"         ,WORLD_THE_LEGO_MOVIE },

/* 036 */ {"Winged Monkey"           ,WORLD_WIZARD_OF_OZ },
/* 037 */ {"Battle Monkey"           ,WORLD_WIZARD_OF_OZ },
/* 038 */ {"Commander Monkey"        ,WORLD_WIZARD_OF_OZ },

/* 039 */ {"Axe Chariot"             ,WORLD_LORD_OF_THE_RINGS },
/* 040 */ {"Axe Hurler"              ,WORLD_LORD_OF_THE_RINGS },
/* 041 */ {"Soaring Chariot"         ,WORLD_LORD_OF_THE_RINGS },

/* 042 */ {"Shelob the Great"        ,WORLD_LORD_OF_THE_RINGS },
/* 043 */ {"8-Legged Stalker"        ,WORLD_LORD_OF_THE_RINGS },
/* 044 */ {"Poison Slinger"          ,WORLD_LORD_OF_THE_RINGS },

/* 045 */ {"Homer's Car"             ,WORLD_THE_SIMPSONS },
/* 046 */ {"The SubmaHomer"          ,WORLD_THE_SIMPSONS },
/* 047 */ {"The Homecraft"           ,WORLD_THE_SIMPSONS },

/* 048 */ {"Taunt-o-Vision"          ,WORLD_THE_SIMPSONS },
/* 049 */ {"The MechaHomer"          ,WORLD_THE_SIMPSONS },
/* 050 */ {"Blast Cam"               ,WORLD_THE_SIMPSONS },

/* 051 */ {"Velociraptor"            ,WORLD_JURASSIC_WORLD },
/* 052 */ {"Spike Attack Raptor"     ,WORLD_JURASSIC_WORLD },
/* 053 */ {"Venom Raptor"            ,WORLD_JURASSIC_WORLD },

/* 054 */ {"Gyrosphere"             ,WORLD_JURASSIC_WORLD },
/* 055 */ {"Sonic Beam Gyrosphere"   ,WORLD_JURASSIC_WORLD },
/* 056 */ {"Speed Boost Gyrosphere"  ,WORLD_JURASSIC_WORLD },

/* 057 */ {"Clown Bike"              ,WORLD_THE_SIMPSONS },
/* 058 */ {"Cannon Bike"             ,WORLD_THE_SIMPSONS },
/* 059 */ {"Anti-Gravity Rocket Bike",WORLD_THE_SIMPSONS },

/* 060 */ {"Mighty Lion Rider"       ,WORLD_LEGO_LEGENDS_OF_CHIMA },
/* 061 */ {"Lion Blazer"             ,WORLD_LEGO_LEGENDS_OF_CHIMA },
/* 062 */ {"Fire Lion"               ,WORLD_LEGO_LEGENDS_OF_CHIMA },

/* 063 */ {"Arrow Launcher"          ,WORLD_LORD_OF_THE_RINGS },
/* 064 */ {"Seeking Shooter"         ,WORLD_LORD_OF_THE_RINGS },
/* 065 */ {"Triple Ballista"         ,WORLD_LORD_OF_THE_RINGS },

/* 066 */ {"Mystery Machine"         ,WORLD_SCOOBY_DOO},
/* 067 */ {"Mystery Tow"             ,WORLD_SCOOBY_DOO },
/* 068 */ {"Mystery Monster"         ,WORLD_SCOOBY_DOO },

/* 069 */ {"Boulder Bomber"          ,WORLD_LEGO_NINJAGO },
/* 070 */ {"Boulder Blaster"         ,WORLD_LEGO_NINJAGO },
/* 071 */ {"Cyclone Jet"             ,WORLD_LEGO_NINJAGO },

/* 072 */ {"Storm Fighter"           ,WORLD_LEGO_NINJAGO },
/* 073 */ {"Lightning Jet"           ,WORLD_LEGO_NINJAGO },
/* 074 */ {"Electro-Shooter"         ,WORLD_LEGO_NINJAGO },

/* 075 */ {"Blade Bike"              ,WORLD_LEGO_NINJAGO },
/* 076 */ {"Flying Fire Bike"        ,WORLD_LEGO_NINJAGO },
/* 077 */ {"Blades of Fire"          ,WORLD_LEGO_NINJAGO },

/* 078 */ {"Samurai Mech"            ,WORLD_LEGO_NINJAGO },
/* 079 */ {"Samurai Shooter"         ,WORLD_LEGO_NINJAGO },
/* 080 */ {"Soaring Samurai Mech"    ,WORLD_LEGO_NINJAGO },

/* 081 */ {"Companion Cube"          ,WORLD_PORTAL2 },
/* 082 */ {"Laser Deflector"         ,WORLD_PORTAL2 },
/* 083 */ {"Gold Heart Emitter"      ,WORLD_PORTAL2 },

/* 084 */ {"Sentry Turret"           ,WORLD_PORTAL2 },
/* 085 */ {"Turret Striker"          ,WORLD_PORTAL2 },
/* 086 */ {"Flying Turret Carrier"   ,WORLD_PORTAL2 },

/* 087 */ {"Scooby Snack"            ,WORLD_SCOOBY_DOO },
/* 088 */ {"Scooby Fire Snack"       ,WORLD_SCOOBY_DOO },
/* 089 */ {"Scooby Ghost Snack"      ,WORLD_SCOOBY_DOO },

/* 090 */ {"Cloud Cukko Car"         ,WORLD_THE_LEGO_MOVIE },
/* 091 */ {"X-Stream Soaker"         ,WORLD_THE_LEGO_MOVIE },
/* 092 */ {"Rainbow Cannon"          ,WORLD_THE_LEGO_MOVIE },

/* 093 */ {"Invisible Jet"           ,WORLD_DC_COMICS },
/* 094 */ {"Stealth Laser Shooter"   ,WORLD_DC_COMICS },
/* 095 */ {"Torpedo Bomber"          ,WORLD_DC_COMICS },

/* 096 */ {"Ninja Copter"            ,WORLD_LEGO_NINJAGO },
/* 097 */ {"Glaciator"               ,WORLD_LEGO_NINJAGO },
/* 098 */ {"Freeze Fighter"          ,WORLD_LEGO_NINJAGO },

/* 099 */ {"Traveling Time Train"    ,WORLD_BACK_TO_THE_FUTURE },
/* 100 */ {"Flying Time Train "      ,WORLD_BACK_TO_THE_FUTURE },
/* 101 */ {"Missile Blast Time Train",WORLD_BACK_TO_THE_FUTURE },

/* 102 */ {"Aqua Watercraft"         ,WORLD_DC_COMICS },
/* 103 */ {"Seven Seas Speeder"      ,WORLD_DC_COMICS },
/* 104 */ {"Trident of Fire"         ,WORLD_DC_COMICS },

/* 105 */ {"Drill Driver"            ,WORLD_DC_COMICS },
/* 106 */ {"Bane Dig 'n' Drill"      ,WORLD_DC_COMICS },
/* 107 */ {"Bane Drill 'n' Blast"    ,WORLD_DC_COMICS },

/* 108 */ {"Quinn-mobile"            ,WORLD_DC_COMICS },
/* 109 */ {"Quinn Ultra Racer"       ,WORLD_DC_COMICS },
/* 110 */ {"Missile Launcher"        ,WORLD_DC_COMICS },

/* 111 */ {"The Jokers Chopper"      ,WORLD_DC_COMICS  },
/* 112 */ {"Mischievous Missile Blaster",WORLD_DC_COMICS },
/* 113 */ {"Lock 'n' Laser Jet"      ,WORLD_DC_COMICS },

/* 114 */ {"Hover Pod"               ,WORLD_DC_COMICS },
/* 115 */ {"Krypton Striker"         ,WORLD_DC_COMICS },
/* 116 */ {"Hover Pod 2"             ,WORLD_DC_COMICS },

/* 117 */ {"Dalek"                   ,WORLD_DOCTOR_WHO },
/* 118 */ {"Fire 'n' Ride Dalek"     ,WORLD_DOCTOR_WHO },
/* 119 */ {"Silver Shooter Dalek"    ,WORLD_DOCTOR_WHO },

/* 120 */ {"Ecto-1"                  ,WORLD_GHOSTBUSTERS },
/* 121 */ {"Ecto-1 Blaster"          ,WORLD_GHOSTBUSTERS },
/* 122 */ {"Ecto-1 Water Diver"      ,WORLD_GHOSTBUSTERS },

/* 123 */ {"Ghost Trap"              ,WORLD_GHOSTBUSTERS },
/* 124 */ {"Ghost Stun'n'Trap"       ,WORLD_GHOSTBUSTERS },
/* 125 */ {"Proton Zapper"           ,WORLD_GHOSTBUSTERS },

/* 126 */ {NTAG_UNKNOWN              ,NTAG_UNKNOWN },   /* asks for update */
/* 127 */ {NTAG_UNKNOWN              ,NTAG_UNKNOWN },
/* 128 */ {NTAG_UNKNOWN              ,NTAG_UNKNOWN },

/* 129 */ {NTAG_UNKNOWN              ,NTAG_UNKNOWN }, /* asks for update */
/* 130 */ {NTAG_UNKNOWN              ,NTAG_UNKNOWN },
/* 131 */ {NTAG_UNKNOWN              ,NTAG_UNKNOWN },

/* 132 */ {"Llyod's Golden Dragon"   ,WORLD_LEGO_NINJAGO },
/* 133 */ {"Llyod's Golden Dragon 1" ,WORLD_LEGO_NINJAGO },
/* 134 */ {"Llyod's Golden Dragon 2" ,WORLD_LEGO_NINJAGO },

/* 135 */ {NTAG_UNKNOWN              ,NTAG_UNKNOWN }, /* asks for update */
/* 136 */ {NTAG_UNKNOWN              ,NTAG_UNKNOWN },
/* 137 */ {NTAG_UNKNOWN              ,NTAG_UNKNOWN },

/* 138 */ {NTAG_UNKNOWN              ,NTAG_UNKNOWN }, /* asks for update */
/* 139 */ {NTAG_UNKNOWN              ,NTAG_UNKNOWN },
/* 140 */ {NTAG_UNKNOWN              ,NTAG_UNKNOWN },

/* 141 */ {NTAG_UNKNOWN              ,NTAG_UNKNOWN }, /* asks for update */
/* 142 */ {NTAG_UNKNOWN              ,NTAG_UNKNOWN },
/* 143 */ {NTAG_UNKNOWN              ,NTAG_UNKNOWN },

/* 144 */ {"Mega Flight Dragon"      ,WORLD_LEGO_NINJAGO },
/* 145 */ {"Mega Flight Dragon 1"    ,WORLD_LEGO_NINJAGO },
/* 146 */ {"Mega Flight Dragon 2"    ,WORLD_LEGO_NINJAGO },

/* 147 */ {NTAG_UNKNOWN              ,NTAG_UNKNOWN }, /* asks for update */
/* 148 */ {NTAG_UNKNOWN              ,NTAG_UNKNOWN },
/* 149 */ {NTAG_UNKNOWN              ,NTAG_UNKNOWN },

/* 150 */ {NTAG_UNKNOWN              ,NTAG_UNKNOWN }, /* asks for update */
/* 151 */ {NTAG_UNKNOWN              ,NTAG_UNKNOWN },
/* 152 */ {NTAG_UNKNOWN              ,NTAG_UNKNOWN },

/* 153 */ {NTAG_UNKNOWN              ,NTAG_UNKNOWN }, /* asks for update */
/* 154 */ {NTAG_UNKNOWN              ,NTAG_UNKNOWN },

/* 155 */ {"Flying White Dragon"     ,WORLD_LEGO_NINJAGO },
/* 156 */ {"Golden Fire Dragon"      ,WORLD_LEGO_NINJAGO },
/* 157 */ {"Ultra Destruction Dragon",WORLD_LEGO_NINJAGO },

/* 158 */ {"Arcade Machine"          ,WORLD_MIDWAY_ARCADE },
/* 159 */ {"8-bit Shooter"           ,WORLD_MIDWAY_ARCADE },
/* 160 */ {"The Pixelator"           ,WORLD_MIDWAY_ARCADE },

/* 161 */ {"G-61555 Spy Hunter"      ,WORLD_MIDWAY_ARCADE },
/* 162 */ {"The Interdiver"          ,WORLD_MIDWAY_ARCADE },
/* 163 */ {"Aerial Spyhunter"        ,WORLD_MIDWAY_ARCADE },

/* 164 */ {"Slime Shooter"           ,WORLD_GHOSTBUSTERS },
/* 165 */ {"Slime Exploder"          ,WORLD_GHOSTBUSTERS },
/* 166 */ {"Slime Streamer"          ,WORLD_GHOSTBUSTERS },

/* 167 */ {"Terror Dog"              ,WORLD_GHOSTBUSTERS },
/* 168 */ {"Terror Dog Destroyer"    ,WORLD_GHOSTBUSTERS },
/* 169 */ {"Soaring Terror Dog"      ,WORLD_GHOSTBUSTERS },

/* 170 */ {"Tandem War Elefant"      ,WORLD_ADVENTURE_TIME},
/* 171 */ {"Cosmic Squid"            ,WORLD_ADVENTURE_TIME},
/* 172 */ {"Psychic Submarine"       ,WORLD_ADVENTURE_TIME},

/* 173 */ {"BMO"                     ,WORLD_ADVENTURE_TIME},
/* 174 */ {"DOGMO"                   ,WORLD_ADVENTURE_TIME},
/* 175 */ {"SNAKEMO"                 ,WORLD_ADVENTURE_TIME},

/* 176 */ {"Jakemobile"              ,WORLD_ADVENTURE_TIME}, /* belongs to Finn */
/* 177 */ {"Snail Dude Jake"         ,WORLD_ADVENTURE_TIME},
/* 178 */ {"Hover Jake"              ,WORLD_ADVENTURE_TIME},

/* 179 */ {"Lumpy Car"               ,WORLD_ADVENTURE_TIME},
/* 180 */ {"Lumpy Land Whale"        ,WORLD_ADVENTURE_TIME},
/* 181 */ {"Lumpy Truck"             ,WORLD_ADVENTURE_TIME},

/* 182 */ {"Lunatic Amp"             ,WORLD_ADVENTURE_TIME}, /* verified */
/* 183 */ {"Shadow Scorpion"         ,WORLD_ADVENTURE_TIME},
/* 184 */ {"Heavy Metal Monster"     ,WORLD_ADVENTURE_TIME},

/* 185 */ {"B.A.'s Van"              ,WORLD_A_TEAM},
/* 186 */ {"Fool Shmasher"           ,WORLD_A_TEAM},
/* 187 */ {"Pain Plane"              ,WORLD_A_TEAM},

/* 188 */ {"Phone Home"              ,WORLD_E_T},
/* 189 */ {"Mobile Uplink"           ,WORLD_E_T},
/* 190 */ {"Super-Charged Satellite" ,WORLD_E_T},

/* 191 */ {"Niffler"                 ,WORLD_FANTASTIC_BEASTS}, /* zu Newt Scamander */
/* 192 */ {"Sinister Scorpion"       ,WORLD_FANTASTIC_BEASTS},
/* 193 */ {"Vicious Vulture"         ,WORLD_FANTASTIC_BEASTS},

/* 194 */ {"Swooping Evil"           ,WORLD_FANTASTIC_BEASTS},
/* 195 */ {"Brutal Bloom"            ,WORLD_FANTASTIC_BEASTS},
/* 196 */ {"Crawling Creeper"        ,WORLD_FANTASTIC_BEASTS},

/* 197 */ {"Ecto-1 (2016)"           ,WORLD_GHOSTBUSTER_2016},
/* 198 */ {"Ectozer"                 ,WORLD_GHOSTBUSTER_2016},
/* 199 */ {"PerfEcto"                ,WORLD_GHOSTBUSTER_2016},

/* 200 */ {"Flash 'n' Finish"        ,WORLD_GREMLINS},
/* 201 */ {"Rampage Record Player"   ,WORLD_GREMLINS},
/* 202 */ {"Stripe's Throne"         ,WORLD_GREMLINS},

/* 203 */ {"R.C. Car"                ,WORLD_GREMLINS},
/* 204 */ {"Gadget-o-matic"          ,WORLD_GREMLINS},
/* 205 */ {"Scarlet Scorpion"        ,WORLD_GREMLINS},

/* 206 */ {"Hogward Express"         ,WORLD_HARRY_POTTER},
/* 207 */ {"Steam Warrior"           ,WORLD_HARRY_POTTER},
/* 208 */ {"Soaring Steam Plane"     ,WORLD_HARRY_POTTER},

/* 209 */ {"Enchanted Car"           ,WORLD_HARRY_POTTER},
/* 210 */ {"Shark Sub"               ,WORLD_HARRY_POTTER},
/* 211 */ {"Monstrous Mouth"         ,WORLD_HARRY_POTTER},

/* 212 */ {"IMF Scrambler"           ,WORLD_MISSION_IMPOSSIBLE},
/* 213 */ {"Shock Cycle"             ,WORLD_MISSION_IMPOSSIBLE},
/* 214 */ {"IMF Covert Jet"          ,WORLD_MISSION_IMPOSSIBLE},

/* 215 */ {"IMF Sports Car"          ,WORLD_MISSION_IMPOSSIBLE},
/* 216 */ {"IMF Tank"                ,WORLD_MISSION_IMPOSSIBLE},
/* 217 */ {"IMF Splorer"             ,WORLD_MISSION_IMPOSSIBLE},

/* 218 */ {"Sonic Speedster"         ,WORLD_SONIC_THE_HEDGEHOG},
/* 219 */ {"Blue Typhoon"            ,WORLD_SONIC_THE_HEDGEHOG},
/* 220 */ {"Moto Bug"                ,WORLD_SONIC_THE_HEDGEHOG},

/* 221 */ {"The Tornado"             ,WORLD_SONIC_THE_HEDGEHOG},
/* 222 */ {"Crabmeat"                ,WORLD_SONIC_THE_HEDGEHOG},
/* 223 */ {"Eggcatcher"              ,WORLD_SONIC_THE_HEDGEHOG},

/* 224 */ {"K.I.T.T."                ,WORLD_KNIGHT_RIDER},
/* 225 */ {"Goliath Armored Semi"    ,WORLD_KNIGHT_RIDER},
/* 226 */ {"K.I.T.T. Jet"            ,WORLD_KNIGHT_RIDER},

/* 227 */ {NTAG_UNKNOWN              ,NTAG_UNKNOWN },
/* 228 */ {NTAG_UNKNOWN              ,NTAG_UNKNOWN },
/* 229 */ {NTAG_UNKNOWN              ,NTAG_UNKNOWN },

/* 230 */ {"Bionic Steed"            ,WORLD_LEGO_BATMAN_MOVIE},
/* 231 */ {"Bat Raptor"              ,WORLD_LEGO_BATMAN_MOVIE},
/* 232 */ {"Ultrabat"                ,WORLD_LEGO_BATMAN_MOVIE},

/* 233 */ {"Batwing"                 ,WORLD_LEGO_BATMAN_MOVIE},
/* 234 */ {"The Black Thunder"       ,WORLD_LEGO_BATMAN_MOVIE},
/* 235 */ {"Bat-Tank"                ,WORLD_LEGO_BATMAN_MOVIE},

/* 236 */ {"Skeleton Orga"           ,WORLD_THE_GOONIES},
/* 237 */ {"Skeleton Jukebox"        ,WORLD_THE_GOONIES},
/* 238 */ {"Skele-Turkey"            ,WORLD_THE_GOONIES},

/* 239 */ {"One-Eyed Willy's Pirate Ship", WORLD_THE_GOONIES},
/* 240 */ {"Fanged Fortune"          ,WORLD_THE_GOONIES},
/* 241 */ {"Inferno Cannon"          ,WORLD_THE_GOONIES},

/* 242 */ {"Buckbeak"                ,WORLD_HARRY_POTTER},
/* 243 */ {"Giant Owl"               ,WORLD_HARRY_POTTER},
/* 244 */ {"Fierce Falcon"           ,WORLD_HARRY_POTTER},

/* 245 */ {"Saturn's Sandworm"       ,WORLD_BEETLEJUISE },
/* 246 */ {"Spooky Spider"           ,WORLD_BEETLEJUISE },
/* 247 */ {"Haunted Vacuum"          ,WORLD_BEETLEJUISE },

/* 248 */ {"PPG Smartphone"          ,WORLD_POWERPUFF_GIRLS },
/* 249 */ {"PPG Hotline"             ,WORLD_POWERPUFF_GIRLS },
/* 250 */ {"Powerpuff Mag-Net"       ,WORLD_POWERPUFF_GIRLS },

/* 251 */ {"Ka-Pow Cannon"           ,WORLD_POWERPUFF_GIRLS },
/* 252 */ {"Slammin' Guitar"         ,WORLD_POWERPUFF_GIRLS },
/* 253 */ {"Megablast-Bot"           ,WORLD_POWERPUFF_GIRLS },

/* 254 */ {"Octi"                    ,WORLD_POWERPUFF_GIRLS },
/* 255 */ {"Super SKunk"             ,WORLD_POWERPUFF_GIRLS },
/* 256 */ {"Sonic Squid"             ,WORLD_POWERPUFF_GIRLS },

/* 257 */ {"T-Car"                   ,WORLD_TEEN_TITANS_GO },
/* 258 */ {"T-Forklift"              ,WORLD_TEEN_TITANS_GO },
/* 259 */ {"T-Plane"                 ,WORLD_TEEN_TITANS_GO },

/* 260 */ {"Spellbook of Azarath"    ,WORLD_TEEN_TITANS_GO },
/* 261 */ {"Raven Wings"             ,WORLD_TEEN_TITANS_GO },
/* 262 */ {"Giant Hand"              ,WORLD_TEEN_TITANS_GO },

/* 263 */ {"Titan Robot"             ,WORLD_TEEN_TITANS_GO},
/* 264 */ {"T-Rocket"                ,WORLD_TEEN_TITANS_GO},
/* 265 */ {"Robot Retriever"         ,WORLD_TEEN_TITANS_GO},

  { NULL }                          /* terminate list */
};

void
ld_print_vehicles(){
    guint vid;
    for (vid = 1; ld_vehicles[vid].name; vid++){
        const ntag_t *chr;
        chr = ld_vehicles+vid;
        g_print("v%03d: %s: %s\n", vid, chr->name, chr->world);
    }
} /* ld_print_vehicles */


void
ld_print_vehicle_by_id(guint vid_){
    const ntag_t *ntag;
    if (vid_ == -1000){
        g_print("vxxx: Tag is prepared for Lego Dimension vehicle/gadget usage.\n");
        return;
    }

    ntag = ld_get_vehicle_by_id(vid_, NULL);
    if(ntag){
        g_print("v%03d: %s: %s\n", vid_, ntag->name, ntag->world);
    } else {
        g_print("%s(vid_:%03d): invalid character id", __func__, vid_);
    }
} /* ld_print_vehicle_by_id */


const ntag_t *
ld_get_vehicle_by_id(guint vid_, GError **error_){

    const ntag_t *result = &ld_unknown_ntag;
    /* Out of Range */
    if (!LD_VID_VALID(vid_)) {
        g_set_error(error_, G_OPTION_ERROR, 9, "Vehicle id(%d) is out of range ("
                    G_STRINGIFY(LD_MIN_CID)".."G_STRINGIFY(LD_MAX_CID)").\n", vid_);
        return NULL;
    }

    if( vid_<= LD_MAX_KNOWN_VID){
        result = ld_vehicles+vid_;
        if( ! result->name)
            g_critical("%s(vid_:%d) max_known_vid(%"G_GSIZE_FORMAT") ", __func__, vid_, LD_MAX_KNOWN_VID);
        g_assert_nonnull((result->name));
    }
    return result;

} /* ld_print_character_by_id */
