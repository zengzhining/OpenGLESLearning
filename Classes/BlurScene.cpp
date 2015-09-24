#include "BlurScene.h"

USING_NS_CC;

Scene* BlurScene::createScene()
{
	auto scene = Scene::create();

	auto layer = BlurScene::create();

	scene->addChild(layer);

	return scene;
}

bool BlurScene::init()
{
	auto size = Director::getInstance()->getWinSize();
	auto hero = Sprite::create("HelloWorld.png");
	hero->setPosition(size / 2);
	addChild(hero);

	mShader = GLProgram::createWithFilenames("myShader/MVP_Stand.vert", "myShader/BoxFilter.frag");

	GLPState = hero->getGLProgramState();

	GLPState->setGLProgram(mShader);
	GLPState->setUniformFloat(mShader->getUniformLocationForName("u_number"), 0.01);

	num = 0.0f;
	tag = true;

	scheduleUpdate();

	return true;
}

void BlurScene::update(float dt)
{
	//使用定时器控制shader
	if (tag == true)
	{
		num += 0.0001f;
	}
	else
		num -= 0.0001f;

	if (num >= 0.01)
		tag = false;

	if (num <= -0.01)
		tag = true;

	log("num : %f", num);
	GLPState->setUniformFloat(mShader->getUniformLocationForName("u_number"), num);

}