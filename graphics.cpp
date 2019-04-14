#include "graphics.h"

#include "globals.h"



void draw_player(int u, int v, int key)
{
    if(key == 0) {
        draw_img(u, v, "LLDDDDDDDLLLLDYYDYDDLLLDYYLYLYYDLLDYYYYYYYDLLDLYYLYYLDLLLLLBBBLLLLLLLPPPPPLLLLLBBBBBBBLLLLYPPPPPYLLLLLBBBBBLLLLLLLDLDLLLL");  
    } else if(key == 1) {
        draw_img(u, v, "LLDDDDDDDLLLLDYYDYDDLLLDYYLYLYYDLLDYYYYYYYDLLDLYYLYYLDLLLLLGGGLLLLLLLYYYYYLLLLLGGGGGGGLLLLYYYYYYYLLLLLGGGGGLLLLLLLDLDLLLL");
    }
}
void draw_leaf(int u, int v) {

    draw_img(u, v, "LLLLGGGLLLLLLGGGGGGGLLLGGGGGGGGGLLLGGGGGGGGGLGGGGGGGGGGGGGGGGGGGGGLGGGGGGGGGLGGGGGGGGGGGLGGGGGGGGGLLLGGGGGGGLLLLLGGGGGLLL");
}
void draw_wood(int u, int v) {
    draw_img(u, v, "LLLDDDDDLLLLLDDDDDDDLLLDDDDDDDDDLLDDDDDDDDDLLDDDDDDDDDLLDDDDDDDDDLLDDDDDDDDDLLDDDDDDDDDLLDDDDDDDDDLDDDDDDDDDDDDDDDDDDDDDD");
}
#define YELLOW 0xFFFF00
#define BROWN  0xD2691E
#define BLUE   0x0000FF
#define DIRT   BROWN
#define PURPLE  0X9400D3

void draw_img(int u, int v, const char* img)
{
    int colors[11*11];
    for (int i = 0; i < 11*11; i++)
    {
        if (img[i] == 'R') colors[i] = RED;
        else if (img[i] == 'Y') colors[i] = YELLOW;
        else if (img[i] == 'G') colors[i] = GREEN;
        else if (img[i] == 'D') colors[i] = DIRT;
        else if (img[i] == '5') colors[i] = LGREY;
        else if (img[i] == '3') colors[i] = DGREY;
        else if (img[i] == 'P') colors[i] = PURPLE;
        else if (img[i] == 'B') colors[i] = BLUE;
        else if(img[i] == 'W') colors[i] = WHITE;
        else colors[i] = BLACK;
    }
    uLCD.BLIT(u, v, 11, 11, colors);
    wait_us(250); // Recovery time!
}

void draw_nothing(int u, int v)
{
    // Fill a tile with blackness
    uLCD.filled_rectangle(u, v, u+10, v+10, BLACK);
}

void draw_wall(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, BROWN);
}

void draw_plant(int u, int v)
{
    draw_img(u, v, "LYYYYYYYYYLYYLLLWLLLYYYLLWLWLWLLYYLLLLYLLLLYYWWWWWWWWWYYLLWWWWWLLYYLWLLLLLWLYYLWLWWWLWLYYWLWLWLWLWYYYWLLLLLWYYLYYYYYYYYYL");
}

void draw_upper_status(int x, int y)
{
    // Draw bottom border of status bar
    uLCD.line(0, 9, 127, 9, GREEN);
    uLCD.color(GREEN);
    uLCD.locate(0, 0);
    uLCD.printf("(%d,%d)",x,y);
    // Add other status info drawing code here
}

void draw_lower_status()
{
    // Draw top border of status bar
    uLCD.line(0, 118, 127, 118, GREEN);
    
    // Add other status info drawing code here
}

