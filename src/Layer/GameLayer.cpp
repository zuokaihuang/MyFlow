
#include <cstdlib>
#include "GameLayer.h"
#include "LeadingMan.h"
#include "NextLayerNPC.h"
#include "Enemy.h"

#include "GameManager.h"

USING_NS_CC;
using namespace tds;

enum
{
	kTagPlayer = 1,
	kTagNextLayerNPC = 2,
	kTagDrawSignal = 3,
};

GameLayer::GameLayer()
{
	g_GameManager->m_GameLayer = this;
	this->retain();
}

GameLayer::~GameLayer()
{
	this->unschedule(CC_SCHEDULE_SELECTOR(GameLayer::onConnect));
}

bool GameLayer::init()
{
	bool ret = false;
	do{

		CC_BREAK_IF(!BaseLayer::init());
		std::srand((unsigned)time(nullptr));

		AddPlayer();
		AddNPC();
		AddFish("Fish",5);
		AddFish("Jellyfish",2);

		this->schedule(CC_SCHEDULE_SELECTOR(GameLayer::onConnect), 2.0f);
		
		ret = true;

	} while (0);
	return ret;
}

void GameLayer::AddPlayer(size_t numbers)
{
	auto player = LeadingMan::create("hzk");
	player->setPosition(100,200);
	player->setScale(0.3f);
	this->addChild(player,1,kTagPlayer);
}

void GameLayer::AddNPC(size_t numbers)
{
	auto nextLayerNpc = NextLayerNPC::create();
	nextLayerNpc->setPosition(200,300);
	this->addChild(nextLayerNpc,2,kTagNextLayerNPC);
}

void GameLayer::AddFish(std::string fishtype, size_t numbers)
{
	for (size_t num = 0; num != numbers; ++num){
		auto fish = EnemyFactory::create(fishtype);
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		auto pX = origin.x + (visibleSize.width ) * CCRANDOM_0_1();
		auto pY = origin.y + (visibleSize.height ) * CCRANDOM_0_1();
		fish->setPosition(Vec2(pX,pY));
		fish->setScale(0.3f);
		this->addChild(fish);
	}
}


void GameLayer::onConnect(float dt)
{
	auto playerPositon = getChildByTag(kTagPlayer)->getPosition();
	auto npcPosition = getChildByTag(kTagNextLayerNPC)->getPosition();

	auto drawSignal = DrawNode::create();
	this->addChild(drawSignal,0, kTagDrawSignal);
	drawSignal->drawLine(npcPosition, playerPositon, Color4F::BLUE);
	//drawSignal->drawCircle(npcPosition, 5, 0, 360, false, Color4F::BLUE);
	//auto scaleby = ScaleBy::create(1, 10);
	//auto action2 = Sequence::create(
	//	scaleby,
	//	FadeOut::create(1), CallFunc::create(std::bind(&GameLayer::RemoveSignal,this,dt)), nullptr);
	//drawSignal->runAction(action2);
	this->scheduleOnce(CC_SCHEDULE_SELECTOR(GameLayer::RemoveSignal),0.1f);
}

void GameLayer::RemoveSignal(float dt)
{
	this->getChildByTag(kTagDrawSignal)->removeFromParent();
	NextLayer();
}


void GameLayer::NextLayer()
{
	auto vecNode = this->getChildren();
	for (auto node : vecNode){
		if (kTagPlayer != node->getTag()){
			auto position = node->getPosition();
			float x;
			if (position.x> Director::getInstance()->getVisibleSize().width/2){
				x = position.x + 30;
			}
			else
				x = position.x - 30;

			auto moveto = MoveTo::create(0.2f, Vec2(x, position.y));
			auto scaleto = ScaleTo::create(0.2f,1.1f);
			auto action = Sequence::create(
				moveto,
				FadeOut::create(0.2f), FadeIn::create(0.2f),
				nullptr);
			node->runAction(action);
			
		}
		
	}
	this->scheduleOnce(CC_SCHEDULE_SELECTOR(GameLayer::onMoveCallBack), 0.3f);
	
}

void GameLayer::PreLayer()
{
	g_GameManager->goPreLayer();
}

void GameLayer::onMoveCallBack(float dt)
{
	g_GameManager->goNextLayer();
}