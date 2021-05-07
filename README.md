# DSP F28335 Examples
Document explaining process of programming TI F28335 using Simulink models and Code Composer Studio v10.3

## 🛠Requirements

### Hardware Requirements
* [TMDSCNCD28335](https://www.ti.com/tool/TMDSCNCD28335)
* [TMDSDOCK28335](https://www.ti.com/tool/TMDSDOCK28335)

### Software Requirements
* MATLAB2020b
* [CCSTUDIO](https://www.ti.com/tool/CCSTUDIO)

## 🧾Configuration
Steps to create Simulink model which can be used to generate DSP program are simple.


### MATLAB
* Create a new Simulink Model
* Drop new Simulink Coder/Target Preferences block on the model. In Initializa Configuration Parameters select:
  * IDE/Tool Chain: Texas Instruments Code Composer Studio
  * Board: SD F28355 Do you want to update the model's Configuration Parameters to correspond to your selections: Yes
* When in your model window, open Tools/Code Generation/Options... dialog. In Code Generation/IDE Link select appropriate Build action:
  * Build - if you just want to generate and compile code, or
  * Build_and_execute - if you want to generate code, compile it and then automatically run on the DSP

Now it should be possible to execute Tools/Code Generation/Build Model action (Ctrl+B) (program doesn't do anything useful at this point, though).


### CCS
