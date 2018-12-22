#include "Vertex.h"
#include "iostream"
#include "Windows.h"
#include "MMSystem.h"
#include "Wire.h"
#include "glfw3.h"
#include "Switch.h"
#include "Cells.h"
#include "Bulb.h"
#include "SOIL.h"
#include "Resistance.h"
#include "Levels_Block.h"
#include "Text.h"

using namespace std;

int WIDTH = 1920, HEIGHT = 1080, level = 0, option = 1, option1 = 1, option2 = 1, Rval1, Rval2;
GLuint textureID;
bool condition = false, en, re, bu, ce, sw, re1, cl = false, check = false, menu = true, info = false, enter = false, enter1 = false, reset = false, l = false, m = false;

//MENU
Levels L1(Vertex(0.1, -0.5), Vertex(0.5, -0.5), Vertex(0.5, 0.0), Vertex(0.1, 0.0));
Levels L2(Vertex(0.1, -0.5), Vertex(0.5, -0.5), Vertex(0.5, 0.0), Vertex(0.1, 0.0));
Levels L3(Vertex(0.1, -0.5), Vertex(0.7, -0.5), Vertex(0.7, 0.0), Vertex(0.1, 0.0));
Levels Exit(Vertex(0.1, -0.5), Vertex(0.5, -0.5), Vertex(0.5, 0.0), Vertex(0.1, 0.0));
Bulb BSel1(Vertex(0.0, 0.0), Vertex(0.07, 0.0), Vertex(0.07, 0.13), Vertex(0.0, 0.13));
Bulb BSel2(Vertex(0.0, 0.0), Vertex(0.07, 0.0), Vertex(0.07, 0.13), Vertex(0.0, 0.13));
Bulb BSel3(Vertex(0.0, 0.0), Vertex(0.07, 0.0), Vertex(0.07, 0.13), Vertex(0.0, 0.13));
Bulb BSel6(Vertex(0.0, 0.0), Vertex(0.07, 0.0), Vertex(0.07, 0.13), Vertex(0.0, 0.13));

//ELECTRICAL COMPONENTS
Wire W(Vertex(-0.5, 0), Vertex(0.5, 0), Vertex(0.5, -0.5), Vertex(-0.5, -0.5));
Cells C(Vertex(0.0, 0.0), Vertex(0.05, 0.0), Vertex(0.05, 0.2), Vertex(0.0, 0.2));
Switch S(Vertex(0.0, 0.0), Vertex(0.1, 0.0), Vertex(0.1, 0.35), Vertex(0.0, 0.35));
Bulb B(Vertex(0.0, 0.0), Vertex(0.13, 0.0), Vertex(0.13, 0.35), Vertex(0.0, 0.35));
//Resistance R(Vertex(0.0, 0.0), Vertex(0.15, 0.0), Vertex(0.15, 0.3), Vertex(0.0, 0.3));
Resistance R(Vertex(0.0, 0.0), Vertex(0.17, 0.0), Vertex(0.17, 0.3), Vertex(0.0, 0.3));
Resistance R1(Vertex(0.0, 0.0), Vertex(0.17, 0.0), Vertex(0.17, 0.3), Vertex(0.0, 0.3));

//VARIABLES OF ELECTRICAL COMPONENTS
Text t14(Vertex(0.0, 0.0), Vertex(0.4, 0.0), Vertex(0.4, 0.5), Vertex(0.0, 0.5));
Text t15(Vertex(0.0, 0.0), Vertex(0.4, 0.0), Vertex(0.4, 0.5), Vertex(0.0, 0.5));

void wait(long msecs)
{
	Sleep(msecs);
}

void Positions(Vertex v1, Vertex v2, Vertex  v3, Vertex v4)
{
	B.setPosition(v1);
	R.setPosition(v2);
	C.setPosition(v3);
	R1.setPosition(v4);
}

void Positions(Vertex v1, Vertex v2, Vertex  v3)
{
	B.setPosition(v1);
	R.setPosition(v2);
	C.setPosition(v3);
}

void Level1()
{
	Vertex v1(-0.5f, 0.5f), v2(0.0, 0.5), v3(0.5, 0.5), v7(-0.8, -0.25);
	t14.setPosition(v7);
	Positions(v1, v2, v3);
}

void Level2()
{
	Vertex v1(-0.5f, 0.5f), v2(0.0, 0.5), v3(0.5, 0.5), v4(0.75, 0.5);
	Positions(v1, v2, v3, v4);
}

