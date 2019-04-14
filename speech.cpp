#include "speech.h"

#include "globals.h"
#include "hardware.h"
GameInputs in;
Timer waitTime;
/**
 * Draw the speech bubble background.
 */
static void draw_speech_bubble();

/**
 * Erase the speech bubble.
 */
static void erase_speech_bubble();

/**
 * Draw a single line of the speech bubble.
 * @param line The text to display
 * @param which If TOP, the first line; if BOTTOM, the second line.
 */
#define TOP    0
#define BOTTOM 1
static void draw_speech_line(const char* line, int which);

/**
 * Delay until it is time to scroll.
 */
static int speech_bubble_wait(GameInputs input);

void draw_speech_bubble()
{
    uLCD.filled_rectangle(0, 113, 128, 93, 0x000000);
    
    uLCD.filled_rectangle(0, 93, 128, 94, 0x00FF7F);
    uLCD.filled_rectangle(0, 113, 128, 111, 0x00FF7F);
    uLCD.filled_rectangle(0, 113, 1, 93, 0x00FF7F);
    uLCD.filled_rectangle(128, 113, 128, 93, 0x00FF7F);
}

void erase_speech_bubble()
{
    GameInputs in = read_inputs();
    while(in.b1) {
        in = read_inputs();
        wait_ms(300);
    }
    uLCD.filled_rectangle(0, 113, 128, 93, 0x000000);
}

void draw_speech_line(const char* line, int which)
{
    uLCD.textbackground_color(0x000000);
    uLCD.color(GREEN);
    uLCD.text_bold(TEXTBOLD);
    if(which == BOTTOM) {
        uLCD.locate(1,13);
        uLCD.printf(line);
    } else {
        uLCD.locate(1,12);
        uLCD.printf(line);   
    }
}

int speech_bubble_wait(GameInputs inputs) {

}
void speech(const char* line1, const char* line2)
{
    draw_speech_bubble();
    draw_speech_line(line1, TOP);
    draw_speech_line(line2, BOTTOM);
    wait_ms(300);
    erase_speech_bubble();
}

void long_speech(const char* lines[], int n)
{
}
