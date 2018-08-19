#include "Shader.h"

Shader::Shader()
{
	mProgramID = NULL;

	mVertexPos3DLocation = -1;
	mTexCoordLocation = -1;

	mProjectionMatrixLocation = -1;
	mCameraMatrixLocation = -1;
	//mModelViewMatrixLocation = -1;
	modelTranslationLocation = -1;
	modelRotationLocation = -1;
	modelScaleLocation = -1;
	mTextureColorLocation = -1;
	mTextureUnitLocation = -1;
	mLightPositionLocation = -1;

	_cameraPos = glm::vec3(0.0f, 1.0f, 0.0f);
	_cameraFront = glm::vec3(1.0f, 0.0f, 0.f);
	_cameraUp = glm::vec3(0.0f, 1.f, 0.0f);
}

Shader::~Shader()
{
	disableVertexPointer();
	disableTexCoordPointer();

	unbind();
	disableVertexPointer();
	disableTexCoordPointer();

	glDeleteProgram(mProgramID);
}

bool Shader::loadProgram(std::string path)
{
	//Generate program
	mProgramID = glCreateProgram();

	//Load vertex shader
	GLuint vertexShader = loadShaderFromFile((path + ".glvs").c_str(), GL_VERTEX_SHADER);

	//Check for errors
	if (vertexShader == 0)
	{
		glDeleteProgram(mProgramID);
		mProgramID = 0;
		return false;
	}

	//Attach vertex shader to program
	glAttachShader(mProgramID, vertexShader);


	//Create fragment shader
	GLuint fragmentShader = loadShaderFromFile((path + ".glfs").c_str(), GL_FRAGMENT_SHADER);

	//Check for errors
	if (fragmentShader == 0)
	{
		glDeleteShader(vertexShader);
		glDeleteProgram(mProgramID);
		mProgramID = 0;
		return false;
	}

	//Attach fragment shader to program
	glAttachShader(mProgramID, fragmentShader);

	//Link program
	glLinkProgram(mProgramID);

	//Check for errors
	GLint programSuccess = GL_TRUE;
	glGetProgramiv(mProgramID, GL_LINK_STATUS, &programSuccess);
	if (programSuccess != GL_TRUE)
	{
		printf("Error linking program %d!\n", mProgramID);
		printProgramLog(mProgramID);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(mProgramID);
		mProgramID = 0;
		return false;
	}

	//Clean up excess shader references
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	mProjectionMatrixLocation = glGetUniformLocation(mProgramID, "projection");
	if (mProjectionMatrixLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "projection");
	}

	mCameraMatrixLocation = glGetUniformLocation(mProgramID, "camera");
	if (mCameraMatrixLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "camera");
	}

	/*mModelViewMatrixLocation = glGetUniformLocation(mProgramID, "model");
	if (mModelViewMatrixLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "model");
	}*/
	modelTranslationLocation = glGetUniformLocation(mProgramID, "modelTranslation");
	if (modelTranslationLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "modelTranslation");
	}
	modelRotationLocation = glGetUniformLocation(mProgramID, "modelRotation");
	if (modelRotationLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "modelRotation");
	}
	modelScaleLocation = glGetUniformLocation(mProgramID, "modelScale");
	if (modelScaleLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "modelScale");
	}

	mLightPositionLocation = glGetUniformLocation(mProgramID, "lightPos");
	if (mLightPositionLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "lightPos");
	}

	mLightMagnitudeLocation = glGetUniformLocation(mProgramID, "lightMag");
	if (mLightMagnitudeLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "lightMag");
	}

	/*mRotationLocation = glGetUniformLocation(mProgramID, "rotation");
	if (mRotationLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "rotation");
	}*/

	//Get variable locations
	mVertexPos3DLocation = glGetAttribLocation(mProgramID, "LVertexPos3D");
	if (mVertexPos3DLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "LVertexPos3D");
	}

	mNormalLocation = glGetAttribLocation(mProgramID, "normal");
	if (mNormalLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "normal");
	}

	mTexCoordLocation = glGetAttribLocation(mProgramID, "LTexCoord");
	if (mTexCoordLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "LTexCoord");
	}

	mTextureColorLocation = glGetUniformLocation(mProgramID, "LTextureColor");
	if (mTextureColorLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "LTextureColor");
	}

	mTextureUnitLocation = glGetUniformLocation(mProgramID, "LTextureUnit");
	if (mTextureUnitLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "LTextureUnit");
	}

	return true;
}

