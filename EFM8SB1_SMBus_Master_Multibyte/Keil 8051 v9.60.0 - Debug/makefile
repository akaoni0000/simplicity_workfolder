################################################################################
# Automatically-generated file. Do not edit!
################################################################################

export WINEDEBUG=-all

# Keil tools exit code 1 is warnings only, so don't treat as an error in make
RC := test $$? -lt 2

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := EFM8SB1_SMBus_Master_Multibyte
BUILD_ARTIFACT_EXTENSION := omf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: main-build

# Main-build Target
main-build: EFM8SB1_SMBus_Master_Multibyte.omf

# Tool invocations
EFM8SB1_SMBus_Master_Multibyte.omf: echo_path $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: Keil 8051 Linker'
	LX51 "@EFM8SB1_SMBus_Master_Multibyte.lnp" || $(RC)
	@echo 'Finished building target: $@'

# Change from all upper case to the expected case
	@-mv "EFM8SB1_SMBUS_MASTER_MULTIBYTE.OMF.CRBUILD" "$@"

# Generate hex file: EFM8SB1_SMBus_Master_Multibyte.hex
	@Ohx51 "EFM8SB1_SMBus_Master_Multibyte.omf" "HEXFILE (EFM8SB1_SMBus_Master_Multibyte.hex)" "H386" 2>&1 >/dev/null

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS) EFM8SB1_SMBus_Master_Multibyte.omf
	-@echo ' '

.PHONY: all clean dependents main-build

-include ../makefile.targets
# echo the path
echo_path:
	@echo PATH=$$PATH
	@echo ' '

