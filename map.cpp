#include "map.h"

#include "globals.h"
#include "graphics.h"

/**
 * The Map structure. This holds a HashTable for all the MapItems, along with
 * values for the width and height of the Map.
 */
struct Map {
    HashTable* items;
    int w, h;
};

/**
 * Storage area for the maps.
 * This is a global variable, but can only be access from this file because it
 * is static.
 */
static Map map;
static int active_map;

/**
 * The first step in HashTable access for the map is turning the two-dimensional
 * key information (x, y) into a one-dimensional unsigned integer.
 * This function should uniquely map (x,y) onto the space of unsigned integers.
 */
static unsigned XY_KEY(int X, int Y) {
    return X*(map.h)+Y;
}

/**
 * This is the hash function actually passed into createHashTable. It takes an
 * unsigned key (the output of XY_KEY) and turns it into a hash value (some
 * small non-negative integer).
 */
unsigned map_hash(unsigned key)
{
    return key%NUMBUCKETS;
}

void maps_init()
{
    
    map.items = createHashTable(map_hash, NUMBUCKETS);
    map.w = WIDTH;
    map.h = HEIGHT;
}

Map* get_active_map()
{
    return &map;
}

Map* set_active_map(int m)
{
    active_map = m;
    return &map;
}

void print_map()
{
    // As you add more types, you'll need to add more items to this array.
    char lookup[] = {'W', 'P'};
    for(int y = 0; y < map_height(); y++)
    {
        for (int x = 0; x < map_width(); x++)
        {
            MapItem* item = get_here(x,y);
            if (item) pc.printf("%c", lookup[item->type]);
            else pc.printf(" ");
        }
        pc.printf("\r\n");
    }
}

int map_width()
{
    Map *map = get_active_map();
    return map->w;
}

int map_height()
{
    Map *map = get_active_map();
    return map->h;
}

int map_area()
{
    Map* map = get_active_map();
    return (map->h * map->w);
}

MapItem* get_north(int x, int y)
{
    Map *map = get_active_map();
    int key = XY_KEY(x, y-1);
    return (MapItem*)getItem(map->items, key);
}

MapItem* get_south(int x, int y)
{
    Map *map = get_active_map();
    int key = XY_KEY(x, y+1);
    return (MapItem*)getItem(map->items, key);
}

MapItem* get_east(int x, int y)
{
    Map *map = get_active_map();
    int key = XY_KEY(x+1, y);
    return (MapItem*)getItem(map->items, key);
}

MapItem* get_west(int x, int y)
{
    Map *map = get_active_map();
    int key = XY_KEY(x-1, y);
    return (MapItem*)getItem(map->items, key);
}

MapItem* get_here(int x, int y)
{
    Map *map = get_active_map();
    int key = XY_KEY(x, y);
    return (MapItem*)getItem(map->items, key);
}


void map_erase(int x, int y)
{
    Map *map = get_active_map();
    int key = XY_KEY(x, y);
    deleteItem(map->items, key);
}

void add_wall(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        
        MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1->type = WALL;
        w1->draw = draw_wall;
        w1->walkable = false;
        w1->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, w1);
        if (val)free(val); // If something is already there, free it
    }

}

void add_plant(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = FLOWWINK;
    w1->draw = draw_flowey_wink;
    w1->walkable = false;
    w1->data = NULL;

    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_sign(int x, int y) {
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = SIGN;
    w1->draw = draw_sign;
    w1->walkable = false;
    w1->data = NULL;

    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val);    
}

void add_door_locked(int x, int y) {
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = DOORLOCKED;
    w1->draw = draw_door_locked;
    w1->walkable = false;
    w1->data = NULL;

    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val);    
}

void add_door_unlocked(int x, int y) {
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = DOORUNLOCKED;
    w1->draw = draw_door_unlocked;
    w1->walkable = false;
    w1->data = NULL;

    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val);    
}


void add_flowey_friendly(int x, int y) {
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = FLOWFRIEND;
    w1->draw = draw_flowey_friendly;
    w1->walkable = false;
    w1->data = NULL;

    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val);    
}

void add_flowey_wink(int x, int y) {
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = FLOWWINK;
    w1->draw = draw_flowey_wink;
    w1->walkable = false;
    w1->data = NULL;

    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val);    
}

void add_flowey_creepy(int x, int y) {
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = FLOWCREEPY;
    w1->draw = draw_flowey_creepy;
    w1->walkable = false;
    w1->data = NULL;

    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); 
}

void add_toby(int x, int y) {
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = TOBY;
    w1->draw = draw_toby;
    w1->walkable = false;
    w1->data = NULL;

    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val);    
}

void add_toby_bone(int x, int y) {
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = TOBYBONE;
    w1->draw = draw_toby_bone;
    w1->walkable = false;
    w1->data = NULL;

    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val);     
}

void add_red_button(int x, int y) {
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = REDBUTTON;
    w1->draw = draw_red_button;
    w1->walkable = false;
    w1->data = NULL;

    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); 
}

void add_green_button(int x, int y) {
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = GREENBUTTON;
    w1->draw = draw_green_button;
    w1->walkable = false;
    w1->data = NULL;

    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val);    
}

void add_blue_button(int x, int y) {
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = BLUEBUTTON;
    w1->draw = draw_blue_button;
    w1->walkable = false;
    w1->data = NULL;

    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val);     
}

void add_river_man(int x, int y) {
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = RIVERMAN;
    w1->draw = draw_river_man;
    w1->walkable = false;
    w1->data = NULL;

    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val);    
}

void add_chest(int x, int y) {
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = CHEST;
    w1->draw = draw_chest;
    w1->walkable = false;
    w1->data = NULL;

    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val);     
}
void add_leaf(int x, int y) {
     MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = LEAF;
    w1->draw = draw_leaf;
    w1->walkable = true;
    w1->data = NULL;

    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val);    
}
void add_wood(int x, int y) {
     MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = WOOD;
    w1->draw = draw_wood;
    w1->walkable = false;
    w1->data = NULL;

    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val);    
}
// add toby, tobybone, riverman, doorlocked, doorunlocked, 