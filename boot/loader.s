section .multiboot
align 4
    dd 0x1BADB002
    dd 0x0
    dd 0xE4524FFE    ; checksum = -(0x1BADB002 + 0x0)

section .text
global loader
extern kmain

loader:
    mov eax, 0xCAFEBABE
    mov esp, kernel_stack + KERNEL_STACK_SIZE
    call kmain

.loop:
    jmp .loop

section .bss
align 4

kernel_stack:                                      
    resb KERNEL_STACK_SIZE  

KERNEL_STACK_SIZE equ 4096