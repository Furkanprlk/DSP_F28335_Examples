README.txt
==========

There is a minor bug in v1.00.00.00 of the sincos library which causes the maximum encoder count to be initialized to a fixed value of 8191.  This corresponds to a 2,048 pulses per revolution (PPR) encoder.  If an encoder with different PPR is used the angular measurement will be incorrect and the coarse result will "wrap around" on an incorrect terminal count.  To prevent this, the correct terminal count should be loaded into the sincos structure in the user's code AFTER the PM_sincos_initLib() function has been called.

The correct terminal count (x) is:  x = (PPR * 4) - 1

e.g. for a 2,500 PPR encoder, x = 9999.

The two structure elements which should be loaded with this value are:
mySincos.qmaxpos
mySincos.qep->QPOSMAX

This bug will be fixed in the next version of the library.