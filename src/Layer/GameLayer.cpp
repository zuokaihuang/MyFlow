#include <unordered_map>
#include <cstdlib>
#include "GameLayer.h"
#include "LeadingMan.h"
#include "NextLayerNPC.h"
#include "PreLayerNPC.h"
#include "Enemy.h"

#include "GameManager.h"

USING_NS_CC;
using namespace tds;
using std::unordered_map;

enum
{
	kTagPlayer = 1,
	kTagNextLayerNPC = 2,
	kTagDrawSignal = 3,
	kTagPreLayerNPC = 4,
};

// < int Layer, Enemy fishType or other >
unordered_map<int, Vector<Enemy*> > FishMap;
unordered_map<int, Vector<Enemy*> > JellyfishFishMap;
unordered_map<int, Vector<Enemy*> > FlockfishMap;

const int MAXLAYER = 20;
const int MAXFISHNUMBERS = 5;
const int MAXJELLYFISHNUMBERS = 2;

GameLayer::GameLayer()
{
	g_GameManager->m_GameLayer = this;
	this->retain();
}

GameLayer::~GameLayer()
{
	this->unschedule(CC_SCHEDULE_SELECTOR(GameLayer::onConnect));
}

void GameLayer::readConfigureFile(std::string path)
{
	// just for debug



	for (auto layer = 0; layer != MAXLAYER; ++layer){

		for (auto num = 0; num != MAXFISHNUMBERS; ++num){
			auto		fish = EnemyFactory::create("Fish");
			FishMap[layer].pushBack(fish);
		}
		for (auto num = 0; num != MAXJELLYFISHNUMBERS; ++num){
			auto		jellyfish = EnemyFactory::create("Jellyfish");
			JellyfishFishMap[layer].pushBack(jellyfish);
		}

	}
}

bool GameLayer::init()
{
	bool ret = false;
	do{

		CC_BREAK_IF(!BaseLayer::init());
		readConfigureFile();

		AddPlayer();
		AddNPC();
		AddFish("Fish",5);
		//AddFish("Jellyfish",2,15);
		std::srand((unsigned)time(nullptr));
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


	auto preLayerNpc = PreLayerNPC::create();
	preLayerNpc->setPosition(300.0f,200.0f);
	this->addChild(preLayerNpc, 2, kTagPreLayerNPC);
}

void GameLayer::AddFish(std::string fishtype, size_t numbers, GLubyte opacity)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	for (size_t layer = 0; layer != 2; ++layer){

		for (auto fish : FishMap[layer]){	

			auto pX = origin.x + (visibleSize.width) * CCRANDOM_0_1();
			auto pY = origin.y + (visibleSize.height) * CCRANDOM_0_1();
			fish->setPosition(Vec2(pX, pY));
			fish->setScale(0.3f);
			//fish->setOpacity(opacity);
			this->addChild(fish);
		}

		for (auto jellyfish : JellyfishFishMap[layer]){

			auto pX = origin.x + (visibleSize.width) * CCRANDOM_0_1();
			auto pY = origin.y + (visibleSize.height) * CCRANDOM_0_1();
			jellyfish->setPosition(Vec2(pX, pY));
			jellyfish->setScale(0.3f);
			//fish->setOpacity(opacity);
			this->addChild(jellyfish);
		}

	}
}


void GameLayer::onConnect(float dt)
{
	auto playerPositon = getChildByTag(kTagPlayer)->getPosition();
	auto npcPosition = getChildByTag(kTagNextLayerNPC)->getPosition();

	auto drawSignal = DrawNode::create();
	this->addChild(drawSignal,0, kTagDrawSignal);
	drawSignal->drawLine(npcPosition, playerPositon, Color4F::BLUE);
	drawSignal->drawCircle(npcPosition, 5, 0, 360, false, Color4F::BLUE);
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
	//NextLayer();
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

void GameLayer::onEnter()
{
	BaseLayer::onEnter();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	
	
}

void GameLayer::onExit()
{
	BaseLayer::onExit();
}
// Add these new methods
bool GameLayer::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}

void GameLayer::onTouchMoved(Touch* touch, Event* event)
{
}


void GameLayer::onTouchEnded(Touch* touch, Event* event)
{
	auto pPlayer = this->getChildByTag(kTagPlayer);
	pPlayer->stopAllActions();

	auto touchPoint = touch->getLocation();
	//touchPoint = this->convertToNodeSpace(touchPoint);

	Point moveDifference = touchPoint - pPlayer->getPosition();
	float distanceToMove = moveDifference.getLength();

	float moveDuration = distanceToMove / 90;

	auto MoveAction = Sequence::create(MoveTo::create(moveDuration, touchPoint),
		CallFunc::create(CC_CALLBACK_0(GameLayer::onStop, this)),
		NULL);
	
	
	pPlayer->runAction(MoveAction);
}

bool GameLayer::checkCollision(cocos2d::Point p)
{
	bool ret = false;
	auto pPlayer = this->getChildByTag(kTagPlayer);
	auto diff = pPlayer->getPosition() - p;
	if (diff.getLength() <= 5.00f){
		log("%s and diff=>%f", __FUNCTIONW__, diff.getLength());
		ret = true;
	}
	return ret;
}