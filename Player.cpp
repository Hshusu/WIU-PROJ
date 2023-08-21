#include "Player.h"

int Player::getSkillCount()
{
	return Skills.size();
}

int Player::PlayerTurn(Entity* Enemy)
{
	GenerateUI(*Enemy);
	for (int i = 0; i < Skills.size(); i++) //Prints amount relative to number of Skills
	{
		std::cout << Skills[i].Name;
		if (i == scrollPos) {
			std::cout << "\033[1;31m <-\033[0m" << std::endl; //Generates the Pointer
		}
		else { std::cout << std::endl; }
		std::cout << Skills[i].Description << " cost:" << Skills[i].Cost << (Skills[i].ManaCost ? "mana " : " hp ") << (Skills[i].Healing ? "heals: " : "deals: ") << Skills[i].Base << std::endl;


	}
	std::cout << "\033[1;36mUse the [W] and [S] Keys to toggle between skills. [X] to Select skill.\033[0m";
	while (1) {
		if ((GetAsyncKeyState('W')) || (GetAsyncKeyState('S')) || (GetAsyncKeyState('X'))) {

			system("cls");
			GenerateUI(*Enemy);
			if (GetAsyncKeyState('W')) // For Controlling the Pointer
			{
				if (scrollPos <= 0) {
					scrollPos = (Skills.size() - 1);
				}
				else
				{
					scrollPos--;
				}
			}
			if (GetAsyncKeyState('S'))
			{

				if (scrollPos > (Skills.size() - 2)) {
					scrollPos = 0;
				}
				else
				{
					scrollPos++;

				}
			}
			if (GetAsyncKeyState('X')) {
				return scrollPos;
			}

			for (int i = 0; i < Skills.size(); i++) //Prints amount relative to number of Skills
			{
				std::cout << Skills[i].Name;
				if (i == scrollPos) {
					std::cout << "\033[1;31m <-\033[0m" << std::endl; //Generates the Pointer
				}
				else { std::cout << std::endl; }
				std::cout << Skills[i].Description << " cost:" << Skills[i].Cost << (Skills[i].ManaCost ? "mana " : " hp ") << (Skills[i].Healing ? "heals: " : "deals: ") << Skills[i].Base << std::endl;
			}
			std::cout << "\033[1;36mUse the [W] and [S] Keys to toggle between skills. [X] to Select skill.\033[0m";
			Sleep(100);
		}
	}
}

void Player::GenerateUI(Entity Enemy)
{
	std::cout << "A " << "\033[1;35m" << Enemy.getName() << "\033[0m" << " approaches you menacingly!" << std::endl;
	std::cout << "they are weak to :";
	switch (Enemy.getWeakness())
	{
	case Fire:
		std::cout << "\033[1;31mFire\033[0m";
		break;
	case Ice:
		std::cout << "\033[1;34mIce\033[0m";
		break;
	case Lightning:
		std::cout << "\033[0;33mLightning\033[0m";
		break;
	case Wind:
		std::cout << "\033[0;32mWind\033[0m";
		break;
	case Darkness:
		std::cout << "\033[0;35mDarkness\033[0m";
		break;
	case Siphon:
		std::cout << "Siphon";
		break;

	default:
		std::cout << "Nothing!!";
		break;
	}
	std::cout << std::endl << "They are Resistant to  : ";
	switch (Enemy.getResistance())
	{
	case Fire:
		std::cout << "\033[1;31mFire\033[0m";
		break;
	case Ice:
		std::cout << "\033[1;34mIce\033[0m";
		break;
	case Lightning:
		std::cout << "\033[0;33mLightning\033[0m";
		break;
	case Wind:
		std::cout << "\033[0;32mWind\033[0m";
		break;
	case Darkness:
		std::cout << "\033[0;35mDarkness\033[0m";
		break;
	case Siphon:
		std::cout << "Siphon";
		break;

	default:
		std::cout << "Nothing!!";
		break;
	}
	std::cout << std::endl;


	int pos;
	std::cout << Enemy.getName() << "'s \033[1;31m[HP] > \033[0m" << Enemy.getHP() << " CR is :" << int(Enemy.getCR()) << std::endl;
	int barWidth = 70;

	std::cout << "[";
	pos = barWidth * Enemy.getHP() / Enemy.getMaxHP();
	for (int i = 0; i < barWidth; ++i) {
		if (i < pos) std::cout << "\033[1;32m=\033[0m";
		else if (i == pos) std::cout << "\033[1;32m>\033[0m";
		else std::cout << " ";
	}
	std::cout << "] " << int(Enemy.getHP());
	std::cout.flush();
	std::cout << std::endl;
	std::cout << "[";
	pos = barWidth * 0.01 * Enemy.getCR();
	for (int i = 0; i < barWidth; ++i) {
		if (i < pos) std::cout << "=";
		else if (i == pos) std::cout << ">";
		else std::cout << " ";
	}
	std::cout << "] " << int(Enemy.getCR()) << " %\r";
	std::cout.flush();

	std::cout << std::endl << std::endl;
	std::cout << "Your \033[1;31m[HP] > \033[0m" << HP << " " << "\033[1;36m[MANA] > \033[0m" << Mana << " CR is :" << CombatReady << std::endl;


	std::cout << "[";
	pos = barWidth * HP / MaxHp;
	for (int i = 0; i < barWidth; ++i) {
		if (i < pos) std::cout << "\033[1;32m=\033[0m";
		else if (i == pos) std::cout << "\033[1;32m>\033[0m";
		else std::cout << " ";
	}
	std::cout << "] " << int(HP);
	std::cout.flush();
	std::cout << std::endl;
	std::cout << "[";
	if (CombatReady == 0)
	{
		pos = barWidth * 1;
	}
	else { pos = barWidth * CombatReady / 100; }
	for (int i = 0; i < barWidth; ++i) {
		if (i < pos) std::cout << "=";
		else if (i == pos) std::cout << ">";
		else std::cout << " ";
	}
	if (CombatReady == 0) { std::cout << "] " << 100 << " %\r"; }
	else { std::cout << "] " << int(CombatReady) << " %\r"; }
	std::cout.flush();

	std::cout << std::endl;

	std::cout << "It's " << Name << " 's turn. " << std::endl;
}

