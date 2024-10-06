#pragma once
#include <string>

class ancestry {
private:
	std::string name;
	int score_increases[6];

public:
	ancestry(std::string name, int strength, int dexterity, int constitution, int intelligence, int wisdom, int charisma);
	ancestry();
	int* get_score_increases();
	std::string get_name();
};