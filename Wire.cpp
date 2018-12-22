#include "Vertex.h"
#include "Wire.h"
#include "glfw3.h"

Wire::Wire()
{

}

Wire::Wire(Vertex v1, Vertex v2, Vertex v3, Vertex v4)
{
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
	this->v4 = v4;
}

void Wire::setTextureID(int texID)
{
	textureID = texID;
}

void Wire::draw()
{
	if (textureID != 0)
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND | GL_ALPHA_TEST);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glBindTexture(GL_TEXTURE_2D, textureID);

	}
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(v1.x, v1.y);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(v2.x, v2.y);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(v3.x, v3.y);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(v4.x, v4.y);
	glBindTexture(GL_TEXTURE_2D, 0);
	glEnd();
}

Wire::~Wire()
{

}
