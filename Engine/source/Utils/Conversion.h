#pragma once
#include <SFML/Graphics.hpp>

class Conversion {
public:
	inline static sf::Color floatToColor(float _col[])
	{
		int vals = (sizeof(_col) / sizeof(_col[0]));

		int alpha = vals == 4 ? _col[3] * 255 : 255;
		
		return {
			static_cast<sf::Uint8>(_col[0] * 255),
			static_cast<sf::Uint8>(_col[1] * 255),
			static_cast<sf::Uint8>(_col[2] * 255),
			static_cast<sf::Uint8>(alpha)
		};
	}

};