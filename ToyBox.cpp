#include "toyBox.h"

ToyBox::ToyBox()
{
	loadAllModels();
	loadAllTextures();
	loadShaders();
}

ToyBox::~ToyBox()
{
	unloadShaders();
}

//models
void ToyBox::loadAllModels()
{
	model["arrow"] = loadModel("models/arrow.obj");
	model["ghost"] = loadModel("models/scary ghost.obj");
	model["dryad"] = loadModel("models/dryad.obj");
	model["wall"] = loadModel("models/wall.obj");
	model["square"] = loadModel("models/square.obj");
	model["rabbit"] = loadModel("models/rabbit.obj");
	model["cube"] = loadModel("models/cube.obj");
	model["sprite"] = loadModel("models/sprite.obj");
	model["level backdrop"] = loadModel("models/level backdrop.obj");
	model["tree"] = loadModel("models/tree.obj");
	model["fern"] = loadModel("models/fern.obj");
}

VIBO ToyBox::loadModel(std::string path)
{
	VIBO vibo = { 0, 0, 0 };
	std::vector<VertexData3D> vertices;
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector<V3rtex> temp_vertices;
	std::vector<TexCoord> temp_uvs;
	std::vector<V3rtex> temp_normals;

	FILE * file;
	errno_t err;
	if ((err = fopen_s(&file, path.c_str(), "r")) != 0) {
		char buf[128];
		strerror_s(buf, sizeof buf, err);
		fprintf_s(stderr, "cannot open file '%s': %s\n",
			path.c_str(), buf);
	}
	else
	{
		while (true) {
			char lineHeader[128];
			// read the first word of the line
			int res = fscanf_s(file, "%s", lineHeader, (unsigned int)_countof(lineHeader));
			if (res == EOF) break; // EOF = End Of File. Quit the loop.

			if (strcmp(lineHeader, "v") == 0) {
				V3rtex vertex;
				fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				temp_vertices.push_back(vertex);
			}
			else if (strcmp(lineHeader, "vt") == 0) {
				TexCoord uv;
				fscanf_s(file, "%f %f\n", &uv.s, &uv.t);
				temp_uvs.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0) {
				V3rtex normal;
				fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				temp_normals.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0) {
				VertexData3D v;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				if (matches != 9) {
					printf("File can't be read by our simple parser : ( Try exporting with other options )\n");
					break;
				}

				for (int i = 0; i < 3; i++)
				{
					v.position = temp_vertices[vertexIndex[i] - 1];
					v.texCoord = temp_uvs[uvIndex[i] - 1];
					v.texCoord.t = 1.f - v.texCoord.t;
					v.normals = temp_normals[normalIndex[i] - 1];
					vertices.push_back(v);
				}
			}
		}
	}

	initVBO(&vibo, &vertices);

	return vibo;
}

void ToyBox::initVBO(VIBO *vi, std::vector<VertexData3D> *vertices)
{
	//If texture is loaded and VBO does not already exist
	if (vi->vbo == 0)
	{
		vi->size = (GLuint)vertices->size();

		//Vertex data
		//VertexData3D *vData = new VertexData3D[_numVertices];
		GLuint *iData = new GLuint[vi->size];

		//Set rendering indices
		for (int i = 0; i < (int)vi->size; i++) iData[i] = i;

		//Create VBO
		glGenBuffers(1, &vi->vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vi->vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(VertexData3D), vertices->data(), GL_DYNAMIC_DRAW);

		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			printf("Error creating vbo! %s\n", gluErrorString(error));
		}

		//Create IBO
		glGenBuffers(1, &vi->ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vi->ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vi->size * sizeof(GLuint), iData, GL_DYNAMIC_DRAW);

		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			printf("Error creating ibo! %s\n", gluErrorString(error));
		}

		//Unbind buffers
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		//delete[] vData;
		delete[] iData;
	}
}

void ToyBox::freeVBO(VIBO *vi)
{
	//Free VBO and IBO
	if (vi->vbo != 0)
	{
		glDeleteBuffers(1, &vi->vbo);
		glDeleteBuffers(1, &vi->ibo);
		vi->vbo = 0;
		vi->ibo = 0;
	}
}


//textures
void ToyBox::loadAllTextures()
{
	texture["title"] = loadTxr("img/title.png");
	texture["blank"] = loadTxr("img/blank.png");
	texture["altar"] = loadTxr("img/altar.png");
	texture["altar light"] = loadTxr("img/altar light.png");
	texture["tab"] = loadTxr("img/tab.png");
	texture["minimize"] = loadTxr("img/minimize.png", true);
	texture["maximize"] = loadTxr("img/maximize.png", true);
	texture["close"] = loadTxr("img/close.png", true);
	texture["dryad"] = loadTxr("img/textures/dryad.png", true);
	texture["level backdrop"] = loadTxr("img/textures/level backdrop.png", true);
	texture["tree"] = loadTxr("img/textures/tree.png", true);
	texture["fern"] = loadTxr("img/textures/fern.png", true);
	texture["brown button"] = loadTxr("img/brown button.png", true);
}

