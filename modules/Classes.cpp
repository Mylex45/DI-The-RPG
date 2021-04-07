#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include "Classes.hpp"

using namespace std;

//////////////////////// Helpful functions ////////////////

static string attribute_to_string(const int attr) {
  if(!attr)
    return "Strength";
  else if(attr == 1)
    return "Dexterity";
  else if(attr == 2)
    return "Agility";
  else if(attr == 3)
    return "Health";
  else
    return "Magic";
}

static bool are_dead(Living** team, const int n) {
  for(int i = 0; i < n; i++) {
    if(team[i]->get_currentHP() > 0)
      return false;
  }
  return true;
}

static void regenerate_hp(Living** team, const int n) {
  for(int i = 0; i < n; i++) {
    if(team[i]->get_currentHP() > 0) {
      team[i]->set_currentHP(team[i]->get_currentHP() + 0.1 * team[i]->get_maxHP());
      if(team[i]->get_currentHP() > team[i]->get_maxHP())
        team[i]->set_currentHP(team[i]->get_maxHP());
    }
  }
}

static void regenerate_mp(Hero** team, const int n) {
  for(int i = 0; i < n; i++) {
    if(team[i]->get_currentHP() > 0 && team[i]->get_currentMP() < team[i]->get_maxMP()) {
      team[i]->set_currentMP(team[i]->get_currentMP() + 0.1 * team[i]->get_maxMP());
      if(team[i]->get_currentMP() > team[i]->get_maxMP())
        team[i]->set_currentMP(team[i]->get_maxMP());
    }
  }
}

//////////////////////// Accessors //////////////////////

string Item::get_name() const {
  return name;
}

int Item::get_price() const {
  return price;
}

int Item::get_required_level() const {
  return req_lev;
}

int Weapon::get_damage() const {
  return damage;
}

bool Weapon::is_one_handed() const {
  return one_handed;
}

int Armor::get_defense() const {
  return defense;
}

int Potion::get_boost() const {
  return attr_boost;
}

int Potion::get_type() const {
  return attr_type;
}

string Spell::get_name() const {
  return name;
}

int Spell::get_price() const {
  return price;
}

int Spell::get_required_level() const {
  return req_lev;
}

int Spell::get_lowest_damage() const {
  return lowest_damage;
}

int Spell::get_highest_damage() const {
  return highest_damage;
}

int Spell::get_cost() const {
  return magic_cost;
}

int IceSpell::get_damage_red() const {
  return damage_reduction;
}

int FireSpell::get_defense_reduction() const {
  return defense_reduction;
}

int LightingSpell::get_dodge_reduction() const {
  return dodge_reduction;
}

int Debuff::get_amount() const {
  return amount;
}

string Debuff::get_type() const {
  return type;
}

int Debuff::get_rounds() const {
  return rounds;
}

string Living::get_name() const {
  return name;
}

int Living::get_level() const {
  return level;
}

int Living::get_maxHP() const {
  return maxhealthPower;
}

int Living::get_currentHP() const {
  return currenthealthPower;
}

int Hero::get_defense() const {
  return defense;
}

int Hero::get_money() const {
  return money;
}

int Hero::get_experience() const {
  return experience;
}

int Hero::get_damage() const {
  return damage;
}

int Hero::get_agility() const {
  return agility;
}

int Hero::get_maxMP() const {
  return maxMagicPower;
}

int Hero::get_currentMP() const {
  return currentMagicPower;
}

int Monster::get_dodge_chance() const {
  return dodge_chance;
}

int Monster::get_defense() const {
  return defense;
}

int Monster::get_min_dmg() const {
  return lowest_damage;
}

int Monster::get_max_dmg() const {
  return highest_damage;
}

Item** Market::get_items() const {
  return item_array;
}

Spell** Market::get_spells() const {
  return spell_array;
}

bool Grid::check_on_market() const {
  if(dynamic_cast<Market*>(map[x][y]))
    return true;
  return false;
}

///////////////////// Mutators ////////////////////////////

