#include "BlurScene.h"
#include "BlurAction.h"

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
	hero = Sprite::create("HelloWorld.png");
	hero->setPosition(size / 2);
	addChild(hero);

	//runBoxFilter();

	//runEdgeFilter();

	runSharpFilter();
	//runOwnAct();

	return true;
}

void BlurScene::runBoxFilter()
{
	auto act = BoxfilterAct::create(2, 0.0f, 0.5);

	hero->runAction(RepeatForever::create(Sequence::create(act, DelayTime::create(0.5), act->reverse(), DelayTime::create(0.5), NULL)));

}

void BlurScene::runEdgeFilter()
{
	auto act = EdgeFilterAct::create(2.0f, 0.0f, 0.008f);
	hero->runAction(RepeatForever::create(Sequence::create(act, DelayTime::create(0.5), act->reverse(), DelayTime::create(0.5), NULL)));
}

void BlurScene::runSharpFilter()
{
	auto act = SharpFilterAct::create(2.0f, 0.0f, 0.01f);
	hero->runAction(RepeatForever::create(Sequence::create(act, DelayTime::create(0.5f), act->reverse(), DelayTime::create(0.5), NULL)));
}

void BlurScene::runOwnAct()
{
	auto shader = GLProgram::createWithFilenames("myShader/MVP_Stand.vert", "myShader/SharpFilter.frag");

	auto state = hero->getGLProgramState();

	state->setGLProgram(shader);

	state->setUniformFloat(shader->getUniformLocationForName("u_number"), 0.01);
}

void BlurScene::update(float dt)
{

}