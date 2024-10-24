#include <Framework/Cfg.h>
#include <Framework/ResourceManager.h>

ResourceManager<sf::Texture, int> Cfg::textures = {};
ResourceManager<sf::Font, int> Cfg::fonts = {};
ResourceManager<sf::Music, int> Cfg::music = {};
ResourceManager<sf::SoundBuffer, int> Cfg::sounds = {};

ActionMap<int> Cfg::playerInputs = {};

void Cfg::Initialize()
{
    initTextures();
    initFonts();
    initMusic();
    initSounds();
	initPlayerInputs();
}

void Cfg::initMusic()
{
}

void Cfg::initSounds()
{
}

void Cfg::initTextures()
{
	textures.load((int)Textures::Logo, "Assets/Textures/Backdrop/logo.png");
	textures.load((int)Textures::Title, "Assets/Textures/Backdrop/title.png");
	textures.load((int)Textures::SelectArrow, "Assets/Textures/GUI/SelectionArrow.png");
	textures.load((int)Textures::InvariantTile, "Assets/Textures/Tilesets/invariantTile64.png");
	textures.load((int)Textures::PlayerAtlas, "Assets/Textures/Entities/playerAtlas.png");

}

void Cfg::initPlayerInputs()
{
	// realtime events
	// Keyboard pressed commands
	playerInputs.map((int)Cfg::PlayerInputs::X, Action(sf::Keyboard::Num9));
	playerInputs.map((int)Cfg::PlayerInputs::Y, Action(sf::Keyboard::X));
	playerInputs.map((int)Cfg::PlayerInputs::A, Action(sf::Keyboard::Num0));
	playerInputs.map((int)Cfg::PlayerInputs::B, Action(sf::Keyboard::Space));
	playerInputs.map((int)Cfg::PlayerInputs::L1, Action(sf::Keyboard::Num7));
	playerInputs.map((int)Cfg::PlayerInputs::R1, Action(sf::Keyboard::Add));
	// menu controls
	playerInputs.map((int)Cfg::PlayerInputs::Start, Action(sf::Keyboard::Enter));
	playerInputs.map((int)Cfg::PlayerInputs::Select, Action(sf::Keyboard::Backspace));
	// direction contro(int)ls
	playerInputs.map((int)Cfg::PlayerInputs::Up, Action(sf::Keyboard::Up));
	playerInputs.map((int)Cfg::PlayerInputs::Down, Action(sf::Keyboard::Down));
	playerInputs.map((int)Cfg::PlayerInputs::Left, Action(sf::Keyboard::Left));
	playerInputs.map((int)Cfg::PlayerInputs::Right, Action(sf::Keyboard::Right));

	// Joystick Control(int)s
	// Axis mappings
    playerInputs.map((int)Cfg::PlayerInputs::AxisX, Action(sf::Joystick::Axis::X, Action::Type::RealTime | Action::Type::Tilted));
	playerInputs.map((int)Cfg::PlayerInputs::AxisY, Action(sf::Joystick::Axis::Y, Action::Type::RealTime | Action::Type::Tilted));
	playerInputs.map((int)Cfg::PlayerInputs::DPadX, Action(sf::Joystick::Axis::PovX, Action::Type::RealTime | Action::Type::Tilted));
	playerInputs.map((int)Cfg::PlayerInputs::DPadY, Action(sf::Joystick::Axis::PovY, Action::Type::RealTime | Action::Type::Tilted));
	// Button mapping(int)s
	playerInputs.map((int)Cfg::PlayerInputs::JoyA, Action(JoystickBtn::A, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map((int)Cfg::PlayerInputs::JoyB, Action(JoystickBtn::B, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map((int)Cfg::PlayerInputs::JoyX, Action(JoystickBtn::X, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map((int)Cfg::PlayerInputs::JoyY, Action(JoystickBtn::Y, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map((int)Cfg::PlayerInputs::JoyL1, Action(JoystickBtn::L1, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map((int)Cfg::PlayerInputs::JoyR1, Action(JoystickBtn::R1, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map((int)Cfg::PlayerInputs::JoyStart, Action(JoystickBtn::Start, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map((int)Cfg::PlayerInputs::JoySelect, Action(JoystickBtn::Select, Action::Type::RealTime | Action::Type::Pressed));

}

void Cfg::initFonts()
{
	fonts.load((int)Fonts::Title, "Assets/Fonts/titleFont.ttf");

}