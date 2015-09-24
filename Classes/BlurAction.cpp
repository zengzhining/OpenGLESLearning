#include "BlurAction.h"

USING_NS_CC;

BoxfilterAct* BoxfilterAct::create()
{
	auto filter = new BoxfilterAct();
	filter->init();
	filter->autorelease();

	return filter;
	
}

bool BoxfilterAct::init()
{
	if(ActionInterval::initWithDuration(1.0f))
		return true;
	return false;
}

BoxfilterAct* BoxfilterAct::clone()
{
	auto filter = new BoxfilterAct();
	filter->init();
	filter->autorelease();

	return filter;

}

BoxfilterAct* BoxfilterAct::reverse()
{
	auto filter = this->clone();
	filter->_tag = false;
	return filter;
}

void BoxfilterAct::startWithTarget(Node *target)
{
	ActionInterval::startWithTarget(target);

	_shader = GLProgram::createWithFilenames("myShader/MVP_Stand.vert", "myShader/BoxFilter.frag");

	_state = target->getGLProgramState();

	_state->setGLProgram(_shader);

	_state->setUniformFloat(_shader->getUniformLocationForName("u_number"), 0.0f);
	

}

void BoxfilterAct::update(float time)
{
	
	if (_tag == true)
	{
		_state->setUniformFloat(_shader->getUniformLocationForName("u_number"), time * 0.01f);
		log("true");
	}
	
	else
	{
		_state->setUniformFloat(_shader->getUniformLocationForName("u_number"), -time * 0.01f);
		log("false");
	}

}