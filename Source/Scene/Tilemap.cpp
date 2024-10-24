#include <Scene/Tilemap.h>
#include <fstream>
#include <assert.h>
#include <iostream>
Tilemap::Tilemap(const std::string& filename)
	: tileset{}
	, tiles{}
	, mapRender{}
	, settings{}
	, tilesVisible{}
{

	settings.antialiasingLevel = 8;
	std::ifstream file;
	file.open(filename);

	if (file.is_open())
	{
		std::string fileType;
		file >> fileType;
		assert(fileType == "Tilemap" && "You are trying to load a different kind of file into a tilemap");

		std::string tilesetFilename;
		file >> tilesetFilename;
		file.close();
		tileset = std::make_unique<Tileset>(tilesetFilename);
		std::ifstream fileAgain;
		fileAgain.open(filename);
		if (fileAgain.is_open())
		{
			std::string ignore1, ignore2;
			fileAgain >> ignore1 >> ignore2;


			tiles.clear();
			tilesVisible.clear();
			int numTiles, cols, rows, width, height;
			fileAgain >> cols >> rows >> width >> height;
			numTiles = cols * rows;
			tiles.reserve(numTiles);
			tilesVisible.reserve(numTiles);

			pitch = cols;
			for (int y = 0; y < rows; ++y)
			{
				for (int x = 0; x < cols; ++x)
				{
					int tileNum;
					fileAgain >> tileNum;
				
					int tilesetCol = tileNum % tileset->getPitch();
					int tilesetRow = tileNum / tileset->getPitch();

					tiles.emplace_back(std::make_unique<Tile>());
					tiles.back()->setFramePos({ tilesetCol * 64, tilesetRow * 64 });
					tiles.back()->setTilesetID(1);
					tiles.back()->setWorldPos({x*64.f,y*64.f});
					tiles.back()->setTexture(*tileset->getTexture());
					tiles.back()->setType(tileset->tileset[(size_t)((tilesetRow*tileset->getPitch()) + tilesetCol)]->getType());

					if (tileNum != 31)
					{
						tilesVisible.emplace_back(std::make_unique<Tile>());
						tilesVisible.back()->setFramePos({ tilesetCol * 64, tilesetRow * 64 });
						tilesVisible.back()->setTilesetID(1);
						tilesVisible.back()->setWorldPos({ x * 64.f,y * 64.f });
						tilesVisible.back()->setTexture(*tileset->getTexture());
						tilesVisible.back()->setType(tileset->tileset[(size_t)((tilesetRow * tileset->getPitch()) + tilesetCol)]->getType());
					}
				}
			}
			tilesVisible.shrink_to_fit();
			fileAgain.close();
		}
		else
		{
			std::cout << "Could not reopen tilemap file" << std::endl;
		}

	}

	assert(tiles.size() > 0 && "Tiles not created!");
	
}

void Tilemap::render(sf::RenderWindow& wnd_)
{
	haltMapX = false;
	haltMapY = false;

	leftside = int(wnd_.getView().getCenter().x) - int(wnd_.getSize().x / 2.f);
	topside = int(wnd_.getView().getCenter().y) - int(wnd_.getSize().y / 2.f);
	rightside = int(wnd_.getView().getCenter().x) + int(wnd_.getSize().x / 2.f);
	bottomside = int(wnd_.getView().getCenter().y) + int(wnd_.getSize().y / 2.f);

	if (leftside < 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			haltMapX = true;
			auto v = wnd_.getView();
			v.setCenter({ float(wnd_.getSize().x / 2),v.getCenter().y});
			wnd_.setView(v);
		}
		leftside = 0;
		rightside = wnd_.getSize().x;
	}
	else if (rightside > (int)mapRender->getTexture().getSize().x)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			haltMapX = true;
			auto v = wnd_.getView();
			v.setCenter({ float(mapRender->getTexture().getSize().x - (wnd_.getSize().x / 2)) ,v.getCenter().y });
			wnd_.setView(v);
		}
		rightside = mapRender->getTexture().getSize().x;
		leftside = rightside - wnd_.getSize().x;
	}

	if (topside < 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			haltMapY = true;
			auto v = wnd_.getView();
			v.setCenter({ v.getCenter().x , float(wnd_.getSize().y / 2)});
			wnd_.setView(v);
		}
		topside = 0;
		bottomside = wnd_.getSize().y;
	}
	else if (bottomside > (int)mapRender->getTexture().getSize().y)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			haltMapY = true;
			auto v = wnd_.getView();
			v.setCenter({ v.getCenter().x , float(mapRender->getTexture().getSize().y - (wnd_.getSize().y / 2))});
			wnd_.setView(v);
		}
		bottomside = mapRender->getTexture().getSize().y;
		topside = bottomside - wnd_.getSize().y;
	}

	sf::Sprite spr;
	spr.setTexture(mapRender->getTexture());
	spr.setTextureRect({ {leftside,topside}, {(int)wnd_.getSize().x, (int)wnd_.getSize().y }});
	spr.setOrigin({ wnd_.getSize().x / 2.f, wnd_.getSize().y / 2.f });
	spr.setPosition(wnd_.getView().getCenter());
	wnd_.draw(spr);

}

void Tilemap::update(float dt_)
{
}



void Tilemap::renderToTexture()
{
	mapRender->setActive(true);
	mapRender->clear(sf::Color::Transparent);
	for (auto& t : tilesVisible)
	{
		mapRender->draw(*t->getSpr());
	}
	mapRender->display();

}

void Tilemap::renderTexture(sf::RenderWindow& wnd_)
{
	if (mapRender) mapRender.release();
	mapRender = nullptr;
	
	

	mapRender = std::make_unique<sf::RenderTexture>();
	unsigned int width = (unsigned int)pitch * (unsigned int)this->tiles.at(0)->getFrameRect().getSize().x;
	unsigned int height = (unsigned int)(((float)tiles.size() / (float)pitch) * (float)this->tiles.at(0)->getFrameRect().getSize().y);

	if (!mapRender->create(width,height))
	{
		throw std::exception("Shit!");
	}
	renderToTexture();
	wnd_.setActive(true);

}

std::vector<std::unique_ptr<Tile>>& Tilemap::getTiles()
{
	return tilesVisible;
}
