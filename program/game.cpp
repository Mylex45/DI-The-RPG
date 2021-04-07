#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "Classes.hpp"

using namespace std;

int main(void) {
  Item* items[50];
  Spell* spells[18];
  char name[30];
  int firespellcount = 0, icespellcount = 0, lightingspellcount = 0;
  for(int i = 0; i < 10; i++) {
    sprintf(name, "Weapon %d", i + 1);
    items[i] = new Weapon(name, 10 * (i / 2 + 1 + (i % 2 == 1)), i / 2 + 1, i + 1 + (i % 2 == 1), i % 2 == 0);
  }
  for(int i = 10; i < 20; i++) {
    sprintf(name, "Armor %d", i - 9);
    items[i] = new Armor(name, 10 * (i - 9), i - 9, i - 9);
  }
  for(int i = 20; i < 50; i++) {
    sprintf(name, "Potion %d", i - 19);
    items[i] = new Potion(name, 10 * ((i - 20) / 5 + 1), (i - 20) / 5 + 1, (i - 20) / 5 + 1, i);
  }
  for(int i = 0; i < 18; i++) {
    if(i % 3 == 0) {
      sprintf(name, "FireSpell %d", ++firespellcount);
      spells[i] = new FireSpell(name, 10 * (i / 3 + 1), i / 3 + 1, i / 4 + 1, i / 3 + 2, i / 3 + 1, i / 3);
    } else if (i % 3 == 1) {
      sprintf(name, "IceSpell %d", ++icespellcount);
      spells[i] = new IceSpell(name, 10 * (i / 3 + 1), i / 3 + 1, i / 4 + 1, i / 3 + 2, i / 3 + 1, i / 3);
    } else {
      sprintf(name, "LightingSpell %d", ++lightingspellcount);
      spells[i] = new LightingSpell(name, 10 * (i / 3 + 1), i / 3 + 1, i / 4 + 1, i / 3 + 2, i / 3 + 1, i / 3);
    }
  }

  // Hero creation

  int n;
  cout << "Enter number of heroes (must be between numbers 1-3)" << endl;
  cin >> n;
  while(n > 3 || n < 1) {
    cout << "Invalid number of heroes\nEnter number of heroes (must be between numbers 1-3)" << endl;
    cin >> n;
  }

  string hero_class, hero_name;
  Hero** team = new Hero*[n];
  for(int i = 0; i < n; i++) {
    cout << "Select a class for hero number " << i + 1 << "\nAvailable options: Sorcerer, Warrior, Paladin" << endl;
    cin >> hero_class;
    while(hero_class != "Sorcerer" && hero_class != "Warrior" && hero_class != "Paladin") {
      cout << "Invalid class, try again" << endl;
      cout << "Select a class for hero number " << i + 1 << "\nAvailable options: Sorcerer, Warrior, Paladin" << endl;
      cin >> hero_class;
    }
    if(hero_class == "Sorcerer") {
      cout << "Name: ";
      cin >> hero_name;
      team[i] = new Sorcerer(hero_name);
    } else if(hero_class == "Warrior") {
      cout << "Name: ";
      cin >> hero_name;
      team[i] = new Warrior(hero_name);
    } else if(hero_class == "Paladin") {
      cout << "Name: ";
      cin >> hero_name;
      team[i] = new Paladin(hero_name);
    }
  }

  srand(time(NULL));
  Grid world(20, 20, items, spells);
  world.display();

  // At this point, the player has full control of the game and can do any actions are available

  string command, direction;
  int selection, number;
  cout << "Available commands: checkInventory, displayStats, move, displayMap, shop, quitGame" << endl;
  cin >> command;
  while(command != "quitGame") {
    bool equip = false;
    bool use = false;
    if(command == "checkInventory") {
      cout << "\nSelect a hero whose inventory you want to check" << endl << "Available options: ";
      for(int i = 0; i < n; i++) {
        cout << i + 1 << " ";
      }
      cout << endl;
      cin >> selection;
      team[selection - 1]->checkInventory();
    } else if(command == "move") {
      cout << "Select direction\nAvailable options: up, down, left, right" << endl;
      cin >> direction;
      if(direction != "up" && direction != "down" && direction != "left" && direction != "right") {
        cout << "invalid direction" << endl;
      } else {
        world.move(team, n, direction);
      }
    } else if(command == "equip") {
      cout << "Select hero\nAvailable options: ";
      for(int i = 0; i < n; i++) {
        if(!team[i]->has_no_armor() || !team[i]->has_no_weapons()) {
          cout << i + 1 << " ";
        }
      }
      cout << endl;
      cin >> selection;
      team[selection - 1]->checkInventory();
      if(team[selection - 1]->has_no_weapons() && team[selection - 1] ->has_no_armor()) {
        cout << "Invalid hero for command <equip>" << endl;
      } else {
        cout << "Select item number to equip (Must be armor or weapon)" << endl;
        cin >> number;
        team[selection - 1]->equip(number - 1);
      }
    } else if(command == "use") {
      cout << "Select hero\nAvailable options: ";
      for(int i = 0; i < n; i++) {
        if(!team[i]->has_no_potions()) {
          cout << i + 1 << " ";
        }
      }
      cout << endl;
      cin >> selection;
      team[selection - 1]->checkInventory();
      if(team[selection - 1]->has_no_potions()) {
        cout << "Invalid hero for command <use>" << endl;
      } else {
        cout << "Select potion number to use (Must be a potion)" << endl;
        cin >> number;
        team[selection - 1]->use(number - 1);
      }
    } else if(command == "shop") {
      world.shop(team, n);
    } else if(command == "displayStats") {
      cout << "Select hero whose stats you want to be displayed" << endl;
      cout << "Available options: ";
      for(int j = 0; j < n; j++) {
        cout << j + 1 << " ";
      }
      cout << endl;
      int i;
      cin >> i;
      if(i < 1)
        i = 1;
      else if(i > n)
        i = n;
      team[i - 1]->displayStats();
    } else if(command == "displayMap"){
      world.display();
    }
    cout << "Available commands: checkInventory, displayStats, move, displayMap, quitGame";
    if(world.check_on_market()) {
      cout << ", shop";
    }
    for(int i = 0; i < n; i++) {
      if(!team[i]->has_no_potions()) {
        use = true;
      }
      if(!team[i]->has_no_armor() || !team[i]->has_no_weapons()) {
        equip = true;
      }
    }
    if(use) {
      cout << ", use";
    }
    if(equip) {
      cout << ", equip";
    }
    cout << endl;
    cin >> command;
  }



  for(int i = 0; i < 30; i++)
    delete items[i];

  for(int i = 0; i < 10; i++)
    delete spells[i];

  for(int i = 0; i < n; i++)
    delete team[i];
  delete[] team;

  return 0;
}