void Living::set_maxHP(const int newmaxHP) {
  maxhealthPower = newmaxHP;
}

void Living::set_currentHP(const int newcurrentHP) {
  currenthealthPower = newcurrentHP;
}

void Hero::str_increase(const int s) {
  strength += s;
}

void Hero::dex_increase(const int d) {
  dexterity += d;
}

void Hero::agi_increase(const int a) {
  agility += a;
}

void Hero::health_increase(const int h) {
  currenthealthPower += h;
  if(currenthealthPower > maxhealthPower) {
    set_currentHP(maxhealthPower);
  }
}

void Hero::magic_increase(const int h) {
  currentMagicPower += h;
  if(currentMagicPower > maxMagicPower) {
    set_currentMP(maxMagicPower);
  }
}

void Hero::increase_money(const int m) {
  money += m;
}

void Hero::increase_experiece(const int e) {
  experience += e;
}

void Hero::set_currentMP(const int m) {
  currentMagicPower = m;
}

void Monster::set_min_dmg(const int dmg) {
  lowest_damage = dmg;
}

void Monster::set_max_dmg(const int dmg) {
  highest_damage = dmg;
}

void Monster::set_defense(const int defense_) {
  defense = defense_;
}

void Monster::set_dodge(const int dodge_) {
  dodge_chance = dodge_;
}

void Square::set_team_on(bool b) {
  is_team_on = b;
}

/////////////////// Constructors ////////////////////////

Item::Item(string name_, const int price_, const int level)
  : name(name_), price(price_), req_lev(level) {

}

Weapon::Weapon(string name_, const int price_, const int level, const int damage_, const bool one_handed_)
  : Item(name_, price_, level), damage(damage_), one_handed(one_handed_) {

}

Armor::Armor(string name_, const int price_, const int level, const int defense_)
  : Item(name_, price_, level), defense(defense_) {

}

Potion::Potion(string name_, const int price_, const int level, const int attr_boost_, const int attr_type_)
  : Item(name_, price_, level), attr_boost(attr_boost_), attr_type(attr_type_ % 5) {

}

Spell::Spell(string name_, const int price_, const int level, const int l_damage, const int h_damage, const int m_cost)
  : name(name_), price(price_), req_lev(level), lowest_damage(l_damage), highest_damage(h_damage), magic_cost(m_cost) {

}

IceSpell::IceSpell(string name_, const int p, const int l, const int l_d, const int h_d, const int m_c, const int d_r)
  : Spell(name_, p, l, l_d, h_d, m_c), damage_reduction(d_r) {

}

FireSpell::FireSpell(string name_, const int p, const int l, const int l_d, const int h_d, const int m_c, const int d_r)
  : Spell(name_, p, l, l_d, h_d, m_c), defense_reduction(d_r) {

}

LightingSpell::LightingSpell(string name_, const int p, const int l, const int l_d, const int h_d, const int m_c, const int d_r)
  : Spell(name_, p, l, l_d, h_d, m_c), dodge_reduction(d_r) {

}

Debuff::Debuff(const int rounds_, const int amount_, string type_)
  : rounds(rounds_), amount(amount_), type(type_) {

}

Living::Living(string name_, const int level_, const int maxHP)
  : name(name_), level(level_), maxhealthPower(maxHP), currenthealthPower(maxHP) {

}

Hero::Hero(string name_)
  : Living(name_, 1, 10), currentMagicPower(5), maxMagicPower(5), strength(10), dexterity(10), agility(10),  money(0), experience(0), damage(2), defense(1), weapon(NULL), armor(NULL)  {

}

Warrior::Warrior(string n)
  : Hero(n), extr_str_per_level(2), extr_agi_per_level(2) {

}

Sorcerer::Sorcerer(string n)
  : Hero(n), extr_dex_per_level(2), extr_agi_per_level(2) {

}

Paladin::Paladin(string n)
  : Hero(n), extr_str_per_level(2), extr_dex_per_level(2) {

}

