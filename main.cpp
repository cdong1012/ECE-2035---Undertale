// Project includes
#include "globals.h"
#include "hardware.h"
#include "map.h"
#include "graphics.h"
#include "speech.h"

#include <stdlib.h>
int menu = 0;
int health = 3;
int omni_pressed = 0;
int run = 0;
int quest = 0; // 0 is before quest, 1 is during quest no key, 2 is with key, 3 is back talking 
int door = 0; // 1 if door unlocked, 0 if door locked
int chest = 0;
int game_over = 0;
char* task[5] = {"talk to the dog to start quest", "go to Snowdin", "go into the room to start the puzzle", "come back to the castle", "go to the castle"};
char* hint[5] = {"Just talk to him", "talk to the riverman", "read the sign", "talk to the riverman", "walk down south"};

char* flowey_wink[4] = {"Howdy!", "I'm FLOWEY", "FLOWEY THE", "FLOWER"};
char* flowey_creepy[4] = {"In this","world...","It's KILL","or BE killed!"};
char* flowey_friendly1[4] = {"That shirt...", "it seems familiar", "reminds me of", "someone"};
char* flowey_friendly2[4] = {"are you sure", "it's yours?", "ugh I hate", "that dog"};
char** flowey_friendly[2] = {flowey_friendly1, flowey_friendly2};

char* sign1[4] = {"Welcome to","Snowdin!", "here you have to","solve a puzzle"};
char* sign2[4] = {"Choose the right", "button. One will", "take you to", "the next level"};
char* sign3[4] = {"Two will kick you","out of the room", "Three strikes", "and you're out"};
char** sign[3] = {sign1, sign2, sign3};

char* toby_pre1[4] = {"ruff ruff", "yo!", "I'm just a dog"};
char* toby_pre2[4] = {"how are ya", "you must be", "new here!", "This is the"};
char* toby_pre3[4] = {"the ruins! We", "have monsters and", "all kind of"};
char* toby_pre4[4] = {"stuff down here", "...", "There is not", "much to do tho"};
char* toby_pre5[4] = {"... oh wait", "there is!! I'm", "hungry.. can you", "get me some bone?"};
char* toby_pre6[4] = {"Where? Snowdin!","it's quite a", "distance from here", "so i suggest"};
char* toby_pre7[4] = {"you get going!", "Bring me a bone", "asap, and ill" };
char* toby_pre8[4] = {"give you something","in return!","good luck!!","..."};
char** toby_pre[8] = {toby_pre1, toby_pre2, toby_pre3,toby_pre4,toby_pre5,toby_pre6,toby_pre7,toby_pre8};
char* toby_bone1[4] = {"Om nom nom", "nom..", "oh hey!", "look at ya"};
char* toby_bone2[4] = {"How did you get", "here so fast?", ".. nom nom", "nom"};
char* toby_bone3[4] = {"what's with the", "look? Didnt", "I tell you I", "could teleport?"};
char* toby_bone4[4] = {"Yea!Like the dude", "on the boat", "pretty nice,","isnt it?"};
char* toby_bone5[4] = {"You just came", "here for nothing!", "bamboozled!","..."};
char* toby_bone6[4] = {"Lol don't be mad", "I'll give ya", "this pretty dope", "shirt!"};
char* toby_bone7[4] = {"The old prince", "threw it away", "you can", "basically go"};
char* toby_bone8[4] = {"anywhere with it", "...", "It's", "pretty nice!"};
char* toby_bone9[4] = {"imma go!", "baiiii", "i'll see ya at", "the starting point"};
char** toby_bone[9] = {toby_bone1, toby_bone2,toby_bone3,toby_bone4,toby_bone5,toby_bone6,toby_bone7,toby_bone8,toby_bone9};

