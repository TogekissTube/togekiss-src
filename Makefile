# Directories
BOOT_DIR = boot
KERNEL_DIR = kernel
DRIVERS_DIR = $(KERNEL_DIR)/drivers
ARCH_DIR = $(KERNEL_DIR)/arch/x86
ISO_DIR = iso
BUILD_DIR = build

# Output files
ISO_NAME = togekissos.iso
KERNEL_BIN = $(BUILD_DIR)/kernel.o
SCREEN_BIN = $(BUILD_DIR)/screen.o
LOADER_BIN = $(BUILD_DIR)/loader.o
GDT_BIN = $(BUILD_DIR)/gdt.o
GDTA_BIN = $(BUILD_DIR)/gdta.o
IDT_BIN = $(BUILD_DIR)/idt.o
IDTA_BIN = $(BUILD_DIR)/idta.o
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
GDT_SRC = $(ARCH_DIR)/gdt.c
GDTA_SRC = $(ARCH_DIR)/gdta.asm
IDT_SRC = $(ARCH_DIR)/idt.c
IDTA_SRC = $(ARCH_DIR)/idta.asm

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

# Build x86 gdt object
$(GDT_BIN): $(GDT_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<

# Build x86 gdta asm object
$(GDTA_BIN): $(GDTA_SRC)
	@mkdir -p $(BUILD_DIR)
	$(AS) $(ASFLAGS) -o $@ $<

# Build x86 idt object
$(IDT_BIN): $(IDT_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<

# Build x86 idta asm object
$(IDTA_BIN): $(IDTA_SRC)
	@mkdir -p $(BUILD_DIR)
	$(AS) $(ASFLAGS) -o $@ $<

# Link the kernel (now with all objects)
$(KERNEL_ELF): $(LOADER_BIN) $(KERNEL_BIN) $(SCREEN_BIN) $(GDT_BIN) $(GDTA_BIN) $(IDT_BIN) $(IDTA_BIN) link.ld
	@mkdir -p $(BUILD_DIR)
	$(LD) $(LDFLAGS) -o $@ $(LOADER_BIN) $(KERNEL_BIN) $(SCREEN_BIN) $(GDT_BIN) $(GDTA_BIN) $(IDT_BIN) $(IDTA_BIN)

iso: $(KERNEL_ELF)
	@mkdir -p $(ISO_DIR)/boot/grub
	cp $(KERNEL_ELF) $(ISO_DIR)/boot/kernel.elf
	echo 'set timeout=0' > $(ISO_DIR)/boot/grub/grub.cfg
	echo 'set default=0' >> $(ISO_DIR)/boot/grub/grub.cfg
	echo 'menuentry "TogekissOS" { multiboot /boot/kernel.elf }' >> $(ISO_DIR)/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO_DIR)/$(ISO_NAME) $(ISO_DIR)

clean:
	rm -rf $(BUILD_DIR) $(ISO_DIR)/boot/kernel.elf $(ISO_DIR)/boot/grub/grub.cfg $(ISO_DIR)/$(ISO_NAME)
