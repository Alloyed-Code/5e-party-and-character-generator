#pragma once
#include <string>

class character_class {
private:
	std::string name;
	int weights[6];
	int first_hp;
	int hp_per;
	int AC;
	std::string AC_name;
	int AC_bonus_1_index;
	int bonus_1_limit;
	int AC_bonus_2_index;
	int bonus_2_limit;
	std::string weapon_name;
	std::string weapon_dice;
	int attack_bonus_index;
	double ability_score_improvements_per_level;
	int foil_index;

public:
	character_class(std::string name, int str_weight, int dex_weight, int con_weight, int int_weight, int wis_weight, int cha_weight, int first_hp, int hp_per, int AC, std::string AC_name, int AC_bonus_1_index, int bonus_1_limit, int AC_bonus_2_index, int bonus_2_limit, std::string weapon_name, std::string weapon_dice, int attack_bonus_index, double ability_score_improvements_per_level, int foil_index);
	character_class();
	std::string get_name();
	int* get_weights();
	int get_firsthp();
	int get_hp_per();
	int get_AC_base();
	std::string get_AC_name();
	int get_AC_bonus1_index();
	int get_AC_bonus2_index();
	int get_AC_bonus1_limit();
	int get_AC_bonus2_limit();
	std::string get_weapon_name();
	std::string get_weapon_dice();
	int get_attack_bonus_index();
	double get_asi_per_level();
	int get_foil_index();
};