char* river_man_line1[4] = {"Tra la la", "The waters are", "wild today.", "That is bad luck"};
char* river_man_line2[4] = {"Tra la la", "The waters are", "wild today.", "That is good luck"};
char* river_man_line3[4] = {"Tra la la", "What's inside an", "acorn? It's" ,"just a mystery."};
char* river_man_line4[4] = {"Tra la la", "Dancing on a boat","is danger.", "But good exercise"};
char* river_man_line5[4] = {"Tra la la", "Why don't you", "sing with me.", "Tra la la."};
char* river_man_line6[4] = {"Tra la la", "Uh oh.", "Suddenly, feeling" ,"tropical..."};
char* river_man_line7[4] = {"Tra la la", "The water is", "very dry", "today"};
char* river_man_line8[4] = {"Tra la la", "The water is", "very wet", "today"};
char* river_man_line9[4] = {"Tra la la", "Tri li li.", "Tre le le.", "..."};
char* river_man_line10[4] = {"Tra la la", "What's my name?" ,"It doesn't", "really matter..."};
char* river_man_line11[4] = {"Tra la la." "I heard dogs" "have a favorite" "food. It's bone!"};
char* river_man_line12[4] = {"Tra la la. You", "can never have", "too many hot dogs", "This is not true"};
char* river_man_line13[4] = {"Tra la la.", "Beware of", "the man who", "speaks in hands"};
char* river_man_line14[4] = {"Tra la la.", "Beware of the", "man who came from", "the other world"};
char* river_man_line15[4] = {"Tra la la.", "Humans, monsters", "...", "flowers"};
char** river_man_line[15] = {river_man_line13, river_man_line3,river_man_line14, river_man_line1, river_man_line15, river_man_line6, river_man_line11, river_man_line8, river_man_line9, river_man_line10,river_man_line7,river_man_line12,river_man_line2,river_man_line4,river_man_line5};
// Functions in this file
int get_action (GameInputs inputs);
int update_game (int action);
void draw_game (int init);
void init_main_map ();
void intit_start();
void init_menu(char* task, char* hint, int health, int key, int chest, int run);
int go_up(int x, int y);
int go_down(int x, int y);
int go_left(int x, int y);
int go_right(int x, int y);
int main ();
int interact(int x, int y);
void check_health();
/**
 * The main game state. Must include Player locations and previous locations for
 * drawing to work properly. Other items can be added as needed.
 */
struct {
    int x,y;    // Current locations
    int px, py; // Previous locations
    int has_key;
} Player;

/**
 * Given the game inputs, determine what kind of update needs to happen.
 * Possbile return values are defined below.
 */
#define NO_ACTION 0
#define ACTION_BUTTON 1
#define MENU_BUTTON 2
#define GO_LEFT 3
#define GO_RIGHT 4
#define GO_UP 5
#define GO_DOWN 6
#define RUN 7
int get_action(GameInputs inputs)
{
    if(!inputs.b1) {
        return ACTION_BUTTON;   
    }
    if(!inputs.b2) {
        return MENU_BUTTON;   
    }
    if(inputs.ax < -0.49) {
        return GO_LEFT;   
    }
    if(inputs.ax >= 0.49) {
        return GO_RIGHT;
    }
    if(inputs.ay >=0.45) {
        return GO_UP;   
    }
    if(inputs.ay <= -0.45) {
        return GO_DOWN;   
    }
    if (!inputs.b3) {
        omni_pressed = !omni_pressed;
    }
    return NO_ACTION;
}

/**
 * Update the game state based on the user action. For example, if the user
 * requests GO_UP, then this function should determine if that is possible by
 * consulting the map, and update the Player position accordingly.
 * 
 * Return values are defined below. FULL_DRAW indicates that for this frame,
 * draw_game should not optimize drawing and should draw every tile, even if
 * the player has not moved.
 */