void Shader::setPointers()
{
	glVertexAttribPointer(mVertexPos3DLocation, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData3D), (GLvoid*)offsetof(VertexData3D, position));
	glVertexAttribPointer(mNormalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData3D), (GLvoid*)offsetof(VertexData3D, normals));
	glVertexAttribPointer(mTexCoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData3D), (GLvoid*)offsetof(VertexData3D, texCoord));
}

void Shader::setVertexPointer(GLsizei stride, const GLvoid* data)
{
	glVertexAttribPointer(mVertexPos3DLocation, 3, GL_FLOAT, GL_FALSE, stride, data);
}

void Shader::setNormalPointer(GLsizei stride, const GLvoid* data)
{
	glVertexAttribPointer(mNormalLocation, 3, GL_FLOAT, GL_FALSE, stride, data);
}

void Shader::setTexCoordPointer(GLsizei stride, const GLvoid* data)
{
	glVertexAttribPointer(mTexCoordLocation, 2, GL_FLOAT, GL_FALSE, stride, data);
}

void Shader::enableVertexPointer()
{
	glEnableVertexAttribArray(mVertexPos3DLocation);
}

void Shader::disableVertexPointer()
{
	glDisableVertexAttribArray(mVertexPos3DLocation);
}

void Shader::enableNormalPointer()
{
	glEnableVertexAttribArray(mNormalLocation);
}

void Shader::disableNormalPointer()
{
	glDisableVertexAttribArray(mNormalLocation);
}

void Shader::enableTexCoordPointer()
{
	glEnableVertexAttribArray(mTexCoordLocation);
}

void Shader::disableTexCoordPointer()
{
	glDisableVertexAttribArray(mTexCoordLocation);
}

void Shader::setProjection(glm::mat4 matrix)
{
	mProjectionMatrix = matrix;
}

void Shader::setCamera(glm::mat4 matrix)
{
	mCameraMatrix = matrix;
}

//void Shader::setModelView(glm::mat4 matrix)
//{
//	mModelViewMatrix = matrix;
//}

void Shader::setModelView(glm::mat4 trans, glm::mat4 rot, glm::mat4 scale)
{
	modelTranslation = trans;
	modelRotation = rot;
	modelScale = scale;
	updateModelView();
}

void Shader::leftMultProjection(glm::mat4 matrix)
{
	mProjectionMatrix = matrix * mProjectionMatrix;
}

//void Shader::leftMultModelView(glm::mat4 matrix)
//{
//	mModelViewMatrix = matrix * mModelViewMatrix;
//}

void Shader::leftMultCamera(glm::mat4 matrix)
{
	mCameraMatrix = matrix * mCameraMatrix;
}

void Shader::updateProjection()
{
	glUniformMatrix4fv(mProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(mProjectionMatrix));
}

//void Shader::updateModelView()
//{
//	glUniformMatrix4fv(mModelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(mModelViewMatrix));
//}

void Shader::updateModelView()
{
	glUniformMatrix4fv(modelTranslationLocation, 1, GL_FALSE, glm::value_ptr(modelTranslation));
	glUniformMatrix4fv(modelRotationLocation, 1, GL_FALSE, glm::value_ptr(modelRotation));
	glUniformMatrix4fv(modelScaleLocation, 1, GL_FALSE, glm::value_ptr(modelScale));
}

void Shader::setTextureColor(Color color)
{
	glUniform4fv(mTextureColorLocation, 1, (const GLfloat*)&color.get());
}

