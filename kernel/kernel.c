#include "kernel/drivers/screen.h"

void kmain() {
    screen_clear(); // Limpia la pantalla
    screen_write("TOGEKISS 0.0.1");
}
