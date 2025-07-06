
global load_idt

load_idt:
    mov eax, [esp + 4]  ; Obtiene la dirección de la IDT
    lidt [eax]          ; Carga la IDT
    ret
