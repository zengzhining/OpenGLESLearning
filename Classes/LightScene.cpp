#include "LightScene.h"
#include "spine/spine-cocos2dx.h"
#include "spine/spine.h"

using namespace spine;

USING_NS_CC;

Scene* LightScene::createScene(){
	auto scene = Scene::create();

	auto layer = LightScene::create();

	scene->addChild(layer);

	return scene;
}

bool LightScene::init(){

	//add a Sprite in the layer
	auto size = Director::getInstance()->getWinSize();
	auto dispatcher = Director::getInstance()->getEventDispatcher();

	auto light = Sprite::create("ball.png");
	light->setScale(2.5);

	light->setPosition(size / 2);

	addChild(light);

	//add the hero 
	auto hero = SkeletonAnimation::createWithFile("spineboy.json", "spineboy.atlas", 0.3);

	auto shaderProgram = GLProgram::createWithFilenames("myVertextShader.vert", "Light.frag");

	auto mstate = GLProgramState::create(shaderProgram);

	hero->setGLProgramState(mstate);

	mstate->setUniformVec2("u_lightPosition", Vec2(light->getPositionX(), light->getPositionY()));
	mstate->setUniformVec2("u_winSize", Vec2(size.width, size.height));

	hero->setPosition(size / 2);

	addChild(hero);

	//add TouchListener
	auto touchEventListener = EventListenerTouchOneByOne::create();
	touchEventListener->onTouchBegan = [light, mstate](Touch* t, Event* e){
		light->setPosition(t->getLocation());
		mstate->setUniformVec2("u_lightPosition", Vec2(light->getPositionX(), light->getPositionY()));
		return true;
	};

	touchEventListener->onTouchMoved = [light, mstate](Touch* t, Event* e) {
		light->setPosition(t->getLocation());
		mstate->setUniformVec2("u_lightPosition", Vec2(light->getPositionX(), light->getPositionY()));
	};

	dispatcher->addEventListenerWithSceneGraphPriority(touchEventListener, this);



	return true;
}