bool checkCollisionBulb(Wire Q1,Bulb Q2)
{
	bool condition = false;
	if (Q2.v1.x<Q1.v1.x || Q2.v2.x>Q1.v2.x)
	{
		condition = false;
	}
	else if (Q2.v1.y > Q1.v1.y + 0.0005)
	{
		condition = false;
	}
	else
	{
		condition = true;
	}
	return condition;
}

bool checkCollisionResistance(Wire Q1, Resistance Q2)
{
	bool condition = false;
	if (Q2.v1.x<Q1.v1.x || Q2.v2.x>Q1.v2.x)
	{
		condition = false;
	}
	else if (Q2.v1.y > Q1.v1.y)
	{
		condition = false;
	}
	else
	{
		condition = true;
	}
	return condition;
}

bool checkCollisionCell(Wire Q1, Cells Q2)
{
	bool condition = false;
	if (Q2.v4.x <= Q1.v4.x || Q2.v4.x >= Q1.v3.x)
	{
		condition = false;
	}
	else if (Q2.v3.y >= (Q1.v3.y + 0.005) || Q2.v3.y < Q1.v3.y)
	{
		condition = false;
	}
	else
	{
		condition = true;
	}
	return condition;
}

GLuint loadTexture(const char * filename)
{
	unsigned char* image;
	int width, height;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	//set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//set our texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load, create texture and generate mipmaps
	image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return textureID;
}

void ChangeResistance()
{
	GLuint texID1 = loadTexture("./assets/Textures/Resistance10ohm_opt.png");
	GLuint texID2 = loadTexture("./assets/Textures/Resistance20ohm_opt.png");
	GLuint texID3 = loadTexture("./assets/Textures/Resistance30ohm_opt.png");
	GLuint texID4 = loadTexture("./assets/Textures/Resistance40ohm_opt.png");
	GLuint texID5 = loadTexture("./assets/Textures/Resistance50ohm_opt.png");
	GLuint texID6 = loadTexture("./assets/Textures/Resistance60ohm_opt.png");
	GLuint texID7 = loadTexture("./assets/Textures/Resistance70ohm_opt.png");
	GLuint texID8 = loadTexture("./assets/Textures/Resistance80ohm_opt.png");
	GLuint texID9 = loadTexture("./assets/Textures/Resistance90ohm_opt.png");
	GLuint texID10 = loadTexture("./assets/Textures/Resistance100ohm_opt.png");
	if (re == true)
	{
		if (option1 == 1)
		{
			R.setTextureID(texID1);
		}
		if (option1 == 2)
		{
			R.setTextureID(texID2);
		}
		if (option1 == 3)
		{
			R.setTextureID(texID3);
		}
		if (option1 == 4)
		{
			R.setTextureID(texID4);
		}
		if (option1 == 5)
		{
			R.setTextureID(texID5);
		}
		if (option1 == 6)
		{
			R.setTextureID(texID6);
		}
		if (option1 == 7)
		{
			R.setTextureID(texID7);
		}
		if (option1 == 8)
		{
			R.setTextureID(texID8);
		}
		if (option1 == 9)
		{
			R.setTextureID(texID9);
		}
		if (option1 == 10)
		{
			R.setTextureID(texID10);
		}
	}
	if (re1 == true)
	{
		if (option2 == 1)
		{
			R1.setTextureID(texID1);
		}
		if (option2 == 2)
		{
			R1.setTextureID(texID2);
		}
		if (option2 == 3)
		{
			R1.setTextureID(texID3);
		}
		if (option2 == 4)
		{
			R1.setTextureID(texID4);
		}
		if (option2 == 5)
		{
			R1.setTextureID(texID5);
		}
		if (option2 == 6)
		{
			R1.setTextureID(texID6);
		}
		if (option2 == 7)
		{
			R1.setTextureID(texID7);
		}
		if (option2 == 8)
		{
			R1.setTextureID(texID8);
		}
		if (option2 == 9)
		{
			R1.setTextureID(texID9);
		}
		if (option2 == 10)
		{
			R1.setTextureID(texID10);
		}
	}
}

