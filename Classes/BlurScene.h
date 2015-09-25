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

	//方盒滤镜
	void runBoxFilter();

	//边沿滤镜
	void runEdgeFilter();

	void runOwnAct();

	static Scene* createScene();

public:
	Sprite* hero;
protected:
private:
	GLProgram* mShader;
	GLProgramState* GLPState;

	float num;
	bool tag;
};

#endif // !__BLURSCENE___
