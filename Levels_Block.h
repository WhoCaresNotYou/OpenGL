#include "Vertex.h"

class Levels
{
public:
	int textureID;
	Vertex v1, v2, v3, v4, position;
	float width, height, halfwidth, halfheight;
	Levels();
	Levels(Vertex v1, Vertex v2, Vertex v3, Vertex v4);
	void setTextureID(int texID);
	void setPosition(Vertex pos);
	void draw();
	void update();
	~Levels();
};