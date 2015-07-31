#include "OpenGLScene.h"

USING_NS_CC;

bool OpenGLScene::init(){
	auto program = GLProgram::createWithFilenames("myVertextShader.vert", "myFragmentShader.frag");

	program->link();
	program->updateUniforms();
	this->setGLProgram(program);

	

	/*GLuint uColorLocation = glGetUniformLocation(program->getProgram(), "u_color");

	float uColor[] = {
		0, 1, 0, 1.0
	};
	glUniform4fv(uColorLocation,1, uColor);*/


	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	

	auto size = Director::getInstance()->getWinSize();


	typedef struct 
	{
		float Position[3];
		float Color[4];
		float TexCoord[2];
	} Vertex;



	GLubyte indices[] = {
		// Front
		0, 1, 2,
		2, 3, 0,
		// Back
		4, 5, 6,
		4, 5, 7,
		// Left
		8, 9, 10,
		10, 11, 8,
		// Right
		12, 13, 14,
		14, 15, 12,
		// Top
		16, 17, 18,
		18, 19, 16,
		// Bottom
		20, 21, 22,
		22, 23, 20

	};
#define TEX_COORD_MAX   1
	Vertex data[] =
	{
		{ { 1, -1, 0 }, { 1, 0, 0, 1 }, { TEX_COORD_MAX, 0 } },
		{ { 1, 1, 0 }, { 0, 1, 0, 1 }, { TEX_COORD_MAX, TEX_COORD_MAX } },
		{ { -1, 1, 0 }, { 0, 0, 1, 1 }, { 0, TEX_COORD_MAX } },
		{ { -1, -1, 0 }, { 0, 0, 0, 1 }, { 0, 0 } },
		// Back
		{ { 1, 1, -2 }, { 1, 0, 0, 1 }, { TEX_COORD_MAX, 0 } },
		{ { -1, -1, -2 }, { 0, 1, 0, 1 }, { TEX_COORD_MAX, TEX_COORD_MAX } },
		{ { 1, -1, -2 }, { 0, 0, 1, 1 }, { 0, TEX_COORD_MAX } },
		{ { -1, 1, -2 }, { 0, 0, 0, 1 }, { 0, 0 }},
		// Left
		{ { -1, -1, 0 }, { 1, 0, 0, 1 }, { TEX_COORD_MAX, 0 } },
		{ { -1, 1, 0 }, { 0, 1, 0, 1 }, { TEX_COORD_MAX, TEX_COORD_MAX } },
		{ { -1, 1, -2 }, { 0, 0, 1, 1 }, { 0, TEX_COORD_MAX } },
		{ { -1, -1, -2 }, { 0, 0, 0, 1 }, { 0, 0 } },
		// Right
		{ { 1, -1, -2 }, { 1, 0, 0, 1 }, { TEX_COORD_MAX, 0 } },
		{ { 1, 1, -2 }, { 0, 1, 0, 1 }, { TEX_COORD_MAX, TEX_COORD_MAX } },
		{ { 1, 1, 0 }, { 0, 0, 1, 1 }, { 0, TEX_COORD_MAX } },
		{ { 1, -1, 0 }, { 0, 0, 0, 1 }, { 0, 0 } },
		// Top
		{ { 1, 1, 0 }, { 1, 0, 0, 1 }, { TEX_COORD_MAX, 0 } },
		{ { 1, 1, -2 }, { 0, 1, 0, 1 }, { TEX_COORD_MAX, TEX_COORD_MAX } },
		{ { -1, 1, -2 }, { 0, 0, 1, 1 }, { 0, TEX_COORD_MAX } },
		{ { -1, 1, 0 }, { 0, 0, 0, 1 }, { 0, 0 } },
		// Bottom
		{ { 1, -1, -2 }, { 1, 0, 0, 1 }, { TEX_COORD_MAX, 0 } },
		{ { 1, -1, 0 }, { 0, 1, 0, 1 }, { TEX_COORD_MAX, TEX_COORD_MAX } },
		{ { -1, -1, 0 }, { 0, 0, 1, 1 }, { 0, TEX_COORD_MAX } },
		{ { -1, -1, -2 }, { 0, 0, 0, 1 }, { 0, 0 } }
	};

	glGenBuffers(1, &vertexVbo);
	glBindBuffer(GL_ARRAY_BUFFER, vertexVbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
	GLuint positionLocation = glGetAttribLocation(program->getProgram(), "a_position");

	glEnableVertexAttribArray(positionLocation);
	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Position));

	//set color
	/*glGenBuffers(1, &colorVbo);
	glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);*/

	GLuint colorLocation = glGetAttribLocation(program->getProgram(), "a_color");
	glEnableVertexAttribArray(colorLocation);
	glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLuint*)offsetof(Vertex, Color));

	GLuint textureLocation = glGetAttribLocation(program->getProgram(), "a_coord");
	glEnableVertexAttribArray(textureLocation);
	glVertexAttribPointer(textureLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoord));

	glGenBuffers(1, &indexVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenTextures(1, &textureId);
	Image* image = new Image();
	std::string imagePath = FileUtils::getInstance()->fullPathForFilename("HelloWorld.png");
	image->initWithImageFile(imagePath);

	glGenTextures(1, &textureId);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	unsigned char *imageData = image->getData();
	int width = image->getWidth();
	int height = image->getHeight();

	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);

	CC_SAFE_DELETE(image);



	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	auto lb = Sprite::create("HelloWorld.png");
	lb->setPosition(size / 2);
	addChild(lb);

	//use camera
	/*auto mCamera = Camera::createOrthographic(size.width, size.height, 0, 1);
	mCamera->setCameraFlag(CameraFlag::USER1);
	addChild(mCamera);
	mCamera->setPosition3D(Vec3(100, 100, 0));
	mCamera->runAction(MoveBy::create(1,Vec3(100,0,0)));
	this->setCameraMask(2);*/

	
	return true;
}

