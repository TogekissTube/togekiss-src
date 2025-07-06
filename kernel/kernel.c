#include "kernel/drivers/screen.h"
#include "kernel/arch/x86/gdt.h"

void kmain() {
    screen_clear(); // Limpia la pantalla
    init_gdt();
    screen_write("TOGEKISS 0.0.2");
}
