#ifndef __OPENGLSCENE__

#define  __OPENGLSCENE__

#include "cocos2d.h"

USING_NS_CC;

class OpenGLScene : Layer {
public:
	static Scene* createScene();

	virtual bool init();

	virtual void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags);

	void onDraw();

	CREATE_FUNC(OpenGLScene);

private:
	CustomCommand _command;

	GLuint vao;
	GLuint vertexVbo;
	GLuint colorVbo;
	GLuint indexVBO;
	GLuint textureId;

};

#endif //__OPENGLSCENE__