################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
source/Utilities/Conversions.obj: ../source/Utilities/Conversions.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"E:/Programs/CCS/ccsv7/tools/compiler/ti-cgt-msp430_16.9.6.LTS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="E:/Programs/CCS/ccsv7/ccs_base/msp430/include" --define=__MSP430G2553__ --printf_support=minimal --preproc_with_compile --preproc_dependency="source/Utilities/Conversions.d_raw" --obj_directory="source/Utilities" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


