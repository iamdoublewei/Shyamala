################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
dsplib/source/vector/%.obj: ../dsplib/source/vector/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/bin/cl430" -vmspx --data_model=large --near_data=none --use_hw_mpy=F5 --include_path="C:/ti/ccs1220/ccs/ccs_base/msp430/include" --include_path="C:/Users/iamdo/workspace_v12/s_okg/dsplib/source" --include_path="C:/Users/iamdo/workspace_v12/s_okg/dsplib/include" --include_path="C:/Users/kisho/workspace_v9/FFT_benchmark/dsplib/include" --include_path="C:/Users/iamdo/workspace_v12/s_okg" --include_path="C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/include" --advice:power="all" --advice:hw_config="all" --define=__MSP430FR5994__ --define=MSP_DISABLE_LEA --define=_MPU_ENABLE -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="dsplib/source/vector/$(basename $(<F)).d_raw" --obj_directory="dsplib/source/vector" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