Monster::Monster(string n, const int l, const int maxHP, const int l_d, const int h_d, const int d, const int d_c)
  : Living(n, l, maxHP), lowest_damage(l_d), highest_damage(h_d), defense(d), dodge_chance(d_c) {

}

Dragon::Dragon(string n, const int l, const int maxHP, const int l_d, const int h_d, const int d, const int d_c)
  : Monster(n, l, maxHP, l_d + 2, h_d + 2, d, d_c) {

}

Exoskeleton::Exoskeleton(string n, const int l, const int maxHP, const int l_d, const int h_d, const int d, const int d_c)
  : Monster(n, l, maxHP, l_d, h_d, d + 2, d_c) {

}

Spirit::Spirit(string n, const int l, const int maxHP, const int l_d, const int h_d, const int d, const int d_c)
  : Monster(n, l, maxHP, l_d, h_d, d, d_c + 10) {

}

Square::Square()
  : is_team_on(false) {

}

Market::Market(Item** items, Spell** spells)
  : item_array(items), spell_array(spells) {

}

Grid::Grid(const int size_x, const int size_y, Item** items, Spell** spells)
  : lines(size_x), columns(size_y) {

  cout << "Generating new world" << endl;
  map = new Square**[lines];
  for(int i = 0; i < size_x; i++) {
    map[i] = new Square*[columns];
  }
  for(int i = 0; i < lines; i++) {
    map[i][0] = new nonAccessible();
    map[i][size_y - 1] = new nonAccessible();
  }
  for(int i = 1; i < columns - 1; i++) {
    map[0][i] = new nonAccessible();
    map[size_x - 1][i] = new nonAccessible();
  }
  for(int i = 1; i < size_x - 1; i++) {
    for(int j = 1; j < size_y - 1; j++) {
      int random = rand() % 101;
      if(random <= 10) {
        map[i][j] = new Market(items, spells);
        x = i;
        y = j;
      } else {
        map[i][j] = new Common();
      }
    }
  }
  map[x][y]->set_team_on(true);
}

//////////////////////////// Deconstructors ////////////////////////

Grid::~Grid() {
  cout << "Deleting world" << endl;
  for(int i = 0; i < lines; i++) {
    for(int j = 0; j < columns; j++) {
      delete map[i][j];
    }
    delete[] map[i];
  }
  delete[] map;
}

////////////////////// Move function ////////////////////////////

void Grid::move(Hero** team, const int n, string direction) {
  if(direction == "up") {
    if(x == 1) {
      cout << "Invalid move, (nonAccessible Square)" << endl;
    } else {
      map[x][y]->set_team_on(false);
      map[--x][y]->set_team_on(true);
    }
  } else if(direction == "down") {
    if(x == lines - 2) {
      cout << "Invalid move, (nonAccessible Square)" << endl;
    } else {
      map[x][y]->set_team_on(false);
      map[++x][y]->set_team_on(true);
    }
  } else if(direction == "left") {
    if(y == 1) {
      cout << "Invalid move, (nonAccessible Square)" << endl;
    } else {
      map[x][y]->set_team_on(false);
      map[x][--y]->set_team_on(true);
    }
  } else {
    if(y == columns - 2) {
      cout << "Invalid move, (nonAccessible Square)" << endl;
    } else {
      map[x][y]->set_team_on(false);
      map[x][++y]->set_team_on(true);
    }
  }
  if(dynamic_cast<Common*>(map[x][y])) {
    int random = rand() % 101;
    if(random <= 25) {
      int num_of_monsters = rand() % n + 1, num_of_dragons = 0, num_of_exoskeletons = 0, num_of_spirits = 0;
      int average_damage = 0, average_defense = 0, average_level = 0, average_HP = 0;
      char name[32];
      Monster** monsters = new Monster*[num_of_monsters];
      for(int i = 0; i < n; i++) {
        average_defense += team[i]->get_defense();
        average_damage += team[i]->get_damage();
        average_level += team[i]->get_level();
        average_HP += team[i]->get_maxHP();
      }
      average_damage /= (n + 1);
      average_defense /= (n + 1);
      average_HP /= (n + 1);
      average_level /= (n + 1);
      for(int i = 0; i < num_of_monsters; i++) {
        int type = rand() % 3;
        if(type == 0) {
          sprintf(name, "Dragon %d", ++num_of_dragons);
          monsters[i] = new Dragon(name, average_level, average_HP, average_damage - 2, average_damage, average_defense, 10);
        } else if(type == 1) {
          sprintf(name, "Exoskeleton %d", ++num_of_exoskeletons);
          monsters[i] = new Exoskeleton(name, average_level, average_HP, average_damage - 2, average_damage, average_defense, 10);
        } else {
          sprintf(name, "Spirit %d", ++num_of_spirits);
          monsters[i] = new Spirit(name, average_level, average_HP, average_damage - 2, average_damage, average_defense, 10);
        }
      }
      Common* square = (Common*)map[x][y];
      square->battle(team, n, monsters, num_of_monsters);
      for(int i = 0; i < num_of_monsters; i++) {
        delete monsters[i];
      }
      delete[] monsters;
    }
  }
}

