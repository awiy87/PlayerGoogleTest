#include "pch.h"
#include <iostream>
#include <vector>

using namespace std;

enum GameStates {
    empty, phase1, phase2, mill, gameOver
};

struct Player {
    Player() {
    }
    Player(int id, bool isAI) {
        this->playerID = id;
        this->isAI = isAI;
    }
    //getters

    int getPlayerID() { return playerID; };
    bool getIsAI() { return isAI; };
    int getPhase1Pieces() { return phase1Pieces; };
    int getPhase2Pieces() { return phase2Pieces; };
    bool getFlight() { return isFlight; };
    int getActiveMills() { return this->activeMills; };
    int getStableMills() { return this->stableMills; };

    // returns their enemy. Remember it is 1 or 2, be careful for accessing data structures
    int getEnemy() { return 3 - this->playerID; };

    //setters

    void setID(int id) { this->playerID = id; };
    void setAI(bool isAI) { this->isAI = isAI; };
    void setPhase1Pieces(int x) { this->phase1Pieces = x; };
    void setPhase2Pieces(int x) { this->phase2Pieces = x; };
    void setFlight(bool flight) { this->isFlight = flight; };
    void setActiveMills(int x) { this->activeMills = x; };
    void setStableMills(int x) { this->stableMills += x; }
    //functions

    //player check called after mill phase, and toggles if they are ready to leave the nest.
    void timetoFly();
    //subtract a piece. Changes depending on the passed board state. Note this is only for placing pieces, really for phase 1
    void subtractPhase2Too() { this->phase2Pieces--; }
    void subtractPiece(GameStates state);
    //add a piece. Only really applies to phase 2 so no need to pass state.
    void addPiece();
    //decrement active mills
    void subtractMills() { this->activeMills--; };
    void subtractMillsStable() { this->stableMills--; }

    int playerID = 0;
    bool isAI = false;
    int phase1Pieces = 9;
    int phase2Pieces = 0;
    bool isFlight = false;
    int activeMills = 0;
    int stableMills = 0;
};



TEST(PlayerTest, StartingPiecesTest) {
	Player p1(1, false);
	EXPECT_EQ(9, p1.getPhase1Pieces());
}

//Time to fly - unit test
//Given an ongoing game in the second phase, when a player is reduced to three pieces, then the text “Player X has entered Flight Mode!” is displayed.
TEST(PlayerTest, timeToFlyUnitTest) {
	Player p1(1, false);
	Player p2(2, false);

	p1.setPhase2Pieces(3);
    p1.timetoFly();
	EXPECT_TRUE(p1.getFlight());

	p2.setPhase2Pieces(4);
    p2.timetoFly();
	EXPECT_FALSE(p2.getFlight());
}

//Capturing Pieces Unit test.
//Given an ongoing game in the first phase, when a player's piece is captured, then their active pieces in phase 1 decrements by 1.
//Given an ongoing game in the second phase, when a player's piece is captured, then their active pieces in phase 2 decrements by 1.
//Also test addPiece function
TEST(PlayerTest, subtractingPiecesTest) {
	GameStates gs1 = phase1;
	GameStates gs2 = phase2;
	Player p1(1, false);
	p1.subtractPiece(gs1);
	EXPECT_EQ(8, p1.getPhase1Pieces());

	p1.addPiece();
	p1.addPiece();
	p1.addPiece();
	p1.subtractPiece(gs2);
	EXPECT_EQ(2, p1.getPhase2Pieces());
}


int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
	system("pause");
}

void Player::timetoFly()
{
    if (this->getPhase2Pieces() <= 3)
    {
        setFlight(true);
    }
}

void Player::subtractPiece(GameStates state)
{
    switch (state) {
    case phase1:
        this->phase1Pieces--;
        break;
    case phase2:
        this->phase2Pieces--;
        break;
    }
}

void Player::addPiece()
{
    this->phase2Pieces++;
}
