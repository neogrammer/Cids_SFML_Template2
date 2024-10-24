#include <Scene/Tileset.h>
#include <fstream>
#include <assert.h>
#include <SFML/Graphics.hpp>
#include <Types/TileTypes.h>


Tileset::Tileset(const std::string& filename)
	: tileset{}
	, tex{}
{
	std::ifstream file;

	file.open(filename);

	if (file.is_open())
	{
		std::string fileType;
		file >> fileType;
		assert(fileType == "Tileset" && "You are trying to read a different kind of file into a tileset.");
		int tilesetID;
		file >> tilesetID;
		int numTiles, cols, rows, width, height;
		file >> numTiles >> cols >> rows >> width >> height;
		pitch = cols;
		std::string texName;
		file >> texName;
		tex.loadFromFile(texName);

		tileset.clear();
		tileset.reserve(numTiles);
		for (int y = 0; y < rows; ++y)
		{
			for (int x = 0; x < cols; ++x)
			{
				if (y * pitch + x >= numTiles)
				{
					break;
				}
				TileFrameType type;
				int typeTmp;
				file >> typeTmp;
				type = static_cast<TileFrameType>(typeTmp);

				if (type == TileFrameType::Empty)
				{
					tileset.emplace_back(std::make_unique<Tile>());
				}
				else
				{

					sf::Vector2f worldPos = { 0.f,0.f };
					sf::Vector2i frameSize = { width, height };
					sf::Vector2i framePos = { x * width, y * height };


					tileset.emplace_back(std::make_unique<Tile>(sf::Vector2f{ 0.f,0.f }, type, tilesetID, framePos, frameSize, &tex));
				}
			}
		}

		file.close();

	}
	
}

Tile Tileset::getTile( int col, int row )
{
	assert(row * pitch + col < tileset.size() && "Whoa, tile out of range of the tileset");
	Tile aTile{};
	Tile& tile = *tileset.at(row * pitch + col);
	aTile.setFramePos(tile.getFramePos());
	aTile.setTilesetID(tile.getTilesetID());
	aTile.setFrameSize(tile.getSize());
	aTile.setTexture(tile.getTexture());
	aTile.setType(tile.getType());
	aTile.setWorldPos(tile.getWorldPos());
	return std::move(aTile);
}

std::unique_ptr<Tile> Tileset::copyTile(int tileNum)
{
	assert(tileNum < tileset.size() && "Whoa, tile out of range of the tileset");
	
	int col = tileNum % pitch;
	int row = tileNum / pitch;

	return std::make_unique<Tile>(getTile(col, row));
}


std::unique_ptr<Tile> Tileset::copyTile(int col, int row)
{
	assert(row * pitch + col < tileset.size() && "Whoa, tile out of range of the tileset");

	//std::unique_ptr<Tile> aTile = std::make_unique<Tile>(tile.getWorldPos(), tile.getType(), tile.getTilesetID(), tile.getFrameRect().getSize(), tile.getFrameRect().getPosition(), &tile.getTexture());
	
	return std::make_unique<Tile>(getTile(col, row));
}

