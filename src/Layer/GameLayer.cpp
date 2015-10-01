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
unordered_map<int, Vector<BaseNPC*> > NPCMap;

const int MAXLAYER = 21;
const int MAXFISHNUMBERS = 6;
const int MAXJELLYFISHNUMBERS = 3;

const float  OPACITY = 20;/*Opacity*/

/*******************************************
 // logic layer

	 Layer 1
	 Layer 2
	 Layer 3
	 ......
	 ......
	 Layer (MAXLAYER-1)
	
*********************************************/

GameLayer::GameLayer()
:m_PreLayer(0), ///0 mean nothing layer 
 m_CurrentLayer(1),
 m_NextLayer(2)
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



	for (auto layer = 1; layer != MAXLAYER; ++layer){

		//add Enemy 
		for (auto num = 0; num != MAXFISHNUMBERS; ++num){
			auto		fish = EnemyFactory::create("Fish");
			FishMap[layer].pushBack(fish);
		}
		for (auto num = 0; num != MAXJELLYFISHNUMBERS; ++num){
			auto		jellyfish = EnemyFactory::create("Jellyfish");
			JellyfishFishMap[layer].pushBack(jellyfish);
		}

		//add NPC  
		if (1 == layer){
			auto nextNPC = NextLayerNPC::create();
			NPCMap[layer].pushBack(nextNPC);
		}
		else if (MAXLAYER-1 == layer){
			auto preNPC = PreLayerNPC::create();
			NPCMap[layer].pushBack(preNPC);
		}
		else {
			auto nextNPC = NextLayerNPC::create();
			NPCMap[layer].pushBack(nextNPC);
			auto preNPC = PreLayerNPC::create();
			NPCMap[layer].pushBack(preNPC);
		}

		//add Food
		//	{
		//	}

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
		//this->setOpacity(122);
		this->setAllChildrenVisibleByLayer(m_CurrentLayer,true);
		this->setAllChildrenVisibleByLayer(m_NextLayer,true);
		this->setAllChildrenOpacityByLayer(m_NextLayer, OPACITY);

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
	/*
	auto nextLayerNpc = NextLayerNPC::create();
	nextLayerNpc->setPosition(200,300);
	this->addChild(nextLayerNpc,2,kTagNextLayerNPC);


	auto preLayerNpc = PreLayerNPC::create();
	preLayerNpc->setPosition(300.0f,200.0f);
	this->addChild(preLayerNpc, 2, kTagPreLayerNPC);
	*/
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	for (auto layer = 1; layer != MAXLAYER; ++layer){

		for (auto npc : NPCMap[layer])
		{
			auto pX = origin.x + (visibleSize.width) * CCRANDOM_0_1();
			auto pY = origin.y + (visibleSize.height) * CCRANDOM_0_1();
			npc->setPosition(pX,pY);
			npc->setVisible(false);
			this->addChild(npc,2,kTagNextLayerNPC);
		}
	}


}

void GameLayer::AddFish(std::string fishtype, size_t numbers, GLubyte opacity)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	for (size_t layer = 1; layer != MAXLAYER; ++layer){

		for (auto fish : FishMap[layer]){	

			auto pX = origin.x + (visibleSize.width) * CCRANDOM_0_1();
			auto pY = origin.y + (visibleSize.height) * CCRANDOM_0_1();
			fish->setPosition(Vec2(pX, pY));
			fish->setScale(0.3f);
			//fish->setOpacity(opacity);
			fish->setVisible(false);
			this->addChild(fish,1,9);
		}

		for (auto jellyfish : JellyfishFishMap[layer]){

			auto pX = origin.x + (visibleSize.width) * CCRANDOM_0_1();
			auto pY = origin.y + (visibleSize.height) * CCRANDOM_0_1();
			jellyfish->setPosition(Vec2(pX, pY));
			jellyfish->setScale(0.3f);
			//fish->setOpacity(opacity);
			jellyfish->setVisible(false);
			this->addChild(jellyfish, 1, 8);
		}

	}
}


void GameLayer::onConnect(float dt)
{
	auto playerPositon = getChildByTag(kTagPlayer)->getPosition();
	Vec2 npcPosition;
	for (auto npc : NPCMap[m_CurrentLayer]){
		if ("NextLayerNPC" == npc->getName())
			npcPosition = npc->getPosition();
	}

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

bool GameLayer::setAllChildrenVisibleByLayer(int layer, bool visible)
{
	bool ret = false;
	// Enemy
	for (auto fish : FishMap[layer]){
		fish->setVisible(visible);
	}
	for (auto jellyfish : JellyfishFishMap[layer]){
		jellyfish->setVisible(visible);
	}

	// NPC
	for (auto npc : NPCMap[layer]){
		npc->setVisible(visible);
	}
	// Food
	ret = true;
	return ret;
}
bool GameLayer::setAllChildrenOpacityByLayer(int layer, GLubyte opacity, float BlurRadius)
{
	bool ret = false;
	// Enemy
	for (auto fish : FishMap[layer]){
		fish->setOpacity(opacity);
		fish->setBlurRadius(BlurRadius);
	}
	for (auto jellyfish : JellyfishFishMap[layer]){
		jellyfish->setOpacity(opacity);
		jellyfish->setBlurRadius(BlurRadius);
	}

	// NPC
	for (auto npc : NPCMap[layer]){
		npc->setOpacity(opacity);
		npc->setBlurRadius(BlurRadius);
	}
	// Food
	ret = true;
	return ret;
}

void GameLayer::NextLayer()
{
	// 1 . set All Children in CurrentLayer	invisible [setVisible(false)]
	this->setAllChildrenVisibleByLayer(m_CurrentLayer,false);
	// 2 .go,go,go, and Nextlayer++ , now the NextLayer become CurrentLayer.
	//  and set children's Opacity to 255 make them clear .
	m_PreLayer = m_CurrentLayer; m_CurrentLayer = m_NextLayer;++m_NextLayer;
	this->setAllChildrenOpacityByLayer(m_CurrentLayer,255);
	// 3 . set All Children  in NextLayer visiable and set opacity to 20 [or less then 20]
	//make them dark [to make them look like  really in the NextLayer.]
	this->setAllChildrenVisibleByLayer(m_NextLayer,true);
	this->setAllChildrenOpacityByLayer(m_NextLayer, OPACITY);
	g_GameManager->goNextLayer();
}

void GameLayer::PreLayer()
{
	// 1 . set All Children in NextLayer invisible [setVisible(false)]
	this->setAllChildrenVisibleByLayer(m_NextLayer, false);
	// 2 . set all CurrentLayer children's Opacity to 20 [or less then 20] make them dark
	this->setAllChildrenOpacityByLayer(m_CurrentLayer, OPACITY);
	//
	// 3 . set all children in PreLayer visible [if opacity is 20 then set it to 255] .
	// PreLayer-- , and now the PreLayer become CurrentLayer.
	this->setAllChildrenVisibleByLayer(m_PreLayer,true);
	this->setAllChildrenOpacityByLayer(m_PreLayer,255);

	m_NextLayer = m_CurrentLayer; m_CurrentLayer = m_PreLayer; --m_PreLayer;

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
		log("%s and diff=>%f", __func__ , diff.getLength());
		ret = true;
	}
	return ret;
}