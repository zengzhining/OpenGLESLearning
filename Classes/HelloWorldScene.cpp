#include "HelloWorldScene.h"
#include "InputHandler.h"
#include "Command.h"
#include "BlendAction.h"
#include "myAction.h"
USING_NS_CC;


Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::init())
    {
        return false;
    }
    this->initWithColor(Color4B::YELLOW);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto eveDispatcher = Director::getInstance()->getEventDispatcher();

	auto textureAlpha = Director::getInstance()->getTextureCache()->addImage("DEMO0_alpha.pkm");

	auto program = GLProgram::createWithFilenames("etc_shader.vert", "etc_shader.frag");
	auto pstate = GLProgramState::create(program);
	pstate->setUniformTexture("u_texture1", textureAlpha);

	this->setGLProgramBuffer("myVertextShader.vert", "myFragmentShader.frag", "gray");
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object

    //初始化按钮事件


	auto keyBoard_listener = EventListenerKeyboard::create();

	auto hellow = Sprite::create("HelloWorld.png");
	hellow->setPosition(visibleSize/2);
	addChild(hellow);

	hero = Sprite::create("DEMO0.pkm");
	hero->setPosition(visibleSize/2);
	addChild(hero);
	hero->setGLProgramState(pstate);

	/*auto bColor = BlendAction::create(0.5);
	auto rColor = bColor->reverse();
	auto repeat_act = RepeatForever::create(Sequence::create(bColor, rColor, NULL));
	auto m_sequence = Speed::create(repeat_act, 2);
	hero->runAction(m_sequence);*/

	auto m_act = myAction::create(1, Color3B::GREEN);

	hellow->runAction(m_act);

	GLProgramCache::getInstance()->addGLProgram(hero->getGLProgram(), "normal");
	InputHandler* controller =  new InputHandler();
	
	keyBoard_listener->onKeyPressed = [controller, this](EventKeyboard::KeyCode keycode , Event* event ) {

		scheduleUpdate();

		
		switch (keycode)
		{
			//w key pressed
		case EventKeyboard::KeyCode::KEY_W :
			//graySprite(hero);
			cmd = controller->handleInput(InputHandler::KeyCode::UP);
			break;
		case EventKeyboard::KeyCode::KEY_S :
			cmd =controller->handleInput(InputHandler::KeyCode::DOWN);
			break;
		case EventKeyboard::KeyCode::KEY_A :
			cmd = controller->handleInput(InputHandler::KeyCode::LEFT);
			break;

		case EventKeyboard::KeyCode::KEY_D :
			//this->turnNormal(hero);
			cmd = controller->handleInput(InputHandler::KeyCode::RIGHT);
			break;
		default:
			break;
		}
	};

	keyBoard_listener->onKeyReleased = [this](EventKeyboard::KeyCode keycode, Event* event) {
		hero->stopAllActions();
		unscheduleUpdate();
		log("key with the keycode %d release", keycode);
	};
	eveDispatcher->addEventListenerWithSceneGraphPriority(keyBoard_listener, this);
	
    
    return true;
}

void HelloWorld::turnNormal(Sprite* sprite) {
	sprite->getGLProgramState()->setGLProgram(GLProgramCache::getInstance()->getGLProgram("normal"));
}

void HelloWorld::update(float dt ) {
	cmd->execute(hero);
}

void HelloWorld::setGLProgramBuffer(std::string str_vert, std::string str_frag, std::string keyName) {
	auto glAche = GLProgramCache::getInstance();

	GLProgram * p = new GLProgram();  
	p->initWithFilenames(str_vert, str_frag);
	p->link();  
	p->updateUniforms(); 
	glAche->addGLProgram(p, keyName);

}
void HelloWorld::graySprite(Sprite* sprite) {
	if(sprite)  {   

		auto p =GLProgramCache::getInstance()->getGLProgram("gray"); 
		 
		//sprite->setGLProgram(p); 
		sprite->getGLProgramState()->setGLProgram(p);


}
}