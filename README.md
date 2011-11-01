# Description

These tools are made to keep X.org and important processes from being swapped out.

# How to install and use

## LD_PRELOAD library

 1. make
 2. LD_PRELOAD=/path/to/libangrymlocker.so /your/application
 
 There are some environment variables, which may be useful:
 
 * ANGRYMLOCKER_DEBUG=1 enables debug messages
 * ANGRYMLOCKER_RESETENV=1 enables unset() of all angrymlocker-related environment variables (including LD_PRELOAD), so childs of this process will be started without angrymlocker.

## X.Org module
 Previous method can't be used to mlockall() Xorg process, so i made a X.Org module for this purpose.

 1. make
 2. sudo make install
 3. Add 'Load "angrymlocker"' to 'Module' section in your xorg.conf.
 4. Restart X.
