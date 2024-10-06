#include <iostream>
#include <string>
#include "character.h"
#include "ancestry.h"
#include "character_class.h"

int AC_bonus(int index, int stat_arr[6], int limit);

character::character(std::string name, ancestry ancestry, character_class character_class, int strength, int dexterity, int constitution, int intelligence, int wisdom, int charisma, int level) {
	this->name = name;
	this->character_ancestry = ancestry;
	this->characters_class = character_class;
	this->strength = strength;
	this->str_bonus = calc_bonus(strength);
	this->dexterity = dexterity;
	this->dex_bonus = calc_bonus(dexterity);
	this->constitution = constitution;
	this->con_bonus = calc_bonus(constitution);
	this->intelligence = intelligence;
	this->int_bonus = calc_bonus(intelligence);
	this->wisdom = wisdom;
	this->wis_bonus = calc_bonus(wisdom);
	this->charisma = charisma;
	this->cha_bonus = calc_bonus(charisma);

	this->level = level;
	this->hit_points = characters_class.get_firsthp() + ((level - 1)* characters_class.get_hp_per() + (level) * con_bonus);

	this->AC = characters_class.get_AC_base();
	int arr[6] = { str_bonus,dex_bonus,con_bonus,int_bonus,wis_bonus,cha_bonus };
	if (characters_class.get_AC_bonus1_index() >= 0) {
		this->AC += AC_bonus(characters_class.get_AC_bonus1_index(), arr, characters_class.get_AC_bonus1_limit());

	}
	if (characters_class.get_AC_bonus2_index() >= 0) {
		this->AC += AC_bonus(characters_class.get_AC_bonus2_index(), arr, characters_class.get_AC_bonus2_limit());

	}

	if (level >= 17) {
		this->proficiency_bonus = 6;
	}
	else if (level >= 13) {
		this->proficiency_bonus = 5;
	}
	else if (level >= 9) {
		this->proficiency_bonus = 4;
	}
	else if (level >= 5) {
		this->proficiency_bonus = 3;
	}
	else{
		this->proficiency_bonus = 2;
	}
}
int character::calc_bonus(int score) {
	return floor(double(score - 10) / 2);
}
std::string character::get_name() {
	return name;
}
ancestry character::get_ancestry() {
	return character_ancestry;
}
character_class character::get_class() {
	return characters_class;
}
int character::get_str() {
	return strength;
}
int character::get_dex() {
	return dexterity;
}
int character::get_con() {
	return constitution;
}
int character::get_int() {
	return intelligence;
}
int character::get_wis() {
	return wisdom;
}
int character::get_cha() {
	return charisma;
}
int character::get_str_bonus() {
	return str_bonus;
}
int character::get_dex_bonus() {
	return dex_bonus;
}
int character::get_con_bonus() {
	return con_bonus;
}
int character::get_int_bonus() {
	return int_bonus;
}
int character::get_wis_bonus() {
	return wis_bonus;
}
int character::get_cha_bonus() {
	return cha_bonus;
}
int character::get_level() {
	return level;
}

void character::print_character(std::ostream& stream) {
	int arr[6] = { str_bonus,dex_bonus,con_bonus,int_bonus,wis_bonus,cha_bonus };

	stream << "Name: " << name << std::endl
		<< "Class: " << characters_class.get_name() << " " << level << " | Ancestry: " << character_ancestry.get_name() << std::endl
		<< "Armor Class: " << AC << " (" << characters_class.get_AC_name() << ") | Hit Point Maximum: " << hit_points << std::endl
		<< "Initiative Bonus: " << (arr[1] >= 0 ? "+" : "") << arr[1] << std::endl
		<< "Strength: " << strength << " (" << (str_bonus > 0 ? "+" : "") << str_bonus << ")" << std::endl
		<< "Dexterity: " << dexterity << " (" << (dex_bonus > 0 ? "+" : "") << dex_bonus << ")" << std::endl
		<< "Constitution: " << constitution << " (" << (con_bonus > 0 ? "+" : "") << con_bonus << ")" << std::endl
		<< "Intelligence: " << intelligence << " (" << (int_bonus > 0 ? "+" : "") << int_bonus << ")" << std::endl
		<< "Wisdom: " << wisdom << " (" << (wis_bonus > 0 ? "+" : "") << wis_bonus << ")" << std::endl
		<< "Charisma: " << charisma << " (" << (cha_bonus > 0 ? "+" : "") << cha_bonus << ")" << std::endl
		<< characters_class.get_weapon_name() << " " << ((arr[characters_class.get_attack_bonus_index()] + proficiency_bonus) >= 0 ? "+" : "") << arr[characters_class.get_attack_bonus_index()] + proficiency_bonus << " " << characters_class.get_weapon_dice() << ((arr[characters_class.get_attack_bonus_index()]) >= 0 ? "+" : "") << arr[characters_class.get_attack_bonus_index()] << std::endl;
}

int AC_bonus(int index, int stat_arr[6], int limit) {
	if (stat_arr[index] > limit) {
		return limit;
	}
	else {
		return stat_arr[index];
	}
}