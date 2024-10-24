#pragma once
#include <SFML/Graphics.hpp>
#include <Types/TileTypes.h>
#include <memory>
#include <Helper/IamCOLLIDABLE.h>

class Tile : public IamCOLLIDABLE
{
protected:
	int tilesetID;
	sf::Vector2i framePos;
	const sf::Vector2i frameSize = {64,64};
	sf::Vector2f worldPos;
	sf::Texture* textureAtlas;
	TileFrameType type;

	// NOT USED
	sf::Vector2i frameSizeN={ 64,64 };
	sf::Vector2f velocityN = { 0.f,0.f };
	sf::Vector2i worldPosOffsetN = { 0,0 };
public:
	Tile(sf::Vector2f worldPos_ = { 0.f,0.f }, TileFrameType tileType_ = TileFrameType::Passable, int tilesetID_ = -1, sf::Vector2i framePos_ = { 0,0 }, sf::Vector2i frameSize_ = { 64,64 }, sf::Texture* textureAtlas_ = nullptr);
	virtual ~Tile();
	Tile(const Tile&) = delete;
	Tile& operator=(const Tile&) = delete;
	Tile(Tile&&) = default;
	Tile& operator=(Tile&&) = default;
	inline sf::FloatRect getWorldRect() { return sf::FloatRect({ worldPos,sf::Vector2f(frameSize) }); }
	inline sf::IntRect getFrameRect() const { return { {framePos},{64,64} }; }
	inline sf::Vector2i getFramePos() const { return framePos; }
	inline sf::Vector2i getSize() const { return { 64,64 }; }
	inline sf::Texture& getTexture() const  { return *textureAtlas; }
	inline int getTilesetID() const { return tilesetID; }
	inline sf::Vector2f getWorldPos() const  { return worldPos; }
	inline void setWorldPos(sf::Vector2f pos_) { worldPos = pos_; }
	inline void setFramePos(sf::Vector2i pos_) { framePos = pos_; }
	inline void setFrameSize(sf::Vector2i size_) { sf::Vector2i newframeSize = { 64,64 }; }
	inline void setTexture(sf::Texture& tex_) { textureAtlas = &tex_; }
	inline void setTilesetID(int id_) { tilesetID = id_; }
	inline TileFrameType getType() const { return type;  }
	inline void setType(TileFrameType type_) { type = type_; }
	virtual std::unique_ptr<sf::Sprite> getSpr() const;
};