#pragma once
#include <vector>
#include <memory>
#include <string>

#include <Scene/Tileset.h>
class Tilemap
{
	std::vector<std::unique_ptr<Tile> > tiles;
	std::vector<std::unique_ptr<Tile> > tilesVisible;
	std::unique_ptr<Tileset> tileset;
	int pitch;
	std::unique_ptr<sf::RenderTexture> mapRender;
	int tw{ 0 };
	int th{0};
	int leftside{ 0 };
	int topside{ 0 };
	int rightside{ 0 };
	int bottomside{0};
public:
	bool haltMapX{ false };
	bool haltMapY{ false };
	sf::ContextSettings settings;
public:
	Tilemap(const std::string& filename);
	~Tilemap() = default;
	void render(sf::RenderWindow& wnd_);
	void update(float dt_);
	void renderToTexture();
	inline bool shouldHaltMapX() { return haltMapX; }
	inline bool shouldHaltMapY() { return haltMapY; }
	void renderTexture(sf::RenderWindow& wnd_);
	std::vector<std::unique_ptr<Tile>>& getTiles();
};