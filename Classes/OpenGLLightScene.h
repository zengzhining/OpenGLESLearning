#include "cocos2d.h"

USING_NS_CC;

class OpenGLLightScene : public Layer {

public:
	CREATE_FUNC(OpenGLLightScene);

	virtual bool init();

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
	virtual void onTouchCancelled(Touch *touch, Event *unused_event);


	virtual void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags);

	void onDraw();

	static Scene* createScene();

private:
	CustomCommand _customCommand;

	GLuint vao;
	GLuint vertexVBO;
	GLuint colorVBO;
	GLuint textureId;
	Vec2 _lightPosition;

};