void Grid::shop(Hero** team, const int n) {
  if(Market* square = dynamic_cast<Market*>(map[x][y])) {
    Item** items = square->get_items();
    Spell** spells = square->get_spells();
    int hero_number, number;
    string category, action;
    cout << "Select hero to shop\nAvailable options: ";
    for(int i = 0; i < n; i++) {
      cout << i + 1 << "/";
    }
    cout << endl;
    cin >> hero_number;
    cout << "Select action:\nAvailable options: buy, sell" << endl;
    cin >> action;
    if(action == "buy") {
      cout << "Select category\nAvailable options: Item, Spell" << endl;
      cin >> category;
      if(category == "Item") {
        square->print_items();
        cout << "Select the number of the item you wish to buy" << endl;
        cin >> number;
        team[hero_number - 1]->buy(items[number - 1]);
      } else if(category == "Spell") {
        square->print_spells();
        cout << "Select the number of the spell you wish to buy" << endl;
        cin >> number;
        team[hero_number - 1]->buy(spells[number - 1]);
      } else {
        cout << "Invalid category" << endl;
      }
    } else if(action == "sell") {
      cout << "Select category\nAvailable options: Item, Spell" << endl;
      cin >> category;
      if(category == "Item") {
        team[hero_number - 1]->checkInventory();
        if(!team[hero_number - 1]->has_no_items()) {
          cout << "Select the number of the item you wish to sell" << endl;
          cin >> number;
          team[hero_number - 1]->sell_item(number - 1);
        }
      } else if(category == "Spell") {
        team[hero_number - 1]->checkSpellbook();
        if(!team[hero_number - 1]->has_no_spells()) {
          cout << "Select the number of the spell you wish to sell" << endl;
          cin >> number;
          team[hero_number - 1]->sell_spell(number - 1);
        }
      } else {
        cout << "Invalid category" << endl;
      }
    } else {
        cout << " Invalid action" << endl;
    }
  }
}

////////////////////// Spells' special effects //////////////////

void IceSpell::special_effect(Monster* m) const {
  m->set_min_dmg(m->get_min_dmg() - damage_reduction);
  if(m->get_min_dmg() < 0)
    m->set_min_dmg(0);
  m->set_max_dmg(m->get_max_dmg() - damage_reduction);
  if(m->get_max_dmg() < 0)
    m->set_max_dmg(0);
  Debuff* d = new Debuff(3, damage_reduction, "dmg_r");
  m->add_debuff(d);
}

void FireSpell::special_effect(Monster* m) const {
  m->set_defense(m->get_defense() - defense_reduction);
  if(m->get_defense() < 0)
    m->set_defense(0);
  Debuff* d = new Debuff(3, defense_reduction, "def_r");
  m->add_debuff(d);
}

