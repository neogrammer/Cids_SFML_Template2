#include <Scene/Tile.h>
#include <Framework/Cfg.h>

Tile::Tile(sf::Vector2f worldPos_, TileFrameType tileType_, int tilesetID_, sf::Vector2i framePos_, sf::Vector2i frameSize_, sf::Texture* textureAtlas_)
	: IamCOLLIDABLE{}
	, tilesetID{tilesetID_}
	, framePos{framePos_}
	, worldPos{worldPos_}
	, textureAtlas{ textureAtlas_ }
	, type{tileType_}
{
	if (textureAtlas == nullptr)
	{
		tilesetID = -1;
		framePos = { 0,0 };
		worldPos = { 0.f,0.f };
		textureAtlas = &Cfg::textures.get((int)Cfg::Textures::InvariantTile);
	}

	loadPointers(worldPos, frameSizeN, velocityN, worldPosOffsetN);
}

Tile::~Tile()
{
}

std::unique_ptr<sf::Sprite> Tile::getSpr()  const
{
	std::unique_ptr<sf::Sprite> spr = std::make_unique<sf::Sprite>(sf::Sprite{});
	spr->setTexture(*textureAtlas);
	spr->setPosition(worldPos);
	spr->setTextureRect({ {framePos},{ frameSize} });

	return std::move(spr);

}