void ResistanceValRef()
{
	if (option1 == 1)
	{
		Rval1 = 10;
	}
	if (option1 == 2)
	{
		Rval1 = 20;
	}
	if (option1 == 3)
	{
		Rval1 = 30;
	}
	if (option1 == 4)
	{
		Rval1 = 40;
	}
	if (option1 == 5)
	{
		Rval1 = 50;
	}
	if (option1 == 6)
	{
		Rval1 = 60;
	}
	if (option1 == 7)
	{
		Rval1 = 70;
	}
	if (option1 == 8)
	{
		Rval1 = 80;
	}
	if (option1 == 9)
	{
		Rval1 = 90;
	}
	if (option1 == 10)
	{
		Rval1 = 100;
	}
	if (option2 == 1)
	{
		Rval2 = 10;
	}
	if (option2 == 2)
	{
		Rval2 = 20;
	}
	if (option2 == 3)
	{
		Rval2 = 30;
	}
	if (option2 == 4)
	{
		Rval2 = 40;
	}
	if (option2 == 5)
	{
		Rval2 = 50;
	}
	if (option2 == 6)
	{
		Rval2 = 60;
	}
	if (option2 == 7)
	{
		Rval2 = 70;
	}
	if (option2 == 8)
	{
		Rval2 = 80;
	}
	if (option2 == 9)
	{
		Rval2 = 90;
	}
	if (option2 == 10)
	{
		Rval2 = 100;
	}
}