void Shader::setTextureUnit(GLuint unit)
{
	glUniform1i(mTextureUnitLocation, unit);
}

GLuint Shader::loadShaderFromFile(std::string path, GLenum shaderType)
{
	//Open file
	GLuint shaderID = 0;
	std::string shaderString;
	std::ifstream sourceFile(path.c_str());

	//Source file loaded
	if (sourceFile)
	{
		//Get shader source
		shaderString.assign((std::istreambuf_iterator< char >(sourceFile)), std::istreambuf_iterator< char >());
		//Create shader ID
		shaderID = glCreateShader(shaderType);

		//Set shader source
		const GLchar* shaderSource = shaderString.c_str();
		glShaderSource(shaderID, 1, (const GLchar**)&shaderSource, NULL);

		//Compile shader source
		glCompileShader(shaderID);

		//Check shader for errors
		GLint shaderCompiled = GL_FALSE;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderCompiled);
		if (shaderCompiled != GL_TRUE)
		{
			printf("Unable to compile shader %d!\n\nSource:\n%s\n", shaderID, shaderSource);
			printShaderLog(shaderID);
			glDeleteShader(shaderID);
			shaderID = 0;
		}
	}
	else
	{
		printf("Unable to open file %s\n", path.c_str());
	}

	return shaderID;
}

bool Shader::bind()
{
	GLenum error = GL_NO_ERROR;
	//Use shaderm
	glUseProgram(mProgramID);

	//Check for error
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error binding shader! %s\n", gluErrorString(error));
		printProgramLog(mProgramID);
		return false;
	}

	return true;
}

void Shader::unbind()
{
	//Use default program
	glUseProgram(NULL);
}

GLuint Shader::getProgramID()
{
	return mProgramID;
}

void Shader::printProgramLog(GLuint program)
{
	//Make sure name is shader
	if (glIsProgram(program))
	{
		//Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			//Print Log
			printf("%s\n", infoLog);
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf("Name %d is not a program\n", program);
	}
}

void Shader::printShaderLog(GLuint shader)
{
	//Make sure name is shader
	if (glIsShader(shader))
	{
		//Shader log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			//Print Log
			printf("%s\n", infoLog);
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf("Name %d is not a shader\n", shader);
	}
}

//from render
void Shader::setLight(glm::vec3 pos, GLfloat mag, int light)
{
	bind();
	mLightPosition[light * 3] = pos.x;
	mLightPosition[light * 3 + 1] = pos.y;
	mLightPosition[light * 3 + 2] = pos.z;
	mLightMagnitude[light] = mag;
	glUniform3fv(mLightPositionLocation, 10, mLightPosition);
	glUniform1fv(mLightMagnitudeLocation, 10, mLightMagnitude);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error setting light! %s\n", gluErrorString(error));
	}
}

void Shader::setCamera(glm::vec3 pos, glm::vec3 YPR, glm::vec3 up)
{
	bind();
	_cameraPos = pos;
	_yawPitchRoll = YPR;
	_cameraFront = glm::vec3(cos(_yawPitchRoll.x) * cos(_yawPitchRoll.y), sin(_yawPitchRoll.y), sin(_yawPitchRoll.x) * cos(_yawPitchRoll.y));
	_cameraUp = up;
	setCamera(glm::lookAt(_cameraPos, _cameraPos + _cameraFront, _cameraUp));
	updateCamera();
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error setting camera! %s\n", gluErrorString(error));
	}
}

void Shader::translateCamera(glm::vec3 p)
{
	bind();
	_cameraPos += p;
	setCamera(glm::lookAt(_cameraPos, _cameraPos + _cameraFront, _cameraUp));
	updateCamera();

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error translating camera! %s\n", gluErrorString(error));
	}
}

