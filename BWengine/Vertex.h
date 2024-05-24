#pragma once

#include <GL/glew.h>

#include "colors.h"

namespace BWengine {

	struct Position {
		float x;
		float y;
	};

	struct UV {
		float u;
		float v;
	};

	// try and make a 4 divisble size for memory allignment reasons
	struct Vertex {
		Position position;
		void setPosition(float x, float y) {
			position.x = x;
			position.y = y;
		}

		ColorRGBA8 color;
		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}

		UV uv;
		void setUV(float u, float v) {
			uv.u = u;
			uv.v = v;
		}
	};

}