void LightingSpell::special_effect(Monster* m) const {
  m->set_dodge(m->get_dodge_chance() - dodge_reduction);
  if(m->get_dodge_chance() < 0)
    m->set_dodge(0);
  Debuff* d = new Debuff(3, dodge_reduction, "dod_r");
  m->add_debuff(d);
}

////////////////////// Hero functions /////////////////////////////

void Hero::use(const int i) {
  if(Potion* p = dynamic_cast<Potion*>(inventory.at(i))) {
    if(p->get_type() == 0) {
      str_increase(p->get_boost());
    } else if(p->get_type() == 1) {
      dex_increase(p->get_boost());
    } else if (p->get_type() == 2) {
      agi_increase(p->get_boost());
    } else if(p->get_type() == 3) {
      health_increase(p->get_boost());
    } else {
      magic_increase(p->get_boost());
    }
    inventory.erase(inventory.begin() + i);
  } else {
    cout << "Given item is not a potion" << endl;
  }

}

void Hero::equip(const int i) {
  Item* item = inventory.at(i);
  if(Weapon* w = dynamic_cast<Weapon*>(item)) {
    if(weapon == NULL) {
      damage += w->get_damage();
      weapon = w;
    } else {
      damage -= weapon->get_damage();
      damage += w->get_damage();
      inventory.push_back(weapon);
      weapon = w;
    }
  } else if(Armor* a = dynamic_cast<Armor*>(item)) {
    if(armor == NULL) {
      defense += a->get_defense();
      armor = a;
    } else {
      defense -= armor->get_defense();
      defense += a->get_defense();
      inventory.push_back(armor);
      armor = a;
    }
  } else {
    cout << "Given item is not weapon/armor" << endl;
  }
  inventory.erase(inventory.begin() + i);
}

void Hero::buy(Item* i) {
  if(i->get_price() <= this->money) {
    this->money -= i->get_price();
    inventory.push_back(i);
  } else {
    cout << i->get_name() << " is too expensive to buy!" << endl;
  }
}

void Hero::buy(Spell* s) {
  if(s->get_price() <= this->money) {
    this->money -= s->get_price();
    spellbook.push_back(s);
  } else {
    cout << s->get_name() << " is too expensive to buy!" << endl;
  }
}

void Hero::sell_item(const int index) {
  if(index < inventory.size()) {
    Item* item = inventory.at(index);
    cout << item->get_name() << " sold!" << endl;
    this->money += item->get_price() / 2;
    inventory.erase(inventory.begin() + index);
  } else {
    cout << "Could not find given item in inventory" << endl;
  }
}

void Hero::sell_spell(const int index) {
  if(index < spellbook.size()) {
    Spell* spell = spellbook.at(index);
    cout << spell->get_name() << " sold!" << endl;
    this->money += spell->get_price() / 2;
    spellbook.erase(spellbook.begin() + index);
  } else {
    cout << "Could not find given spell in inventory" << endl;
  }
}

void Hero::checkInventory() const {
  if(inventory.size() == 0) {
    cout << name << "'s inventory is empty" << endl;
  } else {
    cout << name << "'s inventory consists of:" << endl;
    int counter = 0;
    for(Inventory::const_iterator i = inventory.begin(); i != inventory.end(); ++i) {
        Item* item = *i;
        cout << ++counter << ")" << " ";
        item->display();
    }
  }
}

void Hero::checkSpellbook() const {
  if(spellbook.size() == 0){
    cout << name << "'s spellbook is empty" << endl;
  } else {
    cout << name << "'s spellbook consists of:" << endl;
    int counter = 0;
    for(Spellbook::const_iterator i = spellbook.begin(); i != spellbook.end(); ++i) {
      Spell* spell = *i;
      cout << ++counter << ")" << " ";
      spell->display();
    }
  }
}

Spell* Hero::spell(const int i) {
  if(i < spellbook.size()) {
    return spellbook.at(i);
  } else {
    cout << "No spell found with number " << i + 1 << endl;
  }
}

bool Hero::has_no_items() const {
  return (inventory.size() == 0);
}

