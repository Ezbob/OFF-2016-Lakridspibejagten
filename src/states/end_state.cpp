#include <SFML/Graphics.hpp>
#include <string>
#include "assets.hpp"

using namespace sf;
using namespace std;

#include "end_state.hpp"

end_state::end_state(Game * g) {
	game = g;
}

void end_state::draw(float const dt) {
	int glade_unger = (game->score_pibe % game->children);

	Text t;

	t.setString("Spillet er slut!\n");
	t.setString(t.getString() + "Piber: " + to_string(game->score_pibe) + "\n");
	t.setString(t.getString() + "Gaver: " + to_string(game->score_gave)+ "\n");
	t.setString(t.getString() + "Glade unger: " + to_string(glade_unger));	
	t.setFont(assets::font_main);

	auto size = game->window.getSize();
	size.x /= 2;
	size.y /= 2;
	auto str = t.getString();
	auto p = t.findCharacterPos(t.getString().getSize());
	t.setPosition(size.x - p.x / 2,size.y - p.y / 2);
	game->window.draw(t);
}

void end_state::update(float const dt) {
	
}

void end_state::handleInput() {
	sf::Event event;
	while (game->window.pollEvent(event)) {
		switch(event.type ) {
			case Event::Closed:
			case Event::KeyPressed:
				game->window.close();
			default:
				break;
		}
	};
}

