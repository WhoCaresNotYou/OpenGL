#include "Vertex.h"

class Wire
{
public:
    int textureID;
	Vertex v1, v2, v3, v4;
	Wire();
	Wire(Vertex v1, Vertex v2, Vertex v3, Vertex v4);
	void setTextureID(int texID);
	void draw();
	~Wire();
};
