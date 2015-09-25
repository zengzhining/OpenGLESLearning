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

	runOwnAct();

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

void BlurScene::runOwnAct()
{
	auto act = BoxfilterAct::create(2, 0.0f, 0.5);
	auto act2 = EdgeFilterAct::create(2.0f, 0.0f, 0.008f);
}

void BlurScene::update(float dt)
{

}