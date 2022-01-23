#include <string>

enum Tier
{
	Bronze = 1 , Silver , Gold, Platinum, Diamond
};

class Player
{
private:
	std::string Name;
	int playerScore;
	int highestScore;
	Tier playerTier;
public:
	Player();
	Player(std::string, int, int);

	void setPlayer (std::string , int, int);
	void setName (std::string);
	void set_playerScore (int);
	void set_highestScore (int);
	void currentTier (int);
	void playerScorePlusPlus(const int &);
	void highScorePlusPlus(const int &);

	std::string getName ();
	int get_playerScore ();
	int get_highestScore ();
	std::string getTier_forDisplay();

	~Player();
};
