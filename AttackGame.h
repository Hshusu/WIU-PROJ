#pragma once
class AttackGame
{
private:
	static int const row = 9;
	static int const col = 40;
	bool barMovingLeft = true;
	int barXpos = 0;
	int barYpos = 0;

	int gameOffsetX = 120;
	int gameOffsetY = 14;

	float dmgModifier;

	bool Stop = false;

	char mapData[row][col];
public:
	void SetdmgModifier(float mod);

	float GetdmgModifier(void);

	void SetConsoleTextColor(int colorCode);
	
	void SetCursorPosition(int x, int y);

	void OverlayScreen();

	void DrawAttackStart();

	void DrawBar();

	void MoveBarLeft();

	void MoveBarRight();

	void CheckMapData();

	void CheckInput();

	AttackGame(void);
};