bool Hero::has_no_potions() const {
  for(Inventory::const_iterator i = inventory.begin(); i != inventory.end(); ++i) {
    if(dynamic_cast<Potion*>(*i)) {
      return false;
    }
  }
  return true;
}

bool Hero::has_no_spells() const {
  if(spellbook.size() == 0)
    return true;
  return false;
}

bool Hero::has_no_armor() const {
  for(Inventory::const_iterator i = inventory.begin(); i != inventory.end(); ++i) {
    if(dynamic_cast<Armor*>(*i)) {
      return false;
    }
  }
  return true;
}

bool Hero::has_no_weapons() const {
  for(Inventory::const_iterator i = inventory.begin(); i != inventory.end(); ++i) {
    if(dynamic_cast<Weapon*>(*i)) {
      return false;
    }
  }
  return true;
}

////////////////////// Debuff functions //////////////////////

void Debuff::update_for_round() {
  rounds--;
}

void Monster::add_debuff(Debuff* d) {
  debuffs.push_back(d);
}

void Monster::recover(const int stats, string type) {
  if(type == "dmg_r") {
    if(stats > lowest_damage && stats > highest_damage) {
      this->set_min_dmg(0);
      this->set_max_dmg(0);
    } else if(stats > lowest_damage && stats <= highest_damage) {
      this->set_min_dmg(0);
      this->set_max_dmg(highest_damage - stats);
    } else {
      this->set_min_dmg(stats - lowest_damage);
      this->set_max_dmg(stats - highest_damage);
    }
  } else if(type == "def_r") {
    this->set_defense(stats - defense);
  } else {
    this->set_dodge(stats - dodge_chance);
  }
}

void Monster::update_debuffs() {
  int counter = 0;
  for(Debuffs::const_iterator i = debuffs.begin(); i != debuffs.end(); ++i) {
    Debuff* d = *i;
    d->update_for_round();
    if(d->get_rounds() < 0) {
      this->recover(d->get_amount(), d->get_type());
      debuffs.erase(debuffs.begin() + counter);
      delete d;
    }
    counter++;
  }
}

///////////////////// Attack functions ///////////////////////

void Monster::attack(Hero* h) {
  if(h->get_currentHP() > 0) {
    cout << name << " attacks " << h->get_name();
    int random = rand() % (highest_damage - lowest_damage);
    int damage =  lowest_damage + random;
    int total_damage = damage - h->get_defense();
    if(total_damage < 0)
      total_damage = 0;
    if(rand() % 100 <= h->get_agility()) {
      cout << name << "'s attack was dodged" << endl;
    } else {
      h->set_currentHP(h->get_currentHP() - total_damage);
      cout << " for a total of " << total_damage << " damage!" << endl;
      if(h->get_currentHP() < 0)
        h->set_currentHP(0);
    }
  }
}

void Hero::deal_damage(int damage, Monster* m) {
  int total_damage = damage - m->get_defense();
  if(total_damage < 0)
    total_damage = 0;
  if(rand() % 100 <= m->get_dodge_chance()) {
    cout << endl << this->get_name() << "'s attack was dodged" << endl;
  } else {
    m->set_currentHP(m->get_currentHP() - total_damage);
    cout << " for a total of " << total_damage << " damage!" << endl;
    if(m->get_currentHP() < 0)
      m->set_currentHP(0);
  }
}

void Hero::attack(Monster* m) {
    cout << name << " attacks " << m->get_name();
    int damage = this->damage;
    deal_damage(damage, m);
}

void Hero::castSpell(Spell* s, Monster* m) {
  if(this->level >= s->get_required_level() && this->currentMagicPower >= s->get_cost()) {
    cout << name << " casts " << s->get_name() << " on " << m->get_name();
    int random = rand() % (s->get_highest_damage() - s->get_lowest_damage());
    int damage =  s->get_lowest_damage() + random;
    this->currentMagicPower -= s->get_cost();
    deal_damage(damage, m);
    s->special_effect(m);
  }
}

///////////////////// Battle function /////////////////////////

