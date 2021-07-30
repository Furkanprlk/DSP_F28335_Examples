SFO Library ReadMe
=============

For information on SFO_TI_Build.lib and SFO_TI_Build_V5.lib including usage tips,
constraints, and differences between the two versions, refer to the
HRPWM Reference Guide (lit. number: spru924) on the TI website. 	

* The above versions of the SFO library support only the following HRPWM configuration:
	HRCNFG[HRLOAD]=0 (load on CTR=ZRO)
	HRCNFG[EDGMODE]=10(falling edge MEP control)

Upgrades  
======
11/2007 - SFO_TI_Build_V5.lib/SFO_TI_Build_V5_fpu.lib - SFO_TI_Build_V5B.lib/SFO_TI_Build_V5B_fpu.lib upgrades the SFO_MepEn_V5(n) function 
	 to support all HRPWM configurations.  

Floating-Point vs Fixed Point
==================

The F2833x header files are packaged with both the floating point and the fixed point-
compiled versions of the SFO libraries. The fixed and floating point versions are identical
with the exception that one version is compiled for floating point (fpu version), and
the other is compiled for fixed-point.  See below:

Fixed point                   Floating point
-------------------          ------------------------
SFO_TI_Build.lib           SFO_TI_Build_fpu.lib 
SFO_TI_Build_V5.lib      SFO_TI_Build_V5_fpu.lib

* If your project is compiled for floating-point (fpu32 option), then the included library must
   also be compiled for floating-point. Likewise, if it is compiled for fixed-point,  the included
   library must also be compiled for fixed-point.
* If your project was previously configured for fixed-point and you want to convert it to
   floating-point or vice-versa, follow the steps below:

- To switch your HRPWM SFO project from fixed-point to floating point:
1. Remove the fixed-point library from your project.
2. Add the floating-point library to your project.
3. In Code Composer Studio V3.3+ (with CodeGenTools V5.x), go to Project->Build Options.
4. In the Compiler tab window, click on the "Advanced" category. 
    At "Floating point support:", select "fpu32" from the pull-down menu
    OR type: -v28 --float_support=fpu32 in the text window at the top (-v28 may already be in the text window).
5. Select the "Linker" tab in the "Build Options" window.
6. If using the rts2800 library - Click on the "Libraries" category. 
    In the "Incl. Libraries" textbox, type in the fpu32 version of the rts library
    as follows: rts2800_fpu32.lib
7. Click "OK" and build/compile your project.  You now have a floating-point project.

- To switch your HRPWM SFO project from floating-point to fixed-point:
1. Remove the floating-point library from your project.
2. Add the fixed-point library to your project.
3. In Code Composer Studio 3.3+ (with CodeGenTools V5.x), go to Project->Build Options.
4. In the Compiler tab window, click on the "Advanced" category. 
    At "Floating point support:", select "None" from the pull-down menu
    OR delete: --float_support=fpu32 in the text window at the top.
5. Select the "Linker" tab in the "Build Options" window.
6. If using the rts2800_fpu32 library - Click on the "Libraries" category. 
    In the "Incl. Libraries" textbox, type in the non-fpu32 version of the rts library
    as follows: rts2800_ml.lib or rts2800.lib
7. Click "OK" and build/compile your project.  You now have a fixed-point project.