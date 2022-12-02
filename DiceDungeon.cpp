#include <iostream>
#include <string>
#include <time.h>
#include <Windows.h>
#include <Wincon.h>
#define BACKGROUND_BLACK

//namespaces
using std::cout;
using std::cin;
using std::endl;
using std::string;

//classes
class character
{
public:

    string name;
    int money = 0;

    int hp = 0;
    int current_hp = 0;
    string Attack_dices_types = "null";
    int Attack_dices_number = 0;
    string defensive_dices_types = "null";
    int defensive_dices_number = 0;
    int speed = 0;

    string Weapon_name = "Not Equiped";
    string Weapon_Attack_dices_types = "null";
    int Weapon_Attack_dices_number = 0;
    string Weapon_defensive_dices_types = "null";
    int Weapon_defensive_dices_number = 0;
    int Weapon_speed = 0;
};
class inventory_slot
{
public:
    bool en_uso = false;
    int quantity = 0;
    int heal_hp = 0;
    string item_name = "null";
    string type = "null";
    string item_description = "null";
    int price = 0;

    //weapons info
    string Weapon_name = "null";
    string Weapon_Attack_dices_types = "null";
    int Weapon_Attack_dices_number = 0;
    string Weapon_defensive_dices_types = "null";
    int Weapon_defensive_dices_number = 0;
    int Weapon_speed = 0;



};
class monster
{
public:
    string name;
    string description;

    int hp = 0;
    int current_hp = 0;
    string Attack_dices_types = "null";
    int Attack_dices_number = 0;
    string defensive_dices_types = "null";
    int defensive_dices_number = 0;
    int speed = 0;


};
class weapons
{
public:

    string name = "null";
    string type = "weapons";
    string description = "null";
    int price = 0;

    string Attack_dices_types = "null";
    int Attack_dices_number = 0;
    string defensive_dices_types = "null";
    int defensive_dices_number = 0;
    int speed = 0;



};
class potions
{
public:

    bool en_uso = false;
    int quantity = 0;
    int heal_hp = 0;
    string item_name = "null";
    string type = "Potion";
    string item_description = "null";
    int price = 0;
};
class events
{
public:
    string event_type = "null";
    string event_description = "null";
    string enemy_type = "null";
    int enemy_quantity = 0;
    int event_porcentage = 0;
    int enemy_dificulty = 0;
    bool in_use = false;
};


//funtions
void seed();
int playing();

//void Inventory(inventory_slot** inventory, character* player);
void generate_weapon_stats(weapons* weapons);
void generate_character_stats(character* player, weapons* weapons, inventory_slot* inventory_item);
void generate_event_type(events* events);
void generate_event(events* events);
void logo(HANDLE a);
void hp(int hp, int current_hp);
void show(inventory_slot* inventory_item);
void show_events(events* events);
void equip(inventory_slot* inventory_item, character* player);
void take_weapons(weapons* weapons, inventory_slot* inventory_item);
void take_potion(potions* potion, inventory_slot* inventory_item);
void use_potion(inventory_slot* inventory_item, character* player);
void drop(inventory_slot* inventory_item, character* player);
void shop(character* player, inventory_slot* inventory_item);
void rest(character* player, inventory_slot* Inventory_slots);
void loot(character* player, inventory_slot* Inventory_slots);
void generate_enemy_stats(events* events, monster* enemy);
int battle(events* events, monster* enemy, character* jugador, inventory_slot* inventory_items);
//var

//el juego es basado en dados, los ataques van de uno en uno intercalados. Hay armas que tiren un solo dado pero golpeen muy fuerte
//o armas rapidas que golpeen muchas veces. esto tambien va basado en la velocidad, mientras mas velocidad mas ataques lanzaras
//antes que el enemigo

int main()
{

    HANDLE myColors = GetStdHandle(STD_OUTPUT_HANDLE);
    character player;
    bool is_menu = true;
    char option = 0;

    {
        //Intro
        {
            cout << "|------------Dice Dungeons------------|\n";
            logo(myColors);
            cout << endl;
            cout << "---------------------------------------\n";
            system("pause");
            system("cls");
        }

        //Menu >Start >tutorial >close Game
        while (is_menu)
        {
            option = 0;
            cout << "[Menu]\n\n";
            cout << "1) Start\n" << "2) Tutorial (Not available)\n" << "3) Close Game\n";

            cout << "\nOption: ";
            cin >> option;

            switch (option)
            {
            case '1':
                playing();
                break;
            case '2':
                ;
                break;
            case '3':
                is_menu = false;
                break;
            default:
                cout << "error\n";
                system("pause");
                system("cls");
                break;
            }
        }




    }

}

void seed()
{
    srand(time(0));
}

void generate_weapon_stats(weapons* weapons)
{

    string weapon_class;
    string weapon_class_array[3]{ "Sword","Dagger","Bow" };
    weapons->type = "weapons";
    if (weapons->name == "null")
    {
        weapon_class = weapon_class_array[rand() % 3];
    };
    if (weapons->name == "Sword") { weapon_class = "Sword"; }
    if (weapons->name == "Dagger") { weapon_class = "Dagger"; }
    if (weapons->name == "Bow") { weapon_class = "Bow"; }

    if (weapon_class == "Sword")
    {
        int rarity = rand() % 100 + 1;

        weapons->name = weapon_class;
        weapons->Attack_dices_types = "Heavy";
        weapons->defensive_dices_types = "Shield";
        if (rarity > 90)
        {
            weapons->name.insert(0, "Legendary ");
            weapons->description = { "A shiny and sharp Long Swords. Is quite heavy." };
            weapons->Attack_dices_number = 2;
            weapons->defensive_dices_number = 2;
            weapons->speed = 0;
            weapons->price = rand() % 150 + 90;
        }
        else if (rarity > 70)
        {
            weapons->name.insert(0, "Good ");
            weapons->description = { "A shiny Long Swords." };
            weapons->Attack_dices_number = 2;
            weapons->defensive_dices_number = 1;
            weapons->speed = 0;
            weapons->price = rand() % 90 + 50;
        }
        else if (rarity > 30)
        {
            weapons->name.insert(0, "");
            weapons->description = { "A Long Swords." };
            weapons->Attack_dices_number = 1;
            weapons->defensive_dices_number = 1;
            weapons->speed = 1;
            weapons->price = rand() % 50 + 30;
        }
        else
        {
            weapons->name.insert(0, "Rusty ");
            weapons->description = { "A rusty Long Swords. Its not gonna do much for you." };
            weapons->Attack_dices_number = 1;
            weapons->defensive_dices_number = 0;
            weapons->speed = 0;
            weapons->price = rand() % 30 + 10;
        }
    }
    else if (weapon_class == "Dagger")
    {
        int rarity = rand() % 100 + 1;
        weapons->name = weapon_class;
        weapons->Attack_dices_types = "Light";
        weapons->defensive_dices_types = "Parry";
        if (rarity > 90)
        {
            weapons->name.insert(0, "Legendary ");
            weapons->description = { "A shiny and light dagger. Be careful it cuts a lot." };
            weapons->Attack_dices_number = 6;
            weapons->defensive_dices_number = 2;
            weapons->speed = 2;
            weapons->price = rand() % 150 + 90;
        }
        else if (rarity > 70)
        {
            weapons->name.insert(0, "Good ");
            weapons->description = { "A light dagger." };
            weapons->Attack_dices_number = 5;
            weapons->defensive_dices_number = 2;
            weapons->speed = 2;
            weapons->price = rand() % 90 + 50;
        }
        else if (rarity > 30)
        {
            weapons->name.insert(0, "");
            weapons->description = { "A dagger." };
            weapons->Attack_dices_number = 4;
            weapons->defensive_dices_number = 1;
            weapons->speed = 1;
            weapons->price = rand() % 50 + 30;
        }
        else
        {
            weapons->name.insert(0, "Rusty ");
            weapons->description = { "A rusty dagger. Its not gonna do much for you." };
            weapons->Attack_dices_number = 3;
            weapons->defensive_dices_number = 1;
            weapons->speed = 0;
            weapons->price = rand() % 30 + 10;
        }
    }
    else if (weapon_class == "Bow")
    {
        int rarity = rand() % 100 + 1;
        weapons->name = weapon_class;
        weapons->Attack_dices_types = "Light";
        weapons->defensive_dices_types = "Dodge";
        if (rarity > 90)
        {
            weapons->name.insert(0, "Legendary ");
            weapons->description = { "A bow built of good wood. The rope is well tensioned." };
            weapons->Attack_dices_number = 2;
            weapons->defensive_dices_number = 2;
            weapons->speed = 0;
            weapons->price = rand() % 150 + 90;
        }
        else if (rarity > 70)
        {
            weapons->name.insert(0, "Good ");
            weapons->description = { "A bow built of good wood." };
            weapons->Attack_dices_number = 2;
            weapons->defensive_dices_number = 1;
            weapons->speed = 0;
            weapons->price = rand() % 90 + 50;
        }
        else if (rarity > 30)
        {
            weapons->name.insert(0, "");
            weapons->description = { "A bow." };
            weapons->Attack_dices_number = 1;
            weapons->defensive_dices_number = 1;
            weapons->speed = 1;
            weapons->price = rand() % 50 + 30;
        }
        else
        {
            weapons->name.insert(0, "Rusty ");
            weapons->description = { "an old bow. it could break at any moment." };
            weapons->Attack_dices_number = 1;
            weapons->defensive_dices_number = 0;
            weapons->speed = 0;
            weapons->price = rand() % 30 + 10;
        }
    }

}

