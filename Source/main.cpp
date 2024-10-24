#include <SFML/Graphics.hpp>
#include <Framework/Cfg.h>
#include <Framework/Game.h>

#include <iostream>
int main()
{

	Cfg::Initialize();



	Game demo;
	demo.run();

	
}