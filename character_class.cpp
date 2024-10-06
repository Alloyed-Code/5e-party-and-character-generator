#include <string>
#include "character_class.h"

character_class::character_class(std::string name, int str_weight, int dex_weight, int con_weight, int int_weight, int wis_weight, int cha_weight, int first_hp, int hp_per, int AC, std::string AC_name, int AC_bonus_1_index, int bonus_1_limit, int AC_bonus_2_index, int bonus_2_limit, std::string weapon_name, std::string weapon_dice, int attack_bonus_index, double ability_score_improvements_per_level, int foil_index) {
	this->name = name;
	const int length = 6;
	int weights[length] = { str_weight, dex_weight, con_weight, int_weight, wis_weight, cha_weight };
	for (int i = 0; i < length; i++) {
		this->weights[i] = weights[i];
	}
	this->first_hp = first_hp;
	this->hp_per = hp_per;
	this->AC = AC;
	this->AC_name = AC_name;
	this->AC_bonus_1_index = AC_bonus_1_index;
	this->bonus_1_limit = bonus_1_limit;
	this->AC_bonus_2_index = AC_bonus_2_index;
	this->bonus_2_limit = bonus_2_limit;
	this->weapon_name = weapon_name;
	this->weapon_dice = weapon_dice;
	this->attack_bonus_index = attack_bonus_index;
	this->ability_score_improvements_per_level = ability_score_improvements_per_level;
	this->foil_index = foil_index;
}

character_class::character_class() {
	int weights[6] = { 0 };
	for (int i = 0; i < 6; i++) {
		this->weights[i] = weights[i];
	}
}

std::string character_class::get_name() {
	return name;
}

int* character_class::get_weights() {
	return weights;
}

int character_class::get_firsthp() {
	return first_hp;
}

int character_class::get_hp_per() {
	return hp_per;
}

int character_class::get_AC_base() {
	return AC;
}

std::string character_class::get_AC_name() {
	return AC_name;
}

int character_class::get_AC_bonus1_index() {
	return AC_bonus_1_index;
}

int character_class::get_AC_bonus2_index() {
	return AC_bonus_2_index;
}

int character_class::get_AC_bonus1_limit() {
	return bonus_1_limit;
}

int character_class::get_AC_bonus2_limit() {
	return bonus_2_limit;
}

std::string character_class::get_weapon_name() {
	return weapon_name;
}

std::string character_class::get_weapon_dice() {
	return weapon_dice;
}

int character_class::get_attack_bonus_index() {
	return attack_bonus_index;
}

double character_class::get_asi_per_level() {
	return ability_score_improvements_per_level;
}

int character_class::get_foil_index() {
	return foil_index;
}