void generate_enemy_stats(events* events, monster* enemy)
{
    if (events->enemy_type == "slime")
    {
        enemy->name = "slime";
        enemy->description = "slime";

        enemy->hp = 5 * events->enemy_dificulty;
        enemy->current_hp = 5 * events->enemy_dificulty;
        enemy->Attack_dices_types = "Light";
        enemy->Attack_dices_number = 2 + events->enemy_dificulty;
        enemy->defensive_dices_types = "Dodge";
        enemy->defensive_dices_number = 1 + events->enemy_dificulty;
        enemy->speed = 2;
    }
    if (events->enemy_type == "skeleton")
    {
        enemy->name = "skeleton";
        enemy->description = "skeleton";

        enemy->hp = 10 * events->enemy_dificulty;
        enemy->current_hp = 10 * events->enemy_dificulty;
        enemy->Attack_dices_types = "Light";
        enemy->Attack_dices_number = 2 + events->enemy_dificulty;
        enemy->defensive_dices_types = "Parry";
        enemy->defensive_dices_number = 1 + events->enemy_dificulty;
        enemy->speed = 1;
    }
    if (events->enemy_type == "Dead_armor")
    {
        enemy->name = "Dead_armor";
        enemy->description = "Dead_armor";

        enemy->hp = 20 * events->enemy_dificulty;
        enemy->current_hp = 20 * events->enemy_dificulty;
        enemy->Attack_dices_types = "Heavy";
        enemy->Attack_dices_number = 1 + events->enemy_dificulty;
        enemy->defensive_dices_types = "Shield";
        enemy->defensive_dices_number = 1 + events->enemy_dificulty;
        enemy->speed = 0;
    }
}

void take_weapons(weapons* weapons, inventory_slot* inventory_item)
{
    inventory_item->Weapon_name = weapons->name;
    inventory_item->type = weapons->type;
    inventory_item->item_description = weapons->description;
    inventory_item->quantity++;
    inventory_item->item_name = weapons->name;
    inventory_item->Weapon_Attack_dices_number = weapons->Attack_dices_number;
    inventory_item->Weapon_Attack_dices_types = weapons->Attack_dices_types;
    inventory_item->Weapon_defensive_dices_number = weapons->defensive_dices_number;
    inventory_item->Weapon_defensive_dices_types = weapons->defensive_dices_types;
    inventory_item->Weapon_speed = weapons->speed;
    inventory_item->en_uso = true;
}

void take_potion(potions* potion, inventory_slot* inventory_item)
{
    inventory_item->item_name = potion->item_name;
    inventory_item->heal_hp = potion->heal_hp;
    inventory_item->item_description = potion->item_description;
    inventory_item->price = potion->price;
    inventory_item->quantity++;
    inventory_item->type = potion->type;
    inventory_item->en_uso = true;

}

void generate_character_stats(character* player, weapons* weapons, inventory_slot* inventory_item)
{
    if (weapons->name == "Sword")
    {
        player->hp = 20;
        player->Attack_dices_number = 1;
        player->Attack_dices_types = "Heavy";
        player->current_hp = 20;
        player->defensive_dices_number = 1;
        player->defensive_dices_types = "Shield";
        player->speed = 1;

    }
    if (weapons->name == "Dagger")
    {
        player->hp = 10;
        player->Attack_dices_number = 3;
        player->Attack_dices_types = "Light";
        player->current_hp = 10;
        player->defensive_dices_number = 1;
        player->defensive_dices_types = "Parry";
        player->speed = 3;
    }
    if (weapons->name == "Bow")
    {
        player->hp = 8;
        player->Attack_dices_number = 1;
        player->Attack_dices_types = "Light";
        player->current_hp = 8;
        player->defensive_dices_number = 1;
        player->defensive_dices_types = "Dodge";
        player->speed = 4;
    }

    generate_weapon_stats(weapons);
    take_weapons(weapons, inventory_item);
    equip(inventory_item, player);

}

void generate_event_type(events* events)
{
    int rarity = rand() % 100 + 1;

    if (rarity > 200)
    {
        events->event_type = "Mistery";
    }
    else if (rarity > 50)
    {
        events->event_type = "Fight";
    }
    else if (rarity > 10)
    {
        events->event_type = "Rest";
    }
    else if (rarity > 5)
    {
        events->event_type = "Shop";
    }
    else
    {
        events->event_type = "Loot";
    }

}

void generate_event(events* events)
{
    if (events->event_type == "Shop")
    {
        events->event_description = "You see a shop in the distances.";
        events->enemy_type = "null";
        events->enemy_quantity = 0;
        events->event_porcentage = 0;
        events->enemy_dificulty = 0;
        events->in_use = true;
    }
    if (events->event_type == "Fight")
    {
        events->event_description = "There is a enemy blocking the pass.";
        string enemy_types[3]{ "slime","skeleton","Dead_armor" };
        events->enemy_type = enemy_types[rand() % 3];
        events->enemy_quantity = 1;
        events->event_porcentage = 0;
        events->enemy_dificulty = rand() % 3 + 1;
        events->in_use = true;
    }
    if (events->event_type == "Rest")
    {
        events->event_description = "You see a rest in the distances.";
        events->enemy_type = "null";
        events->enemy_quantity = 0;
        events->event_porcentage = 0;
        events->enemy_dificulty = 0;
        events->in_use = true;
    }
    if (events->event_type == "Mistery")
    {
        events->event_description = "Its not clear in what way is going this path.";
        events->enemy_type = "null";
        events->enemy_quantity = 0;
        events->event_porcentage = 0;
        events->enemy_dificulty = 0;
        events->in_use = true;
    }
    if (events->event_type == "Loot")
    {
        events->event_description = "You see loot.";
        events->enemy_type = "null";
        events->enemy_quantity = 0;
        events->event_porcentage = 0;
        events->enemy_dificulty = 0;
        events->in_use = true;
    }

}

