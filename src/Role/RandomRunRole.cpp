
#include "RandomRunRole.h"
#include "CircleMoveAction.h"
#include "GameManager.h"

using namespace tds;
USING_NS_CC;

RandomRunRole::RandomRunRole(std::string name)
:Role(name),
m_CanRun(true),
m_blurRadius(1),
m_blurSampleNum(2)
{
	
}

bool RandomRunRole::init(std::string name)
{
	bool ret = false;
	do{

		auto path = getPath();
		if (!path.empty()){

			this->initWithFile(path);
			//auto target = Sprite::create(path);
			//target->setPosition(200.0f,200.0f);
			//this->addChild(target,0,1);

		}
		else
			return ret;

		this->scheduleUpdate();
		ret = true;
	} while (0);

	return ret;
}

void RandomRunRole::update(float dt)
{
	this->beginRandomRun();
	checkCollision();
}

void RandomRunRole::checkCollision()
{
	if (this->isVisible() && this->getOpacity()> 20)
		g_GameManager->checkCollision(this);
}

void RandomRunRole::beginRandomRun()
{
	if (this->m_CanRun)
	{
		this->m_CanRun = false;
		//Connect(Vec2());
		//
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		auto pX = origin.x + (visibleSize.width  ) * CCRANDOM_0_1();
		auto pY = origin.y + (visibleSize.height ) * CCRANDOM_0_1();

		

		auto srcPosition = this->getPosition();
		auto distance = srcPosition.getDistance(Vec2(pX, pY));
		auto moveDuration = distance / this->getMoveSpeed();

		//auto direct = (Vec2(pX, pY) - srcPosition).getNormalized();
		//Vec2 moveSpeed = direct * 2;

		//Vec2 expectP = srcPosition + moveSpeed;

		auto moveAction = MoveTo::create(moveDuration, Vec2(pX, pY));
		//	CallFunc::create(std::bind(&RandomRunRole::onMoveCallBack, this)),
		//	NULL);
		//auto  circleto = CircleMoveAction::create(20, srcPosition, 100);
		auto s = Director::getInstance()->getWinSize();

		auto array = PointArray::create(20);

		array->addControlPoint(Vec2(0, 0));
		array->addControlPoint(Vec2(pX, 0));
		array->addControlPoint(Vec2(pX, pY));
		array->addControlPoint(Vec2(0, pY));
		array->addControlPoint(Vec2(0, 0));
		auto action = CardinalSplineBy::create(20, array, 0);
		auto reverse = action->reverse();
		//auto seq1 = Sequence::create(action, CallFunc::create(std::bind(&RandomRunRole::onMoveCallBack, this)),
		//	NULL);
		auto seq2 = Sequence::create(moveAction, CallFunc::create(std::bind(&RandomRunRole::onMoveCallBack, this)),
			NULL);
		//this->runAction(seq1);
		this->runAction(seq2);

		auto rota = RotateBy::create(2,360);
		auto fseq = RepeatForever::create(rota);

		this->runAction(fseq);

	}
}

void RandomRunRole::onMoveCallBack()
{
	this->m_CanRun = true;
}


bool RandomRunRole::initWithTexture(Texture2D* texture, const Rect& rect)
{
	m_blurRadius = 0;
	if (Sprite::initWithTexture(texture, rect))
	{
#if CC_ENABLE_CACHE_TEXTURE_DATA
		auto listener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom* event){
			setGLProgram(nullptr);
			initGLProgram();
		});

		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif

		//initGLProgram();

		return true;
	}

	return false;
}

void RandomRunRole::initGLProgram()
{
	GLchar * fragSource = (GLchar*)String::createWithContentsOfFile(
		FileUtils::getInstance()->fullPathForFilename("Shaders/example_Blur.fsh").c_str())->getCString();
	auto program = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource);

	auto glProgramState = GLProgramState::getOrCreateWithGLProgram(program);
	setGLProgramState(glProgramState);

	auto size = getTexture()->getContentSizeInPixels();
	getGLProgramState()->setUniformVec2("resolution", size);
	getGLProgramState()->setUniformFloat("blurRadius", 1.0);
	getGLProgramState()->setUniformFloat("sampleNum",7.0f);
}

void RandomRunRole::setBlurRadius(float radius)
{
	m_blurRadius = radius;
	//getGLProgramState()->setUniformFloat("blurRadius", m_blurRadius);
}

void RandomRunRole::setBlurSampleNum(float num)
{
	m_blurSampleNum = num;
	//getGLProgramState()->setUniformFloat("sampleNum", m_blurSampleNum);
}