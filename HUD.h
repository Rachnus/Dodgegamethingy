#pragma once
#include <SFML/Graphics.hpp>

class HUD
{
public:
	HUD(sf::RenderWindow *p_window,  bool *p_scene, int *p_score, int *p_wave, sf::Clock *p_clock);
	~HUD();

	void InitializeMainMenu();
	void InitializeHUD();
	void InitializePauseHUD();

	void HUDUpdate(sf::Time &dt);
	//void MainMenuUpdate(sf::Time &dt);
	void Draw();
	void DrawBackground();
	void Input();
	void Poll(sf::Event &Event);
	void RoundStart();

	void FlashDirection(bool *p_direction);
	void SetDirectionTextAlpha(float alpha, bool *p_direction);

	enum Option
	{
		MAIN = 0,
		PLAY = 1,
		EXIT = 2
	}option;

private:
	sf::RenderWindow *window;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite[2];
	//INGAME HUDE
	sf::Clock flash;
	sf::RectangleShape hudbase;
	sf::Vector2<float> hudbasesize;
	sf::Vector2<float> hudbasepos;
	sf::Color hudbaseColor;
	sf::Color labelColor;
	sf::Color popupColor;
	sf::Font fontArial;
	
	std::string stringScore;
	sf::Text textScore;

	std::string stringWave;
	sf::Text textWave;

	sf::Text textWavePopup;

	sf::Text textTime;

	sf::Text textDirection[4];

	bool roundstart;
	
	float popupAlpha;
	const int charactersize;

	bool *scene;
	int *score;
	int *wave;
	sf::Clock *clock;
	//MAIN MENU HUD
	sf::Vector2<float> buttonsize;
	sf::Color buttoncolor;

	sf::RectangleShape buttonsmain[2];
	sf::Text labelButtonsmain[2];
	bool mainbuttons[2];
	//PAUSE MENU HUD

	sf::RectangleShape buttonspause[2];
	sf::Text labelButtonspause[2];
	bool pausebuttons[2];

};

