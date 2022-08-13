# Code Layout

(For some reason, it is requiring me to add everything to the CMakeList...may try resetting that)

## dndv_internals

This is the lowest level of code on the dependency tree; everything can import this, while this does not import any custom code.

All the structures and global variables are (or will be) here, including player data and data access.

## dndv_comms

This is the code to send and receive data between other DnDevices.

The main sending functions relays information to other DnDevices (This could be moved to a lower library, but it'll be included either way)
All other sending functions take the inputs and convert them into the correct sending format.

The receiving code takes the data in, decodes it (with the ID), and calls the correct function.
This function then calls the forward declared functions defined in the other libraries (see Other Libraries)

## dnd

This code houses all DnD (5e) specific items not included in dndv_internals.
Initiative order, attacks, and turn management is all done in this file.

## init.c

This code is the highest level; all initialization is done from here

## Other Libraries

All the other libraries 

#### Rules for Other Libraries

To access globals, import dndv_internals
To send data, inclue dndv_comms
To receive data, register to the event loop (see dndv_comms.h)
And to initialize the code, import its .h file and call its method in init.c
