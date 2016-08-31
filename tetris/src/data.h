#ifndef UUID_05B0DC20_C908_4A86_BF84_E62F301C5C16
#define UUID_05B0DC20_C908_4A86_BF84_E62F301C5C16

#include <SFML/System/Vector2.hpp>

auto const tile_dim = sf::Vector2f(30, 30);

size_t const width = 12;
size_t const height = 21;

static const
size_t color[] {
	0x0aaa0a00,
	0xa0a0a000,
	0xffc0c0ff,
	0xc0ffC0ff,
	0xc0c0ffff
};

static const
int blocks[][4][4]  = {
	{	/* square */
		{0, 0, 0, 0},
		{0, 1, 1, 0},
		{0, 1, 1, 0},
		{0, 0, 0, 0}},

	{	/* bar */
		{0, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 1, 0, 0}},

	{	/* T */
		{0, 1, 0, 0},
		{0, 1, 1, 0},
		{0, 1, 0, 0},
		{0, 0, 0, 0}},

	{	/* l-left */
		{0, 0, 0, 0},
		{1, 1, 1, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 0}},

	{	/* l-right */
		{0, 0, 0, 0},
		{0, 0, 1, 0},
		{1, 1, 1, 0},
		{0, 0, 0, 0}},

	{	/* z-right */
		{0, 0, 0, 0},
		{1, 1, 0, 0},
		{0, 1, 1, 0},
		{0, 0, 0, 0}},

	{	/* z-left */
		{0, 0, 0, 0},
		{0, 0, 1, 1},
		{0, 1, 1, 0},
		{0, 0, 0, 0}}
};

#endif