void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (menu == true)
	{
		if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		{
			if (option != 1)
			{
				option--;
			}
			else
			{
				option = 3;
			}
		}
		if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		{
			if (option != 3)
			{
				option++;
			}
			else
			{
				option = 1;
			}
		}
		if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
		{
			level = option;
			menu = false;
		}
	}
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		re = true;
		bu = false;
		ce = false;
		sw = false;
		re1 = false;
	}
	if (key == GLFW_KEY_B && action == GLFW_PRESS)
	{
		bu = true;
		re = false;
		ce = false;
		sw = false;
		re1 = false;
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS)
	{
		ce = true;
		bu = false;
		re = false;
		sw = false;
		re1 = false;
	}
	if (key == GLFW_KEY_U && action == GLFW_PRESS)
	{
		re1 = true;
		ce = false;
		bu = false;
		re = false;
		sw = false;
	}
	if (ce == true)
	{
		if (key == GLFW_KEY_D && action == GLFW_PRESS)
		{
			C.r = true;
		}
		if (key == GLFW_KEY_D && action == GLFW_RELEASE)
		{
			C.r = false;
		}
		if (key == GLFW_KEY_A && action == GLFW_PRESS)
		{
			C.l = true;
		}
		if (key == GLFW_KEY_A && action == GLFW_RELEASE)
		{
			C.l = false;
		}
		if (key == GLFW_KEY_S && action == GLFW_PRESS)
		{
			C.d = true;
		}
		if (key == GLFW_KEY_S && action == GLFW_RELEASE)
		{
			C.d = false;
		}
		if (key == GLFW_KEY_W && action == GLFW_PRESS)
		{
			C.u = true;
		}
		if (key == GLFW_KEY_W && action == GLFW_RELEASE)
		{
			C.u = false;
		}
	}
	if (re == true)
	{
		if (level != 1)
		{
			if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
			{
				if (option1 != 1)
				{
					option1--;
				}
				else
				{
					option1 = 10;
				}
				ChangeResistance();
			}
			if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
			{
				if (option1 != 10)
				{
					option1++;
				}
				else
				{
					option1 = 1;
				}
				ChangeResistance();
			}
			if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
			{
				enter = true;
			}
		}
		if (enter)
		{
			if (key == GLFW_KEY_D && action == GLFW_PRESS)
			{
				R.r = true;
			}
			if (key == GLFW_KEY_D && action == GLFW_RELEASE)
			{
				R.r = false;
			}
			if (key == GLFW_KEY_A && action == GLFW_PRESS)
			{
				R.l = true;
			}
			if (key == GLFW_KEY_A && action == GLFW_RELEASE)
			{
				R.l = false;
			}
			if (key == GLFW_KEY_S && action == GLFW_PRESS)
			{
				R.d = true;
			}
			if (key == GLFW_KEY_S && action == GLFW_RELEASE)
			{
				R.d = false;
			}
			if (key == GLFW_KEY_W && action == GLFW_PRESS)
			{
				R.u = true;
			}
			if (key == GLFW_KEY_W && action == GLFW_RELEASE)
			{
				R.u = false;
			}
		}
        else
        {
			if (key == GLFW_KEY_D && action == GLFW_PRESS)
			{
				R.r = true;
			}
			if (key == GLFW_KEY_D && action == GLFW_RELEASE)
			{
				R.r = false;
			}
			if (key == GLFW_KEY_A && action == GLFW_PRESS)
			{
				R.l = true;
			}
			if (key == GLFW_KEY_A && action == GLFW_RELEASE)
			{
				R.l = false;
			}
			if (key == GLFW_KEY_S && action == GLFW_PRESS)
			{
				R.d = true;
			}
			if (key == GLFW_KEY_S && action == GLFW_RELEASE)
			{
				R.d = false;
			}
			if (key == GLFW_KEY_W && action == GLFW_PRESS)
			{
				R.u = true;
			}
			if (key == GLFW_KEY_W && action == GLFW_RELEASE)
			{
				R.u = false;
			}
        }
	}
	if (re1 == true)
	{
		if (level != 1)
		{
			if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
			{
				if (option2 != 1)
				{
					option2--;
				}
				else
				{
					option2 = 10;
				}
				ChangeResistance();
			}
			if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
			{
				if (option2 != 10)
				{
					option2++;
				}
				else
				{
					option2 = 1;
				}
				ChangeResistance();
			}
			/*if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
			{
				enter1 = true;
			}*/
		}		
		if (key == GLFW_KEY_D && action == GLFW_PRESS)
		{
			R1.r = true;
		}
		if (key == GLFW_KEY_D && action == GLFW_RELEASE)
		{
			R1.r = false;
		}
		if (key == GLFW_KEY_A && action == GLFW_PRESS)
		{
			R1.l = true;
		}
		if (key == GLFW_KEY_A && action == GLFW_RELEASE)
		{
			R1.l = false;
		}
		if (key == GLFW_KEY_S && action == GLFW_PRESS)
		{
			R1.d = true;
		}
		if (key == GLFW_KEY_S && action == GLFW_RELEASE)
		{
			R1.d = false;
		}
		if (key == GLFW_KEY_W && action == GLFW_PRESS)
		{
			R1.u = true;
		}
		if (key == GLFW_KEY_W && action == GLFW_RELEASE)
		{
			R1.u = false;
		}
	}
	if (bu == true)
	{

		if (key == GLFW_KEY_D && action == GLFW_PRESS)
		{
			B.r = true;
		}
		if (key == GLFW_KEY_D && action == GLFW_RELEASE)
		{
			B.r = false;
		}
		if (key == GLFW_KEY_A && action == GLFW_PRESS)
		{
			B.l = true;
		}
		if (key == GLFW_KEY_A && action == GLFW_RELEASE)
		{
			B.l = false;
		}
		if (key == GLFW_KEY_S && action == GLFW_PRESS)
		{
			B.d = true;
		}
		if (key == GLFW_KEY_S && action == GLFW_RELEASE)
		{
			B.d = false;
		}
		if (key == GLFW_KEY_W && action == GLFW_PRESS)
		{
			B.u = true;
		}
		if (key == GLFW_KEY_W && action == GLFW_RELEASE)
		{
			B.u = false;
		}
	}
	if (key == GLFW_KEY_BACKSPACE&&action == GLFW_PRESS)
	{
		re = false;
		bu = false;
		ce = false;
		re1 = false;
	}
	if (checkCollisionCell(W, C) && checkCollisionResistance(W, R) && checkCollisionBulb(W, B) && re == false && bu == false)
	{
		if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
		{
			Vertex temp(0.0, -0.598);
			C.setPosition(temp);
			if (level == 1)
			{
				GLuint texID4 = loadTexture("./assets/Textures/BulbGlow500.png");
				B.setTextureID(texID4);
			}
			else if (level == 2)
			{
				GLuint texID4 = loadTexture("./assets/Textures/BulbGlow240.png");
				B.setTextureID(texID4);
			}
			check = true;
			GLuint texID5 = loadTexture("./assets/Textures/On_Switch.png");
			info = true;
			S.setTextureID(texID5);
		}
	}
	/*if (checkCollisionCell(W, C) == false)
	{
		GLuint texID4 = loadTexture("./assets/Textures/BulbNotGlow500.png");
		B.setTextureID(texID4);
	}*/
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		menu = true;
	}

}

void checkResistaance()
{
	int Rval = Rval1 + Rval2;
	if (level == 2)
	{
		if (Rval != 120 && l == true && m == true)
		{
			reset = true;
		}
	}
	if (reset)
	{
		l = false;
		m = false;
	}
}

