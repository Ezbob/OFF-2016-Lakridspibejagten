#include <SFML/Graphics.hpp>
#include <algorithm>
#include <string>
#include "assets.hpp"
#include <iostream>

using namespace sf;
using namespace std;

#include "end_state.hpp"

end_state::end_state(Game * g) {
	game = g;

	back.setScale({2.f,2.f});
}

void end_state::draw_summary(float const dt) {
	//std::cerr << "state: " << state << std::endl;
	// draw summary
}

void end_state::draw(float const dt) {
	game->window.clear(sf::Color::White);
	switch (show_texture) {
		case false: draw_summary(dt); break;
		case true:  draw_texture(dt); break;
		default: break;
	}
}

bool end_state::has_won() {
	// Move icons and text to center
	game->icon_gave.setPosition({200,400});
	game->icon_gave.setScale({2.f,2.f});

	game->icon_pibe.setPosition({200,200});
	game->icon_pibe.setTexture(assets::pibe);
	game->icon_pibe.setScale({2.f,2.f});
	game->text_pibe.setPosition({300,200});

	if (game->score_pibe >= game->children && game->score_gave) {
		// Won
		std::cerr << "won: piber = " << game->score_pibe << " / " << game->children << " = children" << std::endl;
		std::cerr << "won: gave?" << game->score_gave << std::endl;
		return true;
	}
	// Lose 
	std::cerr << "lose: piber = " << game->score_pibe << " / " << game->children << " = children" << std::endl;
	std::cerr << "lose: gave?" << game->score_gave << std::endl;
	return true;
}

void end_state::draw_texture(float const dt) {
	game->window.draw(back);

	//game->window.draw(back);
	/*
	int glade_unger = (game->score_pibe % game->children);

	Text t;

	t.setString("Spillet er slut!\n");

	if (game->score_gave == 0) {
		t.setString(t.getString() + "\n\nDu kommer til festen uden en gave --det er ikke god stil");
	}

	if (game->children > game->score_pibe) {
		t.setString(t.getString() + "\n\nDu fik ikke nok piber til alle ungerne!");
	}

	if (game->score_pibe % game->children)
		t.setString(t.getString() + "\n\nNogen af ungerne er sure over at der var andre der fik flere lakridspiber end de selv gjorde.");

	t.setString(t.getString() + "\nPiber: " + to_string(game->score_pibe));
	t.setString(t.getString() + "\nGaver: " + to_string(game->score_gave));
	t.setString(t.getString() + "\nGlade unger: " + to_string(glade_unger));	
	t.setFont(assets::font_main);

	size_t width = 0;

	t.setPosition(0,0);
	for (size_t i = 0; i < t.getString().getSize(); ++i)
		width = max(width, size_t(t.findCharacterPos(i).x));
	
	auto size = game->window.getSize();
	size.x = size.x/ 2 - width / 2;
	size.y /= 2;
	auto str = t.getString();
	auto p = t.findCharacterPos(t.getString().getSize());
	t.setPosition(size.x,size.y - p.y / 2);
	game->window.draw(t);
	*/
}

void end_state::update(float const dt) {
	if (state == 0) {
		if (has_won()) {
			state = 1;
			back.setTexture(assets::story_win);
		} else {
			state = 2;
			back.setTexture(assets::story_lose);
		}
	}
}

void end_state::handleInput() {
	sf::Event event;
	while (game->window.pollEvent(event)) {
		switch(event.type ) {
			case Event::Closed:
			case Event::KeyPressed:
				if (event.key.code == Keyboard::Escape)
					game->window.close();
				if (event.key.code == Keyboard::Space) {
					show_texture = true;
					game->icon_pibe.setPosition({-100,-100});
					game->icon_gave.setPosition({-100,-100});
					game->text_pibe.setPosition({-100,-100});
				}
			default:
				break;
		}
	};
}

