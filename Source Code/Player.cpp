#include <string>

enum Tier 
{
	Bronze = 1 , Silver , Gold, Platinum, Diamond
};

const char *tierName[] = 
{
	"Bronze", "Silver", "Gold", "Platinum", "Diamond", NULL
};

const char *Tier_Name(int Tier) {
	if(Tier < 1 || Tier > 5)
	{
		return "Invalid tier.";
		}

	return tierName[Tier-1];
}


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

Player::Player()
{
	Name = '\0';
	playerScore = 0;
	highestScore = 0;
	playerTier = Bronze;
}

Player::Player(std::string Name, int playerScore, int highestScore)
{
	this -> Name = Name;
	this -> playerScore = playerScore;
	this -> highestScore = highestScore;
	currentTier (playerScore);
}

void Player::setPlayer (std::string Name , int playerScore, int highestScore)
{
	this-> Name = Name;
	this-> playerScore = playerScore;
	this-> highestScore = highestScore;
	currentTier (playerScore);
}

void Player::setName (std::string Name)
{
	this-> Name = Name;
}

void Player::set_playerScore (int playerScore)
{
	this-> playerScore = playerScore;
	currentTier (playerScore);
}

void Player::set_highestScore (int playerScore)
{
	if (this->highestScore > playerScore)
	{
		return;
	}
	this-> highestScore = playerScore;
}

void Player::currentTier (int Score)
{
	if ( Score >=0 && Score <250 )
	{
		playerTier = Bronze;
		return;
	}
	
	else if ( Score >=250 && Score <600 )
	{
		playerTier = Silver;
		return;
	}
	
	else if ( Score >=600 && Score <1100 )
	{
		playerTier = Gold;
		return;
	}
	
	else if ( Score >=1100 && Score <1800 )
	{
		playerTier = Platinum;
		return;
	}
	
	else if ( Score >=1800 && Score <3000 )
	{
		playerTier = Diamond;
		return;
	}
}

std::string Player::getName()
{
	return Name;
}

int Player::get_playerScore()
{
	return playerScore;
}

int Player::get_highestScore()
{
	return highestScore;
}

std::string Player::getTier_forDisplay ()
{
	return (Tier_Name (playerTier));
}

void Player::playerScorePlusPlus (const int & newScore)
{
	playerScore = playerScore + newScore;
	currentTier(playerScore);
}

void Player::highScorePlusPlus (const int & newScore)
{
	if (highestScore < newScore)
	{
		highestScore = newScore;
		return;
	}
	
}

Player::~Player()
{

}
