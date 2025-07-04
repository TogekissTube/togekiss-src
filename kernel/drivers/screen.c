#include "kernel/drivers/screen.h"
#include "kernel/io.h"
#include <stdint.h>

// Puntero al inicio de la memoria de video
uint16_t* video_memory = (uint16_t*)VIDEO_RAM;

// Variables para el cursor
uint8_t cursor_x = 0;
uint8_t cursor_y = 0;

// Función para actualizar el cursor de hardware
static void move_cursor() {
    // Calcula la posición del cursor en la memoria de video
    uint16_t cursorLocation = cursor_y * MAX_COLUMNS + cursor_x;
    // Envía los bytes correspondientes al controlador VGA para actualizar la posición del cursor
    outb(0x3D4, 14);                  
    outb(0x3D5, cursorLocation >> 8); 
    outb(0x3D4, 15);                  
    outb(0x3D5, cursorLocation);      
}

// Función para hacer scroll en la pantalla
static void scroll() {
    // Calcula el byte de atributo para el espacio en blanco predeterminado
    uint8_t attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
    uint16_t blank = ' ' | (attributeByte << 8);

    // Si la fila 25 es el final, necesitamos hacer scroll hacia arriba
    if (cursor_y >= MAX_LINES) {
        // Mueve el contenido de la pantalla una línea hacia arriba
        for (int i = 0; i < (MAX_LINES - 1) * MAX_COLUMNS; i++) {
            video_memory[i] = video_memory[i + MAX_COLUMNS];
        }
        // Llena la última línea con espacios en blanco
        for (int i = (MAX_LINES - 1) * MAX_COLUMNS; i < MAX_LINES * MAX_COLUMNS; i++) {
            video_memory[i] = blank;
        }
        // El cursor ahora debería estar en la última línea
        cursor_y = MAX_LINES - 1;
    }
}

// Función para escribir un carácter en la pantalla
void screen_put(char c) {
    // Manejo de caracteres especiales
    if (c == '\n') {
        cursor_x = 0;       // Reinicia a la columna inicial
        cursor_y++;         // Avanza a la siguiente línea
        scroll();           // Desplaza si es necesario
        move_cursor();      // Actualiza el cursor de hardware
        return;
    }
    
    // Manejo de otros caracteres
    uint16_t offset = cursor_y * MAX_COLUMNS + cursor_x;
    video_memory[offset] = c | (0x0F << 8); // Escribe el carácter y color predeterminado
    cursor_x++; // Avanza el cursor horizontalmente

    // Verifica si hay que mover a la siguiente línea
    if (cursor_x >= MAX_COLUMNS) {
        cursor_x = 0;
        cursor_y++;
        scroll();
    }

    // Actualiza el cursor de hardware
    move_cursor();
}

// Función para borrar la pantalla
void screen_clear() {
    // Llena la pantalla con espacios en blanco
    uint8_t attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
    uint16_t blank = ' ' | (attributeByte << 8);
    for (int i = 0; i < MAX_LINES * MAX_COLUMNS; i++) {
        video_memory[i] = blank;
    }
    // Reinicia las coordenadas del cursor
    cursor_x = 0;
    cursor_y = 0;
    // Actualiza el cursor de hardware
    move_cursor();
}

void screen_write(char *c)
{
   int i = 0;
   while (c[i])
   {
       screen_put(c[i++]);
   }
} 