#define NO_RESULT 0
#define GAME_OVER 1
#define FULL_DRAW 2
int update_game(int action)
{
    // Save player previous location before updating
    Player.px = Player.x;
    Player.py = Player.y;
    
    // Do different things based on the each action.
    // You can define functions like "go_up()" that get called for each case.
    switch(action)
    {
        case GO_UP:
            if(go_up(Player.px, Player.py)) {
                return FULL_DRAW;   
            } else {
                break;
            }
        case GO_LEFT:
            if(go_left(Player.px, Player.py)) {
                return FULL_DRAW;   
            } else {
                break;
            }          
        case GO_DOWN:
            if(go_down(Player.px, Player.py)) {
                return FULL_DRAW;   
            } else {
                break;
            }
        case GO_RIGHT:
            if(go_right(Player.px, Player.py)) {
                return FULL_DRAW;   
            } else {
                break;
            }
        case ACTION_BUTTON:
            if(interact(Player.x,Player.y)) {
                return FULL_DRAW;
            } else {
                break;   
            }
        case MENU_BUTTON: 
            uLCD.cls();
            init_menu(task[menu], hint[menu], health, Player.has_key, chest, run);
            wait_ms(300);
            draw_game(true);
            return FULL_DRAW;
        default:        break;
    }
    return NO_RESULT;
}

