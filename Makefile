CC      = gcc
AS      = nasm
LD      = ld

CFLAGS  = -m32 -ffreestanding -O2 -Wall -Wextra \
          -fno-stack-protector -fno-builtin -nostdlib \
          -Isrc/include
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T linker.ld

BUILD_DIR = build
ISO_DIR   = iso/boot
TARGET    = $(BUILD_DIR)/kernel.elf
ISO       = $(BUILD_DIR)/alexFirstOS.iso

# Aggiunto $(wildcard src/include/*.c) per trovare kiolib.c e simili
C_SOURCES := $(wildcard src/kernel/*.c) \
             $(wildcard src/drivers/*.c) \
             $(wildcard src/misc/*.c) \
             $(wildcard src/include/*.c)

# Converte i percorsi dei sorgenti in percorsi degli oggetti nella build/
C_OBJS := $(patsubst src/%.c, $(BUILD_DIR)/%.o, $(C_SOURCES))

ASM_OBJS = $(BUILD_DIR)/boot.o
OBJS = $(ASM_OBJS) $(C_OBJS)

all: $(ISO)

# Compilazione Bootloader
$(BUILD_DIR)/boot.o: src/boot/boot.asm
	@mkdir -p $(BUILD_DIR)
	$(AS) $(ASFLAGS) $< -o $@

# Regola generica per tutti i .c
# Compila src/include/kiolib.c -> build/include/kiolib.o
$(BUILD_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

$(ISO): $(TARGET)
	@mkdir -p $(ISO_DIR)/grub
	cp $(TARGET) $(ISO_DIR)/kernel.elf
	grub-mkrescue -o $@ iso/

run: $(ISO)
	qemu-system-i386 -cdrom $(ISO) -m 32

clean:
	rm -rf $(BUILD_DIR)/

.PHONY: all run clean