void Player::CalculateStats()
{
	// | 0 is STR | 1 is DEX | 2 is INT | 3 is VIT | 4 is LUK | 5 is WIS | 
	for (int i = 0; i < 6; i++) {
		character_Base_Stats[i] = (10 + character_Level[i]) * character_Modifiers[i];
	}
	//HP Calculations
	MaxHp = (character_Base_Stats[3] * 0.8f) + (character_Base_Stats[4] * 0.6f) + (character_Base_Stats[5] * 0.4f);
	//Mana Calculations
	MaxMana = (character_Base_Stats[2] * 5) + (character_Base_Stats[5] * 10);
	//Damage Caluclations
	DMGModifier = log10(character_Base_Stats[0] + (character_Base_Stats[1] * 0.5f));
	//Speed Calculations
	speed = log10((character_Base_Stats[1] * 1.5f) + (character_Base_Stats[0] * 0.8f) + 5);//log is used inorder to prevent modifiers from becoming too high
	//Magic Modifier
	MagicModifier = log10(character_Base_Stats[2] + (character_Base_Stats[5] * 0.5f));
}

void Player::DisplaySkills(int i)
{

	std::cout << Skills[i].Description << " cost:" << Skills[i].Cost << (Skills[i].ManaCost ? "mana " : " hp ") << (Skills[i].Healing ? "heals: " : "deals: ") << Skills[i].Base << std::endl;
}

Player::Player(std::string Name, float DMGModifier, float MaxHp, float Speed, float MaxMana, int Weak, int Res)
{
	Weakness = Weak;
	Resistance = Res;
	this->Name = Name;
	this->DMGModifier = DMGModifier;
	HP = this->MaxHp = MaxHp;
	this->speed = speed;
	Mana = this->MaxMana = MaxMana;
	Skills.push_back({ "Heal"," ", 5, 4,true,true,false });
	Skills.push_back({ "Slash"," ", 0, 3,false,false,false });
};

Player::Player(float character_Modifiers[6], std::string Name, int Weak, int Res)
{
	Weakness = Weak;
	Resistance = Res;
	this->Name = Name;
	for (int i = 0; i < 6; i++) {
		this->character_Modifiers[i] = character_Modifiers[i];
	}
	CalculateStats();
	HP = MaxHp;
	Mana = MaxMana;
	Skills.push_back({ "\033[1;33mShield bash\033[0m","A well rounded maneuver that blocks and deals damage.", 5, 4, false, false, true, None, 0 });
	Skills.push_back({ "\033[1;32mMeditate\033[0m","Heals hp and blocks. Also advances turn by 50%", 50, 15, true, true, false, Healing, -50 });
	Skills.push_back({ "\033[1;31mBerzerk blade\033[0m","High damage and high cost slash.", 10, 15, false, false, false, Fire, 0 });
};