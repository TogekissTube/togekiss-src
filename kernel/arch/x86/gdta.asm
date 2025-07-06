
global load_gdt

section .text
load_gdt:
    mov eax, [esp + 4]   ; Carga la dirección de la GDT
    lgdt [eax]           ; Carga el registro GDTR

    ; Actualiza los registros de segmento
    mov ax, 0x10         ; Selector del segmento de datos (índice 2, RPL 0)
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Carga el segmento de código
    jmp 0x08:.flush      ; Selector del segmento de código (índice 1, RPL 0)

.flush:
    ret
