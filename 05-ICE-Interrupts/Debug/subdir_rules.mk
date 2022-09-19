################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
ece353.obj: I:/ece353/ece353.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ProgramData/App-V/883E8076-D99D-4911-93C4-940332A6BE1F/BFE39798-EFFD-4CAF-929B-E5A85FC35347/Root/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ProgramData/App-V/883E8076-D99D-4911-93C4-940332A6BE1F/BFE39798-EFFD-4CAF-929B-E5A85FC35347/Root/ccs/ccs_base/arm/include" --include_path="C:/ProgramData/App-V/883E8076-D99D-4911-93C4-940332A6BE1F/BFE39798-EFFD-4CAF-929B-E5A85FC35347/Root/ccs/ccs_base/arm/include/CMSIS" --include_path="I:/ece353/05-ICE-Interrupts" --include_path="I:/ece353" --include_path="C:/ProgramData/App-V/883E8076-D99D-4911-93C4-940332A6BE1F/BFE39798-EFFD-4CAF-929B-E5A85FC35347/Root/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ProgramData/App-V/883E8076-D99D-4911-93C4-940332A6BE1F/BFE39798-EFFD-4CAF-929B-E5A85FC35347/Root/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ProgramData/App-V/883E8076-D99D-4911-93C4-940332A6BE1F/BFE39798-EFFD-4CAF-929B-E5A85FC35347/Root/ccs/ccs_base/arm/include" --include_path="C:/ProgramData/App-V/883E8076-D99D-4911-93C4-940332A6BE1F/BFE39798-EFFD-4CAF-929B-E5A85FC35347/Root/ccs/ccs_base/arm/include/CMSIS" --include_path="I:/ece353/05-ICE-Interrupts" --include_path="I:/ece353" --include_path="C:/ProgramData/App-V/883E8076-D99D-4911-93C4-940332A6BE1F/BFE39798-EFFD-4CAF-929B-E5A85FC35347/Root/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