void draw_start() {
    uLCD.color(GREEN);
    uLCD.text_bold(TEXTBOLD);
    uLCD.locate(0, 5);
    uLCD.text_height(2);
    uLCD.text_width(2);
    uLCD.printf("UNDERTALE");
    
    uLCD.text_height(1);
    uLCD.text_width(1);
    uLCD.locate(3,8);
    uLCD.printf("BY PETER DONG");
    
    uLCD.locate(1,10);
    uLCD.printf("Follow me on ig:");
    
    uLCD.locate(5,12);
    uLCD.printf("@cpeterr");
}
void draw_game_over() {
    uLCD.cls();
    uLCD.color(GREEN);
    uLCD.text_bold(TEXTBOLD);
    uLCD.locate(5, 4);
    uLCD.printf("GAME OVER");
    uLCD.locate(0, 6);
    uLCD.printf("Thanks for playing");
    uLCD.locate(9, 9);
    uLCD.printf("Peter");
    wait_ms(5000);
}

void draw_menu(char* a, char* b, int health_count, int key, int chest, int run) {
    uLCD.cls();
    uLCD.color(GREEN);
    uLCD.text_bold(TEXTBOLD);
    uLCD.locate(0, 4);
    uLCD.printf("task: %s", a);
    
    uLCD.color(RED);
    uLCD.text_bold(TEXTBOLD);
    uLCD.locate(0, 7);
    uLCD.printf("hint: %s", b);
    if(key == 1) {
        uLCD.color(WHITE);
        uLCD.text_bold(TEXTBOLD);
        uLCD.locate(0, 10);
        uLCD.printf("inventory: Chara's shirt");
        if(chest==1) {
            uLCD.printf(", Treasure chest");   
        }
        if(run == 1) {
            uLCD.printf(", Running shoes");   
        }
    } 
    if (health_count == 3) {
        draw_img(85, 10, "LRRRLLLRRRLRRRRRLRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRLRRRRRRRRRLLRRRRRRRRRLLLRRRRRRRLLLLRRRRRRRLLLLLRRRRRLLLLLLLRRRLLLL");
        draw_img(50, 10, "LRRRLLLRRRLRRRRRLRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRLRRRRRRRRRLLRRRRRRRRRLLLRRRRRRRLLLLRRRRRRRLLLLLRRRRRLLLLLLLRRRLLLL");
        draw_img(20, 10, "LRRRLLLRRRLRRRRRLRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRLRRRRRRRRRLLRRRRRRRRRLLLRRRRRRRLLLLRRRRRRRLLLLLRRRRRLLLLLLLRRRLLLL");
    } else if(health_count == 2) {
        draw_img(50, 10, "LRRRLLLRRRLRRRRRLRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRLRRRRRRRRRLLRRRRRRRRRLLLRRRRRRRLLLLRRRRRRRLLLLLRRRRRLLLLLLLRRRLLLL");
        draw_img(20, 10, "LRRRLLLRRRLRRRRRLRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRLRRRRRRRRRLLRRRRRRRRRLLLRRRRRRRLLLLRRRRRRRLLLLLRRRRRLLLLLLLRRRLLLL");           
    } else if(health_count == 1) {
        draw_img(20, 10, "LRRRLLLRRRLRRRRRLRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRLRRRRRRRRRLLRRRRRRRRRLLLRRRRRRRLLLLRRRRRRRLLLLLRRRRRLLLLLLLRRRLLLL");   
    }
    wait_ms(3000);
    
}

void draw_border()
{
    uLCD.filled_rectangle(0,     9, 127,  14, WHITE); // Top
    uLCD.filled_rectangle(0,    13,   2, 114, WHITE); // Left
    uLCD.filled_rectangle(0,   114, 127, 117, WHITE); // Bottom
    uLCD.filled_rectangle(124,  14, 127, 117, WHITE); // Right
}

void draw_sign(int u, int v) {
    draw_img(u, v, "LLDDDDDDDLLLDWWWWWWWDLDWWLLWLWWWDDWWWWWWWWWDDLLWWWLLLWDDWWLLWWWWWDLDDDDDDDDDLLLLLDYDLLLLLLLLDYDLLLLLLLLDYDLLLLLLLLDDDLLLL");  
}

void draw_door_locked(int u, int v) {
    draw_img(u, v, "LLLLLLLLLLLDDDDDDDDDDDDDDDDDDDDDDLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL");
}

