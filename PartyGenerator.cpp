#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <fstream>
#include <sstream>
#include "character.h"
#include "ancestry.h"
#include "character_class.h"

int roll1d6();
int roll4d6_drop();
int lowest_int(int arr[], int length);
ancestry** get_ancestry_list(std::string path, int num_ancestries);
character_class** get_class_list(std::string path, int num_classes);
int get_line_count(std::string path);
ancestry* get_ancestry(std::string name, int num_ancestries, ancestry** ancestry_list);
ancestry* get_ancestry(int num, int num_ancestries, ancestry** ancestry_list);
std::string recommended_class(int scores[], int num_classes, character_class** class_list);
void print_ancestries(int num_ancestries, ancestry** ancestry_list);
void print_scores(int scores[], int character_num);
void print_classes(int num_classes, character_class** class_list);
character_class* get_character_class(std::string name, int num_classes, character_class** class_list);
int get_class_weight(int scores[], character_class* class_);
void company_to_file(std::string company_name, int company_size, character** party);
void sort_ints(int* scores, int length);
void assign_stat_manually(int score, int* scores, int* temp_scores);
int stat_index_from_string(std::string stat);
int get_stat_limit(std::string stat);
void get_ability_improvement(int* score_arr);
void apply_ancestry_bonus(int* scores, ancestry* ancestry);


