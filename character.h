#pragma once
#include <string>
#include "ancestry.h"
#include "character_class.h"

class character {
private:
	int strength;
	int str_bonus;

	int dexterity;
	int dex_bonus;
	
	int constitution;
	int con_bonus;
	
	int intelligence;
	int int_bonus;
	
	int wisdom;
	int wis_bonus;
	
	int charisma;
	int cha_bonus;

	std::string name;
	ancestry character_ancestry;
	character_class characters_class;

	int level;
	int hit_points;
	int AC;
	int proficiency_bonus;

public:
	character(std::string name, ancestry ancestry, character_class character_class, int strength, int dexterity, int constitution, int intelligence, int wisdom, int charisma, int level);
	int calc_bonus(int score);
	std::string get_name();
	ancestry get_ancestry();
	character_class get_class();
	int get_str();
	int get_dex();
	int get_con();
	int get_int();
	int get_wis();
	int get_cha();
	int get_str_bonus();
	int get_dex_bonus();
	int get_con_bonus();
	int get_int_bonus();
	int get_wis_bonus();
	int get_cha_bonus();
	int get_level();
	void print_character(std::ostream& stream);
};