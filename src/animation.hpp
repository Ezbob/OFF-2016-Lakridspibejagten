#ifndef UUID_3E6A550B_7B17_4688_8A84_91CA6A6EED55
#define UUID_3E6A550B_7B17_4688_8A84_91CA6A6EED55

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>

class animation : public sf::Sprite {

	std::vector<int> frame_indices;
	int frame;
	int width;

public:
	animation(std::vector<int> frame_indices, sf::Texture& t, int w=0);
	void setupFrames(sf::Texture& t, int w=0);
	void update(double dt, double ds = 0.2);
	void setFrameOffset(int index);
	void mirror();
	bool is_mirrored;
};

#endif