void CollisionSnap()
{
	if (checkCollisionBulb(W, B))
	{
		Vertex temp(-0.3, 0.105);
		B.setPosition(temp);
		bu = false;
		B.u = false;
		B.d = false;
		B.l = false;
		B.r = false;
	}
	if (checkCollisionResistance(W, R))
	{
		Vertex temp(0.3, 0.07);
		R.setPosition(temp);
		re = false;
		R.u = false;
		R.d = false;
		R.l = false;
		R.r = false;
		l = true;
	}
	if (level != 1)
	{
		if (checkCollisionResistance(W, R1))
		{
			Vertex temp(0.1, 0.07);
			R1.setPosition(temp);
			re1 = false;
			R1.u = false;
			R1.d = false;
			R1.l = false;
			R1.r = false;
			m = true;
		}
	}
}


void addtexture()
{
	GLuint texID12 = loadTexture("./assets/Textures/BulbNotGlow_Lselection.png");
	GLuint texID21 = loadTexture("./assets/Textures/BulbGlow_Lselection.png");
	BSel1.setTextureID(texID21);
	BSel2.setTextureID(texID12);
	BSel3.setTextureID(texID12);
	BSel6.setTextureID(texID12);
	GLuint texID2 = loadTexture("./assets/Textures/Level_1.png");
	L1.setTextureID(texID2);
	GLuint texID3 = loadTexture("./assets/Textures/Level_2.png");
	L2.setTextureID(texID3);
	GLuint texID4 = loadTexture("./assets/Textures/LightUp.png");
	L3.setTextureID(texID4);
	GLuint texID19 = loadTexture("./assets/Textures/Exit.png");
	Exit.setTextureID(texID19);
	if (level == 1)
	{
		GLuint texID9 = loadTexture("./assets/Textures/Resistance10ohm.png");
		R.setTextureID(texID9);
		GLuint texID10 = loadTexture("./assets/Textures/Cell5V.png");
		C.setTextureID(texID10);
		GLuint texID13 = loadTexture("./assets/Textures/Off_Switch.png");
		S.setTextureID(texID13);
		GLuint texID17 = loadTexture("./assets/Textures/Ohm'sLaw_!3d.png");
		t14.setTextureID(texID17);
		GLuint texID18 = loadTexture("./assets/Textures/Result_1.png");
		t15.setTextureID(texID18);
		GLuint texID7 = loadTexture("./assets/Textures/BulbNotGlow500.png");
		B.setTextureID(texID7);
		GLuint texID8 = loadTexture("./assets/Textures/Wire1.jpg");
		W.setTextureID(texID8);
	}
	else if (level == 2)
	{
		GLuint texID7 = loadTexture("./assets/Textures/BulbNotGlow240.png");
		B.setTextureID(texID7);
		GLuint texID8 = loadTexture("./assets/Textures/Wire1.jpg");
		W.setTextureID(texID8);
		GLuint texID9 = loadTexture("./assets/Textures/Resistance10ohm_opt.png");
		R.setTextureID(texID9);
		GLuint texID11 = loadTexture("./assets/Textures/Cell20V.png");
		C.setTextureID(texID11);
		GLuint texID13 = loadTexture("./assets/Textures/Off_Switch.png");
		S.setTextureID(texID13);
		GLuint texID10 = loadTexture("./assets/Textures/Resistance10ohm_opt.png");
		R1.setTextureID(texID10);
	}
}

void render()
{
	W.draw();
	C.draw();
	B.draw();
	R.draw();
	Vertex v(0.5, -0.25);
	S.setPosition(v);
	S.draw();
	if (level != 1)
	{
		R1.draw();
	}
	if (info == true && level == 1)
	{
		Vertex v(0.0, -0.25);
		t15.setPosition(v);
		t15.draw();
	}
	if (level == 1)
	{
		t14.draw();
	}
}

