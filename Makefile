# Directories
BOOT_DIR = boot
KERNEL_DIR = kernel
DRIVERS_DIR = $(KERNEL_DIR)/drivers
ISO_DIR = iso
BUILD_DIR = build

# Output files
ISO_NAME = togekissos.iso
KERNEL_BIN = $(BUILD_DIR)/kernel.o
SCREEN_BIN = $(BUILD_DIR)/screen.o
LOADER_BIN = $(BUILD_DIR)/loader.o
KERNEL_ELF = $(BUILD_DIR)/kernel.elf

# Compiler and flags
AS = nasm
ASFLAGS = -f elf32
CC = gcc
CFLAGS = -m32 -ffreestanding -Wall -Wextra -nostdlib -c -I include/
LD = ld
LDFLAGS = -m elf_i386 -T link.ld

# Sources
LOADER_SRC = $(BOOT_DIR)/loader.s
KERNEL_SRC = $(KERNEL_DIR)/kernel.c
SCREEN_SRC = $(DRIVERS_DIR)/screen.c

.PHONY: all clean iso

all: iso

# Build loader object
$(LOADER_BIN): $(LOADER_SRC)
	@mkdir -p $(BUILD_DIR)
	$(AS) $(ASFLAGS) -o $@ $<

# Build kernel object
$(KERNEL_BIN): $(KERNEL_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<

# Build screen driver object
$(SCREEN_BIN): $(SCREEN_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<

# Link the kernel (now with screen.o)
$(KERNEL_ELF): $(LOADER_BIN) $(KERNEL_BIN) $(SCREEN_BIN) link.ld
	@mkdir -p $(BUILD_DIR)
	$(LD) $(LDFLAGS) -o $@ $(LOADER_BIN) $(KERNEL_BIN) $(SCREEN_BIN)

iso: $(KERNEL_ELF)
	grub-mkrescue -o $(ISO_NAME) $(ISO_DIR)

clean:
	rm -rf $(BUILD_DIR) togekissos.iso
