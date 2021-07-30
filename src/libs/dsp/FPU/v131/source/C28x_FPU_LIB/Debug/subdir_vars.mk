################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CFFT_f32_sincostable.c \
../RFFT_f32_sincostable.c \
../median_noreorder_SP_RV.c 

ASM_SRCS += \
../CFFT_f32.asm \
../CFFT_f32_mag.asm \
../CFFT_f32_phase.asm \
../CFFT_f32s_mag.asm \
../CFFT_f32u.asm \
../FIR_f32.asm \
../ICFFT_f32.asm \
../RFFT_adc_f32.asm \
../RFFT_adc_f32u.asm \
../RFFT_f32.asm \
../RFFT_f32_mag.asm \
../RFFT_f32_phase.asm \
../RFFT_f32s_mag.asm \
../RFFT_f32u.asm \
../abs_SP_CV.asm \
../abs_SP_CV_2.asm \
../add_SP_CSxCV.asm \
../add_SP_CVxCV.asm \
../iabs_SP_CV.asm \
../iabs_SP_CV_2.asm \
../maxidx_SP_RV_2.asm \
../mean_SP_CV_2.asm \
../memcpy_fast.asm \
../memset_fast.asm \
../mpy_SP_CSxCS.asm \
../mpy_SP_CVxCV.asm \
../mpy_SP_CVxCVC.asm \
../mpy_SP_RSxRV_2.asm \
../mpy_SP_RSxRVxRV_2.asm \
../mpy_SP_RVxCV.asm \
../mpy_SP_RVxRV_2.asm \
../rnd_SP_RS.asm \
../sub_SP_CSxCV.asm \
../sub_SP_CVxCV.asm 

ASM_DEPS += \
./CFFT_f32.pp \
./CFFT_f32_mag.pp \
./CFFT_f32_phase.pp \
./CFFT_f32s_mag.pp \
./CFFT_f32u.pp \
./FIR_f32.pp \
./ICFFT_f32.pp \
./RFFT_adc_f32.pp \
./RFFT_adc_f32u.pp \
./RFFT_f32.pp \
./RFFT_f32_mag.pp \
./RFFT_f32_phase.pp \
./RFFT_f32s_mag.pp \
./RFFT_f32u.pp \
./abs_SP_CV.pp \
./abs_SP_CV_2.pp \
./add_SP_CSxCV.pp \
./add_SP_CVxCV.pp \
./iabs_SP_CV.pp \
./iabs_SP_CV_2.pp \
./maxidx_SP_RV_2.pp \
./mean_SP_CV_2.pp \
./memcpy_fast.pp \
./memset_fast.pp \
./mpy_SP_CSxCS.pp \
./mpy_SP_CVxCV.pp \
./mpy_SP_CVxCVC.pp \
./mpy_SP_RSxRV_2.pp \
./mpy_SP_RSxRVxRV_2.pp \
./mpy_SP_RVxCV.pp \
./mpy_SP_RVxRV_2.pp \
./rnd_SP_RS.pp \
./sub_SP_CSxCV.pp \
./sub_SP_CVxCV.pp 

OBJS += \
./CFFT_f32.obj \
./CFFT_f32_mag.obj \
./CFFT_f32_phase.obj \
./CFFT_f32_sincostable.obj \
./CFFT_f32s_mag.obj \
./CFFT_f32u.obj \
./FIR_f32.obj \
./ICFFT_f32.obj \
./RFFT_adc_f32.obj \
./RFFT_adc_f32u.obj \
./RFFT_f32.obj \
./RFFT_f32_mag.obj \
./RFFT_f32_phase.obj \
./RFFT_f32_sincostable.obj \
./RFFT_f32s_mag.obj \
./RFFT_f32u.obj \
./abs_SP_CV.obj \
./abs_SP_CV_2.obj \
./add_SP_CSxCV.obj \
./add_SP_CVxCV.obj \
./iabs_SP_CV.obj \
./iabs_SP_CV_2.obj \
./maxidx_SP_RV_2.obj \
./mean_SP_CV_2.obj \
./median_SP_RV.obj \
./median_noreorder_SP_RV.obj \
./memcpy_fast.obj \
./memset_fast.obj \
./mpy_SP_CSxCS.obj \
./mpy_SP_CVxCV.obj \
./mpy_SP_CVxCVC.obj \
./mpy_SP_RSxRV_2.obj \
./mpy_SP_RSxRVxRV_2.obj \
./mpy_SP_RVxCV.obj \
./mpy_SP_RVxRV_2.obj \
./qsort_SP_RV.obj \
./rnd_SP_RS.obj \
./sub_SP_CSxCV.obj \
./sub_SP_CVxCV.obj 

C_DEPS += \
./CFFT_f32_sincostable.pp \
./RFFT_f32_sincostable.pp \
./median_SP_RV.pp \
./median_noreorder_SP_RV.pp \
./qsort_SP_RV.pp 

