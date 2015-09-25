#include "HelloWorldScene.h"
#include <spine/spine-cocos2dx.h>
#include "spine/spine.h"

#include "BlurAction.h"

using namespace spine;


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
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto sprite = Sprite::create("HelloWorld.png");  
	sprite->setAnchorPoint(Point(0.5, 0.5));  
	sprite->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));  

	this->addChild(sprite); 

	auto skeNode = SkeletonAnimation::createWithFile("spineboy.json", "spineboy.atlas",0.3);
	//skeNode->setPosition(visibleSize);
	//skeNode->setAnimation(0, "walk", true);
	skeNode->setAnchorPoint(Vec2(0.5,0.5));
	skeNode->setPosition(visibleSize/2);
	addChild(skeNode);
	/*skeNode->runAction(Sequence::create(MoveBy::create(1, Vec2(100,0)),CallFunc::create([skeNode](){
	log("<<<<<<<<<<<<<");
	GLProgram * p = new GLProgram();  
	p->initWithFilenames("myVertextShader.vert", "myFragmentShader.frag");  
	p->link();  
	p->updateUniforms();
	skeNode->setGLProgram(p);
	}),NULL));*/

	skeNode->setAnimation(0, "walk", true);
	
	auto act = GreyFilterAct::create(0.8, 0.0,1.0, false);
	
	//skeNode->runAction(RepeatForever::create(Sequence::create(act, act->reverse(), DelayTime::create(1), NULL)));
	//skeNode->runAction(act);

	auto act2 = SharpFilterAct::create(0.5, 0.0, 0.01);

	//sprite->runAction(RepeatForever::create(Sequence::createWithTwoActions(act2, act2->reverse())));
	sprite->runAction(act);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
	
	//graySprite(sprite);
	this->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_COLOR));


    // add a "close" icon to exit the progress. it's an autorelease object
   
    
    return true;
}

void HelloWorld::testOpenGL() {

}

void HelloWorld::graySprite(Sprite * sprite) {
	if(sprite)  {   

		GLProgram * p = new GLProgram();  
		p->initWithFilenames("myVertextShader.vert", "myFragmentShader.frag");  
		p->link();  
		p->updateUniforms();  
		sprite->setGLProgram(p); 
		sprite->getGLProgramState();
}		
}

void HelloWorld::visit(Renderer* renderer, const Mat4& parentTransform, uint32_t parentFlags) {

	Node::visit(renderer, parentTransform, parentFlags);

	_command.init(_globalZOrder);

	_command.func = CC_CALLBACK_0(HelloWorld::onDraw, this);

	Director::getInstance()->getRenderer()->addCommand(&_command);


}

void HelloWorld::onDraw() {
	////获得当前helloworld的shader
	auto glProgram = this->getShaderProgram();
glProgram->use();
	glProgram->setUniformsForBuiltins();
	glPointSize( 10.0f);
	glColor4f( 0.0f,1.0f,0.0f,1.0f);
	 auto size = Director::getInstance()->getWinSize();
	
		 float vertercies[] = { 100,100,
	                           200, 200,
		                          300, 100 };
	   float color[] = { 1,0,0,1,
	                       0,1,0,1,
	                      0,0,1,1 };
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR );
   glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertercies );
	    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT,GL_TRUE, 0, color);
   // 绘制三角形  
	    glDrawArrays(GL_TRIANGLES, 0 ,3 );
     //通知cocos2d-x 的renderer，让它在合适的时候调用这些OpenGL命令  
	    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,3);
	     CHECK_GL_ERROR_DEBUG();

	//auto size = Director::getInstance()->getWinSize();
	////指定将要绘制的三角形的三个顶点，分别位到屏幕左下角，右下角和正中间的顶端
	//float vertercies[] = { 0,0,   //第一个点的坐标
	//	size.width, 0,   //第二个点的坐标
	//	size.width / 2, size.height};  //第三个点的坐标
	////指定每一个顶点的颜色，颜色值是RGBA格式的，取值范围是0-1
	//float color[] = { 0, 1,0, 1,    //第一个点的颜色，绿色
	//	1,0,0, 1,  //第二个点的颜色, 红色
	//	0, 0, 1, 1};  //第三个点的颜色， 蓝色
	////激活名字为position和color的vertex attribute
	//GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);
	////分别给position和color指定数据源
	/*glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertercies);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, color);*/
	//绘制三角形，所谓的draw call就是指这个函数调用
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	//通知cocos2d-x 的renderer，让它在合适的时候调用这些OpenGL命令
	//CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 3);
	////如果出错了，可以使用这个函数来获取出错信息
	//CHECK_GL_ERROR_DEBUG();
	
	//set uniform locations
	


	
	//program->setUniformsForBuiltins();
	
	
	
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