void logo(HANDLE a)
{
    //37

    int color[37][37] = {
        0,5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,5,5,0,0,5,5,0,0,5,5,0,0,0,0,0,5,5,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,0,
        0,5,5,5,0,0,5,5,0,0,5,5,0,0,0,0,5,0,0,5,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,
        0,0,5,5,5,5,5,5,5,5,5,5,5,0,0,0,0,5,0,0,5,0,5,5,0,0,5,5,5,0,5,5,0,0,0,5,
        5,0,0,5,5,5,0,0,5,5,0,0,5,5,0,0,0,0,5,5,5,0,0,0,0,5,0,0,5,0,0,0,0,5,0,5,
        0,0,5,0,5,5,5,0,0,5,5,0,0,5,5,0,0,0,0,5,0,5,0,0,5,5,5,0,0,5,0,0,5,5,5,0,
        5,5,5,5,0,5,5,5,5,5,5,5,5,5,5,5,0,0,0,0,5,0,0,5,0,5,0,5,0,0,5,0,0,5,0,5,
        0,5,0,0,0,0,5,5,5,0,0,5,5,0,0,5,5,0,0,0,0,5,0,0,5,0,5,5,5,0,0,5,0,0,5,5,
        5,0,5,5,5,5,0,5,5,5,0,0,5,5,0,0,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0 };

    for (size_t b = 0; b != 10; b++)
    {
        cout << "|";
        for (size_t i = 0; i != 37; i++)
        {
            SetConsoleTextAttribute(a, 7);
            if (color[b][i] == 0)
            {
                SetConsoleTextAttribute(a, 7);
                cout << " ";
            }
            else if (color[b][i] == 1)
            {
                SetConsoleTextAttribute(a, 7 | BACKGROUND_BLUE);
                cout << " ";
            }
            else if (color[b][i] == 2)
            {
                SetConsoleTextAttribute(a, 7 | BACKGROUND_BLUE | BACKGROUND_RED);
                cout << " ";
            }
            else if (color[b][i] == 3)
            {
                SetConsoleTextAttribute(a, 7 | BACKGROUND_BLUE | BACKGROUND_GREEN);
                cout << " ";
            }
            else if (color[b][i] == 4)
            {
                SetConsoleTextAttribute(a, 7 | BACKGROUND_RED);
                cout << " ";
            }
            else if (color[b][i] == 5)
            {
                SetConsoleTextAttribute(a, 7 | BACKGROUND_RED | BACKGROUND_GREEN);
                cout << " ";
            }
            else if (color[b][i] == 6)
            {
                SetConsoleTextAttribute(a, 7 | BACKGROUND_GREEN);
                cout << " ";
            }
        }
        SetConsoleTextAttribute(a, 7);
        cout << "|" << endl;
    }

    SetConsoleTextAttribute(a, 7);
}

void hp(int hp, int current_hp)
{
    HANDLE myColors = GetStdHandle(STD_OUTPUT_HANDLE);
    string hp_bar;
    hp;
    current_hp;

    string barra_izq, barra_der, barra_izq_plus, barra_der_plus;

    barra_izq += std::to_string(current_hp);
    barra_der += std::to_string(hp);
    barra_izq_plus += std::to_string(current_hp);
    barra_der_plus += std::to_string(hp);

    for (size_t i = 5; i > barra_izq.length(); i--)
    {
        barra_izq_plus.insert(0, " ");
    }
    for (size_t i = 5; i > barra_der.length(); i--)
    {
        barra_der_plus.append(" ");
    }

    int porcentaje = 0;
    if (hp > 0 && current_hp > 0)
    {
        porcentaje = (current_hp * 10) / (hp);
    }

    hp_bar = barra_izq_plus + " / " + barra_der_plus;
    if (porcentaje == 10)
    {
        SetConsoleTextAttribute(myColors, 7 | BACKGROUND_GREEN);
        cout << hp_bar;
    }
    else
    {
        SetConsoleTextAttribute(myColors, 7 | BACKGROUND_GREEN);
        cout << hp_bar.substr(0, porcentaje);
        SetConsoleTextAttribute(myColors, 7 | BACKGROUND_RED);
        cout << hp_bar.substr(porcentaje);
    }
    SetConsoleTextAttribute(myColors, 15);
};

//void Inventory(inventory_slot* inventory, character* player)
//{
//    int b = 1;
//    for (size_t i = 1; i != 11; i++)
//    {
//        if (!inventory[i].en_uso)
//        {
//            cout << "for";
//            cout << b << ") " << inventory[i].item_name;
//            for (int a = 0; a != 25 - inventory[i].item_name.length(); a++)
//            {
//                cout << " ";
//            }
//            cout << inventory[i].price << " GOLD\n";
//            b++;
//        }
//    }
//    inventory[1].item_name = "caca";
//};

void show(inventory_slot* inventory_item)
{
    if (inventory_item->type == "weapons")
    {
        cout << "[" << inventory_item->item_name << "]" << endl;
        cout << inventory_item->item_description << endl;
        cout << "Attack [Types of Dice: " << inventory_item->Weapon_Attack_dices_types << "  Quantity: " << inventory_item->Weapon_Attack_dices_number << "]\n";
        cout << "Defend [Types of Dice: " << inventory_item->Weapon_defensive_dices_types << "  Quantity: " << inventory_item->Weapon_defensive_dices_number << "]\n";
        cout << "Speed [" << inventory_item->Weapon_speed << "]\n";
    }
    else if (inventory_item->type == "Potion")
    {
        cout << "[" << inventory_item->item_name << "]" << endl;
        cout << inventory_item->item_description << endl;
        cout << "healing [" << inventory_item->heal_hp << " hp]" << endl;
    }
    else
    {
        cout << "[" << inventory_item->item_name << "]" << endl;
        cout << inventory_item->item_description << endl;
    }
}

void show_events(events* events)
{
    if (events->event_type == "Shop")
    {
        cout << "[" << events->event_type << "]\n";
        cout << events->event_description << endl;
    }
    if (events->event_type == "Fight")
    {
        cout << "[" << events->event_type << "]\n";
        cout << events->event_description << endl;
        cout << "[Type: " << events->enemy_type << "]\n";
    }
    if (events->event_type == "Rest")
    {
        cout << "[" << events->event_type << "]\n";
        cout << events->event_description << endl;
    }
    if (events->event_type == "Mistery")
    {
        cout << "[" << events->event_type << "]\n";
        cout << events->event_description << endl;
    }
    if (events->event_type == "Loot")
    {
        cout << "[" << events->event_type << "]\n";
        cout << events->event_description << endl;
    }
}

void equip(inventory_slot* inventory_item, character* player)
{
    player->Weapon_name = inventory_item->Weapon_name;
    player->Weapon_Attack_dices_number = inventory_item->Weapon_Attack_dices_number;
    player->Weapon_Attack_dices_types = inventory_item->Weapon_Attack_dices_types;
    player->Weapon_defensive_dices_number = inventory_item->Weapon_defensive_dices_number;
    player->Weapon_defensive_dices_types = inventory_item->Weapon_defensive_dices_types;
    player->Weapon_speed = inventory_item->Weapon_speed;
}

void use_potion(inventory_slot* inventory_item, character* player)
{
    inventory_item->quantity--;
    player->current_hp = player->current_hp + inventory_item->heal_hp;
    if (player->current_hp > player->hp)
    {
        player->current_hp = player->hp;
    }
    if (inventory_item->quantity <= 0)
    {
        inventory_item->heal_hp = 0;
        inventory_item->en_uso = false;
        inventory_item->item_name = "null";
        inventory_item->item_description = "null";
        inventory_item->price = 0;
        inventory_item->type = "null";

    }
}

void drop(inventory_slot* inventory_item, character* player)
{
    bool same = false;
    if (inventory_item->Weapon_name == player->Weapon_name)
    {
        same = true;
    }
    inventory_item->quantity--;
    if (inventory_item->quantity <= 0)
    {
        inventory_item->en_uso = false;
        inventory_item->heal_hp = 0;
        inventory_item->item_description = "null";
        inventory_item->item_name = "null";
        inventory_item->price = 0;
        inventory_item->type = "null";
        inventory_item->Weapon_Attack_dices_number = 0;
        inventory_item->Weapon_Attack_dices_types = "null";
        inventory_item->Weapon_defensive_dices_number = 0;
        inventory_item->Weapon_defensive_dices_types = "null";
        inventory_item->Weapon_name = "null";
        inventory_item->Weapon_speed = 0;
        if (same)
        {
            player->Weapon_name = "Not Equiped";
            player->Weapon_Attack_dices_number = 0;
            player->Weapon_Attack_dices_types = "null";
            player->Weapon_defensive_dices_number = 0;
            player->Weapon_defensive_dices_types = "null";
            player->Weapon_speed = 0;
        }
    }
}

