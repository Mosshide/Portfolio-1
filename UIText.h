#pragma once
#include "Entity.h"
#include "toyBox.h"

class UIText : public Entity
{
public:
	UIText();
	UIText(const UIText& v);
	UIText& operator=(const UIText& v);
	~UIText();
	void update() {};
	void draw();
	void drawClipped(fRectangle clip);
	void setPosition(GLfloat x, GLfloat y);
	void setPositionCenter(GLfloat x, GLfloat y);
	void offsetPosition(GLfloat x, GLfloat y);
	void setSize(GLfloat w, GLfloat h);
	void setRect(fRectangle r);
	void setClip(fRectangle t);
	void setRGBA(Color c);
	void setRotation(float r);
	void setWireframe(bool b);
	void initVBO();
	void freeVBO();
	void refreshText();
	void setText(std::string t);
	void setText(int n) { setText(std::to_string(n)); }
	void setFont(int f);

	VertexData3D vertices[4];
	std::string text;

protected:
	UIShader *_shader;
	Color _color;
	int _font;
	float _rotation;
	fRectangle _clip;
	GLuint _vbo;
	GLuint _ibo;
	int _numVertices;

	GLuint _txr;
	bool _wf;
};