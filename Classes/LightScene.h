#include "cocos2d.h"

USING_NS_CC;

class LightScene : public Layer {

public:
	CREATE_FUNC(LightScene);

	bool  init();

	static Scene* createScene();
};