int main() {
	std::string company_name;
	std::string company_size_string;
	int company_size;
	const std::string ancestry_path = "Data\\ancestries.csv";
	const std::string class_path = "Data\\classes.csv";

	srand(time(0));
	std::cout << "Collecting Ancestries...";
	int num_ancestries = get_line_count(ancestry_path) - 1;
	ancestry** ancestry_list = get_ancestry_list(ancestry_path, num_ancestries);
	std::cout << "Done" << std::endl;
	std::cout << "Collecting Classes...";
	int num_classes = get_line_count(class_path) - 1;
	character_class** class_list = get_class_list(class_path, num_classes);
	std::cout << "Done" << std::endl;

	std::cout << std::endl << "Dungeons and Dragons 5e Party Generator" << std::endl
		<< std::endl << "What is your company called? ";
	std::getline(std::cin, company_name);

	std::cout << "How many characters are there in " << company_name << "? ";
	std::getline(std::cin, company_size_string);
	bool good_number = true;
	for (char c : company_size_string) {
		if (c < '0' || c > '9') {
			good_number = false;
		}
	}
	if (!good_number) {
		std::cout << "Not an integer!" << std::endl;
		delete[] ancestry_list;
		delete[] class_list;
		return 1;
	}
	company_size = stoi(company_size_string);
	if (company_size <= 0) {
		std::cout << "Can not have a party of none!" << std::endl;
		return 10;
	}

	character** party = new character * [company_size];

	bool auto_assign = true;
	std::string assign_string;
	std::cout << "Auto-assign stats or manually assign stats?(a/m) ";
	std::getline(std::cin, assign_string);
	if (assign_string == "a") {
		std::cout << "Auto-assigning stats chosen" << std::endl;
	}
	else if (assign_string == "m") {
		std::cout << "Manual assignment of stats chosen" << std::endl;
		auto_assign = false;
	}
	else {
		std::cout << "Invalid input!" << std::endl;
		delete[] ancestry_list;
		delete[] class_list;
		return 4;
	}

	bool string_num = true;
	int party_level;
	std::string level_string;
	std::cout << "What character level are the party?(1-20 or i for individual levels) ";
	std::getline(std::cin, level_string);
	for (char c : level_string) {
		if (c == 'i') {
			std::cout << "Character level will be chosen per character" << std::endl;
			party_level = -1;
			string_num = false;
			break;
		}
		else if (c < '0' || c > '9') {
			std::cout << "Invalid input!" << std::endl;
			return 5;
		}
	}
	if (string_num) {
		party_level = stoi(level_string);
	}

	for (int i = 0; i < company_size; i++) {
		std::cout << std::endl << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl
			<< "Character " << i + 1 << std::endl
			<< "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;

		int scores[6];
		std::string name;
		ancestry* ancestry = ancestry_list[0];
		character_class* character_class = class_list[0];
		int level;

			bool accepted = false;
			while (accepted == false) {
				if (auto_assign == true) {
					for (int j = 0; j < 6; j++) {
						scores[j] = roll4d6_drop();
					}
				}
				else {
					for (int j = 0; j < 6; j++) {
						scores[j] = 0;
					}
					int temp_scores[6] = { roll4d6_drop(), roll4d6_drop(), roll4d6_drop(), roll4d6_drop(), roll4d6_drop(), roll4d6_drop() };
					sort_ints(temp_scores, 6);
					for (int j = 0; j < 6; j++) {
						std::cout << temp_scores[j] << std::endl;
					}

					std::cout << std::endl << "Assign the previous scores to: Strength(str), Dexterity(dex), Constitution(con), Intelligence(int), Wisdom(wis), Charisma(cha)" << std::endl;
					for (int j = 0; j < 6; j++) {
						assign_stat_manually(j, scores, temp_scores);
					}
				}
				print_scores(scores, i + 1);

				ancestry = get_ancestry(i + 1, num_ancestries, ancestry_list);

				apply_ancestry_bonus(scores, ancestry);

				print_scores(scores, i + 1);

				std::cout << std::endl << "What is character " << i + 1 << "'s name? ";

				std::getline(std::cin, name);

				std::cout << std::endl << "Recomended classes for " << name << " are: " << recommended_class(scores, num_classes, class_list) << std::endl;

				character_class = get_character_class(name, num_classes, class_list);

				if (party_level == -1) {
					std::cout << "What level is " << name << "?(1-20) ";
					std::string level_string;
					std::getline(std::cin, level_string);
					for (char c : level_string) {
						if (c < '0' || c > '9') {
							std::cout << "Invalid input!" << std::endl;
							return 5;
						}
					}
					level = stoi(level_string);
				}
				else {
					level = party_level;
				}

				int ability_score_improvements = 2 * (floor(character_class->get_asi_per_level() * level) - ((character_class->get_name() == "Fighter") ? 1 : 0));
				//std::cout << ability_score_improvements << std::endl;
				std::cout << name << " has " << ability_score_improvements << " ability score improvements" << std::endl;
				for (int j = 0; j < ability_score_improvements; j++) {
					get_ability_improvement(scores);
					print_scores(scores, j + 1);
					std::cout << std::endl;
					if (ability_score_improvements - (j + 1) > 0) {
						std::cout << "Ability score improvements left: " << ability_score_improvements - (j + 1) << std::endl;
					}
				}

				std::cout << "Keep character?(y/n) ";
				std::string input;
				getline(std::cin, input);
				if (input == "y") {
					accepted = true;
				}
				else if (input == "n") {
					std::wcout << std::endl << "Re-generating character..." << std::endl;
				}
				else {
					std::cout << "Invalid input!";
					return 3;
				}

			}

		party[i] = new character(name, *ancestry, *character_class, scores[0], scores[1], scores[2], scores[3], scores[4], scores[5], level);
		//party[i]->print_character(std::cout);
	}
	std::cout << std::endl << "Print Party to File?(y/n) ";
	std::string input;
	std::getline(std::cin, input);
	if (input == "y") {
		std::cout << "Printing to file...";
		company_to_file(company_name, company_size, party);
		std::cout << "Done" << std::endl;
	}
	else if (input == "n") {
		std::cout << "No file will be printed." << std::endl;
	}
	else {
		std::cout << "Invalid input!" << std::endl;
		delete[] ancestry_list;
		delete[] class_list;
		delete[] party;
		return 2;
	}

	std::cout << std::endl << "Generate a party of foils to " << company_name << "?(y/n) ";
	std::getline(std::cin, input);
	if (input == "n") {
		std::cout << "No foil will be generated." << std::endl;
	}
	else if (input == "y") {
		std::string foil_name;
		std::cout << "What is the name of the foil company? ";
		std::getline(std::cin, foil_name);
		character** foil_party = new character * [company_size];

		for (int i = 0; i < company_size; i++) {
			std::cout << std::endl << "The foil to " << party[i]->get_name() << "(" << party[i]->get_class().get_name() << ") is a " << class_list[party[i]->get_class().get_foil_index()]->get_name() << std::endl;
			character_class * foil_class = class_list[party[i]->get_class().get_foil_index()];

			ancestry * foil_ancestry = get_ancestry(i + 1, num_ancestries, ancestry_list);

			int scores[6];
			for (int j = 0; j < 6; j++) {
				scores[j] = 10 + 2 * foil_class->get_weights()[j];
				scores[j] += floor(((2 * ((party[i]->get_level() - 1) * foil_class->get_asi_per_level()))/3)* (1 + foil_class->get_weights()[j]));
				scores[j] += foil_ancestry->get_score_increases()[j];
				if (scores[j] > 20) {
					scores[j] = 20;
				}
			}

			print_scores(scores, i + 1);

			std::string foil_character_name;
			std::cout << std::endl << "What is character foil " << i + 1 << "'s name? ";

			std::getline(std::cin, foil_character_name);

			foil_party[i] = new character(foil_character_name, *foil_ancestry, *class_list[party[i]->get_class().get_foil_index()], scores[0], scores[1], scores[2], scores[3], scores[4], scores[5], party[i]->get_level());
		}

		std::cout << std::endl << "Print Foil to File?(y/n) ";
		std::getline(std::cin, input);
		if (input == "y") {
			std::cout << "Printing to file...";
			company_to_file(foil_name, company_size, foil_party);
			std::cout << "Done" << std::endl;
		}
		else if (input == "n") {
			std::cout << "No file will be printed." << std::endl;
		}
		else {
			std::cout << "Invalid input!" << std::endl;
			delete[] ancestry_list;
			delete[] class_list;
			delete[] party;
			delete[] foil_party;
			return 2;
		}
		delete[] foil_party;
	}
	else {
		std::cout << "Invalid input!" << std::endl;
		delete[] ancestry_list;
		delete[] class_list;
		delete[] party;
		return 6;
	}

	delete[] ancestry_list;
	delete[] class_list;
	delete[] party;
	return 0;
}


