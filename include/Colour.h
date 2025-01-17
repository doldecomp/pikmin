#ifndef _COLOUR_H
#define _COLOUR_H

#include "types.h"

/**
 * @brief TODO
 */
struct Colour {
	Colour() { }

	Colour(const Colour& other)
	{
		r = other.r;
		g = other.g;
		b = other.b;
		a = other.a;
	}

	Colour(u8 _r, u8 _g, u8 _b, u8 _a) { set(_r, _g, _b, _a); }

	void set(u8 _r, u8 _g, u8 _b, u8 _a)
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}

	// unused/inlined:
	void write(struct Stream&);

	void lerpTo(Colour& target, f32 ratio, Colour& outColour)
	{
		outColour.r = (f32(target.r) - f32(r)) * ratio + f32(r);
		outColour.g = (f32(target.g) - f32(g)) * ratio + f32(g);
		outColour.b = (f32(target.b) - f32(b)) * ratio + f32(b);
		outColour.a = (f32(target.a) - f32(a)) * ratio + f32(a);
	}

	// DLL inlines (there are more in sysCore, but they never make it to plugPiki)
	void read(Stream&);

	u8 r, g, b, a; // _00-_04
};

/**
 * @brief TODO
 */
struct ShortColour {
	s16 r, g, b, a; // _00-_0A
};

/**
 * @brief TODO
 */
struct LShortColour {
	s16 r, g, b, a; // _00-_0A
};

#endif
