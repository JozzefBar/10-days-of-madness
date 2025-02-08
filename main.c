#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#define MAX 21
#define MAX_JUNK 20
#define ARMOR_PARTS 4
#define RAND_NUM_1_TO_100 (1 + rand()%100)

const char *roadside_events[] = {                       //random events discovering some junk stuff
        "On the side of the road, you discovered a",
        "At the end of the path, you stumbled upon a piece of",
        "Near the dumpster, you found a segment of",
        "In the middle of the park, you came across a piece of",
        "By the roadside, hidden among the weeds, you uncovered a piece of",
        "Next to the old well, you spotted a piece of",
        "Near the bus stop, you found a piece of",
        "In the middle of the field, you discovered a fragment of",
};

const char *loot_events[] = {           //random events discovering some loot stuff
        "During a walk through abandoned terrain, you noticed a dusty box whose contents weren't immediately clear.\n",
        "While exploring the forest, you came across an old bag that seemed to hold something interesting, though its exact contents remained unknown.\n",
        "Near the coastline, buried beneath the sand, you found a crate whose purpose and contents were uncertain at first glance.\n",
        "On a mountain trail, you stumbled upon a weathered chest, its contents shrouded in mystery until further inspection.\n",
        "By a riverside path, hidden among the rocks, was a duffel bag that appeared to hold valuable items, yet their nature remained ambiguous.\n",
        "Amidst the urban ruins, a battered suitcase lay forgotten, hinting at treasures inside but keeping its secrets well-guarded.\n",
        "In a meadow overlooked by hills, you spotted a nondescript toolbox, suggesting it might hold tools or other surprises within its unassuming exterior.\n",
        "At the edge of a village, you discovered a dusty shoebox partially buried in the ground, promising potential finds that were uncertain upon first glimpse.\n",
        "In an overgrown garden, a hidden chest caught your eye, its purpose and contents raising curiosity as to what lay inside.\n",
        "On a deserted road, a discarded trunk piqued your interest, its locks and hinges holding the promise of unknown treasures within.\n"
};

const char *building_events[] = {               //random events discovering some buildings
        "While traveling through the countryside, you stumbled upon an abandoned building shrouded in mystery.\n",
        "During your journey, you came across a dilapidated house, its walls crumbling and windows shattered.\n",
        "On your way through the forest, you discovered the ruins of an ancient structure, overgrown with vines.\n",
        "As you wandered through the desolate town, you found an old, derelict factory, its machinery rusted and silent.\n",
        "Exploring the remote village, you encountered a forsaken church, its steeple leaning precariously.\n",
        "During your road trip, you spotted a rundown motel, its neon sign flickering weakly.\n",
        "Traveling along the coast, you discovered the ruins of a lighthouse, its light extinguished long ago.\n"
};

const char *zombie_events[] = {         //random events with zombies
        "Encountered a lone zombie and now you have to defend yourself!\n",
        "Came across a zombie unexpectedly and quickly have to prepare to fight!\n",
        "Surprised by a zombie and now have to react swiftly to survive!\n",
        "Came face-to-face with a zombie and now have to fight it off!\n",
        "Encountered a zombie and now have to deal with it alone!\n"
};

//random events with finding something or nothing
const char *loot_find[] = {
        "You discovered a",
        "You found a",
        "You uncovered a"
};

const char *junk_find[] = {
        "You stumbled upon a piece of",
        "you spotted a piece of",
        "you discovered a fragment of"
};

const char *nothing_find[] = {
        "Ultimately, nothing remained.\n",
        "Eventually, there was nothing.\n",
        "In the final outcome, there was nothing.\n"
};

const char *injuries[]= {           //random events with injuries
        "You ended up cutting your hand on a piece of glass. (-10 hp)\n",
        "You fell and scraped your knee on a rock. (-10 hp)\n",
        "You stubbed your toe and it started bleeding. (-10 hp)\n",
        "You stepped on a sharp object and injured your foot. (-10 hp)\n",
        "You got a paper cut on your thumb. (-5 hp)\n",
        "You bumped your head.(-5 hp)\n",
        "You got a splinter in your hand. (-5 hp)\n",
        "You slipped and fell. (-5 hp)\n"
};

