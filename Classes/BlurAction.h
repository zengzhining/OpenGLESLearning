#ifndef __BLURACTION___

#define  __BLURACTION___

#include "cocos2d.h"

USING_NS_CC;

class BoxfilterAct : public ActionInterval
{
public:
	static BoxfilterAct* create();

	virtual BoxfilterAct* clone();
	virtual BoxfilterAct* reverse();
	virtual void startWithTarget(Node *target);

	virtual void update(float time);
protected:

	BoxfilterAct(){};
	virtual ~BoxfilterAct(){};

	bool init();
private:
	GLProgram* _shader;
	GLProgramState* _state;

	bool _tag;
};

#endif //__BLURACTION___