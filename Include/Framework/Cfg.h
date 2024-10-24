#ifndef CFG_H__
#define CFG_H__

#include <SFML/Graphics.hpp>
#include <Framework/ResourceManager.h>
#include <Framework/ActionMap.h>
#include <vector>
#include <variant>
#include <utility>

struct Cfg
{
	Cfg() = delete;
	Cfg(const Cfg&) = delete;
	Cfg& operator=(const Cfg&) = delete;
	static void Initialize();
	// Resource Enums 
	enum class Textures : int { Logo, Title, SelectArrow, InvariantTile, PlayerAtlas, Count };
	enum class Fonts : int { Title, Count };
	enum class Music : int { Count };
	enum class Sounds : int { Count };
	// inputs the player will be able to use
	enum class PlayerInputs : int
	{
		// Keyboard mappable Keypresses
		Up, Down, Left, Right, A, X, Y, B, Start, Select, R1, L1,
		//// Joystick input, like a ps5 controller, DPad* and Axis* are handled differently than the rest of the joystick
		DPadX, DPadY, AxisX, AxisY,
		JoyA, JoyB, JoyX, JoyY, JoyR1, JoyL1, JoyStart, JoySelect
	};
	// resource buckets for each type of resource
	static ResourceManager<sf::Texture, int> textures;
	static ResourceManager<sf::Music, int> music;
	static ResourceManager<sf::SoundBuffer, int> sounds;
	static ResourceManager<sf::Font, int> fonts;
	static ActionMap<int> playerInputs;
private:
    // initalize the resources for the entire game
    static void initFonts();
    static void initMusic();
    static void initSounds();
    static void initTextures();
	static void initPlayerInputs();
};

#endif