void ToyBox::newTxtTxr(GLuint *txr, std::string text, SDL_Color textColor, int f)
{
	if ((int)text.size() > 0)
	{
		//Load image at specified path
		SDL_Surface* loadedSurface = TTF_RenderText_Blended(render->getFont(f), text.c_str(), textColor);
		if (loadedSurface == nullptr)
		{
			printf("Unable to create text %s! SDL_image Error: %s\n", text.c_str(), IMG_GetError());
		}
		else
		{
			/*newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
			if( newTexture == nullptr )
			{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
			}
			else SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);*/

			glGenTextures(1, txr);
			glBindTexture(GL_TEXTURE_2D, *txr);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, loadedSurface->w, loadedSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, loadedSurface->pixels);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			//Unbind texture
			glBindTexture(GL_TEXTURE_2D, NULL);

			//Get rid of old loaded surface
			SDL_FreeSurface(loadedSurface);
		}
	}
}

void ToyBox::newUniTxtTxr(GLuint *txr, Uint16 textureText, SDL_Color textColor, int f)
{
	//Load image at specified path
	SDL_Surface* loadedSurface = TTF_RenderGlyph_Blended(render->getFont(f), textureText, textColor);
	if (loadedSurface == nullptr)
	{
		printf("Unable to create text %s! SDL_image Error: %s\n", "UNICODE", IMG_GetError());
	}
	else
	{
		/*newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if( newTexture == nullptr )
		{
		printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);*/

		glGenTextures(1, txr);
		glBindTexture(GL_TEXTURE_2D, *txr);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, loadedSurface->w, loadedSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, loadedSurface->pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//Unbind texture
		glBindTexture(GL_TEXTURE_2D, NULL);

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
}

void ToyBox::newTxtTxr(GLuint *txr)
{
	glGenTextures(1, txr);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, *txr);

	// Give an empty image to OpenGL ( the last "0" )
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024, 768, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	// Poor filtering. Needed !
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint ToyBox::loadTxr(std::string path, bool filter)
{
	GLuint GLtxr = 0;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		glGenTextures(1, &GLtxr);
		glBindTexture(GL_TEXTURE_2D, GLtxr);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, loadedSurface->w, loadedSurface->h,
			0, GL_RGBA, GL_UNSIGNED_BYTE, loadedSurface->pixels);
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			printf("Error glTexImage2D! %s\n", gluErrorString(error));
		}

		if (filter)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}
		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			printf("Error glTexParameteri %s\n", gluErrorString(error));
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			printf("Error glTexParameteri 2! %s\n", gluErrorString(error));
		}

		glBindTexture(GL_TEXTURE_2D, 0);

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return GLtxr;
}

void ToyBox::clearTexture(GLuint txr)
{
	/*SDL_SetRenderTarget(renderer, txr);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_SetTextureBlendMode(txr, SDL_BLENDMODE_NONE);
	SDL_RenderClear(renderer);
	SDL_SetTextureBlendMode(txr, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(renderer, nullptr);*/
}

//shaders
bool ToyBox::loadShaders()
{
	shader = new Shader;
	uiShader = new UIShader;

	//Load basic shader program
	if (!shader->loadProgram("shaders/shader"))
	{
		printf("Unable to load basic shader!\n");
		return false;
	}
	shader->bind();
	//shader->setProjection(glm::ortho<GLfloat>(0.0, (GLfloat)SCREEN_WIDTH, (GLfloat)SCREEN_HEIGHT, 0.0, 1.0, -1.0));
	//shader->setProjection(glm::ortho<GLfloat>(0.0, 1.f, 1.f, 0.0, 1.0, -1.0));
	//shader->setProjection(glm::ortho<GLfloat>(0.0, (GLfloat)SCREEN_WIDTH, (GLfloat)SCREEN_HEIGHT, 0.0, 1.0, -1.0));
	shader->setProjection(glm::perspective(glm::radians(80.0f), /*1.f*/(float)render->getScreenWidth() / render->getScreenHeight(), 0.1f, 1000.0f));
	shader->updateProjection();
	shader->setCamera(glm::lookAt(shader->_cameraPos, shader->_cameraPos + shader->_cameraFront, shader->_cameraUp));
	shader->updateCamera();
	shader->setModelView(glm::mat4(), glm::mat4(), glm::mat4());
	shader->updateModelView();
	shader->setTextureUnit(0);
	shader->enableVertexPointer();
	shader->enableNormalPointer();
	shader->enableTexCoordPointer();
	shader->unbind();


	//Load basic ui shader program
	if (!uiShader->loadProgram("shaders/shaderUI"))
	{
		printf("Unable to load UI shader!\n");
		return false;
	}
	uiShader->bind();
	uiShader->setProjection(glm::ortho<GLfloat>(0.0, (GLfloat)render->getScreenWidth(), (GLfloat)render->getScreenHeight(), 0.0, 1.0, -1.0));
	uiShader->updateProjection();
	uiShader->setTextureUnit(0);
	uiShader->enableVertexPointer();
	uiShader->enableTexCoordPointer();

	return true;
}

void ToyBox::unloadShaders()
{
	delete shader;
	delete uiShader;
}


ToyBox *toyBox;