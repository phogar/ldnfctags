# ldnfctags
Lego Dimensions - NFC tag handling

This tiny tool can read, identify and write NFC Tags for the Lego Dimensions game. A catalog of characters and devices is included but does not support upgrade of latter ones.

It uses [libnfc](http://nfc-tools.org ) to access the NFC hardware. Therefore it should work with all devices supported by libnfc. Nevertheless it was developed and tested with a NFC532 based [board](https://www.sunfounder.com/pn532-nfc-module-for-raspberry-pi.html) in UART mode produced by Sunfounder.

## Credits
Thanks to @ags131, @bettse and @socram8888 for publishing their code on github.com.
This helped me to understand the crypto algorithm and the Ultralight Device part.

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
 
## Usage
The most usable tool build by cmake is the command line interface
 ldcli

The binary can be found in build/src/.

ldcli --help-all

Prints complete usage message.