int battle(events* events, monster* enemy, character* jugador, inventory_slot* inventory_items)
{
    bool is_battle = true, is_turn = true, is_inventory = true, is_fight = true;
    char option = 0;

    int rolls = 0;
    int espacio = 0;



    int player_attack_rolls[30] = { 0 };
    string player_attack_rolls_type[30] = { "null" };
    int player_total_rolls = 0;
    int player_dodges = 0;
    int player_shield = 0;
    int player_current_shield = 0;
    int player_parry = 0;
    string player_set_type = "null";
    int player_speed_counter = 0;
    int player_counter = 0;

    int enemy_attack_rolls[30] = { 0 };
    string enemy_attack_rolls_type[30] = { "null" };
    int enemy_total_rolls = 0;
    int enemy_dodges = 0;
    int enemy_shield = 0;
    int enemy_current_shield = 0;
    int enemy_parry = 0;
    string enemy_set_type = "null";
    int enemy_speed_counter = 0;
    int enemy_counter = 0;


    generate_enemy_stats(events, enemy);
    while (is_battle)
    {
        is_turn = true;
        while (is_turn)
        {
            cout << "[player: " << jugador->name << "] " << "[";
            hp(jugador->hp, jugador->current_hp);
            cout << "]" << endl;
            cout << "[player Dice Type: " << jugador->Attack_dices_types << "] " << "[Quantity: " << jugador->Attack_dices_number << "]\n";
            cout << "[Weapon Dice Type: " << jugador->Weapon_Attack_dices_types << "] " << "[Quantity: " << jugador->Weapon_Attack_dices_number << "]\n";
            cout << "[player Defensive Dice Type: " << jugador->defensive_dices_types << "] " << "[Quantity: " << jugador->defensive_dices_number << "]\n";
            cout << "[Weapon Defensive Dice Type: " << jugador->Weapon_defensive_dices_types << "] " << "[Quantity: " << jugador->Weapon_defensive_dices_number << "]\n";
            cout << endl << endl;

            cout << "[Enemy: " << enemy->name << "] " << "[";
            hp(enemy->hp, enemy->current_hp);
            cout << "]" << endl << endl;


            cout << "1) Roll Dices\n" << "2) inventory\n";
            cout << "\nOption: ";
            option = 0;
            cin >> option;


            switch (option)
            {
            case '1':
                is_turn = false;
                rolls = 0;
                espacio = 0;
                player_shield = 0;
                player_current_shield = 0;
                player_parry = 0;
                player_dodges = 0;
                //player Roll base
                {


                    rolls = jugador->Attack_dices_number;
                    player_set_type = jugador->Attack_dices_types;
                    while (rolls > 0)
                    {
                        if (player_set_type == "Heavy")
                        {
                            player_attack_rolls[espacio] = rand() % 3 + 4;
                            player_attack_rolls_type[espacio] = "Heavy";
                        }
                        if (player_set_type == "Light")
                        {
                            player_attack_rolls[espacio] = rand() % 3 + 1;
                            player_attack_rolls_type[espacio] = "Light";
                        }
                        espacio++;
                        rolls--;
                    }
                }
                //player Roll arma
                {
                    rolls = 0;

                    rolls = jugador->Weapon_Attack_dices_number;
                    player_set_type = jugador->Weapon_Attack_dices_types;
                    while (rolls > 0)
                    {
                        if (player_set_type == "Heavy")
                        {
                            player_attack_rolls[espacio] = rand() % 3 + 4;
                            player_attack_rolls_type[espacio] = "Heavy";
                        }
                        if (player_set_type == "Light")
                        {
                            player_attack_rolls[espacio] = rand() % 3 + 1;
                            player_attack_rolls_type[espacio] = "Light";
                        }
                        espacio++;
                        rolls--;
                    }
                }
                player_total_rolls = espacio;
                //player Roll Defensivo base
                {
                    rolls = jugador->defensive_dices_number;
                    player_set_type = jugador->defensive_dices_types;
                    while (rolls > 0)
                    {
                        if (player_set_type == "Shield")
                        {
                            player_shield = player_shield + rand() % 6 + 1;
                            player_current_shield = player_shield;
                        }
                        if (player_set_type == "Parry")
                        {
                            if (rand() % 2 + 1 == 1)
                            {
                                player_parry++;
                            }
                        }
                        if (player_set_type == "Dodge")
                        {
                            if (rand() % 2 + 1 == 1)
                            {
                                player_dodges++;
                            }
                        }
                        rolls--;
                    }
                }
                //player Roll Defensivo arma
                {
                    rolls = jugador->Weapon_defensive_dices_number;
                    player_set_type = jugador->Weapon_defensive_dices_types;
                    while (rolls > 0)
                    {
                        if (player_set_type == "Shield")
                        {
                            player_shield = player_shield + rand() % 6 + 1;
                            player_current_shield = player_shield;
                        }
                        if (player_set_type == "Parry")
                        {
                            if (rand() % 2 + 1 == 1)
                            {
                                player_parry++;
                            }
                        }
                        if (player_set_type == "Dodge")
                        {
                            if (rand() % 2 + 1 == 1)
                            {
                                player_dodges++;
                            }
                        }
                        rolls--;
                    }
                }

                rolls = 0;
                espacio = 0;
                enemy_shield = 0;
                enemy_current_shield = 0;
                enemy_parry = 0;
                enemy_dodges = 0;
                //enemy Roll bases
                {


                    rolls = enemy->Attack_dices_number;
                    enemy_set_type = enemy->Attack_dices_types;
                    while (rolls > 0)
                    {
                        if (enemy_set_type == "Heavy")
                        {
                            enemy_attack_rolls[espacio] = rand() % 3 + 4;
                            enemy_attack_rolls_type[espacio] = "Heavy";
                        }
                        if (enemy_set_type == "Light")
                        {
                            enemy_attack_rolls[espacio] = rand() % 3 + 1;
                            enemy_attack_rolls_type[espacio] = "Light";
                        }
                        espacio++;
                        rolls--;
                    }
                }
                enemy_total_rolls = espacio;
                //enemy Roll Defensivo base
                {
                    rolls = enemy->defensive_dices_number;
                    player_set_type = enemy->defensive_dices_types;
                    while (rolls > 0)
                    {
                        if (enemy_set_type == "Shield")
                        {
                            enemy_shield = enemy_shield + rand() % 6 + 1;
                            enemy_current_shield = enemy_shield;
                        }
                        if (enemy_set_type == "Parry")
                        {
                            if (rand() % 2 + 1 == 1)
                            {
                                enemy_parry++;
                            }
                        }
                        if (enemy_set_type == "Dodge")
                        {
                            if (rand() % 2 + 1 == 1)
                            {
                                enemy_dodges++;
                            }
                        }
                        rolls--;
                    }
                }

                cout << endl;
                system("pause");
                system("cls");
                break;
            case '2':
                is_inventory = true;
                while (is_inventory)
                {
                    system("pause");
                    system("cls");
                    int b = 1;
                    int lugar_opciones[10000] = { 0 };
                    cout << "[player: " << jugador->name << "] " << "[";
                    hp(jugador->hp, jugador->current_hp);
                    cout << "]" << endl;
                    cout << "[Gold:" << jugador->money << "]\n";

                    for (size_t i = 0; i != 10; i++)
                    {
                        if (inventory_items[i].en_uso)
                        {
                            lugar_opciones[b] = i;
                            cout << b << ") " << inventory_items[i].item_name;
                            for (int a = 0; a != 25 - inventory_items[i].item_name.length() - std::to_string(b).length(); a++)
                            {
                                cout << " ";
                            }
                            cout << inventory_items[i].quantity << " Quantity\n";
                            b++;
                        }
                    }

                    cout << endl << "1) Show info\n" << "2) Equip/Use\n" << "3) Drop\n" << "4) Go back\n";

                    cout << "\nOption: ";
                    option = 0;
                    cin >> option;
                    int number_of_item = 0;
                    switch (option)
                    {
                    case'1':
                        cout << "\nNumber of the item: ";
                        number_of_item = 0;
                        cin >> number_of_item;
                        show(&inventory_items[lugar_opciones[number_of_item]]);


                        break;
                    case'2':
                        cout << "\nNumber of the item: ";
                        number_of_item = 0;
                        cin >> number_of_item;
                        show(&inventory_items[lugar_opciones[number_of_item]]);
                        if (inventory_items[lugar_opciones[number_of_item]].type == "weapons")
                        {
                            cout << "\n1) equip";
                            cout << "\n2) Go back";

                            cout << "\n\nOption: ";
                            option = 0;
                            cin >> option;
                            switch (option)
                            {
                            case'1':
                                equip(&inventory_items[lugar_opciones[number_of_item]], jugador);
                                break;
                            default:
                                break;
                            }
                        }
                        else if (inventory_items[lugar_opciones[number_of_item]].type == "Potion")
                        {
                            cout << "\n1) Use";
                            cout << "\n2) Go back";

                            cout << "\n\nOption: ";
                            option = 0;
                            cin >> option;
                            switch (option)
                            {
                            case'1':
                                use_potion(&inventory_items[lugar_opciones[number_of_item]], jugador);
                                break;
                            default:
                                break;
                            }
                        }
                        break;
                    case'3':
                        cout << "\nNumber of the item: ";
                        number_of_item = 0;
                        cin >> number_of_item;
                        show(&inventory_items[lugar_opciones[number_of_item]]);
                        cout << "\n1) drop";
                        cout << "\n2) Go back";

                        cout << "\n\nOption: ";
                        option = 0;
                        cin >> option;
                        switch (option)
                        {
                        case'1':
                            drop(&inventory_items[lugar_opciones[number_of_item]], jugador);
                            break;
                        default:
                            break;
                        }
                        break;
                    case'4':
                        is_inventory = false;
                        system("pause");
                        system("cls");
                        break;
                    default:
                        cout << "error\n";
                        system("pause");
                        system("cls");
                        break;
                    }
                }
                break;
            default:
                break;
            }
        }

        cout << "[player: " << jugador->name << "] " << "[";
        hp(jugador->hp, jugador->current_hp);
        cout << "]";
        cout << " Shield[";
        hp(player_shield, player_current_shield);
        cout << "]" << endl;
        cout << "[Parrys: " << player_parry << "] ";
        cout << "[Dodges: " << player_dodges << "]\n";
        cout << "[Attacks]\n";
        cout << "| ";
        for (size_t i = 0; i <= player_total_rolls - 1; i++)
        {
            cout << player_attack_rolls[i];
            cout << " | ";
        }
        cout << endl << endl;

        cout << "[enemy: " << enemy->name << "] " << "[";
        hp(enemy->hp, enemy->current_hp);
        cout << "]";
        cout << " Shield[";
        hp(enemy_shield, enemy_current_shield);
        cout << "]" << endl;
        cout << "[Parrys: " << enemy_parry << "] ";
        cout << "[Dodges: " << enemy_dodges << "]\n";
        cout << "[Attacks]\n";
        cout << "| ";
        for (size_t i = 0; i <= enemy_total_rolls - 1; i++)
        {
            cout << enemy_attack_rolls[i];
            cout << " | ";
        }
        cout << endl << endl;

        player_total_rolls--;
        enemy_total_rolls--;

        system("pause");
        system("cls");
        //Combat

        enemy_speed_counter = enemy->speed;
        player_speed_counter = jugador->speed + jugador->Weapon_speed;
        player_counter = 10 - player_speed_counter;
        enemy_counter = 10 - enemy_speed_counter;
        is_fight = true;
        while (is_fight)
        {
            //player Counter
            if (player_counter <= 0 && player_total_rolls != -1)
            {

                if (enemy_current_shield > 0)
                {
                    if (enemy_current_shield - player_attack_rolls[player_total_rolls] < 0)
                    {
                        enemy_current_shield = 0;
                        enemy->current_hp = enemy->current_hp - (player_attack_rolls[player_total_rolls] - enemy_current_shield);
                    }
                    else
                    {
                        enemy_current_shield = enemy_current_shield - player_attack_rolls[player_total_rolls];
                    }

                }
                else if (enemy_parry > 0)
                {
                    if (player_current_shield > 0)
                    {
                        if (player_current_shield - player_attack_rolls[player_total_rolls] < 0)
                        {
                            player_current_shield = 0;
                            jugador->current_hp = jugador->current_hp - (player_attack_rolls[player_total_rolls] - player_current_shield);
                        }
                        else
                        {
                            player_current_shield = player_current_shield - player_attack_rolls[player_total_rolls];
                        }
                    }
                    else if (player_dodges > 0)
                    {
                        player_dodges--;
                    }
                    else
                    {
                        jugador->current_hp = jugador->current_hp - player_attack_rolls[player_total_rolls];
                    }
                    enemy_parry--;
                }
                else if (enemy_dodges > 0)
                {
                    enemy_dodges--;
                }
                else
                {

                    enemy->current_hp = enemy->current_hp - player_attack_rolls[player_total_rolls];

                }

                cout << "[player: " << jugador->name << "] " << "[";
                hp(jugador->hp, jugador->current_hp);
                cout << "]";
                cout << " Shield[";
                hp(player_shield, player_current_shield);
                cout << "]" << endl;
                cout << "[Parrys: " << player_parry << "] ";
                cout << "[Dodges: " << player_dodges << "]\n";
                cout << "[Attacks]\n";
                cout << "| ";
                if (player_total_rolls != -1)
                {
                    player_total_rolls--;
                }
                if (player_total_rolls != -1)
                {
                    for (size_t i = 0; i <= player_total_rolls; i++)
                    {
                        cout << player_attack_rolls[i];
                        cout << " | ";
                    }
                }
                cout << endl << endl;

                cout << "[enemy: " << enemy->name << "] " << "[";
                hp(enemy->hp, enemy->current_hp);
                cout << "]";
                cout << " Shield[";
                hp(enemy_shield, enemy_current_shield);
                cout << "]" << endl;
                cout << "[Parrys: " << enemy_parry << "] ";
                cout << "[Dodges: " << enemy_dodges << "]\n";
                cout << "[Attacks]\n";
                cout << "| ";

                if (enemy_total_rolls != -1)
                {
                    for (size_t i = 0; i <= enemy_total_rolls; i++)
                    {
                        cout << enemy_attack_rolls[i];
                        cout << " | ";
                    }
                }
                cout << endl << endl;

                player_counter = 10 - player_speed_counter;
                if (jugador->current_hp <= 0)
                {
                    system("pause");
                    system("cls");
                    return 0;
                }
                else if (enemy->current_hp <= 0)
                {
                    system("pause");
                    system("cls");
                    return 1;
                }
                system("pause");
                system("cls");
            }




            //enemy Counter
            if (enemy_counter <= 0 && enemy_total_rolls != -1)
            {
                if (player_current_shield > 0)
                {
                    if (player_current_shield - enemy_attack_rolls[enemy_total_rolls] < 0)
                    {
                        player_current_shield = 0;
                        jugador->current_hp = jugador->current_hp - (enemy_attack_rolls[enemy_total_rolls] - player_current_shield);
                    }
                    else
                    {
                        player_current_shield = player_current_shield - enemy_attack_rolls[enemy_total_rolls];
                    }

                }
                else if (player_parry > 0)
                {
                    if (enemy_current_shield > 0)
                    {
                        if (enemy_current_shield - enemy_attack_rolls[enemy_total_rolls] < 0)
                        {
                            enemy_current_shield = 0;
                            enemy->current_hp = enemy->current_hp - (enemy_attack_rolls[enemy_total_rolls] - enemy_current_shield);
                        }
                        else
                        {
                            enemy_current_shield = enemy_current_shield - enemy_attack_rolls[enemy_total_rolls];
                        }
                    }
                    else if (enemy_dodges > 0)
                    {
                        enemy_dodges--;
                    }
                    else
                    {
                        enemy->current_hp = enemy->current_hp - enemy_attack_rolls[enemy_total_rolls];
                    }
                    player_parry--;
                }
                else if (player_dodges > 0)
                {

                    player_dodges--;

                }
                else
                {

                    jugador->current_hp = jugador->current_hp - enemy_attack_rolls[enemy_total_rolls];

                }

                cout << "[player: " << jugador->name << "] " << "[";
                hp(jugador->hp, jugador->current_hp);
                cout << "]";
                cout << " Shield[";
                hp(player_shield, player_current_shield);
                cout << "]" << endl;
                cout << "[Parrys: " << player_parry << "] ";
                cout << "[Dodges: " << player_dodges << "]\n";
                cout << "[Attacks]\n";
                cout << "| ";
                if (enemy_total_rolls != -1)
                {
                    enemy_total_rolls--;
                }
                if (player_total_rolls != -1)
                {
                    for (size_t i = 0; i <= player_total_rolls; i++)
                    {
                        cout << player_attack_rolls[i];
                        cout << " | ";
                    }
                }
                cout << endl << endl;

                cout << "[enemy: " << enemy->name << "] " << "[";
                hp(enemy->hp, enemy->current_hp);
                cout << "]";
                cout << " Shield[";
                hp(enemy_shield, enemy_current_shield);
                cout << "]" << endl;
                cout << "[Parrys: " << enemy_parry << "] ";
                cout << "[Dodges: " << enemy_dodges << "]\n";
                cout << "[Attacks]\n";
                cout << "| ";

                if (enemy_total_rolls != -1)
                {
                    for (size_t i = 0; i <= enemy_total_rolls; i++)
                    {
                        cout << enemy_attack_rolls[i];
                        cout << " | ";
                    }
                }
                cout << endl << endl;

                player_counter = 10 - player_speed_counter;

                if (jugador->current_hp <= 0)
                {
                    system("pause");
                    system("cls");
                    return 0;
                }
                else if (enemy->current_hp <= 0)
                {
                    system("pause");
                    system("cls");
                    return 1;
                }
                system("pause");
                system("cls");


            }



            if (enemy_total_rolls == -1 && player_total_rolls == -1)
            {
                is_fight = false;
            }

            player_counter--;
            enemy_counter--;

        }




        system("pause");
        system("cls");
    }
}

