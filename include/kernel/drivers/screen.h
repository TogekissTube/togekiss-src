#ifndef SCREEN_H
#define SCREEN_H


#define MAX_LINES       80
#define MAX_COLUMNS     25
#define TAB_WIDTH       8    
#define VIDEO_RAM       0xB8000
#define LINE_RAM        (MAX_COLUMNS*2)
#define PAGE_RAM        (MAX_LINES * MAX_COLUMNS)
#define BLANK_CHAR      (' ')
#define BLANK_ATTR      (0x70)          
#define CHAR_OFF(x,y)   (LINE_RAM*(y)+2*(x))

void screen_put(char c);

void screen_clear();

void screen_write(char *c);

#endif