#pragma once

#define TILE_SIZE 32

// textures helper
#define NULLTEX 0
#define NULLTEX_WHITE 1
#define STARS_BKG 2
#define SIGN 3
#define SIGN_TRIANGLE 4

namespace game {
	const float m_PI = 3.1415926535897932384626433832795f;
	const float m_2PI = 6.283185307179586476925286766559f;
	const float g = 9.81f;
	const float airViscosity = 1.8e-5;

	// util functions
	inline float min4(float a, float b, float c, float d) {
		return fminf(a, fminf(b, fminf(c, d)));
	}
}