TMS320x2834x BOOT ROM Source

This download includes the source of the boot ROM contents
on TMS320x2834x Delfino devices. 

For each version of the boot ROM there is one .zip file
included where the version of the release is reflected
in the name of the .zip file.  The boot ROM version
on a particular device is stored in memory location
0x3FFFBA in the boot ROM.

The .zip contains all source including the project file, 
header files and the .out file used to generate the boot
ROM contents. 

=============================================
IMPORTANT NOTE: 

The boot ROM projects are CCSv3.3 projects. To open in CCSv4,
click on Project -> Import Legacy CCSv3.3 Project

NOTE: The boot to XINTF x32 mode mentioned in the code
      does not properly configure the XD lines.  Thus
      the mode has been removed from the documentation.
      This does not affect XINTF operation in x32 mode
      when configured by the user.  It only affects the
      boot mode.
      At this time there are no plans to fix this boot mode.

=============================================