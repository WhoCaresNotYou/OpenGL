#include "Vertex.h"
#include "glfw3.h"
#include "Cells.h"

Cells::Cells()
{

}

Cells::Cells(Vertex v1, Vertex v2, Vertex v3, Vertex v4)
{
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
	this->v4 = v4;
	width = v2.x - v1.x;
	height = v3.y - v2.y;
	halfwidth = width / 2;
	halfheight = height / 2;
}

void Cells::setTextureID(int texID)
{
	textureID = texID;
}

void Cells::setPosition(Vertex pos)
{
	position = pos;

	v1.x = position.x - halfwidth;
	v1.y = position.y - halfheight;

	v2.x = v1.x;
	v2.y = position.y + halfheight;

	v3.x = position.x + halfwidth;
	v3.y = v2.y;

	v4.x = v3.x;
	v4.y = v1.y;
}


void Cells::draw()
{
	if (textureID != 0)
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND | GL_ALPHA_TEST);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glBindTexture(GL_TEXTURE_2D, textureID);

	}
	//glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_QUADS);
	//glTexCoord2f(1.0, 1.0);
	//glVertex2f(0.05, 0.1);
	//glTexCoord2f(1.0, 0.0);
	//glVertex2f(0.05, -0.1);
	//glTexCoord2f(0.0, 0.0);
	//glVertex2f(-0.05, -0.1);
	//glTexCoord2f(0.0, 1.0);
	//glVertex2f(-0.05, 0.1);
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

void Cells::update()
{
	if (r)
	{
		v1.x += 0.0004;
		v2.x += 0.0004;
		v3.x += 0.0004;
		v4.x += 0.0004;
	}
	if (l)
	{

		v1.x -= 0.0004;
		v2.x -= 0.0004;
		v3.x -= 0.0004;
		v4.x -= 0.0004;
	}
	if (d)
	{
		v1.y -= 0.0004;
		v2.y -= 0.0004;
		v3.y -= 0.0004;
		v4.y -= 0.0004;
	}
	if (u)
	{
		v1.y += 0.0001;
		v2.y += 0.0001;
		v3.y += 0.0001;
		v4.y += 0.0001;
	}
}

Cells::~Cells()
{

}
