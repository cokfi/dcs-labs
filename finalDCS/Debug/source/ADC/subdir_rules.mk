################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
source/ADC/bspADC.obj: ../source/ADC/bspADC.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"E:/Programs/CCS/ccsv7/tools/compiler/ti-cgt-msp430_16.9.6.LTS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="E:/Programs/CCS/ccsv7/ccs_base/msp430/include" --define=__MSP430G2553__ --printf_support=minimal --preproc_with_compile --preproc_dependency="source/ADC/bspADC.d_raw" --obj_directory="source/ADC" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/ADC/halADC.obj: ../source/ADC/halADC.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"E:/Programs/CCS/ccsv7/tools/compiler/ti-cgt-msp430_16.9.6.LTS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="E:/Programs/CCS/ccsv7/ccs_base/msp430/include" --define=__MSP430G2553__ --printf_support=minimal --preproc_with_compile --preproc_dependency="source/ADC/halADC.d_raw" --obj_directory="source/ADC" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


