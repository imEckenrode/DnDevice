# Code Layout

Code is broken up into sending and receiving code, plus the initialization

To register a receiving function for a particular ID, modify dndv_rcv's function pointer array to add in the address 

Note: dndv_rcv does not include any functions it calls to prevent a loop using forward declaration