int roll1d6() {
	return rand() % (6) + 1;
}

int roll4d6_drop() {
	const int num_rolls = 4;
	int rolls[num_rolls] = { roll1d6(), roll1d6(), roll1d6(), roll1d6()};
	int lowest_index = lowest_int(rolls, num_rolls);
	int total = 0;
	for (int i = 0; i < num_rolls; i++) {
		total += rolls[i];
	}
	total -= rolls[lowest_index];

	return total;
}

int lowest_int(int arr[], int length) {
	int lowest_index = 0;
	for (int i = 1; i < length; i++) {
		if (arr[i] < arr[lowest_index]) {
			lowest_index = i;
		}
	}
	return lowest_index;
}

ancestry** get_ancestry_list(std::string path, int num_ancestries) {

	ancestry** list = new ancestry * [num_ancestries];

	std::ifstream stream;
	stream.open(path);

	std::string line;
	std::getline(stream, line);

	for (int i = 0; i < num_ancestries; i++) {
		std::getline(stream, line);

		std::stringstream ss(line);

		std::string substr;

		std::getline(ss, substr, ',');
		std::string name = substr;

		std::getline(ss, substr, ',');
		int strength = stoi(substr);

		std::getline(ss, substr, ',');
		int dexterity = stoi(substr);

		std::getline(ss, substr, ',');
		int constitution = stoi(substr);

		std::getline(ss, substr, ',');
		int intelligence = stoi(substr);

		std::getline(ss, substr, ',');
		int wisdom = stoi(substr);

		std::getline(ss, substr, ',');
		int charisma = stoi(substr);

		list[i] = new ancestry(name, strength, dexterity, constitution, intelligence, wisdom, charisma);
	}
	stream.close();
	return list;
}

int get_line_count(std::string path) {
	std::ifstream stream;
	stream.open(path);

	int num_lines = 0;
	std::string line;

	while (std::getline(stream, line)) {
		num_lines++;
	}

	stream.close();

	return num_lines;
}

ancestry* get_ancestry(std::string name, int num_ancestries, ancestry** ancestry_list) {
	std::cout << std::endl << "What ancestry is " << name << "?(? for list of ancestries) ";
	std::string input;
	std::getline(std::cin, input);
	if (input == "?") {
		print_ancestries(num_ancestries, ancestry_list);
		return get_ancestry(name, num_ancestries, ancestry_list);
	}
	else {
		for (int i = 0; i < num_ancestries; i++) {
			if (input == ancestry_list[i]->get_name()) {
				return ancestry_list[i];
			}
		}
		std::cout << "Ancestry not found! Try again!" << std::endl;
		return get_ancestry(name, num_ancestries, ancestry_list);
	}
}

ancestry* get_ancestry(int num, int num_ancestries, ancestry** ancestry_list) {
	std::cout << std::endl << "What ancestry is character " << num << "?(? for list of ancestries) ";
	std::string input;
	std::getline(std::cin, input);
	if (input == "?") {
		print_ancestries(num_ancestries, ancestry_list);
		return get_ancestry(num, num_ancestries, ancestry_list);
	}
	else {
		for (int i = 0; i < num_ancestries; i++) {
			if (input == ancestry_list[i]->get_name()) {
				return ancestry_list[i];
			}
		}
		std::cout << "Ancestry not found! Try again!" << std::endl;
		return get_ancestry(num, num_ancestries, ancestry_list);
	}
}

void print_ancestries(int num_ancestries, ancestry** ancestry_list) {
	std::cout << std::endl << "Available Ancestries:" << std::endl;
	for (int i = 0; i < num_ancestries; i++) {
		std::cout << ancestry_list[i]->get_name() << ": ";
		if (ancestry_list[i]->get_score_increases()[0] != 0) {
			std::cout << "Str +" << ancestry_list[i]->get_score_increases()[0] << ", ";
		}
		if (ancestry_list[i]->get_score_increases()[1] != 0) {
			std::cout << "Dex +" << ancestry_list[i]->get_score_increases()[1] << ", ";
		}
		if (ancestry_list[i]->get_score_increases()[2] != 0) {
			std::cout << "Con +" << ancestry_list[i]->get_score_increases()[2] << ", ";
		}
		if (ancestry_list[i]->get_score_increases()[3] != 0) {
			std::cout << "Int +" << ancestry_list[i]->get_score_increases()[3] << ", ";
		}
		if (ancestry_list[i]->get_score_increases()[4] != 0) {
			std::cout << "Wis +" << ancestry_list[i]->get_score_increases()[4] << ", ";
		}
		if (ancestry_list[i]->get_score_increases()[5] != 0) {
			std::cout << "Cha +" << ancestry_list[i]->get_score_increases()[5];
		}
		std::cout << std::endl;
	}
}

void print_scores(int scores[], int character_num) {
	std::cout << std::endl << "Character " << character_num << "'s Stat Scores:" << std::endl;
	std::cout << "Strength: " << scores[0] << std::endl;
	std::cout << "Dexterity: " << scores[1] << std::endl;
	std::cout << "Constitution: " << scores[2] << std::endl;
	std::cout << "Intelligence: " << scores[3] << std::endl;
	std::cout << "Wisdom: " << scores[4] << std::endl;
	std::cout << "Charisma: " << scores[5] << std::endl;
}

std::string recommended_class(int scores[], int num_classes, character_class** class_list) {
	int first_class_index = 0;
	int second_class_index = 1;
	for (int i = 1; i < num_classes; i++) {
		if (get_class_weight(scores, class_list[i]) > get_class_weight(scores, class_list[first_class_index])) {
			second_class_index = first_class_index;
			first_class_index = i;
		}
		else if (get_class_weight(scores, class_list[i]) > get_class_weight(scores, class_list[second_class_index])) {
			second_class_index = i;
		}
	}
	return class_list[first_class_index]->get_name() + " or " + class_list[second_class_index]->get_name();
}

