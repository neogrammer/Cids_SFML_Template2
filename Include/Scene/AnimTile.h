#pragma once

#include <Scene/Tile.h>

class AnimTile : public Tile
{
	using Tile::Tile;
public:
	~AnimTile() override final = default;
};