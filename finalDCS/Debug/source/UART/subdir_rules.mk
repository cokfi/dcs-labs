################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
source/UART/bspUART.obj: ../source/UART/bspUART.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"E:/Programs/CCS/ccsv7/tools/compiler/ti-cgt-msp430_16.9.6.LTS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="E:/Programs/CCS/ccsv7/ccs_base/msp430/include" --define=__MSP430G2553__ --printf_support=minimal --preproc_with_compile --preproc_dependency="source/UART/bspUART.d_raw" --obj_directory="source/UART" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/UART/halUART.obj: ../source/UART/halUART.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"E:/Programs/CCS/ccsv7/tools/compiler/ti-cgt-msp430_16.9.6.LTS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="E:/Programs/CCS/ccsv7/ccs_base/msp430/include" --define=__MSP430G2553__ --printf_support=minimal --preproc_with_compile --preproc_dependency="source/UART/halUART.d_raw" --obj_directory="source/UART" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


