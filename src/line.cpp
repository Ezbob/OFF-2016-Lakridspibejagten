
#include <cmath>
#include <SFML/Graphics/PrimitiveType.hpp>

#include "line.hpp"

using namespace sf;

sfLine::sfLine(const Vector2f& point1, const Vector2f& point2):
	color(Color::Yellow), thickness(5.f)
{
	Vector2f direction = point2 - point1;
	Vector2f unitDirection =  direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
	Vector2f unitPerpendicular(-unitDirection.y,unitDirection.x);

	Vector2f offset = (thickness/2.f)*unitPerpendicular;

	vertices[0].position = point1 + offset;
	vertices[1].position = point2 + offset;
	vertices[2].position = point2 - offset;
	vertices[3].position = point1 - offset;

	for (int i=0; i<4; ++i)
		vertices[i].color = color;
}

void sfLine::setColor(Color c) {
	color = c;
	for (int i=0; i<4; ++i)
		vertices[i].color = color;
}

void sfLine::draw(RenderTarget &target, RenderStates states) const
{
	// fjern advarsel om at states ikke bliver brugt
	while (false) states = states;

	target.draw(vertices, 4, Quads);
}