character_class** get_class_list(std::string path, int num_classes) {

	character_class** list = new character_class * [num_classes];

	std::ifstream stream;
	stream.open(path);

	std::string line;
	std::getline(stream, line);

	for (int i = 0; i < num_classes; i++) {
		std::getline(stream, line);

		std::stringstream ss(line);

		std::string substr;

		std::getline(ss, substr, ',');
		std::string name = substr;

		std::getline(ss, substr, ',');
		int str_weight = stoi(substr);

		std::getline(ss, substr, ',');
		int dex_weight = stoi(substr);

		std::getline(ss, substr, ',');
		int con_weight = stoi(substr);

		std::getline(ss, substr, ',');
		int int_weight = stoi(substr);

		std::getline(ss, substr, ',');
		int wis_weight = stoi(substr);

		std::getline(ss, substr, ',');
		int cha_weight = stoi(substr);

		std::getline(ss, substr, ',');
		int first_hp = stoi(substr);

		std::getline(ss, substr, ',');
		int hp_per = stoi(substr);

		std::getline(ss, substr, ',');
		int AC = stoi(substr);

		std::getline(ss, substr, ',');
		int AC_bonus_1_index = stat_index_from_string(substr);
		int bonus_1_limit = get_stat_limit(substr);

		std::getline(ss, substr, ',');
		int AC_bonus_2_index = stat_index_from_string(substr);
		int bonus_2_limit = get_stat_limit(substr);

		std::getline(ss, substr, ',');
		std::string AC_name = substr;

		std::getline(ss, substr, ',');
		std::string weapon_name = substr;

		std::getline(ss, substr, ',');
		std::string weapon_dice = substr;

		std::getline(ss, substr, ',');
		int attack_bonus_index = stat_index_from_string(substr);

		getline(ss, substr, ',');
		double ability_score_improvement_per_level = stod(substr);

		getline(ss, substr, ',');
		int foil_index = stoi(substr);

		list[i] = new character_class(name, str_weight, dex_weight, con_weight, int_weight, wis_weight, cha_weight, first_hp, hp_per, AC, AC_name, AC_bonus_1_index, bonus_1_limit, AC_bonus_2_index, bonus_2_limit, weapon_name, weapon_dice, attack_bonus_index, ability_score_improvement_per_level, foil_index);
	}
	stream.close();
	return list;
}

character_class* get_character_class(std::string name, int num_classes, character_class** class_list) {
	std::cout << std::endl << "What class is " << name << "?(? for list of classes) ";
	std::string input;
	std::getline(std::cin, input);
	if (input == "?") {
		print_classes(num_classes, class_list);
		return get_character_class(name, num_classes, class_list);
	}
	else {
		for (int i = 0; i < num_classes; i++) {
			if (input == class_list[i]->get_name()) {
				return class_list[i];
			}
		}
		std::cout << "Class not found! Try again!" << std::endl;
		return get_character_class(name, num_classes, class_list);
	}
}

void print_classes(int num_classes, character_class** class_list) {
	std::cout << std::endl << "Available Classes:" << std::endl;
	for (int i = 0; i < num_classes; i++) {
		std::cout << class_list[i]->get_name() << std::endl;
	}
	std::cout << std::endl;
}

int get_class_weight(int scores[], character_class* class_) {
	int score = 0;
	for (int j = 0; j < 6; j++) {
		score += scores[j] * class_->get_weights()[j];
	}
	//std::cout << class_->get_name() << " " << score << std::endl;
	return score;
}

void company_to_file(std::string company_name, int company_size, character** party) {
	std::string company_file_path = "Data\\" + company_name + ".txt";
	std::ofstream stream;
	stream.open(company_file_path);
	if (stream.is_open()) {
		stream << company_name << std::endl;

		for (int i = 0; i < company_size; i++) {
			stream << std::endl;
			party[i]->print_character(stream);
		}
	}
	else {
		std::cout << "Failed to open file...";
	}
	stream.close();
}

void sort_ints(int* scores, int length) {
	
	for (int i = 0; i < length; i++) {
		int max_index = i;

		for (int j = i + 1; j < length; j++) {
			if (scores[j] > scores[max_index]) {
				max_index = j;
			}
		}
		if (i != max_index) {
			std::swap(scores[i], scores[max_index]);
		}
	}
}