void Shader::rotateCamera(glm::vec3 q)
{
	bind();
	_yawPitchRoll += q;
	if (_yawPitchRoll.x < 0) while (_yawPitchRoll.x < 0) _yawPitchRoll.x += 2 * (float)M_PI;
	if (_yawPitchRoll.x > 2 * (float)M_PI) while (_yawPitchRoll.x > 2 * (float)M_PI) _yawPitchRoll.x -= 2 * (float)M_PI;

	//if pitch becomes parallel to "look at"'s up vec: bad things
	//if (_yawPitchRoll.y < -(float)M_PI / 2) _yawPitchRoll.y = -(float)M_PI / 2;
	//if (_yawPitchRoll.y > (float)M_PI / 2) _yawPitchRoll.y = (float)M_PI / 2;
	if (_yawPitchRoll.y < -(float)M_PI / 2 + .15) _yawPitchRoll.y = -(float)M_PI / 2 + .15f;
	if (_yawPitchRoll.y >(float)M_PI / 2 - .15) _yawPitchRoll.y = (float)M_PI / 2 - .15f;

	if (_yawPitchRoll.z < -(float)M_PI / 2) _yawPitchRoll.z = -(float)M_PI / 2;
	if (_yawPitchRoll.z >(float)M_PI / 2) _yawPitchRoll.z = (float)M_PI / 2;

	_cameraFront = glm::vec3(cos(_yawPitchRoll.x) * cos(_yawPitchRoll.y), sin(_yawPitchRoll.y), sin(_yawPitchRoll.x) * cos(_yawPitchRoll.y));
	setCamera(glm::lookAt(_cameraPos, _cameraPos + _cameraFront, _cameraUp));
	updateCamera();

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error rotating camera! %s\n", gluErrorString(error));
	}
}

void Shader::setCameraTranslate(glm::vec3 p)
{
	bind();
	_cameraPos = p;
	setCamera(glm::lookAt(_cameraPos, _cameraPos + _cameraFront, _cameraUp));
	updateCamera();

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error setting camera translate! %s\n", gluErrorString(error));
	}
}

void Shader::setCameraRotate(glm::vec3 q)
{
	bind();
	_yawPitchRoll = q;
	if (_yawPitchRoll.x < 0) while (_yawPitchRoll.x < 0) _yawPitchRoll.x += 2 * (float)M_PI;
	if (_yawPitchRoll.x > 2 * (float)M_PI) while (_yawPitchRoll.x > 2 * (float)M_PI) _yawPitchRoll.x -= 2 * (float)M_PI;

	if (_yawPitchRoll.y < -(float)M_PI / 2) while (_yawPitchRoll.y < -(float)M_PI / 2) _yawPitchRoll.y += (float)M_PI;
	if (_yawPitchRoll.y >(float)M_PI / 2) while (_yawPitchRoll.y >(float)M_PI / 2) _yawPitchRoll.y -= (float)M_PI;

	if (_yawPitchRoll.z < -(float)M_PI / 2) while (_yawPitchRoll.z < -(float)M_PI / 2) _yawPitchRoll.z += (float)M_PI;
	if (_yawPitchRoll.z >(float)M_PI / 2) while (_yawPitchRoll.z >(float)M_PI / 2) _yawPitchRoll.z -= (float)M_PI;

	_cameraFront = glm::vec3(cos(_yawPitchRoll.x) * cos(_yawPitchRoll.y), sin(_yawPitchRoll.y), sin(_yawPitchRoll.x) * cos(_yawPitchRoll.y));
	setCamera(glm::lookAt(_cameraPos, _cameraPos + _cameraFront, _cameraUp));
	updateCamera();

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error setting camera rotate! %s\n", gluErrorString(error));
	}
}

void Shader::updateCamera()
{
	bind();
	setCamera(glm::lookAt(_cameraPos, _cameraPos + _cameraFront, _cameraUp));
	glUniformMatrix4fv(mCameraMatrixLocation, 1, GL_FALSE, glm::value_ptr(mCameraMatrix));

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error updating camera! %s\n", gluErrorString(error));
	}
}