void Common::battle(Hero** team, const int n, Monster** monsters, const int m) {
  while(!are_dead((Living**)team, n) && !are_dead((Living**)monsters, m)) {
    string action;
    int i = 0, k = 0, selection;
    while(i < n) {
      cout << "Select category of action: Hero, displayStats" << endl;
      cin >> action;
      if(action == "displayStats") {
        cout << "Enter 0 to display the stats of a chosen monster" << endl;
        cout << "Enter 1 to display the stats of a chosen hero" << endl;
        cin >> selection;
        if(!selection) {
          cout << "Select a monster number" << endl << "Available options: ";
          for(int a = 0; a < m; a++) {
            cout << a + 1 << "/";
          }
          cout << endl;
          cin >> selection;
          if(selection > m || selection < 1) {
            cout << "Invalid selection" << endl;
            continue;
          } else {
            monsters[selection - 1]->displayStats();
          }
        } else if(selection == 1) {
          cout << "Select a hero number" << endl << "Available options: ";
          for(int a = 0; a < n; a++) {
            cout << a + 1 << "/";
          }
          cout << endl;
          cin >> selection;
          if(selection > n || selection < 1) {
            cout << "Invalid selection" << endl;
            continue;
          } else {
            team[selection - 1]->displayStats();
          }
        } else {
          cout << "Invalid selection" << endl;
        }
        continue;
      } else if(action == "Hero") {
        if(team[i]->get_currentHP() == 0)
          i++;
        cout << "Select " << team[i]->get_name() << "'s action\nAvailable options: attack";
        if(!team[i]->has_no_spells())
          cout << ", castSpell";
        if(!team[i]->has_no_potions())
          cout << ", use";
        cout << endl;
        cin >> action;
        if(action == "attack") {
          if(!m) {
            team[i++]->attack(monsters[0]);
          } else {
            cout << "Select which monster you want " << team[i]->get_name() << " to attack" << endl
              << "Must be between 1 and " << m << endl;
            cin >> selection;
            while(selection < 1 && selection > m) {
              cout << "Invalid monster number, try again" << endl << "Must be between 1 and " << m << endl;
              cin >> selection;
            }
            team[i++]->attack(monsters[selection - 1]);
          }
        } else if(action == "castSpell" && !team[i]->has_no_spells()) {
          cout << "Select a spell to cast" << endl;
          team[i]->checkSpellbook();
          cin >> selection;
          cout << "Select a monster to castSpell on\nAvailable options: ";
          for(int k = 0; k < m; k++) {
            cout << k + 1 << "/";
          }
          cout << endl;
          int monster_number;
          cin >> monster_number;
          team[i++]->castSpell(team[i]->spell(selection - 1), monsters[monster_number - 1]);
        } else if(action == "use" && !team[i]->has_no_potions()) {
          team[i]->checkInventory();
          cout << "Select potion number to use (Must be a potion)" << endl;
          cin >> selection;
          team[i++]->use(selection - 1);
          }
      }
    }
    i = 0;
    while(k < m) {
      if(are_dead((Living**)team, n))
        break;
      if(monsters[k]->get_currentHP() > 0) {
        int random_hero = rand() % n;
        while(team[random_hero]->get_currentHP() == 0) {
          random_hero = rand() % n;
        }
        monsters[k++]->attack(team[random_hero]);
      } else {
        k++;
        continue;
      }
    }
    k = 0;
    cout << "\nEnd of round!\nBoth alive Heroes and alive Monsters regenerate 10% of their Maximum Health Power!\n" << endl;
    regenerate_hp((Living**)team, n);
    regenerate_hp((Living**)monsters, m);
    regenerate_mp(team, n);
    for(int a = 0; a < m; a++) {
      monsters[a]->update_debuffs();
    }
  }
  if(are_dead((Living**)team, n)) {
    cout << "The monsters have won this battle!" << endl;
    for(int j = 0; j < n; j++) {
      team[j]->set_currentHP(team[j]->get_maxHP() / 2);
      team[j]->increase_money(-(team[j]->get_money() / 2));
    }
  } else {
    cout << "Heroes have won this battle!" << endl;
    for(int j = 0; j < n; j++) {
      if(team[j]->get_currentHP() == 0) {
        team[j]->set_currentHP(team[j]->get_maxHP() / 2);
      } else {
        team[j]->increase_money(3 + monsters[0]->get_level());
        team[j]->increase_experiece(2 + monsters[0]->get_level());
        if(team[j]->get_experience() >= 10 + team[j]->get_level()) {
          team[j]->levelUp();
        }
      }
    }
  }
}