void shop(character* player, inventory_slot* inventory_item)
{
    bool is_shoping = true;
    int Money = 0;
    bool is_sum = false;
    weapons slot1, slot2;
    generate_weapon_stats(&slot1);
    generate_weapon_stats(&slot2);
    potions Potion;
    Potion.en_uso = true;
    Potion.heal_hp = 5;
    Potion.item_description = "Potion that Heal 5 hp.";
    Potion.item_name = "Red Potion";
    Potion.quantity++;
    Potion.price = 20;


    while (is_shoping)
    {
        cout << "[player: " << player->name << "] " << "[";
        hp(player->hp, player->current_hp);
        cout << "]" << endl;
        cout << "[Gold:" << player->money << "]\n\n";

        cout << "[Shop]\n";

        cout << "\n1)[Weapon: " << slot1.name << " ] [Price: " << slot1.price << " ]\n";
        cout << "Attack [Types of Dice: " << slot1.Attack_dices_types << " | Quantity: " << slot1.Attack_dices_number << "]\n";
        cout << "Defend [Types of Dice: " << slot1.defensive_dices_types << " | Quantity: " << slot1.defensive_dices_number << "]\n";
        cout << "Speed [" << slot1.speed << "]\n";
        cout << "\n2)[Weapon: " << slot2.name << " ] [Price: " << slot2.price << " ]\n";
        cout << "Attack [Types of Dice: " << slot2.Attack_dices_types << " | Quantity: " << slot2.Attack_dices_number << "]\n";
        cout << "Defend [Types of Dice: " << slot2.defensive_dices_types << " | Quantity: " << slot2.defensive_dices_number << "]\n";
        cout << "Speed [" << slot2.speed << "]\n";
        cout << "\n3)[Potion: " << Potion.item_name << " ] [Price: " << Potion.price << " ]\n";
        cout << "Attack [Healing: " << Potion.heal_hp << " hp]\n";
        cout << "\n4) Leave\n";
        char option = 0;
        cout << "\nOption: ";
        cin >> option;
        switch (option)
        {
        default:
        case '1':
            Money = player->money - slot1.price;


            if (Money >= 0)
            {
                for (size_t i = 2; i <= 9; i++)
                {
                    if (inventory_item[i].Weapon_name == slot1.name)
                    {
                        inventory_item[i].quantity++;
                        i = 9;
                        is_sum = true;
                        player->money = Money;
                        is_shoping = false;
                    }
                }
                if (!is_sum)
                {
                    for (size_t i = 2; i <= 9; i++)
                    {
                        if (inventory_item[i].en_uso == false)
                        {
                            take_weapons(&slot1, &inventory_item[i]);
                            i = 9;
                            is_sum = true;
                            player->money = Money;
                            is_shoping = false;
                        }
                    }
                }
                if (!is_sum)
                {
                    cout << "\nYou dont have space\n\n";
                    system("pause");
                    system("cls");
                }
            }
            else
            {
                cout << "\nYou dont have money for that\n\n";
                system("pause");
                system("cls");
            }
            break;
        case '2':
            Money = player->money - slot2.price;


            if (Money >= 0)
            {
                for (size_t i = 2; i <= 9; i++)
                {
                    if (inventory_item[i].Weapon_name == slot2.name)
                    {
                        inventory_item[i].quantity++;
                        i = 9;
                        is_sum = true;
                        player->money = Money;
                        is_shoping = false;
                    }
                }
                if (!is_sum)
                {
                    for (size_t i = 2; i <= 9; i++)
                    {
                        if (inventory_item[i].en_uso == false)
                        {
                            take_weapons(&slot2, &inventory_item[i]);
                            i = 9;
                            is_sum = true;
                            player->money = Money;
                            is_shoping = false;
                        }
                    }
                }
                if (!is_sum)
                {
                    cout << "\nYou dont have space\n\n";
                    system("pause");
                    system("cls");
                }
            }
            else
            {
                cout << "\nYou dont have money for that\n\n";
                system("pause");
                system("cls");
            }
            break;
        case '3':
            Money = player->money - Potion.price;

            if (Money >= 0)
            {
                for (size_t i = 1; i <= 9; i++)
                {

                    if (inventory_item[i].item_name == Potion.item_name)
                    {

                        inventory_item[i].quantity++;
                        i = 9;
                        is_sum = true;
                        player->money = Money;
                        is_shoping = false;
                    }
                }
                if (!is_sum)
                {
                    for (size_t i = 1; i <= 9; i++)
                    {

                        if (inventory_item[i].en_uso == false)
                        {
                            take_potion(&Potion, &inventory_item[i]);
                            i = 9;
                            is_sum = true;
                            player->money = Money;
                            is_shoping = false;
                        }
                    }
                }
                if (!is_sum)
                {
                    cout << "\nYou dont have space\n\n";
                    system("pause");
                    system("cls");
                }
            }
            else
            {
                cout << "\nYou dont have money for that\n\n";
                system("pause");
                system("cls");
            }
            break;
        case '4':
            is_shoping = false;
            break;
            cout << "error\n";
            system("pause");
            system("cls");
            break;
        }
    }
    system("pause");
    system("cls");
}

