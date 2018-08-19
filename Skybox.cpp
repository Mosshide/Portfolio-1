#include "Skybox.h"

Skybox::Skybox()
{
	//std::vector<std::string> txr_faces;
	//txr_faces.push_back("img/skybox/right.png");
	//txr_faces.push_back("img/skybox/left.png");
	//txr_faces.push_back("img/skybox/top.png");
	//txr_faces.push_back("img/skybox/bottom.png");
	//txr_faces.push_back("img/skybox/back.png");
	//txr_faces.push_back("img/skybox/front.png");

	//glGenTextures(1, &_txr);
	//glBindTexture(GL_TEXTURE_CUBE_MAP, _txr);

	//int width, height, nrChannels;
	//unsigned char *data;
	//for (GLuint i = 0; i < txr_faces.size(); i++)
	//{
	//	SDL_Surface* loadedSurface = IMG_Load(txr_faces[i].c_str());
	//	if (loadedSurface == nullptr)
	//	{
	//		printf("Unable to load image %s! SDL_image Error: %s\n", txr_faces[i].c_str(), IMG_GetError());
	//	}
	//	else
	//	{
	//		glTexImage2D(
	//			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
	//			0, GL_RGB, width, height, 0,
	//			GL_RGB, GL_UNSIGNED_BYTE, data
	//		);
	//		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	//		glBindTexture(GL_TEXTURE_2D, 0);

	//		SDL_FreeSurface(loadedSurface);
	//	}
	//}
}

Skybox::~Skybox()
{
}