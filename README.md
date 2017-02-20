# ldnfctags
Lego Dimensions - NFC Tag Tool

This tiny tool can read, identify and work with NFC Tags for the Lego Dimensions game. A catalog of characters and devices is included but it does not understand Upgrades of latter ones.

It uses [libnfc](http://nfc-tools.org ) to access the NFC hardware. Therefore it should work with all devices supported by libnfc. Nevertheless it was developed and tested with a PN532 based [board](https://www.itead.cc/wiki/ITEAD_PN532_NFC_MODULE) in UART mode produced by itead Studio.


## Credits
Thanks to [ags131](http://github.com/ags131/node-ld), [socram8888](http://github.com/socram8888/ulread) and [bettse](http://github.com/bettse) for publishing their code and discussing their findings. :+1:

This helped me to understand the crypto algorithm and the [Mifare Ultralight NFC tags](https://en.wikipedia.org/wiki/MIFARE).

## Fast Track
```
  git clone https://github.com/phogar/ldnfctags.git
  cd ldnfctags
  ./cmake-debug-makefiles.sh
  cd build
  make
  ./src/ldcli --help-all
```

## Building with details
### Dependencies

 Tools used to build the binaries:

 * sh
 * C and C++ compiler
 * cmake

Dependencies of the source code:

 * libnfc v1.7.1
 * glib2 v2.40

And additional libraries for the Graphical User Interface:

 * gtk+3  v3.10
 * gtkmm3 v3.4

## compile
Run ./cmake-debug-makefile.sh and let cmake check the dependencies and create a Makefile in the subdirectory build.
Change to *build* and run *make*.
 
## Configuration
libnfc must be configured to find the NFC tag reader.
Configuration examples can be found in [etc/nfc](etc/nfc).
## Usage
The most complete tool in this repository is **ldcli**.
It can be found in **build/src/**.
Call 
```
ldcli --help-all
```
to get this complete usage message.

```
Usage:
  ldcli [OPTION...] - Lego Dimensions cli

ldcli works on Near Field Communication Tags for the Lego Dimensions game.
It can read, write tags and list brief information about known characters.
Read and write operations depend on a preconfigured libnfc installation.

Help Options:
  -h, --help              Show help options
  --help-all              Show all help options
  --help-command          Show command options

Command Options :
  -l, --list              List known characters.
  -r, --read              Read NFC tag and dump information.
  -c, --character=CID     Write character with id CID to NFC tag. [1<CID<99]
  -i, --initialize        Initialize NFC tag for vehicle/gadget usage. Lego Dimensions USB pad will accept the tag as an empty tag.
  -v, --vehicle=VID       Write vehicle with id VID to NFC tag. [0<=VID<1000]

Application Options:
  -w, --write             Per default writing to a NFC tag is disable. Use this flag to enable.

Before using this tool you'll have to configure libnfc.
```