int interact(int x, int y) {
    MapItem *item = get_south(x, y);

    if(item->type == CHEST) {
        speech("you found a", "chest!!!");
        draw_game(true);
        wait_ms(150);
        map_erase(x,y+1);
        draw_game(true);
        wait_ms(150);
        chest = 1;
        map_erase(x,y-2);
        draw_game(true);
        quest = 99;
        wait_ms(150);
        
        add_leaf(11, 10);
        add_wood(11, 11);
        add_wood(11, 12);
        return 1;  
    }
    
    if(item->type == WOOD) {
        if(run == 0) {
            speech("Hi kid!,","Im a tree");
            draw_game(true);
            wait_ms(150);
            speech("...","uhm so...");
            draw_game(true);
            wait_ms(150);
            speech("some kid left", "their running");
            draw_game(true);
            wait_ms(150);
            speech("shoes here, imma", "give it to you");
            draw_game(true);
            wait_ms(150);
            run = 1;
        } else {
            speech("oh you dont", "want the shoes");  
            draw_game(true);
            wait_ms(150);
            speech("no mo? Ill", "take it back then");
            draw_game(true);
            wait_ms(150);
            run = 0;
        }       
    }
    if(item->type == TOBY) {
        if(quest == 0) {
            for(int i =0; i<8;i++) {
                for(int j = 0; j < 4;j+=2) {
                    speech(toby_pre[i][j], toby_pre[i][j+1]);
                    draw_game(true);   
                }   
            }
            wait_ms(150);  
            quest=1;
            menu = 1;
            menu++;
        } else if(quest == 1) {
            speech("well..","what are you waiting for!");
            draw_game(true);
            wait_ms(300);
            menu = 1;
        } else if(quest == 3) {
            speech("ruff ruff,","looking good!!");
            draw_game(true);
            wait_ms(300); 
            speech("you can go to", "the castle");
            draw_game(true);
            wait_ms(300);
            speech("down south now!", "Have fun");
            draw_game(true);
            wait_ms(300);
            menu = 4;  
        } else if(quest == 99) {
            speech("congrats! you","finish the game");
            draw_game(true);
            wait_ms(300);
            game_over = 1;
        }
        
        return 1;  
    }
    if(item->type == FLOWWINK) {
    // generate a 500Hz tone using PWM hardware output
        speaker.period(1.0/500.0); // 500hz period
        speaker =0.5; //50% duty cycle - max volume
        wait(1);
        speaker=0.0; // turn off audio
        wait(1);
        if(quest == 2) {
            add_flowey_friendly(x, y+1);
            draw_game(true);
            wait_ms(100);
            for(int i = 0; i <2;i++) {
                for(int j = 0; j < 4;j+=2) {
                    speech(flowey_friendly[i][j], flowey_friendly[i][j+1]);
                    draw_game(true);
                }
            }
            draw_nothing(x,y+1);
            draw_game(true);
            wait_ms(100); 
        } else {
            for(int i = 0; i < 4;i+=2) {
                speech(flowey_wink[i], flowey_wink[i+1]);
                draw_game(true);   
            }
            add_flowey_creepy(x, y+1);
            draw_game(true);
            return 1;
        }
        return 1;
    }
    if(item->type == FLOWCREEPY) {
    // generate a 500Hz tone using PWM hardware output
        speaker.period(1.0/500.0); // 500hz period
        speaker =0.5; //50% duty cycle - max volume
        wait(1);
        speaker=0.0; // turn off audio
        wait(1);
 
        if(quest != 2) {
            for(int i = 0; i < 4;i+=2) {
                speech(flowey_creepy[i], flowey_creepy[i+1]);
                draw_game(true);   
            }  
            add_flowey_wink(x, y+1);
            draw_game(true);
            return 1;
        } else {
            add_flowey_friendly(x, y+1);
            draw_game(true);
            wait_ms(100);
            for(int i = 0; i <2;i++) {
                for(int j = 0; j < 4;j+=2) {
                    speech(flowey_friendly[i][j], flowey_friendly[i][j+1]);
                    draw_game(true);
                }
            }  
            draw_nothing(x,y+1);
            draw_game(true);
            wait_ms(100);
        }
        return 1;
    }
    if(item->type == FLOWFRIEND) {
    // generate a 500Hz tone using PWM hardware output
        speaker.period(1.0/500.0); // 500hz period
        speaker =0.5; //50% duty cycle - max volume
        wait(1);
        speaker=0.0; // turn off audio
        wait(1);
        for(int i = 0; i <2;i++) {
            for(int j = 0; j < 4;j+=2) {
                speech(flowey_friendly[i][j], flowey_friendly[i][j+1]);
                draw_game(true);
            }
        }
        wait_ms(100);
        draw_nothing(x,y+1);
        draw_game(true);
        wait_ms(100);
        return 1;
    }
    if(item->type == SIGN) {
        door = 1;
        for(int i = 0; i < 3;i++) {
            for(int j = 0; j < 4;j+=2) {
                speech(sign[i][j], sign[i][j+1]);
                draw_game(true);   
                wait_ms(200);
            }   
        }
        return 1;
    }
    
    if(item->type == DOORLOCKED) {
        if(x == 2) {
            speech("Door locked", "Not a royalty");
            draw_game(true);
            wait_ms(150);
        } else if(x== map_width()-3) {
            speech("You use the","key you just found");
            draw_game(true);
            wait_ms(150);
            add_door_unlocked(x,y+1);
            draw_game(true);
            menu = 2;
        } else {
            if(door == 0) {
                speech("door locked", "read the sign");
                draw_game(true);
                wait_ms(300);
                speech("first to unlock", "this door!"); 
                draw_game(true);
                wait_ms(300);
            } else if(door == 1) {
                speech("You hear the", "door opens");
                draw_game(true);
                wait_ms(150);
                add_door_unlocked(x, y+1);
                draw_game(true);   
            }  
        }
        return 1;
    }
    
    if(item->type == DOORUNLOCKED){
        wait_ms(150); 
        Player.y += 2;
        draw_game(true);
        return 1;
    }
    
    if(item->type == REDBUTTON) {
        if(y+1 == map_height()-38) {
            waver.dac_out();
            speech("uh oh", "wrong one");
            draw_game(true);
            wait_ms(150);
            Player.x = map_width()-35;
            Player.y = map_height()-43;
            draw_game(true);
            health--;
            return 1;
        } else if(y+1 == map_height()-34) {
            speech("uh oh", "wrong one");
            draw_game(true);
            wait_ms(150);
            Player.x = map_width()-35;
            Player.y = map_height()-43;
            draw_game(true);
            health--;
            return 1;
        } else if(y+1 == map_height()-31) {
            speech("You hear", "a click!");
            draw_game(true);
            wait_ms(150);
            Player.y += 3;
            draw_game(true);
        } else if(y+1 == map_height()-27) {
            speech("You hear", "a click!");
            draw_game(true);
            wait_ms(150);
            Player.y += 3;
            draw_game(true);
            wait_ms(300);
    
        }
        return 1;
    }
    if(item->type == GREENBUTTON) {
        if(y+1 == map_height()-38) {
            speech("You hear", "a click!");
            draw_game(true);
            wait_ms(150);
            Player.y += 3;
            draw_game(true);
        } else if(y+1 == map_height()-34) {
            speech("uh oh", "wrong one");
            draw_game(true);
            wait_ms(150);
            Player.x = map_width()-35;
            Player.y = map_height()-43;
            draw_game(true);
            health--;
        } else if(y+1 == map_height()-31) {
            speech("uh oh", "wrong one");
            draw_game(true);
            wait_ms(150);
            Player.x = map_width()-35;
            Player.y = map_height()-43;
            draw_game(true);
            health--;
        } else if(y+1 == map_height()-27) {
            speech("uh oh", "wrong one");
            draw_game(true);
            wait_ms(150);
            Player.x = map_width()-35;
            Player.y = map_height()-43;
            draw_game(true);
            health--;
        }
        return 1;
    }
    if(item->type == BLUEBUTTON) {
        if(y+1 == map_height()-38) {
            speech("uh oh", "wrong one");
            draw_game(true);
            wait_ms(150);
            Player.x = map_width()-35;
            Player.y = map_height()-43;
            draw_game(true);
            health--;
        } else if(y+1 == map_height()-34) {
            speech("You hear", "a click!");
            draw_game(true);
            wait_ms(150);
            Player.y += 3;
            draw_game(true);
        } else if(y+1 == map_height()-31) {
            speech("uh oh", "wrong one");
            draw_game(true);
            wait_ms(150);
            Player.x = map_width()-35;
            Player.y = map_height()-43;
            draw_game(true);
            health--;
        } else if(y+1 == map_height()-27) {
            speech("uh oh", "wrong one");
            draw_game(true);
            wait_ms(150);
            Player.x = map_width()-35;
            Player.y = map_height()-43;
            draw_game(true);
            health--;
        }
        return 1;
    }
    if(item->type == TOBYBONE) {
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 4;j+=2) {
                speech(toby_bone[i][j], toby_bone[i][j+1]);
                draw_game(true);
                wait_ms(150);   
            }   
        }
        map_erase(x,y+1);
        draw_game(true);
        wait_ms(300);
        Player.has_key = 1;
        quest=2;
        
        draw_game(true); 
        wait_ms(300);
        map_erase(x-3, y+2);
        menu = 3;
        return 1;   
    }
    
    if(item->type == RIVERMAN) {
        if(quest == 1) { // head to snowdin
            speech("Tra la la", "Everything is");
            draw_game(true);
            wait_ms(150);
            speech("not how they", "seem to be");
            draw_game(true);
            wait_ms(150);
            menu = 2;
            Player.x = map_width()-36;
            Player.y = map_height()-45;
            draw_game(true);
            wait_ms(150);
        } else if(quest==2) { // got the keys
            speech("Tra la la", "Did I");
            draw_game(true);
            wait_ms(150);
            speech("not warn", "ya...");
            draw_game(true);
            wait_ms(150);
            uLCD.cls();
            Player.x = 5;
            Player.y = 5;
            draw_game(true);
            wait_ms(300);
            quest++;
        } else {
            int index = rand()%15;
            for(int i = 0; i <4;i+=2 ) {
                speech(river_man_line[index][i], river_man_line[index][i+1]);
                draw_game(true);
                wait_ms(150);   
            }
        }   
    }
    return 0;
}

