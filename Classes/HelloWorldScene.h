#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
class Command;

class HelloWorld : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void update(float delta);

	void graySprite(cocos2d::Sprite* sprite);

	void turnNormal (cocos2d::Sprite* sprite);
	
	void setGLProgramBuffer(std::string str_vert, std::string str_frag, std::string keyName);


	cocos2d::Sprite* hero;

	Command* cmd;
};

#endif // __HELLOWORLD_SCENE_H__