//Enums for weapon types, junk, armor part and armor material with lists of items
typedef enum weapon_types{
    NONE,                       //Score points 0
    Pistol,                     //Score points 3
    Submachine,                 //Score points 5
    Machine,                    //Score points 7
} WEAPONS;

const char* weaponNames[] = {
        "Glock",
        "Colt",
        "MP5",
        "Uzi",
        "AK47",
        "M16"
};

typedef enum junk{
    EMPTY, Fruit, Bandage, Cloth,  Fiber, Paper, Glue, Bottle, Spring, Tape
} JUNK;

const char* junkNames[] = {
        "EMPTY",            //Score points 0
        "Fruit",            //Score points 1
        "Bandage",
        "Cloth",            //Score points 2
        "Fiber",
        "Paper",
        "Glue",             //Score points 3
        "Bottle",
        "Spring",           //Score points 4
        "Tape"
};

typedef enum armor_part{
    Helmet,
    Chest,
    Gloves,
    Legs
} ARMOR_PART;

const char* armor_parts_names[] = {
        "Helmet",
        "Chest",
        "Gloves",
        "Legs"
};

typedef enum armor_material{
    NOTHING,                    //Score points 0
    Leather,                    //Score points: Gloves(1) Legs(2) Helmet(3) Chest(5)
    Scrap,                      //Score points: Gloves(2) Legs(4) Helmet(6) Chest(7)
    Steel                       //Score points: Gloves(3) Legs(5) Helmet(7) Chest(8)
} ARMOR_MATERIAL;

const char* armor_materials[] = {
        "NOTHING",
        "Leather",
        "Scrap",
        "Steel"
};

//Structs for time, zombie, armory, weapon, player
typedef struct real_time{
    int day;
    int hour;
    int minutes;
} TIME;

typedef struct zombie{
    int tier;
    int damage;
    int health;
} ZOMBIE;

typedef struct armory{
    ARMOR_PART part;
    ARMOR_MATERIAL material;
    int armor;
} ARMORY;

typedef struct weapon{
    WEAPONS type;
    const char *name;
    int tier;
    int damage;
} WEAPON;

typedef struct player{
    char name[MAX];
    int health;
    int sum_armor;
    JUNK inventory[MAX_JUNK];
    WEAPON weapon;
    ARMORY armory[ARMOR_PARTS];
} PLAYER;

//all functions that are used
void beginning_end(FILE* story, bool end, PLAYER* player);
void replace_substring(const char *buffer, const char *search_for, const char *replace_with, char *result);
void help_text();
void print_name(const char *name);
void print_healtharmor(int health, int armor);
void print_armor(const ARMORY *armory);
void print_weapon(WEAPON weapon);
void print_inventory(const JUNK *inventory);
void use_of_item(PLAYER *player);
int specific_item_position(PLAYER *player, bool inventory_open);
int waitForContinue(PLAYER* player, bool can_leave);
int wrong_option(int option);
void x_second_countdown(int sec);
PLAYER creating_player();
void time_management(TIME *real_time);
JUNK junk_found(bool lootable);
void add_junk_to_inventory(PLAYER *player, JUNK found_junk);
WEAPON create_weapon(PLAYER *player, int rand_weapon);
ARMORY create_armor(PLAYER *player, int rand_armor);
int armor_sum(ARMORY *player_armory);
ZOMBIE zombie_creation(TIME *real_time);
void zombie_fight(PLAYER *player, ZOMBIE *zombie);
int calculateDamage(int baseDamage, int armor);
void game_progress(PLAYER *player, TIME *real_time, int rand_game_event);
void looting_something(PLAYER *player, TIME *real_time, int *option, bool is_building);
void hurt_player(PLAYER *player, int rand_injury_event, bool is_building);
int score_counting(PLAYER *player);
void ending(PLAYER *player);




void replace_substring(const char *buffer, const char *search_for, const char *replace_with, char *result) {    //rewriting player's name in file in the end story
    const char *new_buffer = buffer;
    const char *found;
    while((found = strstr(new_buffer, search_for)) != NULL){
        strncat(result, new_buffer, found - new_buffer);
        strcat(result, replace_with);
        new_buffer = found + strlen(search_for);

    strcat(result, new_buffer);
    }
}