void init_start() {
    GameInputs in = read_inputs();
    draw_start();
    while(in.b1) {
        Timer t; t.start();
        in = read_inputs();
        t.stop();
        int dt = t.read_ms();
        if(dt < 100) wait_ms(100-dt);   
    }
    uLCD.cls();
}

void init_menu(char *a, char *b, int health_count, int key, int chest, int run) {
        GameInputs in = read_inputs();
        draw_menu(a, b, health_count, key, chest, run);  
        uLCD.cls(); 
}

void init_game_over() {
    GameInputs in = read_inputs();
    draw_game_over();
    uLCD.cls();   
}
/**
 * Entry point for frame drawing. This should be called once per iteration of
 * the game loop. This draws all tiles on the screen, followed by the status 
 * bars. Unless init is nonzero, this function will optimize drawing by only 
 * drawing tiles that have changed from the previous frame.
 */
void draw_game(int init)
{
    // Draw game border first
    if(init) draw_border();
    
    // Iterate over all visible map tiles
    for (int i = -5; i <= 5; i++) // Iterate over columns of tiles
    {
        for (int j = -4; j <= 4; j++) // Iterate over one column of tiles
        {
            // Here, we have a given (i,j)
            
            // Compute the current map (x,y) of this tile
            int x = i + Player.x;
            int y = j + Player.y;
            
            // Compute the previous map (px, py) of this tile
            int px = i + Player.px;
            int py = j + Player.py;
                        
            // Compute u,v coordinates for drawing
            int u = (i+5)*11 + 3;
            int v = (j+4)*11 + 15;
            
            // Figure out what to draw
            DrawFunc draw = NULL;
            if (init && i == 0 && j == 0) // Only draw the player on init
            {
                draw_player(u, v, Player.has_key);
                continue;
            }
            else if (x >= 0 && y >= 0 && x < map_width() && y < map_height()) // Current (i,j) in the map
            {
                MapItem* curr_item = get_here(x, y);
                MapItem* prev_item = get_here(px, py);
                if (init || curr_item != prev_item) // Only draw if they're different
                {
                    if (curr_item) // There's something here! Draw it
                    {
                        draw = curr_item->draw;
                    }
                    else // There used to be something, but now there isn't
                    {
                        draw = draw_nothing;
                    }
                }
            }
            else if (init) // If doing a full draw, but we're out of bounds, draw the walls.
            {
                draw = draw_wall;
            }

            // Actually draw the tile
            if (draw) draw(u, v);
        }
    }

    // Draw status bars    
    draw_upper_status(Player.x, Player.y);
    draw_lower_status();
}