void assign_stat_manually(int score, int* scores, int* temp_scores) {
	std::cout << "Where should " << temp_scores[score] << " go? ";
	std::string stat_assignment;
	std::getline(std::cin, stat_assignment);

	if (stat_assignment == "str") {
		if (!scores[0]) {
			scores[0] = temp_scores[score];
			std::cout << temp_scores[score] << " is assigned to Strength" << std::endl;
		}
		else {
			std::cout << scores[0] << " is already assigned to Strength!" << std::endl;
			assign_stat_manually(score, scores, temp_scores);
		}
	}
	else if (stat_assignment == "dex") {
		if (!scores[1]) {
			scores[1] = temp_scores[score];
			std::cout << temp_scores[score] << " is assigned to Dexterity" << std::endl;
		}
		else {
			std::cout << scores[1] << " is already assigned to Dexterity!" << std::endl;
			assign_stat_manually(score, scores, temp_scores);
		}
	}
	else if (stat_assignment == "con") {
		if (!scores[2]) {
			scores[2] = temp_scores[score];
			std::cout << temp_scores[score] << " is assigned to Constitution" << std::endl;
		}
		else {
			std::cout << scores[2] << " is already assigned to Constitution!" << std::endl;
			assign_stat_manually(score, scores, temp_scores);
		}
	}
	else if (stat_assignment == "int") {
		if (!scores[3]) {
			scores[3] = temp_scores[score];
			std::cout << temp_scores[score] << " is assigned to Intelligence" << std::endl;
		}
		else {
			std::cout << scores[3] << " is already assigned to Intelligence!" << std::endl;
			assign_stat_manually(score, scores, temp_scores);
		}
	}
	else if (stat_assignment == "wis") {
		if (!scores[4]) {
			scores[4] = temp_scores[score];
			std::cout << temp_scores[score] << " is assigned to Wisdom" << std::endl;
		}
		else {
			std::cout << scores[4] << " is already assigned to Wisdom!" << std::endl;
			assign_stat_manually(score, scores, temp_scores);
		}
	}
	else if (stat_assignment == "cha") {
		if (!scores[5]) {
			scores[5] = temp_scores[score];
			std::cout << temp_scores[score] << " is assigned to Charisma" << std::endl;
		}
		else {
			std::cout << scores[5] << " is already assigned to Charisma!" << std::endl;
			assign_stat_manually(score, scores, temp_scores);
		}
	}
	else {
		std::cout << "Invalid input! Valid inputs include: str, dex, con, int, wis, cha" << std::endl;
		assign_stat_manually(score, scores, temp_scores);
	}
}

int stat_index_from_string(std::string stat) {
	if (stat == "str" || stat == "str2") {
		return 0;
	}
	else if (stat == "dex" || stat == "dex2") {
		return 1;
	}
	else if (stat == "con" || stat == "con2") {
		return 2;
	}
	else if (stat == "int" || stat == "int2") {
		return 3;
	}
	else if (stat == "wis" || stat == "wis2") {
		return 4;
	}
	else if (stat == "cha" || stat == "cha2") {
		return 5;
	}
	else {
		return -1;
	}
}

int get_stat_limit(std::string stat) {
	if (stat.length() > 3) {
		return int(stat[3] - '0');
	}
	else {
		return 99;
	}
}

void get_ability_improvement(int* score_arr) {
	std::cout << "Assign an ability score improvement to a stat to a maximum ability score of 20.(str, dex, con, int, wis, cha) ";
	std::string asi;
	getline(std::cin, asi);
	int score_index = stat_index_from_string(asi);
	if (score_index == -1) {
		std::cout << "Invalid input!" << std::endl;
		get_ability_improvement(score_arr);
	}
	else if (score_arr[score_index] >= 20) {
		std::cout << "Can not increase a score above 20!" << std::endl;
		get_ability_improvement(score_arr);
	}
	else {
		score_arr[score_index] += 1;
	}
}

void apply_ancestry_bonus(int* scores, ancestry* ancestry) {
	scores[0] += ancestry->get_score_increases()[0];
	scores[1] += ancestry->get_score_increases()[1];
	scores[2] += ancestry->get_score_increases()[2];
	scores[3] += ancestry->get_score_increases()[3];
	scores[4] += ancestry->get_score_increases()[4];
	scores[5] += ancestry->get_score_increases()[5];
}