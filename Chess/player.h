#pragma once
class Player
{
private:
	int color;
	bool isAutomaton;
public:
	Player();
	~Player();

	char* GetNextMove();

	bool GetNextMove(char input[32]);
};

