#include "kernel/arch/x86/idt.h"
#include "kernel/io.h"

idt_entry_t idt[IDT_ENTRIES];
idt_ptr_t idt_ptr;

// Función para establecer una entrada en la IDT
void idt_set_entry(int num, uint32_t base, uint16_t selector, uint8_t type_attr) {
    idt[num].offset_low = base & 0xFFFF;
    idt[num].selector = selector;
    idt[num].zero = 0;
    idt[num].type_attr = type_attr;
    idt[num].offset_high = (base >> 16) & 0xFFFF;
}

// Declaración de `load_idt` definida en ensamblador
extern void load_idt(uint32_t);

// Inicialización de la IDT
void init_idt() {

    idt_ptr.limit = sizeof(idt_entry_t) * IDT_ENTRIES - 1;
    idt_ptr.base = (uint32_t)&idt;
    
    // Inicializa todas las entradas de la IDT a 0
    for (int i = 0; i < IDT_ENTRIES; i++) {
        idt_set_entry(i, 0, 0, 0);
    }

    // Cargar la IDT
    load_idt((uint32_t)&idt_ptr);
}