void main()
{
	glfwInit();
	int k = 1, v = 1;

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "CIRCUITS", NULL, NULL);
	glfwSetKeyCallback(window, keyCallBack);
	glfwMakeContextCurrent(window);
	glViewport(0, 0, WIDTH, HEIGHT);
	addtexture();
	while (v == 1)
	{
		do
		{
			glClearColor(0, 0, 0, 0);
			glClear(GL_COLOR_BUFFER_BIT);
			GLuint texID12 = loadTexture("./assets/Textures/BulbNotGlow_Lselection.png");
			GLuint texID21 = loadTexture("./assets/Textures/BulbGlow_Lselection.png");
			Vertex v1(0.0, 0.3), v2(0.0, 0.1), v3(-0.025, 0.7),/* v4(0.0, -0.3), v5(0.0, -0.5),*/ v12(0.0, -0.7); //Text Blocks
			Vertex v6(-0.18, 0.33), v7(-0.18, 0.13),/* v8(-0.18, -0.07), v9(-0.18, -0.27), v10(-0.18, -0.47),*/ v11(-0.18, -0.67); //Bulb Block
			if (option == 1)
			{
				BSel1.setTextureID(texID21);
				BSel2.setTextureID(texID12);
				BSel6.setTextureID(texID12);
				glColor3f(1, 1, 1);
				L1.setPosition(v1);
				L1.draw();
				L3.setPosition(v3);
				L3.draw();
				BSel1.setPosition(v6);
				BSel1.draw();
				glColor3f(0.2, 0.2, 0.2);
				L2.setPosition(v2);
				L2.draw();
				BSel2.setPosition(v7);
				BSel2.draw();
				Exit.setPosition(v12);
				Exit.draw();
				BSel6.setPosition(v11);
				BSel6.draw();
			}
			if (option == 2)
			{
				BSel1.setTextureID(texID12);
				BSel2.setTextureID(texID21);
				BSel6.setTextureID(texID12);
				glColor3f(0.2, 0.2, 0.2);
				L1.setPosition(v1);
				L1.draw();
				BSel1.setPosition(v6);
				BSel1.draw();
				glColor3f(1, 1, 1);
				L2.setPosition(v2);
				L2.draw();
				L3.setPosition(v3);
				L3.draw();
				BSel2.setPosition(v7);
				BSel2.draw();
				glColor3f(0.2, 0.2, 0.2);
				Exit.setPosition(v12);
				Exit.draw();
				BSel6.setPosition(v11);
				BSel6.draw();
			}
			if (option == 3)
			{
				BSel1.setTextureID(texID12);
				BSel2.setTextureID(texID12);
				
				BSel6.setTextureID(texID21);
				glColor3f(0.2, 0.2, 0.2);
				L1.setPosition(v1);
				L1.draw();
				BSel1.setPosition(v6);
				BSel1.draw();
				L2.setPosition(v2);
				L2.draw();
				BSel2.setPosition(v7);
				BSel2.draw();
				glColor3f(1, 1, 1);
				L3.setPosition(v3);
				L3.draw();
				Exit.setPosition(v12);
				Exit.draw();
				BSel6.setPosition(v11);
				BSel6.draw();
			}
			if (menu == false)
			{
				break;
			}
			level++;
			glfwSwapBuffers(window);
			glfwPollEvents();
		} while (!glfwWindowShouldClose(window));
		glColor3f(1, 1, 1);
		switch (level)
		{
		case 1:
			k = 1;
			Level1();
			glfwSetKeyCallback(window, keyCallBack);
			addtexture();
			PlaySound(TEXT("./assets/Music/AAMO.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
			do
			{
				glClearColor(0, 0, 0, 0);
				glClear(GL_COLOR_BUFFER_BIT);
				render();
				CollisionSnap();
				B.update();
				R.update();
				C.update();
				if (check)
				{
					if (k == 2)					
					{
						wait(5000);
						break;
					}
					else if (k == 1)
					{
						k++;
					}
				}
				if (menu == true)
				{
					break;
				}
				glfwSwapBuffers(window);
				glfwPollEvents();
			} while (!glfwWindowShouldClose(window));
			level++;
			check = false;
			break;
		case 2:
			k = 1;
			info = false;
			Level2();
			glfwSetKeyCallback(window, keyCallBack);
			addtexture();
			PlaySound(TEXT("./assets/Music/AAMO.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
			do
			{
				glClearColor(0, 0, 0, 0);
				glClear(GL_COLOR_BUFFER_BIT);
				ResistanceValRef();
				checkResistaance();
				render();
				CollisionSnap();
				B.update();
				R.update();
				R1.update();
				C.update();
				if (check)
				{
					if (k == 2)
					{
						wait(1000);
						break;
					}
					else if (k == 1)
					{
						k++;
					}
				}
				if (menu == true)
				{
					break;
				}
				if (reset == true)
				{
					break;
				}
				glfwSwapBuffers(window);
				glfwPollEvents();
			} while (!glfwWindowShouldClose(window));
			if (reset == false)
			{
				level++;
			}
			else
			{
				menu = true;
				reset = false;
				break;
			}
			check = false;
			break;
		default:
			exit(0);
			break;
		}
	}
	glfwTerminate();
}
