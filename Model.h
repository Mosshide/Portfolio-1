#pragma once
#include "toyBox.h"
#include "toyBox.h"
#include "UserInput.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

class Model// : public Entity
{
public:
	Model();
	Model(const Model& v);
	Model& operator=(const Model& v);
	~Model();
	void setModel(std::string m);
	void setTxr(std::string t);
	void setColor(Color c);
	void setBounds(GLfloat b);
	void setTranslation(float x, float y, float z);
	void setTranslation(glm::vec3 v) { setTranslation(v.x, v.y, v.z); }
	void setRotation(float anglex, float angley, float anglez);
	void setScalar(float x, float y, float z);
	void setScalar(float s) { setScalar(s, s, s); }
	void setTransformation(glm::mat4 m);
	glm::mat4 getTranslation() { return _translation; }
	bool isPicked();
	void draw();	

protected:
	Color _color;
	Shader *_shader;
	GLuint _txr;
	VIBO _vibo;

	GLfloat _bounds;

	glm::mat4 _scalar;
	glm::mat4 _rotation;
	glm::mat4 _translation;
	glm::mat4 _transformation;
};

