#pragma once

#include <GL/glew.h>

namespace BWengine {
//add predefined colors
	struct ColorRGBA8 {
		ColorRGBA8() : r(0), g(0), b(0), a(255) { }
		ColorRGBA8(GLubyte R, GLubyte G, GLubyte B, GLubyte A) :
			r(R), g(G), b(B), a(A) { }
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	};
}