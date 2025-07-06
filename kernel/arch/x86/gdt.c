#include "kernel/arch/x86/gdt.h"

// La GDT y su puntero
gdt_entry_t gdt[GDT_ENTRIES];
gdt_ptr_t gdt_ptr;

// Declaración de `load_gdt` definida en ensamblador
extern void load_gdt(uint32_t);

// Configura una entrada en la GDT
void gdt_set_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
    gdt[num].base_low = base & 0xFFFF;
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = limit & 0xFFFF;
    gdt[num].granularity = (limit >> 16) & 0x0F;

    gdt[num].granularity |= (granularity & 0xF0);
    gdt[num].access = access;
}

// Inicializa la GDT
void init_gdt() {
    gdt_ptr.limit = sizeof(gdt_entry_t) * GDT_ENTRIES - 1;
    gdt_ptr.base = (uint32_t)&gdt;

    // Entrada nula
    gdt_set_entry(0, 0, 0, 0, 0);

    // Segmento de código
    gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    // Segmento de datos
    gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    // Cargar la nueva GDT
    load_gdt((uint32_t)&gdt_ptr);
}