/**
 * Initialize the main world map. Add walls around the edges, interior chambers,
 * and plants in the background so you can see motion.
 */
void init_main_map()
{
    // "Random" plants
    Map* map = set_active_map(0);
    
    for(int i = map_width() + 3; i < map_area(); i += 40)
    {
        if((i%map_width() > (map_width()-40)) && (i%map_width() < (map_width()-20))) {
            if((i/map_height() > (map_height()-40)) && (i/map_width() < (map_height()-20))) {
                
            } else {
                add_plant(i % map_width(), i / map_width());
            }   
        } else {
            add_plant(i % map_width(), i / map_width());   
        }
        
        
    }
    pc.printf("plants\r\n");
    
    pc.printf("Adding walls!\r\n");
    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());
    pc.printf("Walls done!\r\n"); 

    add_river_man(1, 3);
    
    add_toby(4, 8);
    add_river_man(map_width()-36,map_height()-44);

    add_wall(map_width()-40, map_height()-40, HORIZONTAL, 20); //add puzzle room
    add_wall(map_width()-40, map_height()-40, VERTICAL, 20);
    add_wall(map_width()-40, map_height()-20, HORIZONTAL, 20);
    add_wall(map_width()-20, map_height()-40, VERTICAL, 20);
    
    add_wall(map_width()-40, map_height()-37, HORIZONTAL,20); // add floor
    add_wall(map_width()-40, map_height()-33, HORIZONTAL,20);
    add_wall(map_width()-40, map_height()-30, HORIZONTAL,20);
    add_wall(map_width()-40, map_height()-26, HORIZONTAL,20);
    
 
    add_red_button(map_width()-37, map_height()-38); // first floor button
    add_green_button(map_width()-31, map_height()-38);
    add_blue_button(map_width()-23, map_height()-38);
    
    add_red_button(map_width()-37, map_height()-34); // second floor button
    add_green_button(map_width()-31, map_height()-34);
    add_blue_button(map_width()-23, map_height()-34);
    
    add_red_button(map_width()-37, map_height()-31); // third floor button
    add_green_button(map_width()-31, map_height()-31);
    add_blue_button(map_width()-23, map_height()-31);
    
    add_red_button(map_width()-37, map_height()-27); // fourth floor button
    add_green_button(map_width()-31, map_height()-27);
    add_blue_button(map_width()-23, map_height()-27);
    
    add_toby_bone(map_width()-23, map_height()-21);
    add_door_locked(map_width()-35, map_height()-40);
    add_sign(map_width()-36, map_height()-41);
    
    add_wall(0, map_height()-5, HORIZONTAL, 5);
    add_wall(5, map_height()-5, VERTICAL, 5);
    
    add_door_locked(3, map_height()-5);
    add_chest(2, map_height()-2);

    print_map();
}