////////////// LevelUp and stats_increase functions //////////

void Hero::levelUp() {
    experience -= 10 + level;
    cout << name << " has advanced to level " << ++level << "!" << endl;
    maxhealthPower += 1;
    currenthealthPower += 1;
    currentMagicPower += 1;
    maxMagicPower += 1;
    this->stats_increase();
}

void Warrior::stats_increase() {
  strength += 1 + extr_str_per_level;
  dexterity += 1;
  agility += 1 + extr_agi_per_level;
}

void Sorcerer::stats_increase() {
  strength += 1;
  dexterity += 1 + extr_dex_per_level;
  agility += 1 + extr_agi_per_level;
}

void Paladin::stats_increase() {
  strength += 1 + extr_str_per_level;
  dexterity += 1 + extr_dex_per_level;
  agility += 1;
}

/////////////////// Display functions ////////////////////////

void Weapon::display() const {
  string hands;
  if(one_handed == true) {
    hands = "one";
  } else {
    hands = "two";
  }
  cout << "Weapon: " << name << " Price: " << price << " Required level: " <<
    req_lev << " Damage: " << damage << " Hands required: " << hands << endl;
}

void Armor::display() const {
  cout << "Armor: " << name << " Price: " << price << " Required level: " <<
    req_lev << " Defense: " << defense << endl;
}

void Potion::display() const {
  string type = attribute_to_string(attr_type);
  cout << type << " potion: " << name << " Price: " << price << " Required level: " <<
    req_lev << " " << type << " boost: " << attr_boost << endl;
}

void Spell::display() const {
  cout << name << " Price: " << price << " Required level: " << req_lev << " Minimum damage: " <<
    lowest_damage << " Maximum damage: " << highest_damage << " Magic cost: " << magic_cost << endl;
}

void Hero::displayStats() const {
  cout << "Hero name: " << name << "\nLevel: " << level << "\nHealthPower: " << currenthealthPower
    << "/" << maxhealthPower << "\nStrength: " << strength << "\nDexterity: " << dexterity
    << "\nAgility: " << agility << "\nDamage: " << damage << "\nDefense: " << defense
    << "\nMoney: " << money << "\nExperience: " << experience << "/10" << endl;
}

void Monster::displayStats() const {
  cout << "Monster name: " << name << "\nLevel: " << level << "\nHealthPower: " << currenthealthPower
    << "/" << maxhealthPower << "\nMinimum damage: " << lowest_damage << "\nMaximum damage: " << highest_damage
    << "\nDodge chance: " << dodge_chance << "%\nDefense: " << defense << endl;
}

void Common::display() const {
  if(!is_team_on)
    cout << "[C]";
  else
    cout << "[C/T]";
}

void Market::display() const {
  if(!is_team_on)
    cout << "[M]";
  else
    cout << "[M/T]";
}

void Market::print_items() {
  for(int i = 0; i < 50; i++) {
    cout << i + 1 << ") ";
    item_array[i]->display();
  }
}

void Market::print_spells() {
  for(int i = 0; i < 18; i++) {
    cout << i + 1 << ")";
    spell_array[i]->display();
  }
}

void nonAccessible::display() const {
  cout << "[NA]";
}

void Grid::display() const {
  for(int i = 0; i < lines; i++) {
    for(int j = 0; j < columns; j++) {
      map[i][j]->display();
      cout << '\t';
    }
    cout << endl;
  }
}
