#ifndef UUID_4989FA0E_529A_40B9_BE4D_571877D2E875
#define UUID_4989FA0E_529A_40B9_BE4D_571877D2E875

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class sfLine : public sf::Drawable
{
private:
	sf::Vertex vertices[4];
	sf::Color color;
	float thickness;

public:
	sfLine(const sf::Vector2f& point1, const sf::Vector2f& point2);
	void setColor(sf::Color c);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif
