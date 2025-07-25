######################################
# target
######################################
TARGET = ch582_ble
# ../../


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization for size
OPT = -Os


#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

NEWLIB?=/usr/include/newlib #debian

######################################
# source
######################################
# C sources
C_SOURCES = \
src/peripheral_main.c \
src/peripheral.c \
src/app_uart.c \
src/ble_uart_service/ble_uart_service_16bit.c \
src/app_drv_fifo/app_drv_fifo.c \
Profile/devinfoservice.c \
Profile/gattprofile.c \
../../ble-lib/HAL/KEY.c \
../../ble-lib/HAL/LED.c \
../../ble-lib/HAL/MCU.c \
../../ble-lib/HAL/RTC.c \
../../ble-lib/HAL/SLEEP.c \
../../vendor/StdPeriphDriver/CH58x_timer1.c \
../../vendor/StdPeriphDriver/CH58x_adc.c \
../../vendor/StdPeriphDriver/CH58x_flash.c \
../../vendor/StdPeriphDriver/CH58x_usb2hostBase.c \
../../vendor/StdPeriphDriver/CH58x_uart2.c \
../../vendor/StdPeriphDriver/CH58x_spi1.c \
../../vendor/StdPeriphDriver/CH58x_usbhostBase.c \
../../vendor/StdPeriphDriver/CH58x_timer3.c \
../../vendor/StdPeriphDriver/CH58x_usbhostClass.c \
../../vendor/StdPeriphDriver/CH58x_timer2.c \
../../vendor/StdPeriphDriver/CH58x_uart1.c \
../../vendor/StdPeriphDriver/CH58x_clk.c \
../../vendor/StdPeriphDriver/CH58x_gpio.c \
../../vendor/StdPeriphDriver/CH58x_usb2hostClass.c \
../../vendor/StdPeriphDriver/CH58x_pwr.c \
../../vendor/StdPeriphDriver/CH58x_timer0.c \
../../vendor/StdPeriphDriver/CH58x_pwm.c \
../../vendor/StdPeriphDriver/CH58x_uart0.c \
../../vendor/StdPeriphDriver/CH58x_spi0.c \
../../vendor/StdPeriphDriver/CH58x_i2c.c \
../../vendor/StdPeriphDriver/CH58x_usbdev.c \
../../vendor/StdPeriphDriver/CH58x_usb2dev.c \
../../vendor/StdPeriphDriver/CH58x_uart3.c \
../../vendor/StdPeriphDriver/CH58x_sys.c \
../../vendor/RVMSIS/core_riscv.c \


# ASM sources
ASM_SOURCES =  \
../../vendor/Startup/startup_CH583.S

#######################################
# binaries
#######################################
#PREFIX = riscv-none-elf-
PREFIX = riscv64-elf-
#debian
#PREFIX = riscv64-unknown-elf-
PREFIX = riscv-wch-elf-

CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size

HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

#######################################
# CFLAGS
#######################################
# cpu
CPU = -march=rv32imac_zicsr -mabi=ilp32 -msmall-data-limit=8 

# For gcc version less than v12
# CPU = -march=rv32imac -mabi=ilp32 -msmall-data-limit=8

# fpu
FPU = 

# float-abi
FLOAT-ABI =

# mcu
MCU = $(CPU) $(FPU) $(FLOAT-ABI)

# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
-I$(NEWLIB) \
-I../../vendor/StdPeriphDriver/inc \
-I../../vendor/RVMSIS \
-I../../vendor/Core \
-I../../ble-lib/HAL/include \
-I../../ble-lib/LIB \
-IProfile/include \
-Isrc/app_drv_fifo \
-Isrc/ble_uart_service \
-Isrc/include

# compile gcc flags
ASFLAGS = $(MCU) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = ../../vendor/Ld/Link.ld 

# libraries
LIBS = -lc -lm -lnosys ../../vendor/StdPeriphDriver/libISP583.a ../../ble-lib/LIB/LIBCH58xBLE.a
LIBDIR = 
LDFLAGS = $(MCU) -mno-save-restore -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -T $(LDSCRIPT) -nostartfiles -Xlinker --gc-sections -Wl,-Map=$(BUILD_DIR)/$(TARGET).map --specs=nano.specs $(LIBS)

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.S=.o)))
vpath %.S $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.S Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@
#$(LUAOBJECTS) $(OBJECTS)
$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# Program
#######################################
program: $(BUILD_DIR)/$(TARGET).elf
	sudo wch-openocd -f ./wch-riscv.cfg -c 'init; halt; program $(BUILD_DIR)/$(TARGET).elf; reset; wlink_reset_resume; exit;'

isp: $(BUILD_DIR)/$(TARGET).bin
	wchisp flash $(BUILD_DIR)/$(TARGET).bin

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***

