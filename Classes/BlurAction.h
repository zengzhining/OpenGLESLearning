#ifndef __BLURACTION___

#define  __BLURACTION___

#include "cocos2d.h"

USING_NS_CC;
//注意模糊特效不能两个同时使用，因为无法让一个精灵同时使用两个shader

//方形模糊特效
class BoxfilterAct : public ActionInterval
{
public:
	static BoxfilterAct* create(float durtion = 1.0f ,float from = 0.0f, float to = 0.01f);

	virtual BoxfilterAct* clone() const override ;
	virtual BoxfilterAct* reverse() const override ;
	virtual void startWithTarget(Node *target) override;

	virtual void update(float time);
protected:

	BoxfilterAct(){};
	virtual ~BoxfilterAct(){};

	bool init(float durtion, float from, float to);
private:

	//动作持续的时间
	float _durition;

	//动作开始的数字
	float _from;
	//动作结束的数字
	float _to;

	//动作持续的差值
	float _deltaNumber;

	//记录当前的num
	float _num;

	GLProgram* _shader;
	GLProgramState* _state;
};

//边沿模糊特效
class EdgeFilterAct : public ActionInterval
{
public:
	static EdgeFilterAct* create(float time, float from, float to);

	virtual EdgeFilterAct* clone() const override;
	virtual EdgeFilterAct* reverse() const override;
	virtual void startWithTarget(Node *target) override;

	virtual void update(float time) override;

protected:
	EdgeFilterAct(){}

	virtual ~EdgeFilterAct(){}

	bool init(float time, float from, float to);
private:
	float _duration;
	float _from;
	float _to;
	float _deltaNum;
	float _num;

	GLProgram* _shader;
	GLProgramState* _state;

};


#endif //__BLURACTION___