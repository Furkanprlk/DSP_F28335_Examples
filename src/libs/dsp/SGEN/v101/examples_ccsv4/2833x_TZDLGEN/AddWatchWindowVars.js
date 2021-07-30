//Add watch window variables
expRemoveAll
expAdd "tgen.prescalar" getQValue(0) 
expAdd "tgen.freq" getQValue(15)    
expAdd "tgen.step_max" getQValue(0) 
expAdd "tgen.task" getNatural()
expAdd "tgen.alpha" getQValue(16)        
expAdd "tgen.gain" getQValue(15)      
expAdd "tgen.offset" getQValue(15)                    
expAdd "tgen.out" getQValue(15) 
openAnalysisView('Single Time','C:/TI/controlSUITE/libs/dsp/SGEN/v101/examples_ccsv4/2833x_TZDLGEN/tzdlgen.graphProp')
