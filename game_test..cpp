#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "X.h"
#include "Level.h"
#include "Game.h"

void checker(int RandQ, std::vector<int>& positions) {
	for (unsigned int i = 0; i < 15; i++) {
		if (positions[i] == (RandQ + 1)) {
			if (positions[i - 1] == 0 ||
				positions[i + 1] == 0 ||
				positions[i - 4] == 0 ||
				positions[i + 4] == 0) {

			}

	}
	
}

bool buildsAreEqual(const std::vector<int>& positions1, const std::vector<int>& positions2) {
	for (int i = 0; i < 15; i++) {
		if (positions1[i] != positions2[i]) {
			return false;
		}

	}
	return true;
}

// Test
TEST_CASE(" test") {
	Game game;

	int numOfCheckIterations = 100;

	std::vector<int> positions;
	
	int n = 0;
	// для проверки удобнее так и просто значения менять positions[i] 
	for (int i = 0; i < 15; i++) {
		positions[i] = n + 1;
		n++;
	}
	positions[15] = 0;
	int RandQ = 0; // это в какую плашку мы тыкаем ( в смысле что по i, а не цифре, что хранится в positions[i]
	for (unsigned int i = 0; i < numOfCheckIterations; i++)
	{
		RandQ = rand() % 16;
		
	}
