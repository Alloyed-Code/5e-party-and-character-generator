#include <string>
#include "ancestry.h"

ancestry::ancestry(std::string name, int strength, int dexterity, int constitution, int intelligence, int wisdom, int charisma) {
	const int length = 6;
	this->name = name;
	int score_increases[length] = {strength, dexterity, constitution, intelligence, wisdom, charisma};
	for (int i = 0; i < length; i++) {
		this->score_increases[i] = score_increases[i];
	}
}
ancestry::ancestry() {
	int scores[6] = { 0 };
	for (int i = 0; i < 6; i++) {
		score_increases[i] = scores[i];
	}
}

int* ancestry::get_score_increases() {
	return score_increases;
}

std::string ancestry::get_name() {
	return name;
}