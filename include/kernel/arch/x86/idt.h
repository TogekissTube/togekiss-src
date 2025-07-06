#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define IDT_ENTRIES 256

// Estructura para una entrada en la IDT
typedef struct {
    uint16_t offset_low;   // Bits 0-15 de la dirección del manejador
    uint16_t selector;     // Selector de segmento de código
    uint8_t zero;          // Debe ser 0
    uint8_t type_attr;     // Tipo y atributos
    uint16_t offset_high;  // Bits 16-31 de la dirección del manejador
} __attribute__((packed)) idt_entry_t;

// Estructura para la dirección de la IDT
typedef struct {
    uint16_t limit;        // Tamaño de la IDT menos 1
    uint32_t base;         // Dirección base de la IDT
} __attribute__((packed)) idt_ptr_t;

void init_idt();
void idt_set_entry(int index, uint32_t base, uint16_t selector, uint8_t flags);

#endif
