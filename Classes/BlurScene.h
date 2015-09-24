#ifndef __BLURSCENE___

#define __BLURSCENE___

#include "cocos2d.h"

USING_NS_CC;

class BlurScene : Layer
{
public:
	CREATE_FUNC(BlurScene);

	bool init();

	void update(float dt);

	static Scene* createScene();
protected:
private:
	GLProgram* mShader;
	GLProgramState* GLPState;

	float num;
	bool tag;
};

#endif // !__BLURSCENE___