void beginning_end(FILE* story, bool end, PLAYER* player){              //story from beginning and ending from file
    char buffer[256];
    while(fgets(buffer, 255, story) != NULL){
        const char* search_for = "*name";
        char *found = strstr(buffer, search_for);
        if (found && end == true){
            char *result = (char *)malloc(strlen(buffer) - strlen(search_for) + strlen(player->name) + 1);
            if (!result) {
                perror("Memory allocation failed");
                return;
            }
            result[0] = '\0';
            replace_substring(buffer, search_for, player->name, result);

            for(int i = 0; i < strlen(result); i++){
                putchar(result[i]);
                fflush(stdout);
                Sleep(1);
                //Sleep(60);
            }
            free(result);
        }
        if(end == false || !found){
            for(int i = 0; i < strlen(buffer); i++){
                putchar(buffer[i]);
                fflush(stdout);
                Sleep(1);
                //Sleep(60);
            }
        }
        if(end == true) {
            fflush(stdout);
            printf("Next: ");
            waitForContinue(NULL, false);
        }
    }
}

void help_text(){               //help option with input "h"
    char buffer[256];
    FILE* help_file = fopen("help.txt", "r");
    while(fgets(buffer, 255, help_file) != NULL)
        printf("%s", buffer);
    fclose(help_file);
}

void print_inventory(const JUNK *inventory){        //option with input "i"
    printf("\n");
    for(int i = 0; i < MAX_JUNK; i++){
        printf("   %i: %s%7s    %s", i + 1,  i < 9 ? " ": "", junkNames[inventory[i]], (i + 1)%5 == 0 ? "\n": " ");
    }
}

void print_armor(const ARMORY *armory){         //option with input "r"
    printf("\n");
    for(int i = 0; i < ARMOR_PARTS; i++){
        printf("   %s: %s\n       Armor: %i\n", armor_parts_names[i], armor_materials[armory[i].material], armory[i].armor);
    }
}

void print_weapon(const WEAPON weapon){         //option with input "w"
    printf("\n   Type: %s\n   Name: %s\n   Tier: %i\n   Damage: %i\n", weapon.type == NONE ? "NONE": weapon.type == Pistol ? "Pistol" :
                                                                    weapon.type == Submachine ? "Submachine" : "Machine",
                                                                    weapon.name, weapon.tier, weapon.damage);
}

void print_name(const char *name){              //option with input "n"
    printf("\n   Name: %s\n", name);
}

void print_healtharmor(const int health, const int armor){          //option with input "a"
    printf("\n   Health: %i      Armor: %i\n", health, armor);
}

