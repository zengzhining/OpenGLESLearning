#include "OpenGLLightScene.h"
#include "NewSprite.h"
#include "spine/spine-cocos2dx.h"
#include "spine/spine.h"

USING_NS_CC;
using namespace spine;

Scene* OpenGLLightScene::createScene(){
	auto scene = Scene::create();

	auto layer = OpenGLLightScene::create();

	scene->addChild(layer);

	return scene;
}

bool OpenGLLightScene::init(){
	auto program = new GLProgram();
	program->initWithFilenames("myVertextShader.vert", "myFragmentShader.frag");
	program->link();
	//set uniform locations
	program->updateUniforms();

	//    this->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_COLOR));
	this->setGLProgram(program);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);



	typedef struct {
		float Position[2];
		float Color[4];
		float TexCoord[2];
		float Normal[2];
	} Vertex;

	    auto size = Director::getInstance()->getVisibleSize();
	Vertex data[] =
	{
		{ { -1, -1 }, { 1, 1, 1, 1 }, { 0, 1 }, { 0, 0.7 } },

		{ { 1, -1 }, { 1, 1, 1, 1 }, { 1, 1 }, { 0, 1 } },

		{ { -1, 1 }, { 1, 1, 1, 1 }, { 0, 0 }, { 0, 1 } },

		{ { 1, 1 }, { 1, 1, 1, 1 }, { 1, 0 }, { 0, 0.7 } }
	};

	GLubyte indices[] = { 0, 1, 2,  //第一个三角形索引
		2, 3, 1 }; //第二个三角形索引

	glGenBuffers(1, &vertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
	GLuint positionLocation = glGetAttribLocation(program->getProgram(), "a_position");
	//    CCLOG("position =%d", positionLocation);
	glEnableVertexAttribArray(positionLocation);


	glVertexAttribPointer(positionLocation,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, Position));

	//set for color
	//    glGenBuffers(1, &colorVBO);
	//    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	//    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

	GLuint colorLocation = glGetAttribLocation(program->getProgram(), "a_color");
	glEnableVertexAttribArray(colorLocation);
	glVertexAttribPointer(colorLocation,
		4,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, Color));

	GLuint textureLocation = glGetAttribLocation(program->getProgram(), "a_coord");
	glEnableVertexAttribArray(textureLocation);
	glVertexAttribPointer(textureLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoord));

	//adding surface normals
	GLuint normalLocation = glGetAttribLocation(program->getProgram(), "a_normal");
	glEnableVertexAttribArray(normalLocation);
	glVertexAttribPointer(normalLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));

	GLuint indexVBO;
	glGenBuffers(1, &indexVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//method 1: the hard way
	Image *image = new Image;
	std::string imagePath = FileUtils::getInstance()->fullPathForFilename("HelloWorld.png");
	image->initWithImageFile(imagePath);

	//    glPixelStorei(GL_UNPACK_ALIGNMENT, 8);


	glGenTextures(1, &textureId);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);
	//    GL::bindTexture2DN(1,textureId);



	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	unsigned char *imageData = image->getData();
	int width = image->getWidth();
	int height = image->getHeight();
	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGB,
		width,
		height,
		0,
		GL_RGB,
		GL_UNSIGNED_BYTE,//must be GL_UNSIGNED_BYTE
		imageData);


	//    //method2: the easier way
	//    Texture2D *texture = new Texture2D;
	//    texture->initWithImage(image);
	//    textureId = texture->getName();
	//    
	//    //method3: the easiest way
	//    Sprite *sprite = Sprite::create("HelloWorld.png");
	//    textureId = sprite->getTexture()->getName();

	CC_SAFE_DELETE(image);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	

	auto skeNode = SkeletonAnimation::createWithFile("spineboy.json", "spineboy.atlas", 0.3);

	skeNode->setPosition(0, size.height);

	addChild(skeNode);

	_lightPosition = skeNode->getPosition();

	skeNode->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.1, Vec2(10, -10)), CallFunc::create([skeNode, this](){
		_lightPosition = skeNode->getPosition();
	}), NULL)));

	auto newSp = NewSprite::create("game_title.png");
	newSp->setPosition(size.width / 2, size.height / 2);
	addChild(newSp);

	auto newProgram = GLProgram::createWithFilenames("normalShader.vert", "normalShader.frag");

	auto newState = GLProgramState::create(newProgram);

	newState->setUniformVec4("u_color", Vec4(1.0, 1.0, 1.0, 1.0));
	skeNode->setGLProgramState(newState);
	newState->setUniformCallback("u_color", [program](GLProgram* P, Uniform* uniform){
		program->setUniformLocationWith4f(uniform->location, 1.0, 1.0, 0.0, 1.0);
	});
	return true;
}

bool OpenGLLightScene::onTouchBegan(Touch *touch, Event *unused_event) {
	auto size = Director::getInstance()->getWinSize();
	
	return true;
}

void OpenGLLightScene::onTouchMoved(Touch *touch, Event *unused_event) {
	Vec2 pos = touch->getLocation();
	_lightPosition = pos;
	Size winSize = Director::getInstance()->getWinSizeInPixels();
	CCLOG("light position. x= %f, y = %f", _lightPosition.x / winSize.width, _lightPosition.y / winSize.height);
}

void OpenGLLightScene::onTouchEnded(Touch *touch, Event *unused_event) {
	
}

void OpenGLLightScene::onTouchCancelled(Touch *touch, Event *unused_event){

}
void OpenGLLightScene::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags){
	Layer::visit(renderer, parentTransform, parentFlags);

	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(OpenGLLightScene::onDraw, this);
	renderer->addCommand(&_customCommand);
}

void OpenGLLightScene::onDraw(){

	//question1: why the triangle goes to the up side
	//如果使用对等矩阵，则三角形绘制会在最前面
	Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	Director::getInstance()->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
	Director::getInstance()->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);


	auto glProgram = getGLProgram();

	glProgram->use();

	//set uniform values, the order of the line is very important
	glProgram->setUniformsForBuiltins();
	GLuint textureLocation = glGetUniformLocation(glProgram->getProgram(), "CC_Texture0");
	glUniform1i(textureLocation, 0);



	auto size = Director::getInstance()->getWinSize();

	//use vao
	glBindVertexArray(vao);

	GLuint uColorLocation = glGetUniformLocation(glProgram->getProgram(), "u_color");

	static float uColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glUniform4fv(uColorLocation, 1, uColor);

	GLuint lightPositionLocation = glGetUniformLocation(glProgram->getProgram(), "u_lightPosition");
	GLuint lightColorPosition = glGetUniformLocation(glProgram->getProgram(), "u_lightColor");

	glUniform3f(lightPositionLocation, _lightPosition.x, _lightPosition.y, 100);

	glUniform3f(lightColorPosition, 1, 1, 1);


	GL::bindTexture2D(textureId);

	//    glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (GLvoid*)0);

	glBindVertexArray(0);

	CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 6);
	CHECK_GL_ERROR_DEBUG();

	Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);

	Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

}