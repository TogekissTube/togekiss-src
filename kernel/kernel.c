#include "kernel/drivers/screen.h"
#include "kernel/arch/x86/gdt.h"
#include "kernel/arch/x86/idt.h"

void kmain() {
    screen_clear(); // Limpia la pantalla
    init_gdt();
    init_idt();
    screen_write("TOGEKISS 0.0.2");
}
