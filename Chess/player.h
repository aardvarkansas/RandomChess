#pragma once
class Player
{
private:
	int color;
	bool isHuman=false;
public:
	Player();
	Player(bool isHuman);
	~Player();

	char* GetNextMove();

	bool GetRandomMove(char *input);
	bool GetNextMove(char input[32]);
};