/**
 * Program entry point! This is where it all begins.
 * This function orchestrates all the parts of the game. Most of your
 * implementation should be elsewhere - this holds the game loop, and should
 * read like a road map for the rest of the code.
 */
int main()
{
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");
    init_start();
    // Initialize the maps
    maps_init();
    
    init_main_map();
    
    // Initialize game state
    set_active_map(0);
    Player.x = 5;
    Player.y = 5;

    // Initial drawing
    draw_game(true);

    
    GameInputs in;
    int action;
    int update;
    // Main game loop
    while(!game_over)
    {
        // Timer to measure game update speed
        Timer t; t.start();
        
        // Actuall do the game update:
        // 1. Read inputs    
        in = read_inputs();
        // 2. Determine action (get_action) 
        action = get_action(in);  
        // 3. Update game (update_game)
        update = update_game(action);
        check_health();
        // 3b. Check for game over
        // 4. Draw frame (draw_game)
        draw_game(update);
        // 5. Frame delay
        t.stop();
        int dt = t.read_ms();
        if (dt < 100) wait_ms(100 - dt);
    }
    init_game_over();
}

void check_health() {
    if(health == 0) {
        uLCD.cls();
        init_main_map();
        Player.x = 5;
        Player.y = 5;
        menu = 0; 
        health = 3;
        quest = 0;
        door = 0;
        draw_game(true);
    }
}
int go_up(int x, int y) {
    MapItem *item = get_north(x,y);
    if(item->walkable || omni_pressed) {
        if(run) {
            Player.y -= 2;   
        } else {
            Player.y--;
        }
        return 1;   
    }  else {
        return 0;   
    }
}

int go_down(int x, int y) {
    MapItem *item = get_south(x,y);
    if(item->walkable || omni_pressed) {
        if(run) {
            Player.y += 2;   
        } else {
            Player.y++;
        }
        return 1;   
    } else {
        return 0;   
    }
}

int go_left(int x, int y) {
    MapItem *item = get_west(x,y);
    if(item->walkable || omni_pressed) {
        if(run==1) {
            Player.x -= 2;   
        } else {
            Player.x--;
        }
        return 1;   
    } else {
        return 0;   
    }  
}

int go_right(int x, int y) {
    MapItem *item = get_east(x,y);
    if(item->walkable || omni_pressed) {
        if(run == 1) {
            Player.x += 2;   
        } else {
            Player.x++;
        }
        return 1;   
    } else {
        return 0;   
    }   
}