Scene* OpenGLScene::createScene(){

	auto scene = Scene::create();

	auto layer = OpenGLScene::create();

	scene->addChild(layer);

	return scene;
}

void OpenGLScene::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags) {
	Layer::visit(renderer, parentTransform, parentFlags);

	_command.init(_globalZOrder);
	_command.func = CC_CALLBACK_0(OpenGLScene::onDraw, this);

	//renderer->addCommand(&_command);
}

void OpenGLScene::onDraw(){
	log("onDraw");
	Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	Director::getInstance()->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
	Director::getInstance()->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);

	

	Mat4 projectionMatrix;
	Mat4::createPerspective(60, 480 / 320, 1.0, 42, &projectionMatrix);
	Director::getInstance()->multiplyMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, projectionMatrix);

	Mat4 modelViewMatrix;
	Mat4::createLookAt(Vec3(0, 0, 1), Vec3(0, 0, 0), Vec3(0, 1, 0), &modelViewMatrix);
	modelViewMatrix.translate(0, 0, -5);

	static float rotation = 0;
	modelViewMatrix.rotate(Vec3(1, 1, 1), CC_DEGREES_TO_RADIANS(rotation));
	rotation++;
	if (rotation > 360) {
		rotation = 0;
	}
	Director::getInstance()->multiplyMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, modelViewMatrix);

	auto p = this->getGLProgram();

	p->use();
	p->setUniformsForBuiltins();
	GLuint textureLocation = glGetUniformLocation(p->getProgram(), "CC_Texture0");
	glUniform1i(textureLocation, 0);

	auto size = Director::getInstance()->getWinSize();
	glBindVertexArray(vao);

	GLuint uColorLocation = glGetUniformLocation(p->getProgram(), "u_color");

	float uColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glUniform4fv(uColorLocation, 1, uColor);

	GL::bindTexture2D(textureId);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (GLvoid*)0);
	glBindVertexArray(0);

	CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 36);
	CHECK_GL_ERROR_DEBUG();

	


	Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
	Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);


}