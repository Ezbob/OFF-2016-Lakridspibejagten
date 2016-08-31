#ifndef UUID_8DB4C94D_C9A5_45BF_BDBA_FA8F202A4938
#define UUID_8DB4C94D_C9A5_45BF_BDBA_FA8F202A4938

#include <SFML/Graphics/Texture.hpp>

class MainMap : public sf::Texture {
	unsigned x;
	unsigned y;

public:
	MainMap(unsigned _x, unsigned _y);
};

#endif