void rest(character* player, inventory_slot* Inventory_slots)
{
    char option;
    bool rest = false, is_resting = true;


    while (is_resting)
    {
        cout << "[player: " << player->name << "] " << "[";
        hp(player->hp, player->current_hp);
        cout << "]" << endl;
        cout << "[Gold:" << player->money << "]\n\n";

        cout << "[Rest]\n";

        cout << "\nYou find a good rest place... what you want to do?\n";
        cout << "\n1) Rest (heal 5 hp)";
        cout << "\n2) Show Stats";
        cout << "\n3) Show Inventory";
        cout << "\n4) Continue\n";


        cout << "\nOption: ";
        option = 0;
        cin >> option;

        switch (option)
        {
        case '1':
            if (!rest)
            {
                rest = true;
                player->current_hp = player->current_hp + 5;
                if (player->current_hp > player->hp)
                {
                    player->current_hp = player->hp;
                }

                cout << "\nYou rest and heal 5 hp\n";
            }
            else
            {
                cout << "\nYou already rest\n";
            }

            break;
        case '2':
        {
            system("pause");
            system("cls");

            cout << "[player: " << player->name << "] " << "[";
            hp(player->hp, player->current_hp);
            cout << "]" << endl;
            cout << "[Gold:" << player->money << "]\n\n";
            cout << "Attack [Types of Dice: " << player->Attack_dices_types << "  Quantity: " << player->Attack_dices_number << "]\n";
            cout << "Defend [Types of Dice: " << player->defensive_dices_types << "  Quantity: " << player->defensive_dices_number << "]\n";
            cout << "Speed [" << player->speed << "]\n\n";

            cout << "[Weapon:" << player->Weapon_name << "]\n";
            cout << "Attack [Types of Dice: " << player->Weapon_Attack_dices_types << "  Quantity: " << player->Weapon_Attack_dices_number << "]\n";
            cout << "Defend [Types of Dice: " << player->Weapon_defensive_dices_types << "  Quantity: " << player->Weapon_defensive_dices_number << "]\n";
            cout << "Speed [" << player->Weapon_speed << "]\n";
        };
        break;
        case '3':
            bool is_inventory;
            is_inventory = true;
            while (is_inventory)
            {
                system("pause");
                system("cls");
                int b = 1;
                int lugar_opciones[10000] = { 0 };
                cout << "[player: " << player->name << "] " << "[";
                hp(player->hp, player->current_hp);
                cout << "]" << endl;
                cout << "[Gold:" << player->money << "]\n";

                for (size_t i = 0; i != 10; i++)
                {
                    if (Inventory_slots[i].en_uso)
                    {
                        lugar_opciones[b] = i;
                        cout << b << ") " << Inventory_slots[i].item_name;
                        for (int a = 0; a != 25 - Inventory_slots[i].item_name.length() - std::to_string(b).length(); a++)
                        {
                            cout << " ";
                        }
                        cout << Inventory_slots[i].quantity << " Quantity\n";
                        b++;
                    }
                }

                cout << endl << "1) Show info\n" << "2) Equip/Use\n" << "3) Drop\n" << "4) Go back\n";

                cout << "\nOption: ";
                option = 0;
                cin >> option;
                int number_of_item = 0;
                switch (option)
                {
                case'1':
                    cout << "\nNumber of the item: ";
                    number_of_item = 0;
                    cin >> number_of_item;
                    show(&Inventory_slots[lugar_opciones[number_of_item]]);
                    break;
                case'2':
                    cout << "\nNumber of the item: ";
                    number_of_item = 0;
                    cin >> number_of_item;
                    show(&Inventory_slots[lugar_opciones[number_of_item]]);
                    if (Inventory_slots[lugar_opciones[number_of_item]].type == "weapons")
                    {
                        cout << "\n1) equip";
                        cout << "\n2) Go back";

                        cout << "\n\nOption: ";
                        option = 0;
                        cin >> option;
                        switch (option)
                        {
                        case'1':
                            equip(&Inventory_slots[lugar_opciones[number_of_item]], player);
                            break;
                        default:
                            break;
                        }
                    }
                    else if (Inventory_slots[lugar_opciones[number_of_item]].type == "Potion")
                    {
                        cout << "\n1) Use";
                        cout << "\n2) Go back";

                        cout << "\n\nOption: ";
                        option = 0;
                        cin >> option;
                        switch (option)
                        {
                        case'1':
                            use_potion(&Inventory_slots[lugar_opciones[number_of_item]], player);
                            break;
                        default:
                            break;
                        }
                    }
                    break;
                case'3':
                    cout << "\nNumber of the item: ";
                    number_of_item = 0;
                    cin >> number_of_item;
                    show(&Inventory_slots[lugar_opciones[number_of_item]]);
                    cout << "\n1) drop";
                    cout << "\n2) Go back";

                    cout << "\n\nOption: ";
                    option = 0;
                    cin >> option;
                    switch (option)
                    {
                    case'1':
                        drop(&Inventory_slots[lugar_opciones[number_of_item]], player);
                        break;
                    default:
                        break;
                    }
                    break;
                case'4':
                    is_inventory = false;
                    break;
                default:
                    cout << "error\n";
                    break;
                }
            }
            break;
        case '4':
            is_resting = false;
            break;
        }
        system("pause");
        system("cls");
    }
}

