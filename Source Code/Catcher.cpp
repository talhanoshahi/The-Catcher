#include <fstream>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdio>
#include <map>
#include <experimental/filesystem>
#include "Player.hpp"

namespace fs= std::experimental::filesystem;

#define SCREEN_WIDTH 720 
#define SCREEN_HEIGHT 720 

void setText (sf::Text &, sf::Font &, float);
void setOrigin (sf::Text &);
const int numberOfFiles (fs::path &);

int main()
{
	std::string CurrentDirectory = fs::current_path();
	std::string pathToFolder = CurrentDirectory + "/Players";
	std::map <sf::String, Player> Gamer;
	std::fstream playerFile;
	fs::path toFolder(pathToFolder);
	sf::String playerUsername;

	bool displayWelcome = true;
	bool selectPlayer = false;
	bool playerType_new = false;
	bool playerType_existing = false;
	bool mainMenu = false;
	bool deletePlayer = false;
	bool myProfile = false;
	bool newGame = false;
	bool gameOver = true;
	bool objectDropped = true;
	bool shapeIsOnTheScreen = false;
	bool displayGameOver = false;
	bool dataStored = false;

	int chance = 5;
	int gameScore = 0;
	int objectShape;
	int circleRadius;
	int circlePosition;
	
	srand (time(0));

	sf::Font font;
	font.loadFromFile ("times_new_roman.ttf");

	sf::Text Welcome;
	Welcome.setString ("Welcome to The Catcher!!!");
	setText (Welcome, font, 50);
	setOrigin (Welcome);
	Welcome.setStyle (sf::Text::Bold);
	Welcome.setPosition (sf::Vector2f (SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f));
	
	sf::Text BOT;
	BOT.setString ("Developed by BOT;");
	setText (BOT, font, 40);
	setOrigin (BOT);
	BOT.setPosition(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT-40.0f);
	BOT.setStyle (sf::Text::Bold);

	sf::Text Text1;
	setText (Text1, font, 30);
	setOrigin (Text1);
	
	sf::Text Text2;
	setText (Text2, font, 25);
	setOrigin (Text2);
	
	sf::Text Text3;
	setText (Text3, font, 25);
	setOrigin (Text3);
	
	sf::Text Text4;
	setText (Text4, font, 25);
	setOrigin (Text4);

	sf::RectangleShape textInput (sf::Vector2f (200, 40));
	textInput.setFillColor (sf::Color::Transparent);
	textInput.setOutlineColor (sf::Color::White);
	textInput.setOutlineThickness (3.0f);

	sf::CircleShape Circle;
	sf::CircleShape Square (0, 4);

	sf::RectangleShape board (sf::Vector2f(70.0f, 20.0f));
	board.setPosition (340, 660);

	sf::RectangleShape leftBorder (sf::Vector2f (SCREEN_WIDTH, 3));
	leftBorder.setPosition (30, 0);
	leftBorder.rotate (90);

	sf::RectangleShape rightBorder (sf::Vector2f (SCREEN_WIDTH, 3));
	rightBorder.setPosition (SCREEN_WIDTH-30, 0);
	rightBorder.rotate (90);

	sf::RenderWindow window (sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "This is BOT's Game!");

	while (window.isOpen ())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
		        window.close();
		}

		window.clear();

		if (displayWelcome)
		{
			window.draw (Welcome);
			window.draw (BOT);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				displayWelcome = false;
				selectPlayer = true;
			}
			
		}

		else if (selectPlayer)
		{
			Text1.setString ("Select Player Type");
			Text2.setString ("1. New Player");
			Text3.setString ("2. Existing Player");
			Text4.setString ("3. Delete Player");

			Text1.setPosition ( 160 , 300);
			Text2.setPosition ( 200 , 360);
			Text3.setPosition ( 200 , 400);
			Text4.setPosition ( 200 , 440);

			window.draw (Text1);
			window.draw (Text2);
			window.draw (Text3);
			window.draw (Text4);
			
			if (sf::Mouse::getPosition(window).x >= Text2.getPosition().x && sf::Mouse::getPosition(window).x <= (Text2.getPosition().x+Text2.getLocalBounds().width) && sf::Mouse::getPosition(window).y >= Text2.getPosition().y && sf::Mouse::getPosition(window).y <= (Text2.getPosition().y +Text2.getLocalBounds().height))
			{
				Text2.setFillColor(sf::Color::Blue);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					selectPlayer = false;
					playerType_new = true;
				}
				
			}
			else
			{
				Text2.setFillColor(sf::Color::White);
			} 
			
			if (sf::Mouse::getPosition(window).x >= Text3.getPosition().x && sf::Mouse::getPosition(window).x <= (Text3.getPosition().x+Text3.getLocalBounds().width) && sf::Mouse::getPosition(window).y >= Text3.getPosition().y && sf::Mouse::getPosition(window).y <= (Text3.getPosition().y +Text3.getLocalBounds().height))
			{
				Text3.setFillColor(sf::Color::Blue);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					selectPlayer = false;
					playerType_existing = true;
				}
			}
			else
			{
				Text3.setFillColor(sf::Color::White);
			}
			
			if (sf::Mouse::getPosition(window).x >= Text4.getPosition().x && sf::Mouse::getPosition(window).x <= (Text4.getPosition().x+Text4.getLocalBounds().width) && sf::Mouse::getPosition(window).y >= Text4.getPosition().y && sf::Mouse::getPosition(window).y <= (Text4.getPosition().y +Text4.getLocalBounds().height))
			{
				Text4.setFillColor(sf::Color::Blue);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					selectPlayer = false;
					deletePlayer = true;
				}
			}
			else
			{
				Text4.setFillColor(sf::Color::White);
			}
		}

		else if (playerType_new)
		{
			bool namingComplete = false;

			Text1.setString ( "Enter your username: " );
			Text1.setPosition ( 50, SCREEN_HEIGHT/2.0f );

			Text2.setString (" ");
			Text2.setFillColor (sf::Color::White);
			Text2.setPosition (350, SCREEN_HEIGHT/2.0f);
		
			if (event.type == sf::Event::TextEntered)
			{
				if ((event.text.unicode >= 65 && event.text.unicode <=90) || (event.text.unicode > 96 && event.text.unicode <=122))
				{
					playerUsername += event.text.unicode;
					event.text.unicode = 128;
				}
				
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				playerType_new = false;
				mainMenu = true;
				namingComplete = true;
			}

			if (namingComplete)
			{
				if (fs::exists (fs::path (pathToFolder + "/" + (playerUsername.toAnsiString()))))
				{
					std::string Name;
					int scores[2];

					playerFile.open ((pathToFolder + "/" + (playerUsername.toAnsiString())), std::ios::in);
					if (playerFile.is_open())
					{
						std::string read;
						
						getline(playerFile,Name);
						getline(playerFile,read);
						scores[0] = stoi (read);
						getline(playerFile,read);
						scores[1] = stoi (read);
						playerFile.close();
					}
					
					Gamer [playerUsername] = Player (Name, scores[0], scores[1]);
				}
				else
				{
					Gamer [playerUsername] = Player (playerUsername.toAnsiString(), 0, 0);
					std::ofstream inputFile (pathToFolder+"/"+((playerUsername.toAnsiString()).c_str()));
					if (inputFile.is_open())
					{
						inputFile << (playerUsername.toAnsiString()) << std::endl;
						inputFile << int(0) << std::endl;
						inputFile << int(0) << std::endl;
					}

					inputFile.close();
				}
				
				
			}
			
			Text2.setString(playerUsername);

			textInput.setPosition (350, SCREEN_HEIGHT/2.0f);

			window.draw (Text1);
			window.draw (textInput);			
			window.draw (Text2);
		}
		
		else if (playerType_existing)
		{
			Text1.setString ( "Select your profile: " );
			Text1.setPosition ( SCREEN_WIDTH/3.0f, 220 );
			
			window.draw (Text1);

			const int filesNumber = numberOfFiles(toFolder);

			sf::Text fileNames [filesNumber];
			int i = 0;
			int height= SCREEN_HEIGHT/2.0f -80;

			if (fs::exists (toFolder) && fs::is_directory (toFolder))
			{
				for (const auto& entry: fs::directory_iterator (toFolder))
				{
					auto name = entry.path ().filename();
					fileNames[i].setString (name.c_str());
					fileNames[i].setFont (font);
					fileNames[i].setFillColor (sf::Color::White);
					fileNames[i].setPosition (250, height);
					height += 50;
					i++;
				}
			}

			for ( i = 0; i < filesNumber; i++)
			{
				if (sf::Mouse::getPosition(window).x >= fileNames[i].getPosition().x && sf::Mouse::getPosition(window).x <= (fileNames[i].getPosition().x+fileNames[i].getLocalBounds().width) && sf::Mouse::getPosition(window).y >= fileNames[i].getPosition().y && sf::Mouse::getPosition(window).y <= (fileNames[i].getPosition().y +fileNames[i].getLocalBounds().height))
				{
					fileNames[i].setFillColor(sf::Color::Blue);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						playerType_existing = false;
						mainMenu = true;
						playerUsername = fileNames[i].getString ();

						std::string Name;
						int scores[2];

						playerFile.open ((pathToFolder + "/" + (playerUsername.toAnsiString())), std::ios::in);
						if (playerFile.is_open())
						{
							std::string read;

							getline(playerFile,Name);
							getline(playerFile,read);
							scores[0] = stoi (read);
							getline(playerFile,read);
							scores[1] = stoi (read);
							playerFile.close();
						}

						Gamer[playerUsername] = Player (Name , scores[0] , scores[1]);

						break;
					}
				}
				else
				{
					fileNames[i].setFillColor(sf::Color::White);
				}
				
			}
			
			for ( i = 0; i < filesNumber; i++)
			{
				window.draw (fileNames[i]);
			}
				
		}
		
		else if (deletePlayer)
		{
			Text1.setString ( "Select the profile to delete: " );
			Text1.setPosition ( SCREEN_WIDTH/3.0f, 220 );
			
			window.draw (Text1);

			const int filesNumber = numberOfFiles(toFolder);

			sf::Text fileNames [filesNumber+1];
			int i = 0;
			int height= SCREEN_HEIGHT/2.0f -80;

			if (fs::exists (toFolder) && fs::is_directory (toFolder))
			{
				for (const auto& entry: fs::directory_iterator (toFolder))
				{
					auto name = entry.path ().filename();
					fileNames[i].setString (name.c_str());
					fileNames[i].setFont (font);
					fileNames[i].setFillColor (sf::Color::White);
					fileNames[i].setPosition (250, height);
					height += 50;
					i++;
				}
			}
				
			fileNames[filesNumber].setString ("<= Back");
			fileNames[filesNumber].setFont (font);
			fileNames[filesNumber].setFillColor (sf::Color::White);
			fileNames[filesNumber].setPosition (SCREEN_WIDTH/3.0f, height);

			for ( i = 0; i < filesNumber; i++)
			{
				if (sf::Mouse::getPosition(window).x >= fileNames[i].getPosition().x && sf::Mouse::getPosition(window).x <= (fileNames[i].getPosition().x+fileNames[i].getLocalBounds().width) && sf::Mouse::getPosition(window).y >= fileNames[i].getPosition().y && sf::Mouse::getPosition(window).y <= (fileNames[i].getPosition().y +fileNames[i].getLocalBounds().height))
				{
					fileNames[i].setFillColor(sf::Color::Blue);
					if (event.type == sf::Event::MouseButtonPressed)
					{
						if (event.mouseButton.button == sf::Mouse::Left)
						{
							fs::remove ((pathToFolder+"/"+(((fileNames[i].getString()).toAnsiString()).c_str())));
						}
						event.type = sf::Event::TextEntered;
					}
				}
				else
				{
					fileNames[i].setFillColor(sf::Color::White);
				}
			
				
			}

			if (sf::Mouse::getPosition(window).x >= fileNames[filesNumber].getPosition().x && sf::Mouse::getPosition(window).x <= (fileNames[filesNumber].getPosition().x+fileNames[filesNumber].getLocalBounds().width) && sf::Mouse::getPosition(window).y >= fileNames[filesNumber].getPosition().y && sf::Mouse::getPosition(window).y <= (fileNames[filesNumber].getPosition().y +fileNames[filesNumber].getLocalBounds().height))
			{
				fileNames[filesNumber].setFillColor(sf::Color::Blue);
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						deletePlayer = false;
						selectPlayer = true;
					}
					event.type = sf::Event::TextEntered;
				}
			}
			else
			{
				fileNames[i].setFillColor(sf::Color::White);
			}
			
			for ( i = 0; i <= filesNumber; i++)
			{
				window.draw (fileNames[i]);
			}
				
		}

		else if (mainMenu)
		{
			sf::Text mainMenuText[4];
			int i = 0;
			int height = SCREEN_HEIGHT/2.5f;

			for (i = 0; i < 4; i++)
			{
				setText (mainMenuText[i], font, 30);
			}
			
			mainMenuText[0].setString (playerUsername.toAnsiString());
			mainMenuText[0].setPosition(10,15);


			mainMenuText[1].setString ("New Game");
			mainMenuText[2].setString ("My Profile");
			mainMenuText[3].setString ("Exit");

			for (i = 1; i < 4; i++)
			{
				setOrigin (mainMenuText[i]);
				mainMenuText[i].setPosition(SCREEN_WIDTH/2.0f, height);
				height += SCREEN_HEIGHT/8;
			}
			
			if (sf::Mouse::getPosition(window).x >= (mainMenuText[1].getPosition().x-mainMenuText[1].getLocalBounds().width) && sf::Mouse::getPosition(window).x <= (mainMenuText[1].getPosition().x+mainMenuText[1].getLocalBounds().width) && sf::Mouse::getPosition(window).y >= (mainMenuText[1].getPosition().y-mainMenuText[1].getLocalBounds().height) && sf::Mouse::getPosition(window).y <= (mainMenuText[1].getPosition().y +mainMenuText[1].getLocalBounds().height))
			{
				mainMenuText[1].setFillColor(sf::Color::Blue);
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						newGame = true;
						mainMenu = false;
					}
				}
			}	
			else
			{
				mainMenuText[1].setFillColor(sf::Color::White);
			}
			
			if (sf::Mouse::getPosition(window).x >= (mainMenuText[2].getPosition().x-mainMenuText[2].getLocalBounds().width/2.0f) && sf::Mouse::getPosition(window).x <= (mainMenuText[2].getPosition().x+mainMenuText[2].getLocalBounds().width/2.0f) && sf::Mouse::getPosition(window).y >= (mainMenuText[2].getPosition().y - mainMenuText[2].getLocalBounds().height/2.0f) && sf::Mouse::getPosition(window).y <= (mainMenuText[2].getPosition().y +mainMenuText[2].getLocalBounds().height/2.0f))
			{
				mainMenuText[2].setFillColor(sf::Color::Blue);
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						myProfile = true;
						mainMenu = false;
					}
				}
			}	
			else
			{
				mainMenuText[2].setFillColor(sf::Color::White);
			}	

			if (sf::Mouse::getPosition(window).x >= (mainMenuText[3].getPosition().x-mainMenuText[3].getLocalBounds().width) && sf::Mouse::getPosition(window).x <= (mainMenuText[3].getPosition().x+mainMenuText[3].getLocalBounds().width) && sf::Mouse::getPosition(window).y >= (mainMenuText[3].getPosition().y - mainMenuText[3].getLocalBounds().height) && sf::Mouse::getPosition(window).y <= (mainMenuText[3].getPosition().y +mainMenuText[3].getLocalBounds().height))
			{
				mainMenuText[3].setFillColor(sf::Color::Blue);
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						window.close();
					}
				}
			}	
			else
			{
				mainMenuText[3].setFillColor(sf::Color::White);
			}

			for (i = 0; i < 4; i++)
			{
				window.draw (mainMenuText[i]);
			}
			
		}

		if (newGame)
		{
			sf::Text ContinueTOGame;
			ContinueTOGame.setString("Press any key to Continue;");
			setText (ContinueTOGame, font, 40);
			setOrigin (ContinueTOGame);
			ContinueTOGame.setPosition (SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f);

			gameScore = 0;
			chance = 5;
			dataStored = false;
			
			if (event.type == sf::Event::TextEntered)
			{
				newGame = false;
				gameOver = false;
			}
			

			window.draw (ContinueTOGame);
		}
		

		if (myProfile)
		{
			sf::Text profileText[5];
			int i = 0;
			int height = SCREEN_HEIGHT/4.0f;

			profileText [0].setString("Username: " + Gamer [playerUsername].getName());
			profileText [1].setString("Total Score: " + std::to_string (Gamer [playerUsername].get_playerScore()));
			profileText [2].setString("Highest Score: " + std::to_string (Gamer [playerUsername].get_highestScore()));
			profileText [3].setString("Tier: " + Gamer [playerUsername].getTier_forDisplay());
			profileText [4].setString("Back");

			setText (profileText[0], font, 35);
			setOrigin (profileText[0]);
			setText (profileText[4], font, 35);
			setOrigin (profileText[4]);

			for (i = 1; i < 4; i++)
			{
				setText (profileText[i], font, 25);
				setOrigin (profileText[i]);
			}

			profileText[0].setPosition(SCREEN_WIDTH/2.0f, height);
			height += SCREEN_HEIGHT/4.0f;

			for ( i = 1; i < 4; i++)
			{
				profileText[i].setPosition(SCREEN_WIDTH/2.0f, height);
				height += SCREEN_HEIGHT/8.0f;
			}

			profileText[4].setPosition(SCREEN_WIDTH/4.0f, height);

			if (sf::Mouse::getPosition(window).x >= (profileText[4].getPosition().x-profileText[4].getLocalBounds().width) && sf::Mouse::getPosition(window).x <= (profileText[4].getPosition().x+profileText[4].getLocalBounds().width) && sf::Mouse::getPosition(window).y >= (profileText[4].getPosition().y - profileText[4].getLocalBounds().height) && sf::Mouse::getPosition(window).y <= (profileText[4].getPosition().y +profileText[4].getLocalBounds().height))
			{
				profileText[4].setFillColor(sf::Color::Blue);
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						myProfile = false;
						mainMenu = true;
					}
				}
			}	
			else
			{
				profileText[4].setFillColor(sf::Color::White);
			}

			for (i = 0; i < 5; i++)
			{
				window.draw (profileText[i]);
			}
			
		}

		if (!gameOver)
		{
			window.setMouseCursorVisible(false);

			window.draw (board);
			
			if (gameScore < 200)
			{
			
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) )
				{
					board.move (-1.2 , 0);
				}

				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) )
				{
					board.move (1.2 , 0);
				}
			}

			else if (gameScore >= 200 && gameScore < 500)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) )
				{
					board.move (-1.7 , 0);
				}

				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) )
				{
					board.move (1.7 , 0);
				}
			}
			
			else if (gameScore >= 500 && gameScore < 1000)
			{
			
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) )
				{
					board.move (-2.5 , 0);
				}

				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) )
				{
					board.move (2.5 , 0);
				}
			}

			if (shapeIsOnTheScreen != true)
			{
				objectShape = rand () % 2;
				if (objectShape == 0)
				{
					circleRadius = rand () % 30;
					if (circleRadius == 0)
					{
						circleRadius += 2;
					}
					
					circlePosition = rand () % 720;
					
					if (circlePosition <40)
					{
						circlePosition = circlePosition + 50;
					}
					else if (circlePosition > 40 && circlePosition < 650)
					{
						circlePosition = circlePosition + 50;
					}
					else if (circlePosition >650)
					{
						circlePosition = circlePosition - 50;
					}
					
					Circle.setRadius (circleRadius);
					Circle.setPosition (circlePosition, 0);
					shapeIsOnTheScreen = true;
				}
				else if (objectShape == 1)
				{
					circleRadius = rand () % 30;
					if (circleRadius == 0)
					{
						circleRadius += 2;
					}
					
					circlePosition = rand () % 720;

					if (circlePosition <40)
					{
						circlePosition = circlePosition + 50;
					}
					else if (circlePosition > 40 && circlePosition < 650)
					{
						circlePosition = circlePosition + 50;
					}
					else if (circlePosition >650)
					{
						circlePosition = circlePosition - 50;
					}
					
					Square.setRadius (circleRadius);
					Square.setPosition (circlePosition, 0);
					shapeIsOnTheScreen = true;
				}
			}

			if (objectShape == 0 && shapeIsOnTheScreen == true)
			{
				if (gameScore < 200)
				{
					Circle.move (0, 1);
				}
				else if (gameScore >= 200 && gameScore < 500)
				{
					Circle.move (0, 2);
				}
				else if (gameScore >= 500 && gameScore < 1000)
				{
					Circle.move (0, 3);
				}
				
				window.draw (Circle);
				if (Circle.getPosition().x < ((board.getPosition().x)+70) && Circle.getPosition().x > ((board.getPosition().x)-70) && Circle.getPosition().y > 650 && Circle.getPosition().y < 670)
				{
					gameScore += 4;
					shapeIsOnTheScreen = false;
				}
				else if (Circle.getPosition().y > 670 /* board.getPosition().y */)
				{
					chance --;
					shapeIsOnTheScreen = false;
				}
				
			}
			else if (objectShape == 1 && shapeIsOnTheScreen == true)
			{
				if (gameScore < 200)
				{
					Square.move (0, 1);
				}
				else if (gameScore >= 200 && gameScore < 500)
				{
					Square.move (0, 2);
				}
				else if (gameScore >= 500 && gameScore < 1000)
				{
					Square.move (0, 3);
				}
				window.draw (Square);
				if (Square.getPosition().x < ((board.getPosition().x)+70) && Square.getPosition().x > ((board.getPosition().x)-70) && Square.getPosition().y > 650 && Square.getPosition().y < 670)
				{
					gameScore += 6;
					shapeIsOnTheScreen = false;
				}
				else if (Square.getPosition().y > 670 /* board.getPosition().y */)
				{
					chance --;
					shapeIsOnTheScreen = false;
				}
				
			}

			if (chance <= 0)
			{
				gameOver = true;
				displayGameOver = true;
			}

			sf::Text printWhileGaming[2];
			printWhileGaming[0].setString("Score: " + std::to_string(gameScore));
			printWhileGaming[1].setString("Chances Left: " + std::to_string(chance));

			for (int i = 0; i < 2; i++)
			{
				setText (printWhileGaming[i], font, 25);
			}

			printWhileGaming[0].setPosition(35,0);
			printWhileGaming[1].setPosition(SCREEN_WIDTH-220.0f,0);
			
			
			window.draw (leftBorder);
			window.draw (rightBorder);
			window.draw (printWhileGaming[0]);
			window.draw (printWhileGaming[1]);
		}

		else if (displayGameOver)
		{
			if (!dataStored)
			{
				Gamer [playerUsername].playerScorePlusPlus(gameScore);
				Gamer [playerUsername].highScorePlusPlus(gameScore);
				dataStored = true;
			}
			
			
			playerFile.open(pathToFolder + "/" + Gamer[playerUsername].getName(), std::ios::out | std::ios::trunc);
			if (playerFile.is_open())
			{
				playerFile << (Gamer[playerUsername].getName()) << std::endl;
				playerFile << (Gamer[playerUsername].get_playerScore()) << std::endl;
				playerFile << (Gamer[playerUsername].get_highestScore()) << std::endl;
				playerFile.close();
			}

			window.setMouseCursorVisible(true);

			sf::Text GameOverText[2];
			GameOverText[0].setString("Game Over");
			setText (GameOverText[0], font, 50);
			GameOverText[0].setStyle(sf::Text::Bold);
			
			GameOverText[1].setString("Score: " + std::to_string(gameScore));
			setText (GameOverText[1], font, 30);
			
			for (int i = 0, height = SCREEN_HEIGHT/5.0f; i < 2; i++, height += SCREEN_HEIGHT/6.0f )
			{
				setOrigin (GameOverText[i]);
				GameOverText[i].setPosition(SCREEN_WIDTH/2.0f, height);
				window.draw (GameOverText[i]);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				displayGameOver = false;
				mainMenu = true;
			}
	
		}
		
		window.display();
		
	}

	if (playerFile.is_open())
	{
		playerFile.close();
	}
	
	return 0;
}

void setText (sf::Text & set,sf::Font & font, float Size)
{
	set.setFont (font);
	set.setCharacterSize (Size);
	set.setFillColor (sf::Color::White);
}

void setOrigin (sf::Text & Origin)
{
	sf::FloatRect textRect = Origin.getLocalBounds();
	Origin.setOrigin(textRect.left + textRect.width/2.0f,textRect.top  + textRect.height/2.0f);
}

const int numberOfFiles (fs::path & toFolder)
{
	int number_of_files = 0;
	for (auto const & file : fs::directory_iterator(toFolder))
	{
		++number_of_files;
	}
	return number_of_files;
}