void draw_door_unlocked(int u, int v) {
    draw_img(u, v, "LLLLLLLLLLLDDLLLLLLLLLDDDLLLLLLLLLDDDLLLLLLLLLDDDLLLLLLLLLDDDLLLLLLLLLDDDLLLLLLLLLDDDLLLLLLLLLDDDLLLLLLLLLDDLLLLLLLLLLLLL");   
}

void draw_flowey_friendly(int u, int v) {
    draw_img(u, v, "LYYYYYYYYYLYYWWWWWWWYYYWWWLWLWWWYYWWWLWLWWWYYWLWWWWWLWYYYWLLLLLWYYLLYYYYYYYLLLLLLGGLLLLLLLLGGLLLLLLLGLGGLLGLLLLGGGGGGGLLL");   
}

void draw_flowey_wink(int u, int v) {
    draw_img(u, v, "LYYYYYYYYYLYYWWLWWWWYYYWWWLWLLWWYYWLWWWWWWWYYWWLLLLLWWYYYWRRWWWWYYLLYYYYYYYLLLLLLGGLLLLLLLLGGLLLLLLLGLGGLLGLLLLGGGGGGGLLL");   
}

void draw_flowey_creepy(int u, int v) {
    draw_img(u, v, "LYYYYYYYYYLYYLLLWLLLYYYLLWLWLWLLYYLLLLYLLLLYYWWWWWWWWWYYLLWWWWWLLYYLWLLLLLWLYYLWLWWWLWLYYWLWLWLWLWYYYWLLLLLWYYLYYYYYYYYYL");   
}

void draw_toby(int u, int v) {
    draw_img(u, v, "LLYLLLYLLLLLYWLLLWLLLLYWWWWWWYLLLYWLWWLWYYLLYWWWWWWWYYLYWWLLWWWYYYYLWLWWLWWWYYWLLLLWWWWYYWWWWWWWWWYLYWYWYYWYYYLLYLYLLYLLY");
}

void draw_toby_bone(int u, int v) {
    draw_img(u, v, "LLYLLLYLLLLLYWYYYWYLLLYWWWWWWYLLLYWLWWLWYYLLYWWWWWWWYYLYWWLLWWWYYYYLWLWWLRRWYYWLLLLRWRWYRRRRRRRWRWWWWWWWWWWRWWRRRRRRRRWWW");   
}

void draw_red_button(int u, int v) {
    draw_img(u, v, "LLRRRRRRRLLLRRRRRRRRRLRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRLRRRRRRRRRLLLRRRRRRRLLLLLRRRRRLLLLLLRRRRRLLLLRRRRRRRRRLRRRRRRRRRRR");   
}

void draw_green_button(int u, int v) {
    draw_img(u, v, "LLGGGGGGGLLLGGGGGGGGGLGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGLGGGGGGGGGLLLGGGGGGGLLLLLGGGGGLLLLLLGGGGGLLLLGGGGGGGGGLGGGGGGGGGGG");
}
void draw_chest(int u, int v) {
    draw_img(u, v, "LLLYYYYYLLLLLYDDDDDYLLLYDDDDDDDYLYDDDDDDDDDYYDDDYYYDDDYYDDDDYDDDDDLLLLLLLLLLLYDDDDDDDDDYYDDDDDDDDDYYYDDDDDDDYYYYYYYYYYYYY");   
}
void draw_blue_button(int u, int v) {
    draw_img(u, v, "LLBBBBBBBLLLBBBBBBBBBLBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBLBBBBBBBBBLLLBBBBBBBLLLLLBBBBBLLLLLLBBBBBLLLLBBBBBBBBBLBBBBBBBBBBB");   
}

void draw_river_man(int u, int v) {
    draw_img(u, v, "LLLPPPPPPLLLLPBLLBBPPLLLPBLLBBBBPLLPBLLBBBBPLLPBLLBBPPBDLLPBBBBPLLDLPBBBBBPLLDDPBBBBBPDDDDPBBBBBPDDDDDPPPPPDDDPDDDDDDDDDL");   
}