void loot(character* player, inventory_slot* Inventory_slots)
{
    cout << "[player: " << player->name << "] " << "[";
    hp(player->hp, player->current_hp);
    cout << "]" << endl;
    cout << "[Gold:" << player->money << "]\n\n";

    cout << "[Loot]\n";
    int a = rand() % 3;
    int gold = rand() % 100 + 50;
    potions Potion;
    bool is_sum = false;
    weapons Slot;

    switch (a)
    {
    case 0:
        Potion.en_uso = true;
        Potion.heal_hp = 5;
        Potion.item_description = "Potion that Heal 5 hp.";
        Potion.item_name = "Red Potion";
        Potion.quantity++;
        Potion.price = 20;

        cout << "\nYou Find a " << Potion.item_name << "!!!\n";
        for (size_t i = 1; i <= 9; i++)
        {

            if (Inventory_slots[i].item_name == Potion.item_name)
            {

                Inventory_slots[i].quantity++;
                i = 9;
                is_sum = true;
            }
        }
        if (!is_sum)
        {
            for (size_t i = 1; i <= 9; i++)
            {

                if (Inventory_slots[i].en_uso == false)
                {
                    take_potion(&Potion, &Inventory_slots[i]);
                    i = 9;
                    is_sum = true;
                }
            }
        }
        if (!is_sum)
        {
            cout << "\nYou dont have space to take it\n";
        }
        break;
    case 1:
        generate_weapon_stats(&Slot);

        cout << "\nYou Find a " << Slot.name << "!!!\n";
        for (size_t i = 2; i <= 9; i++)
        {
            if (Inventory_slots[i].Weapon_name == Slot.name)
            {
                Inventory_slots[i].quantity++;
                i = 9;
                is_sum = true;
            }
        }
        if (!is_sum)
        {
            for (size_t i = 2; i <= 9; i++)
            {
                if (Inventory_slots[i].en_uso == false)
                {
                    take_weapons(&Slot, &Inventory_slots[i]);
                    i = 9;
                    is_sum = true;

                }
            }
        }
        if (!is_sum)
        {
            cout << "\nYou dont have space to take it\n";
        }
        break;
    case 2:

        cout << "\nYou Find " << gold << "G!!!\n";
        player->money = player->money + gold;
        break;

    default:
        break;

    }
    system("pause");
    system("cls");
}

