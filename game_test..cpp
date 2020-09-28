#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "X.h"
#include "Level.h"


void checker(int RandQ, std::vector<int>& positions) {
	int placeRandQ;
	int emptyNumber;
	int t;
	for (unsigned int i = 0; i < 15; i++) {
		if (positions[i] == (RandQ + 1)) {
			placeRandQ = i;
		}
		if (positions[i] == 0) {
			emptyNumber = i;
		}
	}
	bool CanIMove(unsigned int slot, unsigned int freeSlot) {
		if ((slot == 3 && freeSlot == 4) || (slot == 4 && freeSlot == 3)) return false;
		if ((slot == 7 && freeSlot == 8) || (slot == 8 && freeSlot == 7)) return false;
		if ((slot == 11 && freeSlot == 12) || (slot == 12 && freeSlot == 11)) return false;
		if (slot == freeSlot - 1 ||
			slot == freeSlot + 1 ||
			slot == freeSlot - 4 ||
			slot == freeSlot + 4)
			return true;
		return false;
	}
	if (CanIMove(placeRandQ, emptyNumber)) {
		t = emptyNumber;
		emptyNumber = placeRandQ;
		placeRandQ = t;
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
		checker(RandQ, positions);
		// убираем в load рестарт... теперь он сразу не собирает рандомную комбинацию плашек, только после f2 теперь мешает
		
		CHECK(buildsAreEqual(positions, ));
	}

