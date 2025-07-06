#ifndef GDT_H
#define GDT_H

#include <stdint.h>

// Tamaño de la GDT
#define GDT_ENTRIES 3

// Estructura para una entrada en la GDT
typedef struct {
    uint16_t limit_low;   // Bits bajos del límite
    uint16_t base_low;    // Bits bajos de la base
    uint8_t base_middle;  // Bits medios de la base
    uint8_t access;       // Byte de acceso
    uint8_t granularity;  // Granularidad y bits altos del límite
    uint8_t base_high;    // Bits altos de la base
} __attribute__((packed)) gdt_entry_t;

// Puntero a la GDT
typedef struct {
    uint16_t limit;       // Tamaño de la GDT menos 1
    uint32_t base;        // Dirección base de la GDT
} __attribute__((packed)) gdt_ptr_t;

void init_gdt();

#endif