int playing()
{
    character player;
    char option = 0;
    bool is_playing = true, is_adventure = true, is_inventory = true, is_class = true;
    bool event_taken = true;
    events slots[4];
    monster enemigo;
    inventory_slot Inventory_slots[10];


    system("pause");
    system("cls");

    cin.ignore();
    cout << "Enter your name: ";
    getline(cin, player.name);

    system("pause");
    system("cls");

    while (is_class)
    {
        cout << "[classes]\n\n";
        cout << "1) Swordman\n" << "2) Assassin\n" << "3) Archer\n";
        cout << "\nOption: ";
        option = 0;
        cin >> option;

        switch (option)
        {
        case'1':
            cout << "\n\n[Swordman]";
            cout << "\n A heavy swordsman who has good attack and defense."
                "\n His direct combat style is ideal against large enemies.";
            cout << "\n\n1) Select\n" << "2) See Others\n";
            cout << "\nOption: ";
            option = 0;
            cin >> option;
            if (option == '1')
            {
                weapons starter;
                starter.name = "Sword";
                generate_character_stats(&player, &starter, &Inventory_slots[1]);
                is_class = false;
            }
            system("pause");
            system("cls");
            break;
        case'2':
            cout << "\n\n[Assassin]";
            cout << "\n An assassin capable of deflecting and catching his opponents off guard."
                "\n A light and skilful style for the most experienced.";
            cout << "\n\n1) Select\n" << "2) See Others\n";
            cout << "\nOption: ";
            option = 0;
            cin >> option;
            if (option == '1')
            {
                weapons starter;
                starter.name = "Dagger";
                generate_character_stats(&player, &starter, &Inventory_slots[1]);
                is_class = false;
            }
            system("pause");
            system("cls");
            break;
        case'3':
            cout << "\n\n[Archer]";
            cout << "\n A skilled Archer, who kills his enemies from a distance."
                "\n Dodge and go down little by little his victims leaving unharmed.";
            cout << "\n\n1) Select\n" << "2) See Others\n";
            cout << "\nOption: ";
            option = 0;
            cin >> option;
            if (option == '1')
            {
                weapons starter;
                starter.name = "Bow";
                generate_character_stats(&player, &starter, &Inventory_slots[1]);
                is_class = false;
            }
            system("pause");
            system("cls");
            break;
        default:
            cout << "error\n";
            system("pause");
            system("cls");
            break;
        }

    }

    /*{
        Inventory_slots[1].item_name = "Katana";
        Inventory_slots[1].en_uso = true;
        Inventory_slots[1].item_description = "una katana muy molona";
        Inventory_slots[1].price = 500;
        Inventory_slots[1].quantity = 1;
        Inventory_slots[1].type = "weapons";
        Inventory_slots[1].Weapon_Attack_dices_number = 1;
        Inventory_slots[1].Weapon_Attack_dices_types = "Heavy";
        Inventory_slots[1].Weapon_defensive_dices_types = "Shield";
        Inventory_slots[1].Weapon_defensive_dices_number = 1;
        Inventory_slots[1].Weapon_name = "Katana";
        Inventory_slots[1].Weapon_speed = 2;

        Inventory_slots[2].en_uso = true;
        Inventory_slots[2].heal_hp = 30;
        Inventory_slots[2].item_description = "Su color rojo es cuestionable, me pregunto a que sabra";
        Inventory_slots[2].item_name = "pocion menor";
        Inventory_slots[2].price = 10;
        Inventory_slots[2].quantity = 1;
        Inventory_slots[2].type = "Potion";
    }*/

    while (is_playing)
    {

        cout << "[player: " << player.name << "] " << "[";
        hp(player.hp, player.current_hp);
        cout << "]" << endl;
        cout << "[Gold:" << player.money << "]\n\n";
        cout << "1) Show Stats\n" << "2) Show Inventory\n" << "3) Go adventure\n";

        cout << "\nOption: ";
        option = 0;
        cin >> option;

        switch (option)
        {
        case '1':
        {
            system("pause");
            system("cls");

            cout << "[player: " << player.name << "] " << "[";
            hp(player.hp, player.current_hp);
            cout << "]" << endl;
            cout << "[Gold:" << player.money << "]\n\n";
            cout << "Attack [Types of Dice: " << player.Attack_dices_types << "  Quantity: " << player.Attack_dices_number << "]\n";
            cout << "Defend [Types of Dice: " << player.defensive_dices_types << "  Quantity: " << player.defensive_dices_number << "]\n";
            cout << "Speed [" << player.speed << "]\n\n";

            cout << "[Weapon:" << player.Weapon_name << "]\n";
            cout << "Attack [Types of Dice: " << player.Weapon_Attack_dices_types << "  Quantity: " << player.Weapon_Attack_dices_number << "]\n";
            cout << "Defend [Types of Dice: " << player.Weapon_defensive_dices_types << "  Quantity: " << player.Weapon_defensive_dices_number << "]\n";
            cout << "Speed [" << player.Weapon_speed << "]\n";

            system("pause");
            system("cls");
        };
        break;
        case '2':
            is_inventory = true;
            while (is_inventory)
            {
                system("pause");
                system("cls");
                int b = 1;
                int lugar_opciones[10000] = { 0 };
                cout << "[player: " << player.name << "] " << "[";
                hp(player.hp, player.current_hp);
                cout << "]" << endl;
                cout << "[Gold:" << player.money << "]\n";

                for (size_t i = 0; i != 10; i++)
                {
                    if (Inventory_slots[i].en_uso)
                    {
                        lugar_opciones[b] = i;
                        cout << b << ") " << Inventory_slots[i].item_name;
                        for (int a = 0; a != 25 - Inventory_slots[i].item_name.length() - std::to_string(b).length(); a++)
                        {
                            cout << " ";
                        }
                        cout << Inventory_slots[i].quantity << " Quantity\n";
                        b++;
                    }
                }

                cout << endl << "1) Show info\n" << "2) Equip/Use\n" << "3) Drop\n" << "4) Go back\n";

                cout << "\nOption: ";
                option = 0;
                cin >> option;
                int number_of_item = 0;
                switch (option)
                {
                case'1':
                    cout << "\nNumber of the item: ";
                    number_of_item = 0;
                    cin >> number_of_item;
                    show(&Inventory_slots[lugar_opciones[number_of_item]]);


                    break;
                case'2':
                    cout << "\nNumber of the item: ";
                    number_of_item = 0;
                    cin >> number_of_item;
                    show(&Inventory_slots[lugar_opciones[number_of_item]]);
                    if (Inventory_slots[lugar_opciones[number_of_item]].type == "weapons")
                    {
                        cout << "\n1) equip";
                        cout << "\n2) Go back";

                        cout << "\n\nOption: ";
                        option = 0;
                        cin >> option;
                        switch (option)
                        {
                        case'1':
                            equip(&Inventory_slots[lugar_opciones[number_of_item]], &player);
                            break;
                        default:
                            break;
                        }
                    }
                    else if (Inventory_slots[lugar_opciones[number_of_item]].type == "Potion")
                    {
                        cout << "\n1) Use";
                        cout << "\n2) Go back";

                        cout << "\n\nOption: ";
                        option = 0;
                        cin >> option;
                        switch (option)
                        {
                        case'1':
                            use_potion(&Inventory_slots[lugar_opciones[number_of_item]], &player);
                            break;
                        default:
                            break;
                        }
                    }
                    break;
                case'3':
                    cout << "\nNumber of the item: ";
                    number_of_item = 0;
                    cin >> number_of_item;
                    show(&Inventory_slots[lugar_opciones[number_of_item]]);
                    cout << "\n1) drop";
                    cout << "\n2) Go back";

                    cout << "\n\nOption: ";
                    option = 0;
                    cin >> option;
                    switch (option)
                    {
                    case'1':
                        drop(&Inventory_slots[lugar_opciones[number_of_item]], &player);
                        break;
                    default:
                        break;
                    }
                    break;
                case'4':
                    is_inventory = false;
                    system("pause");
                    system("cls");
                    break;
                default:
                    cout << "error\n";
                    system("pause");
                    system("cls");
                    break;
                }
            }
            /*Inventory(&Inventory_slots[1], &player);*/
            break;
        case '3':
            is_adventure = true;
            while (is_adventure)
            {
                system("pause");
                system("cls");
                if (slots[0].in_use == false || slots[1].in_use == false || slots[2].in_use == false)
                {
                    generate_event_type(&slots[0]);
                    generate_event_type(&slots[1]);
                    generate_event_type(&slots[2]);
                    generate_event(&slots[0]);
                    generate_event(&slots[1]);
                    generate_event(&slots[2]);
                }

                cout << "[events]\n";
                cout << "\n1)"; show_events(&slots[0]);
                cout << "\n2)"; show_events(&slots[1]);
                cout << "\n3)"; show_events(&slots[2]);
                cout << "\n4) Go back to menu.";  cout << endl;
                cout << "\nOption: ";
                option = 0;
                cin >> option;

                system("pause");
                system("cls");

                switch (option)
                {
                case'1':
                    if (slots[0].event_type == "Mistery")
                    {

                    }
                    else if (slots[0].event_type == "Fight")
                    {
                        if (battle(&slots[0], &enemigo, &player, Inventory_slots) == 0)
                        {
                            system("pause");
                            system("cls");
                            cout << "\nyou die...\n";
                            system("pause");
                            system("cls");
                            return 0;

                        };

                        loot(&player, Inventory_slots);

                    }
                    else if (slots[0].event_type == "Rest")
                    {
                        rest(&player, Inventory_slots);
                    }
                    else if (slots[0].event_type == "Shop")
                    {
                        shop(&player, Inventory_slots);
                    }
                    else if (slots[0].event_type == "Loot")
                    {
                        loot(&player, Inventory_slots);
                    }

                    slots[0].in_use = false;
                    break;
                case'2':
                    if (slots[1].event_type == "Mistery")
                    {

                    }
                    else if (slots[1].event_type == "Fight")
                    {
                        if (battle(&slots[1], &enemigo, &player, Inventory_slots) == 0)
                        {
                            system("pause");
                            system("cls");
                            cout << "\nyou die...\n";
                            system("pause");
                            system("cls");
                            return 0;
                        };

                        loot(&player, Inventory_slots);
                    }
                    else if (slots[1].event_type == "Rest")
                    {
                        rest(&player, Inventory_slots);
                    }
                    else if (slots[1].event_type == "Shop")
                    {
                        shop(&player, Inventory_slots);
                    }
                    else if (slots[1].event_type == "Loot")
                    {
                        loot(&player, Inventory_slots);
                    }
                    slots[0].in_use = false;
                    break;
                case'3':
                    if (slots[2].event_type == "Mistery")
                    {

                    }
                    else if (slots[2].event_type == "Fight")
                    {
                        if (battle(&slots[2], &enemigo, &player, Inventory_slots) == 0)
                        {
                            system("pause");
                            system("cls");
                            cout << "\nyou die...\n";
                            system("pause");
                            system("cls");
                            return 0;
                        };

                        loot(&player, Inventory_slots);
                    }
                    else if (slots[2].event_type == "Rest")
                    {
                        rest(&player, Inventory_slots);
                    }
                    else if (slots[2].event_type == "Shop")
                    {
                        shop(&player, Inventory_slots);
                    }
                    else if (slots[2].event_type == "Loot")
                    {
                        loot(&player, Inventory_slots);
                    }
                    slots[0].in_use = false;
                    break;
                case'4':
                    is_adventure = false;
                    break;
                default:
                    cout << "error\n";
                    break;
                }
                break;
            };
            break;
        default:
            cout << "error\n";
            system("pause");
            system("cls");
            break;
        }

    }

    return 0;
}