OBJS__QTD += \
".\CFFT_f32.obj" \
".\CFFT_f32_mag.obj" \
".\CFFT_f32_phase.obj" \
".\CFFT_f32_sincostable.obj" \
".\CFFT_f32s_mag.obj" \
".\CFFT_f32u.obj" \
".\FIR_f32.obj" \
".\ICFFT_f32.obj" \
".\RFFT_adc_f32.obj" \
".\RFFT_adc_f32u.obj" \
".\RFFT_f32.obj" \
".\RFFT_f32_mag.obj" \
".\RFFT_f32_phase.obj" \
".\RFFT_f32_sincostable.obj" \
".\RFFT_f32s_mag.obj" \
".\RFFT_f32u.obj" \
".\abs_SP_CV.obj" \
".\abs_SP_CV_2.obj" \
".\add_SP_CSxCV.obj" \
".\add_SP_CVxCV.obj" \
".\iabs_SP_CV.obj" \
".\iabs_SP_CV_2.obj" \
".\maxidx_SP_RV_2.obj" \
".\mean_SP_CV_2.obj" \
".\median_SP_RV.obj" \
".\median_noreorder_SP_RV.obj" \
".\memcpy_fast.obj" \
".\memset_fast.obj" \
".\mpy_SP_CSxCS.obj" \
".\mpy_SP_CVxCV.obj" \
".\mpy_SP_CVxCVC.obj" \
".\mpy_SP_RSxRV_2.obj" \
".\mpy_SP_RSxRVxRV_2.obj" \
".\mpy_SP_RVxCV.obj" \
".\mpy_SP_RVxRV_2.obj" \
".\qsort_SP_RV.obj" \
".\rnd_SP_RS.obj" \
".\sub_SP_CSxCV.obj" \
".\sub_SP_CVxCV.obj" 

ASM_DEPS__QTD += \
".\CFFT_f32.pp" \
".\CFFT_f32_mag.pp" \
".\CFFT_f32_phase.pp" \
".\CFFT_f32s_mag.pp" \
".\CFFT_f32u.pp" \
".\FIR_f32.pp" \
".\ICFFT_f32.pp" \
".\RFFT_adc_f32.pp" \
".\RFFT_adc_f32u.pp" \
".\RFFT_f32.pp" \
".\RFFT_f32_mag.pp" \
".\RFFT_f32_phase.pp" \
".\RFFT_f32s_mag.pp" \
".\RFFT_f32u.pp" \
".\abs_SP_CV.pp" \
".\abs_SP_CV_2.pp" \
".\add_SP_CSxCV.pp" \
".\add_SP_CVxCV.pp" \
".\iabs_SP_CV.pp" \
".\iabs_SP_CV_2.pp" \
".\maxidx_SP_RV_2.pp" \
".\mean_SP_CV_2.pp" \
".\memcpy_fast.pp" \
".\memset_fast.pp" \
".\mpy_SP_CSxCS.pp" \
".\mpy_SP_CVxCV.pp" \
".\mpy_SP_CVxCVC.pp" \
".\mpy_SP_RSxRV_2.pp" \
".\mpy_SP_RSxRVxRV_2.pp" \
".\mpy_SP_RVxCV.pp" \
".\mpy_SP_RVxRV_2.pp" \
".\rnd_SP_RS.pp" \
".\sub_SP_CSxCV.pp" \
".\sub_SP_CVxCV.pp" 

C_DEPS__QTD += \
".\CFFT_f32_sincostable.pp" \
".\RFFT_f32_sincostable.pp" \
".\median_SP_RV.pp" \
".\median_noreorder_SP_RV.pp" \
".\qsort_SP_RV.pp" 

ASM_SRCS_QUOTED += \
"../CFFT_f32.asm" \
"../CFFT_f32_mag.asm" \
"../CFFT_f32_phase.asm" \
"../CFFT_f32s_mag.asm" \
"../CFFT_f32u.asm" \
"../FIR_f32.asm" \
"../ICFFT_f32.asm" \
"../RFFT_adc_f32.asm" \
"../RFFT_adc_f32u.asm" \
"../RFFT_f32.asm" \
"../RFFT_f32_mag.asm" \
"../RFFT_f32_phase.asm" \
"../RFFT_f32s_mag.asm" \
"../RFFT_f32u.asm" \
"../abs_SP_CV.asm" \
"../abs_SP_CV_2.asm" \
"../add_SP_CSxCV.asm" \
"../add_SP_CVxCV.asm" \
"../iabs_SP_CV.asm" \
"../iabs_SP_CV_2.asm" \
"../maxidx_SP_RV_2.asm" \
"../mean_SP_CV_2.asm" \
"../memcpy_fast.asm" \
"../memset_fast.asm" \
"../mpy_SP_CSxCS.asm" \
"../mpy_SP_CVxCV.asm" \
"../mpy_SP_CVxCVC.asm" \
"../mpy_SP_RSxRV_2.asm" \
"../mpy_SP_RSxRVxRV_2.asm" \
"../mpy_SP_RVxCV.asm" \
"../mpy_SP_RVxRV_2.asm" \
"../rnd_SP_RS.asm" \
"../sub_SP_CSxCV.asm" \
"../sub_SP_CVxCV.asm" 

C_SRCS_QUOTED += \
"../CFFT_f32_sincostable.c" \
"../RFFT_f32_sincostable.c" \
"../median_noreorder_SP_RV.c" 


