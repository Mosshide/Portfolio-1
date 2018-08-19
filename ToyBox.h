#pragma once
#include "Render.h"
#include <map>

class ToyBox
{
public:
	ToyBox();
	~ToyBox();

	//models
	void loadAllModels();
	VIBO loadModel(std::string path);
	void initVBO(VIBO *vi, std::vector<VertexData3D> *vertices);
	void freeVBO(VIBO *vi);

	std::map<std::string, VIBO> model;

	//textures
	void loadAllTextures();
	void newTxtTxr(GLuint *txr, std::string textureText, SDL_Color textColor, int f);
	void newUniTxtTxr(GLuint *txr, Uint16 textureText, SDL_Color textColor, int f);
	void newTxtTxr(GLuint *txr);
	GLuint loadTxr(std::string path, bool filter = false);
	void clearTexture(GLuint txr);

	std::map<std::string, GLuint> texture;

	//shaders
	bool loadShaders();
	void unloadShaders();

	Shader *shader;
	UIShader *uiShader;
};

extern ToyBox *toyBox;