TARGET := dcdc_controller
BUILD_DIR := build

CC := arm-none-eabi-gcc
OBJCOPY := arm-none-eabi-objcopy
SIZE := arm-none-eabi-size

CFLAGS := \
-mcpu=cortex-m4 \
-mthumb \
-ffunction-sections \
-fdata-sections \
-fno-common \
-std=c11 \
-Wall \
-Wextra \
-Werror=implicit-function-declaration \
-Iinclude

LDFLAGS := \
-T linker/tm4c123g.ld \
-nostartfiles \
-specs=nosys.specs \
-Wl,--gc-sections

SOURCES := \
src/main.c \
src/system.c \
src/pwm.c \
src/adc.c \
src/control_loop.c \
src/startup_gcc.c

OBJECTS := $(SOURCES:src/%.c=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR)/$(TARGET).bin

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@
	$(SIZE) $@

$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -rf $(BUILD_DIR)

flash: $(BUILD_DIR)/$(TARGET).bin
	openocd -f board/ek-tm4c123gxl.cfg -c "program $< verify reset exit"

.PHONY: all clean flash
