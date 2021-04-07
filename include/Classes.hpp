#include <string>
#include <vector>

using namespace std;

class Monster;

class Item {
  protected:
    string name;
    int price, req_lev;
  public:
    Item(string, const int, const int);
    string get_name() const;
    int get_price() const;
    int get_required_level() const;
    virtual void display() const = 0;
};

typedef vector<Item*> Inventory;

class Weapon : public Item {
  private:
    int damage;
    bool one_handed;
  public:
    Weapon(string, const int, const int, const int, const bool);
    int get_damage() const;
    bool is_one_handed() const;
    void display() const;
};

class Armor : public Item {
  private:
    int defense;
  public:
    Armor(string, const int, const int, const int);
    int get_defense() const;
    void display() const;
};

class Potion : public Item {
  private:
    int attr_boost, attr_type;
    bool used;
  public:
    Potion(string, const int, const int, const int, const int);
    int get_boost() const;
    int get_type() const;
    bool is_used() const;
    void use();
    void display() const;
};

class Spell {
  protected:
    string name;
    int price, req_lev, lowest_damage, highest_damage, magic_cost;
  public:
    Spell(string, const int, const int, const int, const int, const int);
    string get_name() const;
    int get_price() const;
    int get_required_level() const;
    int get_lowest_damage() const;
    int get_highest_damage() const;
    int get_cost() const;
    virtual void special_effect(Monster*) const = 0;
    void display() const;
};

typedef vector<Spell*> Spellbook;

class IceSpell : public Spell {
  private:
    int damage_reduction;
  public:
    IceSpell(string, const int, const int, const int, const int, const int, const int);
    int get_damage_red() const;
    void special_effect(Monster*) const;
};

class FireSpell : public Spell {
  private:
    int defense_reduction;
  public:
    FireSpell(string, const int, const int, const int, const int, const int, const int);
    int get_defense_reduction() const;
    void special_effect(Monster*) const;
};

class LightingSpell : public Spell {
  private:
    int dodge_reduction;
  public:
    LightingSpell(string, const int, const int, const int, const int, const int, const int);
    int get_dodge_reduction() const;
    void special_effect(Monster*) const;
};

class Debuff {
  private:
    int rounds, amount;
    string type;
  public:
    Debuff(const int, const int, string);
    void update_for_round();
    string get_type() const;
    int get_amount() const;
    int get_rounds() const;
};

typedef vector<Debuff*> Debuffs;

class Living {
  protected:
    string name;
    int level, maxhealthPower, currenthealthPower;
  public:
    Living(string, const int, const int);
    string get_name() const;
    int get_level() const;
    int get_maxHP() const;
    int get_currentHP() const;
    void set_maxHP(const int);
    void set_currentHP(const int);
    virtual void displayStats() const = 0;
};

class Hero : public Living {
  protected:
    int maxMagicPower, currentMagicPower, strength, dexterity, agility, money, experience, damage, defense;
    Weapon* weapon;
    Armor* armor;
    Inventory inventory;
    Spellbook spellbook;
  public:
    Hero(string);
    void levelUp();
    void use(const int);
    void equip(const int);
    void buy(Item*);
    void buy(Spell*);
    void sell_item(const int);
    void sell_spell(const int);
    void checkInventory() const;
    void checkSpellbook() const;
    void deal_damage(int, Monster*);
    void attack(Monster*);
    void castSpell(Spell*, Monster*);
    void str_increase(const int);
    void dex_increase(const int);
    void agi_increase(const int);
    void health_increase(const int);
    void magic_increase(const int);
    void increase_experiece(const int);
    void increase_money(const int);
    void set_currentMP(const int);
    int get_money() const;
    int get_experience() const;
    int get_damage() const;
    int get_agility() const;
    int get_maxMP() const;
    int get_currentMP() const;
    Spell* spell(const int);
    void displayStats() const;
    virtual void stats_increase() = 0;
    int get_defense() const;
    bool has_no_items() const;
    bool has_no_spells() const;
    bool has_no_potions() const;
    bool has_no_weapons() const;
    bool has_no_armor() const;
};

class Warrior : public Hero {
  private:
    int extr_str_per_level, extr_agi_per_level;
  public:
    Warrior(string);
    void stats_increase();
};

class Sorcerer : public Hero {
  private:
    int extr_dex_per_level, extr_agi_per_level;
  public:
    Sorcerer(string);
    void stats_increase();
};

class Paladin : public Hero {
  private:
    int extr_str_per_level, extr_dex_per_level;
  public:
    Paladin(string);
    void stats_increase();
};

class Monster : public Living {
  protected:
    int lowest_damage, highest_damage, defense, dodge_chance;
    Debuffs debuffs;
  public:
    Monster(string, const int, const int, const int, const int, const int, const int);
    int get_dodge_chance() const;
    int get_defense() const;
    int get_min_dmg() const;
    int get_max_dmg() const;
    void set_min_dmg(const int);
    void set_max_dmg(const int);
    void set_defense(const int);
    void set_dodge(const int);
    void displayStats() const;
    void attack(Hero*);
    void update_debuffs();
    void add_debuff(Debuff*);
    void recover(const int, string);
};

class Dragon : public Monster {
  public:
    Dragon(string, const int, const int, const int, const int, const int, const int);
};

class Exoskeleton : public Monster {
  public:
    Exoskeleton(string, const int, const int, const int, const int, const int, const int);
};

class Spirit : public Monster {
  public:
    Spirit(string, const int, const int, const int, const int, const int, const int);
};

class Square {
  protected:
    bool is_team_on;
  public:
    Square();
    virtual void display() const = 0;
    void set_team_on(bool);
};

class Common : public Square {
  public:
    void display() const;
    void battle(Hero**, const int, Monster**, const int);
};

class Market : public Square {
  private:
    Item** item_array;
    Spell** spell_array;
  public:
    Market(Item**, Spell**);
    void display() const;
    void print_items();
    void print_spells();
    Item** get_items() const;
    Spell** get_spells() const;
};

class nonAccessible : public Square {
  public:
    void display() const;
};

class Grid {
  private:
    Square*** map;
    int x, y, lines, columns;
  public:
    Grid(const int, const int, Item**, Spell**);
    ~Grid();
    void display() const;
    void move(Hero**, const int, string);
    void shop(Hero**, const int);
    bool check_on_market() const;
};
