################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./aes.obj" \
"./s_aes_sw.obj" \
"./driverlib/adc12_b.obj" \
"./driverlib/aes256.obj" \
"./driverlib/comp_e.obj" \
"./driverlib/crc.obj" \
"./driverlib/crc32.obj" \
"./driverlib/cs.obj" \
"./driverlib/dma.obj" \
"./driverlib/esi.obj" \
"./driverlib/eusci_a_spi.obj" \
"./driverlib/eusci_a_uart.obj" \
"./driverlib/eusci_b_i2c.obj" \
"./driverlib/eusci_b_spi.obj" \
"./driverlib/framctl.obj" \
"./driverlib/framctl_a.obj" \
"./driverlib/gpio.obj" \
"./driverlib/hspll.obj" \
"./driverlib/lcd_c.obj" \
"./driverlib/mpu.obj" \
"./driverlib/mpy32.obj" \
"./driverlib/mtif.obj" \
"./driverlib/pmm.obj" \
"./driverlib/ram.obj" \
"./driverlib/ref_a.obj" \
"./driverlib/rtc_b.obj" \
"./driverlib/rtc_c.obj" \
"./driverlib/saph.obj" \
"./driverlib/saph_a.obj" \
"./driverlib/sdhs.obj" \
"./driverlib/sfr.obj" \
"./driverlib/sysctl.obj" \
"./driverlib/timer_a.obj" \
"./driverlib/timer_b.obj" \
"./driverlib/tlv.obj" \
"./driverlib/uups.obj" \
"./driverlib/wdt_a.obj" \
"../lnk_msp430fr5994.cmd" \
$(GEN_CMDS__FLAG) \
-llibmpu_init.a \
-llibmath.a \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include driverlib/subdir_vars.mk
-include subdir_rules.mk
-include driverlib/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
s_aes_sw.out \

EXE_OUTPUTS__QUOTED += \
"s_aes_sw.out" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "s_aes_sw.out"

# Tool invocations
s_aes_sw.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: MSP430 Linker'
	"C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --advice:power=all --advice:hw_config=all --define=__MSP430FR5994__ --define=_MPU_ENABLE -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 -z -m"s_aes_sw.map" --heap_size=160 --stack_size=160 --cinit_hold_wdt=on -i"C:/ti/ccs1220/ccs/ccs_base/msp430/include" -i"C:/ti/ccs1220/ccs/ccs_base/msp430/lib/5xx_6xx_FRxx" -i"C:/ti/ccs1220/ccs/ccs_base/msp430/lib/FR59xx" -i"C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/lib" -i"C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/include" --priority --reread_libs --define=_MPU_ENABLE --diag_wrap=off --display_error_number --warn_sections --xml_link_info="s_aes_sw_linkInfo.xml" --use_hw_mpy=F5 --rom_model -o "s_aes_sw.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "aes.obj" "s_aes_sw.obj" "driverlib\adc12_b.obj" "driverlib\aes256.obj" "driverlib\comp_e.obj" "driverlib\crc.obj" "driverlib\crc32.obj" "driverlib\cs.obj" "driverlib\dma.obj" "driverlib\esi.obj" "driverlib\eusci_a_spi.obj" "driverlib\eusci_a_uart.obj" "driverlib\eusci_b_i2c.obj" "driverlib\eusci_b_spi.obj" "driverlib\framctl.obj" "driverlib\framctl_a.obj" "driverlib\gpio.obj" "driverlib\hspll.obj" "driverlib\lcd_c.obj" "driverlib\mpu.obj" "driverlib\mpy32.obj" "driverlib\mtif.obj" "driverlib\pmm.obj" "driverlib\ram.obj" "driverlib\ref_a.obj" "driverlib\rtc_b.obj" "driverlib\rtc_c.obj" "driverlib\saph.obj" "driverlib\saph_a.obj" "driverlib\sdhs.obj" "driverlib\sfr.obj" "driverlib\sysctl.obj" "driverlib\timer_a.obj" "driverlib\timer_b.obj" "driverlib\tlv.obj" "driverlib\uups.obj" "driverlib\wdt_a.obj" 
	-$(RM) "aes.d" "s_aes_sw.d" "driverlib\adc12_b.d" "driverlib\aes256.d" "driverlib\comp_e.d" "driverlib\crc.d" "driverlib\crc32.d" "driverlib\cs.d" "driverlib\dma.d" "driverlib\esi.d" "driverlib\eusci_a_spi.d" "driverlib\eusci_a_uart.d" "driverlib\eusci_b_i2c.d" "driverlib\eusci_b_spi.d" "driverlib\framctl.d" "driverlib\framctl_a.d" "driverlib\gpio.d" "driverlib\hspll.d" "driverlib\lcd_c.d" "driverlib\mpu.d" "driverlib\mpy32.d" "driverlib\mtif.d" "driverlib\pmm.d" "driverlib\ram.d" "driverlib\ref_a.d" "driverlib\rtc_b.d" "driverlib\rtc_c.d" "driverlib\saph.d" "driverlib\saph_a.d" "driverlib\sdhs.d" "driverlib\sfr.d" "driverlib\sysctl.d" "driverlib\timer_a.d" "driverlib\timer_b.d" "driverlib\tlv.d" "driverlib\uups.d" "driverlib\wdt_a.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