int specific_item_position(PLAYER *player, bool inventory_open){        //function that check if the number is from 1 to 20
    int position;
    while (1) {
        if (scanf("%d", &position) != 1) {
            printf("Invalid input. Please enter a number: ");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if(position == -2 && inventory_open == true) {      //you can open the inventory again if you are in option where you want to replace item in inventory
            print_inventory(player->inventory);
            printf("\nEnter a number:");
        }
        else if(position >= 1 && position <= 20) break;
        else if(position == -1) return 'l';
        else printf("Invalid position. Please enter a number between 1 and 20.: ");
    }
    return position;
}

void use_of_item(PLAYER *player){               //function that allows user to use item
    printf("Put a number of item you want to use (-1 to leave inventory): ");
    while(1){
        int item_position = specific_item_position(player, false);
        int heal;
        if(item_position == 'l') return;
        else if(player->inventory[item_position - 1] == Fruit){                 // + 5 hp
            heal = player->health + 5 <= 100 ? 5 : 100 - player->health;
            printf("\nYou healed yourself for %dhp.\n", heal);
            player->inventory[item_position - 1] = EMPTY;
            player->health += heal;
            break;
        }
        else if(player->inventory[item_position - 1] == Bandage){               // + 10 hp
            heal = player->health + 10 <= 100 ? 10 : 100 - player->health;
            printf("\nYou healed yourself for %dhp.\n", heal);
            player->inventory[item_position - 1] = EMPTY;
            player->health += heal;
            break;
        }
        else {
            printf("Nothing can be done with this item, choose another one or leave the inventory (put -1)\n");
            printf("\nInput: ");
        }
    }
}

int wrong_option(int option){               //function to find if the input is incorrect
    return (option == 'q' || option == 'c' || option == 'l' || option == 'h' || option == 'i' || option == 'r' || option == 'w' || option == 'n' || option == 'a' || option == 'e') ? 1: 0;
}

int waitForContinue(PLAYER* player, bool can_leave) {       //function that takes input and put some result
    int option;
    do {
        option = getchar();
        while (getchar() != '\n');

        option = tolower(option);
        if(option == 'q') exit(1);
        else if (option == 'c') return 1;
        else if (option == 'l' && can_leave == true) return 0;
        else if(option == 'h' && player != NULL) help_text();
        else if(option == 'i' && player != NULL) {
            print_inventory(player->inventory);
            printf("\nDo you want to use any item?: ");
            if(waitForContinue(NULL, true)) use_of_item(player);
        }
        else if(option == 'r' && player != NULL) print_armor(player->armory);
        else if(option == 'w' && player != NULL) print_weapon(player->weapon);
        else if(option == 'n' && player != NULL) print_name(player->name);
        else if(option == 'a' && player != NULL) print_healtharmor(player->health, player->sum_armor);
        else if(option == 'e' && player != NULL){
            printf("\n");
            print_name(player->name);
            print_healtharmor(player->health, player->sum_armor);
            print_weapon(player->weapon);
            print_armor(player->armory);
            print_inventory(player->inventory);
        }
        else if (wrong_option(option)) printf("You cannot use this shortcut now.\n");
        else printf("Invalid input. Please try again.\n");
        printf("\nAnother input: ");
    } while(1);
}

PLAYER creating_player(){           //function creating player
    PLAYER player;
    char buffer[100];

    printf("Enter a name (length max. 20): ");
    fgets(buffer, 99, stdin);
    if (strlen(buffer) >= MAX) {
        printf("The name is too long. Please enter a shorter name (max. 20 characters).\n");
        return creating_player();
    }

    buffer[strcspn(buffer, "\n")] = '\0';
    strcpy(player.name, buffer);

    player.health = 100;
    for(int i = 0; i < MAX_JUNK; i++){
        player.inventory[i] = EMPTY;
    }
    player.weapon.type = NONE;
    player.weapon.name = "Fist";
    player.weapon.tier = 0;
    player.weapon.damage = 3;
    for(int i = 0; i < ARMOR_PARTS; i++){
        player.armory[i].part = (ARMOR_PART)i;
        player.armory[i].material = NOTHING;
        player.armory[i].armor = 0;
    }
    player.sum_armor = 0;

    return player;
}

void x_second_countdown(int sec){            //function for countdown from x seconds
    for(int i = sec; i > 0; i--){
        printf("%i.. ", i);
        fflush(stdout);
        Sleep(1000);
    }
    Sleep(500);
}

void time_management(TIME *real_time){        //function working on time management
    real_time->minutes += 20;
    if(real_time->minutes == 60) {
        real_time->hour++;
        real_time->minutes = 0;
    }
    if(real_time->hour == 23){
        printf("Time for sleep. Next day starts in \n");
        x_second_countdown(5);

        system("clear");
        real_time->day++;
        real_time->hour = 7;
    }
}

void add_junk_to_inventory(PLAYER *player, JUNK found_junk){    //function that add junk to inventory or replace some junk with another
    int position = -1;
    for(int i = 0; i < MAX_JUNK; i++){
        if(player->inventory[i] == EMPTY){
            position = i + 1;
            break;
        }
    }
    if(position == -1){
        printf("Your inventory is full. Enter a position between 1 and 20 to replace an item (if you want to see your inventory (put '-2') or leave (put -1)): ");
        position = specific_item_position(player, true);
    }
    if(position == 'l') return;
    if(player->inventory[position - 1] == EMPTY)
        printf("Successfully added %s to the inventory at position %d\n", junkNames[found_junk], position);
    else
        printf("Successfully added %s to the inventory at position %d replacing %s\n", junkNames[found_junk], position, junkNames[player->inventory[position - 1]]);
    player->inventory[position - 1] = found_junk;
}

JUNK junk_found(bool lootable){             //creating random junk with random junk event
    JUNK found_junk = (JUNK) 1 + rand()%9;
    if(lootable == false) printf("\n%s %s\n", roadside_events[rand()%8], junkNames[found_junk]);
    else printf("\n%s %s.\n", junk_find[rand()%3], junkNames[found_junk]);
    printf("Do you want to add this junk to your inventory?: ");
    return found_junk;
}

ZOMBIE zombie_creation(TIME *real_time){        //creating zombie based on your day
    ZOMBIE zombie;
    if(real_time->day < 3) zombie.tier = 1;
    else if(real_time->day == 3) zombie.tier = 1 + rand()%2;            //I or II
    else if(real_time->day > 3 && real_time->day < 5) zombie.tier = 2;
    else if(real_time->day == 5) zombie.tier = 2 + rand()%2;            //II or III
    else if(real_time->day > 5 && real_time->day < 7) zombie.tier = 3;
    else if(real_time->day == 7) zombie.tier = 3 + rand()%2;            //III or IV
    else if(real_time->day > 7 && real_time->day < 9) zombie.tier = 4;
    else if(real_time->day == 9) zombie.tier = 4 + rand()%2;            //IV or V
    else zombie.tier = 5;

    if(zombie.tier == 1){
        zombie.health = 10;
        zombie.damage = 1 + rand()%3;       //1 - 3 dmg
    }
    else if(zombie.tier == 2) {
        zombie.health = 15;
        zombie.damage = 3 + rand()%6;       //3 - 8 dmg
    }
    else if(zombie.tier == 3) {
        zombie.health = 25;
        zombie.damage = 7 + rand()%6;       //7 - 12 dmg
    }
    else if(zombie.tier == 4) {
        zombie.health = 35;
        zombie.damage = 10 + rand()%9;      //10 - 18 dmg
    }
    else  {
        zombie.health = 50;
        zombie.damage = 17 + rand()%9;      //17 - 25 dmg
    }
    return zombie;
}

int calculateDamage(int baseDamage, int armor){     //calculating damage reduction based on your armor
    double damageReduction = armor*0.01;        //1% per 1 armor
    double reducedDamage = baseDamage*(1 - damageReduction);
    return (int)round(reducedDamage);
}

void zombie_fight(PLAYER *player, ZOMBIE *zombie){      //simulation of zombie fight
    printf("Prepare for fight!\n");
    Sleep(2000);
    printf("Are you ready for fight?: ");
    waitForContinue(player, false);
    printf("\n %20s's health: %3d               %3d :Zombie's health", player->name, player->health, zombie->health);
    printf("\n %20s    Armor: %3d               %3d :Tier", "", player->sum_armor, zombie->tier);
    printf("\n %20s   Damage: %3d               %3d :Damage\n", "", player->weapon.damage, zombie->damage);
    Sleep(1000);
    printf("\n  The fight starts in ");
    x_second_countdown(3);
    printf("\n");
    while (player->health > 0 && zombie->health > 0){
        zombie->health -= player->weapon.damage;
        printf("\n %20sYou hit him for %d damage. Zombie's health is %d", "", player->weapon.damage, zombie->health);
        Sleep(500);
        if(zombie->health > 0) {
            int ReceivedDamaged = calculateDamage(zombie->damage, player->sum_armor);
            player->health -= ReceivedDamaged;
            printf("\n %20sYou received %d damage. Your health is %d", "", ReceivedDamaged, player->health);
        }
        else break;
        printf("\n  Next move: ");
        waitForContinue(player, false);
    }
    if (player->health > 0) printf("\n\n  You killed the zombie!!!\n\n");
}

WEAPON create_weapon(PLAYER *player, int rand_weapon){          //creating random weapon based on probability with random loot_event, optionally you can replace your weapon
    WEAPON new_weapon;
    if(rand_weapon > 85) new_weapon.type = Machine;                 //15% for Machine
    else if(rand_weapon > 50) new_weapon.type = Submachine;         //35% for Submachine
    else new_weapon.type = Pistol;                                  //50% for Pistol

    new_weapon.name = new_weapon.type == Machine ? weaponNames[4 + rand()%2] : new_weapon.type == Submachine ? weaponNames[2 + rand()%2] : weaponNames[rand()%2];
    new_weapon.tier = new_weapon.type == Machine ? 3 :  new_weapon.type == Submachine ? 2 : 1;
    new_weapon.damage = new_weapon.type == Machine ? 14 + rand()%8 : new_weapon.type == Submachine ? 9 + rand()%6 : 3 + rand()%6;

    printf("%s %s (%d DMG)!\n", loot_find[rand()%3], new_weapon.name, new_weapon.damage);
    if(strcmp(player->weapon.name, "Fist") != 0) printf("\nDo you want to replace your %s (%d DMG) with this new %s (%d DMG)?: ", player->weapon.name, player->weapon.damage, new_weapon.name, new_weapon.damage);
    else printf("\nDo you want to equip %s?: ", new_weapon.name);

    return new_weapon;
}

ARMORY create_armor(PLAYER *player, int rand_armor){                  //creating random armor part based on probability with random loot_event, optionally you can replace your armor part
    ARMORY new_armor;                                                             //ARMOR                                //Steel     //Scrap     //Leather
    new_armor.part = (ARMOR_PART)rand()%ARMOR_PARTS;                                                        //Helmet        18          13          5
    if(rand_armor > 85) new_armor.material = Steel;                    //15% for steel material             //Chest         21          15          7
    else if(rand_armor > 50) new_armor.material = Scrap;               //35% for scrap material             //Gloves        12          9           3
    else new_armor.material = Leather;                                 //50% for leather material           //Legs          15          10          4

    if(new_armor.material == Steel) new_armor.armor = new_armor.part == Helmet ? 18 : new_armor.part == Chest ? 21 : new_armor.part == Gloves ? 12 : 15;
    else if(new_armor.material == Scrap) new_armor.armor = new_armor.part == Helmet ? 13 : new_armor.part == Chest ? 15 : new_armor.part == Gloves ? 9 : 10;
    else new_armor.armor = new_armor.part == Helmet ? 5 : new_armor.part == Chest ? 7 : new_armor.part == Gloves ? 3 : 4;

    printf("%s %s %s (%d armor)!\n", loot_find[rand()%3], armor_materials[new_armor.material], armor_parts_names[new_armor.part], new_armor.armor);
    if(player->armory[new_armor.part].material != NOTHING) printf("\nDo you want to replace your %s %s (%d armor) with new %s %s (%d armor)?: ",
                                                           armor_materials[player->armory[new_armor.part].material], armor_parts_names[player->armory[new_armor.part].part], player->armory[new_armor.part].armor,
                                                           armor_materials[new_armor.material], armor_parts_names[new_armor.part], new_armor.armor);
    else printf("\nDo you want to clothe %s %s?: ",  armor_materials[new_armor.material], armor_parts_names[new_armor.part]);

    return new_armor;
}

int armor_sum(ARMORY *player_armory){       //function for the amount armor you have
    int sum = 0;
    for(int i = 0; i < ARMOR_PARTS; i++)
        sum += player_armory[i].armor;
    return sum;
}

void hurt_player(PLAYER *player, int rand_injury_event, bool is_building){          //function that create injury for player, probability is based on if you are in building or not
    if((rand_injury_event > 70 && is_building == false) || (rand_injury_event > 40 && is_building == true)) {           //critical injury - 10hp: 30% (object) ---- 60% (building)
        printf("%s", injuries[rand()%4]);
        player->health -= 10;
    }
    else {                                                                                                              //normal injury - 5hp: 70% (object) ---- 40% (building)
        printf("%s", injuries[4 + rand()%4]);
        player->health -= 5;
    }
}

void looting_something(PLAYER *player, TIME *real_time, int *option, bool is_building){         //number of things you find in loot with some nothing_find event at the end
    int num_of_things = is_building == false ? rand()%3 : 1 + rand()%4;             //lootable object 0 - 2 items, building 1 - 4 items
    if (num_of_things == 0) {
        printf("%s\n", nothing_find[rand()%3]);
        return;
    }

    while(num_of_things > 0 && player->health > 0 && *option){                  //probability for things you find or injury or finding a zombie based on where you are (in building or if it is some object)
        int rand_gen_case = RAND_NUM_1_TO_100;                                     //90% item, 10% injury (object) --- 75% item 12% injury 13% zombie encounter (building)
        if((rand_gen_case > 80 && is_building == false) || (rand_gen_case > 70 && is_building == true)){                //20% gun (object) ---- 30% gun (building)
            WEAPON new_weapon = create_weapon(player, RAND_NUM_1_TO_100);
            *option = waitForContinue(player, true);
            if(*option) player->weapon = new_weapon;
        }
        else if((rand_gen_case > 50 && is_building == false) || (rand_gen_case > 35 && is_building == true)){           //30% armor (object) ---- 35% armor (building)
            ARMORY new_armor = create_armor(player, RAND_NUM_1_TO_100);
            *option = waitForContinue(player, true);
            if(*option){
                player->armory[new_armor.part] = new_armor;
                player->sum_armor = armor_sum(player->armory);
            }
        }
        else if((rand_gen_case > 10 && is_building == false) || ((rand_gen_case > 25 && is_building == true))){         //40% junk (object) ---- 10% junk (building)
            JUNK junk = junk_found(true);
            *option = waitForContinue(player, true);
            if(*option) add_junk_to_inventory(player, junk);
        }
        else if(rand_gen_case > 13 && is_building == true){                                                             //13% zombie encounter (building)
            printf("\n%s", zombie_events[rand()%5]);
            ZOMBIE zombie = zombie_creation(real_time);
            zombie_fight(player, &zombie);
        }
        else hurt_player(player, RAND_NUM_1_TO_100, is_building);                                         //10% injury (object) ---- 12% injury (building)

        num_of_things--;
        printf("\nDo you want to continue in searching?: ");
        *option = waitForContinue(player, true);
    }
    if (*option) printf("There was nothing else useful :(.\n\n");
}

void game_progress(PLAYER *player, TIME *real_time, int rand_game_event){           //function that chooses what will happen in game
    if(player->health < 100 && real_time->minutes == 0) player->health++;

    int option;
    if(rand_game_event >= 0 && rand_game_event <= 5){                                       //finding junk in environment (5%)
        JUNK junk = junk_found(false);
        option = waitForContinue(player, true);
        if(option) add_junk_to_inventory(player, junk);
    }
    else if(rand_game_event >= 6 && rand_game_event <= 11){                                 //finding loot in environment (interaction) (6%)
        printf("\n%s", loot_events[rand()%10]);
        printf("Do you want to check it out?: ");
        option = waitForContinue(player, true);
        if(option) looting_something(player, real_time, &option, false);
    }
    else if(rand_game_event >= 12 && rand_game_event <= 18){                                //building (interaction) (7%)  -- + 2 hours of time
        if((real_time->hour < 21 && (real_time->day != 10 || real_time->hour < 16))) {
            printf("\n%s", building_events[rand() % 7]);
            printf("Do you want to explore it? (It takes 2 HOURS!): ");
            option = waitForContinue(player, true);
            if (option) {
                looting_something(player, real_time, &option, true);
                real_time->hour += 2;
            }
        }
        else {
            printf("\nYou found an interesting place, but there's no time left to explore it today.\n");        //if there is no time for exploring
            printf("You need to find a place to rest for the night.\n");
        }
    }
    else if(rand_game_event >= 18 && rand_game_event <= 25){                                //zombie encounter (8%)
        printf("\n%s", zombie_events[rand()%5]);
        ZOMBIE zombie = zombie_creation(real_time);
        zombie_fight(player, &zombie);
    }
}

int score_counting(PLAYER *player){             //function counting score based on items, weapon tier and armor you find
    int junk_score = 0, weapon_score = 0, armor_score = 0;
    for(int i = 0; i < MAX_JUNK; i++){
        if(player->inventory[i] != EMPTY){                                                                                              //Empty slot 0
            if(player->inventory[i] == Bandage || player->inventory[i] == Fruit) junk_score += 1;                                       //Bandage, Fruit: 1
            else if(player->inventory[i] == Cloth || player->inventory[i] == Fiber || player->inventory[i] == Paper) junk_score += 2;   //Cloth, Fiber, Paper: 2
            else if(player->inventory[i] == Glue || player->inventory[i] == Bottle) junk_score += 3;                                    //Glue, Bottle: 3
            else if(player->inventory[i] == Spring || player->inventory[i] == Tape) junk_score += 4;                                    //Spring, Tape: 4
        }
    }

    weapon_score += player->weapon.tier == 0 ? 0 : player->weapon.tier == 1 ? 3 : player->weapon.tier == 2 ? 5 : 7;     //Weapon tier (0: 0, 1: 3, 2: 5, 3: 7)

    for(int i = 0; i < ARMOR_PARTS; i++){
        if(player->armory[i].material == NOTHING) armor_score += 0;                                                                                         //No armor: 0
        else if(player->armory[i].part == Gloves) armor_score += player->armory[i].material == Leather ? 1 : player->armory[i].material == Scrap ? 2 : 3;   //Gloves (Leather: 1, Scrap: 2, Steel: 3)
        else if(player->armory[i].part == Legs) armor_score += player->armory[i].material == Leather ? 2 : player->armory[i].material == Scrap ? 4 : 5;     //Legs (Leather: 2, Scrap: 4, Steel: 5)
        else if(player->armory[i].part == Helmet) armor_score += player->armory[i].material == Leather ? 3 : player->armory[i].material == Scrap ? 5 : 7;   //Helmet (Leather: 3, Scrap: 5, Steel: 7)
        else if(player->armory[i].part == Chest) armor_score += player->armory[i].material == Leather ? 5 : player->armory[i].material == Scrap ? 7 : 8;    //Chest (Leather: 5, Scrap: 7, Steel: 8)
    }

    printf("\nYour collected junk has value: %d\n", junk_score);
    printf("Your collected weapon has value: %d\n", weapon_score);
    printf("Your collected Armory has value: %d\n", armor_score);

    return junk_score + weapon_score + armor_score;
}

void ending(PLAYER *player){        //the end story
    if(player->health > 0){
        Sleep(1000);
        printf("You have arrived at the location. To continue put 'c': ");
        waitForContinue(NULL, false);
        system("clear");

        FILE* ending_file = fopen("ending.txt", "r");
        beginning_end(ending_file, true, player);
        fclose(ending_file);

        printf("\nTo see your score put 'c' key: ");
        waitForContinue(NULL, false);
        system("clear");
        int sum_score = score_counting(player);
        printf("\nYOUR SCORE IS %d!! CONGRATULATION!\n", sum_score);
        printf("\nIf you want to review all your belongings at the end, you have one last chance.: ");
        waitForContinue(player, false);
    }
    else printf("\nYOU DIED!!!\n");         //if your health is 0 or below
    printf("\nTHANK YOU FOR PLAYING :)\nThe game ends in: ");
    x_second_countdown(5);
}

int main() {
    printf("PUT 'C' KEY TO START THE GAME: ");          //start of the game
    waitForContinue(NULL, false);
    system("clear");

    FILE* story = fopen("beginning.txt", "r");     //beginning story
    if(story == NULL) {
        printf("There is an error with the story, restart the game and try again!");
        return 0;
    }
    beginning_end(story, false, NULL);
    fclose(story);

    waitForContinue(NULL, false);

    //creating player and the real start of the game
    printf("\nCreating player...\n");
    PLAYER player = creating_player();
    printf("Player created. Name: %s\n", player.name);
    printf("\nTo understand how to progress in game, put 'h' (if you understand everything put 'c'): ");

    waitForContinue(&player, false);
    printf("\nJOURNEY BEGGINS!!! ");
    x_second_countdown(5);

    system("clear");
    TIME real_time = {1,7,0};               //Game time at the start
    srand(time(NULL));                              //For random everytime

    int rand_game_event;
    while((real_time.day != 10 || real_time.hour != 18) && player.health > 0){      //the whole game progress
        if(real_time.day == 10 && real_time.hour == 7) printf("You are almost there! You should arrive there by this evening\n");
        printf("Day %i. %0.2i:%0.2i Input: ", real_time.day, real_time.hour, real_time.minutes);
        waitForContinue(&player, false);
        rand_game_event = RAND_NUM_1_TO_100;
        game_progress(&player, &real_time, rand_game_event);
        time_management(&real_time);
    }
    ending(&player);            //end story
    return 0;
}