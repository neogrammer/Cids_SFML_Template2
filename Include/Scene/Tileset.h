#pragma once
#include <vector>
#include <memory>
#include <string>

#include <Scene/Tile.h>
class Tileset
{
public:
	std::vector<std::unique_ptr<Tile> > tileset;
	sf::Texture tex;
	int pitch;
public:
	Tileset(const std::string& filename);
	~Tileset() = default;
	Tile getTile( int col, int row );
	std::unique_ptr<Tile> copyTile(int tileNum);
	std::unique_ptr<Tile> copyTile(int col, int row);
	inline int getPitch() { return pitch; }
	inline sf::Texture* getTexture() { return &tex; }
};