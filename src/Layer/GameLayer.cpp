#include <unordered_map>
#include <cstdlib>
#include "GameLayer.h"
#include "LeadingMan.h"
#include "NextLayerNPC.h"
#include "PreLayerNPC.h"
#include "Enemy.h"
#include "SpeciallyEffectLayer.h"
#include "GameManager.h"
#include "Operate.h"
#include "Role/RoleEnergyPoints.h"
USING_NS_CC;
using namespace tds;
using std::unordered_map;

enum
{
	kTagPlayer = 1,
	kTagNextLayerNPC = 2,
	kTagDrawSignalNext = 3,
	kTagDrawSignalPre = 4,
	kTagPreLayerNPC = 5,
	kTagSpeciallyEffectLayer = 6,
};

// < int Layer, Enemy fishType or other >
unordered_map<int, Vector<Enemy*> > FoodMap;
unordered_map<int, Vector<Enemy*> > FishMap;
unordered_map<int, Vector<Enemy*> > JellyfishFishMap;
unordered_map<int, Vector<Enemy*> > FlockfishMap;
unordered_map<int, Vector<BaseNPC*> > NPCMap;



const float GameLayer::OPACITY = 18;

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
	auto MAXLAYER = g_GameManager->m_levelConfigure.size() + 1; // we +1 becouse layer begin with 1 not 0
	
	// just for debug

	for (auto layer = 1; layer != MAXLAYER; ++layer){
		 
		//add Enemy
		auto MAXFISHNUMBERS = atoi(g_GameManager->m_levelEnemyConfigure[layer]["Fish"]["num"].c_str());
		for (auto num = 0; num != MAXFISHNUMBERS; ++num){
			auto		fish = EnemyFactory::create("Fish");
			fish->setInWhichLayer(layer);
			fish->initFromConfigure(g_GameManager->m_levelEnemyConfigure[layer]["Fish"]);

			FishMap[layer].pushBack(fish);
		}

		auto MAXJELLYFISHNUMBERS = atoi(g_GameManager->m_levelEnemyConfigure[layer]["Jellyfish"]["num"].c_str());
		for (auto num = 0; num != MAXJELLYFISHNUMBERS; ++num){
			auto		jellyfish = EnemyFactory::create("Jellyfish");

			jellyfish->initFromConfigure(g_GameManager->m_levelEnemyConfigure[layer]["Jellyfish"]);
			jellyfish->setInWhichLayer(layer);
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
		auto MAXFOODNUMBERS = atoi(g_GameManager->m_levelEnemyConfigure[layer]["Food"]["num"].c_str());
		auto foodType = atoi(g_GameManager->m_levelEnemyConfigure[layer]["Food"]["foodType"].c_str());
		auto experienceValueHold = atof(g_GameManager->m_levelEnemyConfigure[layer]["Food"]["experienceValueHold"].c_str());

		for (auto num = 0; num != MAXFOODNUMBERS; ++num){
			auto food = Food::create(foodType);
			food->setInWhichLayer(layer);
			food->setExperienceValueHold(experienceValueHold);
			FoodMap[layer].pushBack(food);
		}

	}
}

bool GameLayer::init()
{
	bool ret = false;
	do{

		CC_BREAK_IF(!BaseLayer::init());
		int r = 0;

		r = g_GameManager->initXMLConfigure("Lvl.xml");

		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/player/Player.plist", "images/player/Player.pvr.ccz");
		 
		readConfigureFile();

		auto speciallyeffectLayer = SpeciallyEffectLayer::create();
		speciallyeffectLayer->initBgColorFromConfigure();
		this->addChild(speciallyeffectLayer, -1, kTagSpeciallyEffectLayer);


		AddPlayer();
		AddNPC();
		AddFish("Fish",5);
		AddFood();
		//AddFish("Jellyfish",2,15);
		//this->setOpacity(122);
		this->setAllChildrenVisibleByLayer(m_CurrentLayer,true);
		this->setAllChildrenVisibleByLayer(m_NextLayer,true);
		this->setAllChildrenOpacityByLayer(m_NextLayer, OPACITY);

		std::srand((unsigned)time(nullptr));
		this->schedule(CC_SCHEDULE_SELECTOR(GameLayer::onConnect), 2.0f);
		this->scheduleUpdate();
		ret = true;

	} while (0);
	return ret;
}

void GameLayer::AddPlayer(size_t numbers)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto player = LeadingMan::create("hzk");
	player->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	//player->setScale(0.5f);
	//player->RunLevelAction(1);

	auto hp = EnergyPoints::create();
	hp->setScale(0.3f);
	hp->setPosition(player->getPositionX() + player->getContentSize().width / 2, player->getPositionY());
	this->addChild(hp, 2, 11);
	player->addHP(hp);


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
	auto MAXLAYER = g_GameManager->m_levelConfigure.size() + 1;
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
void GameLayer::AddFood(size_t numbers)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto MAXLAYER = g_GameManager->m_levelConfigure.size() + 1;
	for (auto layer = 1; layer != MAXLAYER; ++layer){

		for (auto food : FoodMap[layer])
		{
			auto pX = visibleSize.width *  CCRANDOM_0_1();// (3 - *6);
			auto pY = visibleSize.height * CCRANDOM_0_1();// (3 - *6);
			food->setPosition(pX, pY);
			//food->setScale(0.3f);
			food->setVisible(false);
			this->addChild(food);
		}
	}
}

void GameLayer::AddFish(std::string fishtype, size_t numbers, GLubyte opacity)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto MAXLAYER = g_GameManager->m_levelConfigure.size() + 1;
	for (size_t layer = 1; layer != MAXLAYER; ++layer){

		for (auto fish : FishMap[layer]){	

			auto pX = visibleSize.width * CCRANDOM_0_1();// (3 - CCRANDOM_0_1() * 6);
			auto pY = visibleSize.height * CCRANDOM_0_1();// (3 - CCRANDOM_0_1() * 6);
			
			fish->setPosition(Vec2(pX, pY));
			//fish->setScale(0.3f);
			//fish->setOpacity(opacity);
			
			
			auto hp = EnergyPoints::create();
			hp->setScale(0.3f);
			hp->setPosition(pX+fish->getContentSize().width,pY);
			this->addChild(hp,2,11);
			fish->addHP(hp);

			fish->setVisible(false);
			this->addChild(fish,1,9);
		}

		for (auto jellyfish : JellyfishFishMap[layer]){

			auto pX = visibleSize.width * CCRANDOM_0_1();// (3 - *6);
			auto pY = visibleSize.height * CCRANDOM_0_1(); //(3 -  * 6);
			jellyfish->setPosition(Vec2(pX, pY));
			//jellyfish->setScale(0.3f);
			//fish->setOpacity(opacity);
			jellyfish->setVisible(false);
			this->addChild(jellyfish, 1, 8);
		}

	}
}

bool GameLayer::checknpcOutoffPlayerVision(cocos2d::Point p)
{
	bool ret = false;
	auto speLayer = dynamic_cast<SpeciallyEffectLayer*>(getChildByTag(kTagSpeciallyEffectLayer));
	auto spep = speLayer->getPosition();

	auto rect = Rect(spep.x,
		spep.y,
		speLayer->getContentSize().width,
		speLayer->getContentSize().height);

	ret =  rect.containsPoint(p);

	return !ret;
}

cocos2d::Vec2 GameLayer::getIntersection_NPC_and_SPELayerRect(cocos2d::Rect rect ,cocos2d::Point p)
{

	/*
			D---------C
			|		 |
			A---------B
	*/
	Vec2 A(rect.getMinX(),rect.getMinY());
	Vec2 B(rect.getMaxX(),rect.getMinY());
	Vec2 C(rect.getMaxX(),rect.getMaxY());
	Vec2 D(rect.getMinX(),rect.getMaxY());

	Vec2 PlayerP = getChildByTag(kTagPlayer)->getPosition();
	Vec2 npcP = p;

	Vec2 point;
	if ( Vec2::isSegmentIntersect(A, B, PlayerP,p)){
		point = Vec2::getIntersectPoint(A,B,PlayerP,p);
	}
	else if (Vec2::isSegmentIntersect(B, C, PlayerP, p)){
		point = Vec2::getIntersectPoint(B,C, PlayerP, p);
	}
	else if (Vec2::isSegmentIntersect(C, D, PlayerP, p)){
		point = Vec2::getIntersectPoint(C, D, PlayerP, p);
	}
	else if (Vec2::isSegmentIntersect(A, D, PlayerP, p)){
		point = Vec2::getIntersectPoint(A, D, PlayerP, p);
	}

	return point;
}


void GameLayer::onConnect(float dt)
{
	//auto playerPositon = getChildByTag(kTagPlayer)->getPosition();
	auto npc = NPCMap[m_CurrentLayer].at(0);
	if (npc)
		drawSignalIfNPCisOutoffVision(npc);
}

void GameLayer::drawSignalIfNPCisOutoffVision(const BaseNPC* npc)
{
		if (checknpcOutoffPlayerVision(npc->getPosition()))
		{
			auto speLayer = dynamic_cast<SpeciallyEffectLayer*>(getChildByTag(kTagSpeciallyEffectLayer));
			auto spep = speLayer->getPosition();
			auto rect = Rect(spep.x,
					spep.y,
					speLayer->getContentSize().width,
					speLayer->getContentSize().height);
			Point center = getIntersection_NPC_and_SPELayerRect(rect, npc->getPosition());
			auto drawSignalNext = DrawNode::create();
			Color4F color;
			if ("NextLayerNPC" == npc->getName())
			{
				color = Color4F::RED;
				this->addChild(drawSignalNext, 0, kTagDrawSignalNext);
			}
			else
			{
				color = Color4F::WHITE;
				this->addChild(drawSignalNext, 0, kTagDrawSignalPre);
			}
				
			for (int c = 1; c != 6; ++c)
				drawSignalNext->drawCircle(center, 10 * c, 0, 360, false, color);	
		}
		if ("NextLayerNPC" == npc->getName())
			this->scheduleOnce(CC_SCHEDULE_SELECTOR(GameLayer::RemoveSignalNext), 0.3f);
		else
			this->scheduleOnce(CC_SCHEDULE_SELECTOR(GameLayer::RemoveSignalPre), 0.3f);
}

void GameLayer::RemoveSignalNext(float dt)
{
	auto drawnext = dynamic_cast<DrawNode*>(this->getChildByTag(kTagDrawSignalNext));
	if (drawnext){
		drawnext->removeFromParent();
	}
	if (2 == NPCMap[m_CurrentLayer].size())
	{
		auto npc = NPCMap[m_CurrentLayer].at(1);
		if (npc)
			drawSignalIfNPCisOutoffVision(npc);
	}
}
void GameLayer::RemoveSignalPre(float dt)
{
	auto drawpre = dynamic_cast<DrawNode*>(this->getChildByTag(kTagDrawSignalPre));
	if (drawpre){
		drawpre->removeFromParent();
	}
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
	for (auto food : FoodMap[layer]){
		food->setVisible(visible);
	}

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
	for (auto food : FoodMap[layer]){
		food->setOpacity(opacity);
		food->setBlurRadius(BlurRadius);
	}


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
	//g_GameManager->goNextLayer();
}

void GameLayer::onSPELayerMove(cocos2d::Vec2 direction, float distance)
{
	auto speLayer = dynamic_cast<SpeciallyEffectLayer*>(getChildByTag(kTagSpeciallyEffectLayer));
	Vec2 velocity = direction * (distance < 32 ? 2 : 4);
	speLayer->setVelocity(velocity);
}

void GameLayer::onPlayerMove(cocos2d::Vec2 direction, float distance)
{
	auto pPlayer = dynamic_cast<LeadingMan*>(this->getChildByTag(kTagPlayer));

	Vec2 velocity = direction * (distance < 32 ? 2 : 4);
	pPlayer->setLastVelocity(velocity);
	pPlayer->setVelocity(velocity);

}

void GameLayer::onSPELayerStop()
{
	auto speLayer = dynamic_cast<SpeciallyEffectLayer*>(getChildByTag(kTagSpeciallyEffectLayer));
	speLayer->setVelocity(Vec2::ZERO);
}

void GameLayer::onPlayerStop()
{
	auto pPlayer = dynamic_cast<LeadingMan*>(this->getChildByTag(kTagPlayer));
	pPlayer->setLastVelocity(pPlayer->getVelocity());
	pPlayer->setVelocity(Vec2::ZERO);
	
}

void GameLayer::onPlayerRotation(double rotation)
{
	auto pPlayer = dynamic_cast<LeadingMan*>(this->getChildByTag(kTagPlayer));
	//pPlayer->stopAllActions();
	//pPlayer->runAction(RotateTo::create(0.08f,rotation));
	pPlayer->setRotation(rotation);
}



void GameLayer::onEnter()
{
	BaseLayer::onEnter();
	auto listener = EventListenerTouchOneByOne::create();
	//listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	//listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);

	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	
	auto listener2 = EventListenerTouchAllAtOnce::create();
	//listener2->onTouchesBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	listener2->onTouchesMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);

	_mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseMove = CC_CALLBACK_1(GameLayer::onMouseMove, this);

	//_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

}

void GameLayer::onExit()
{
	BaseLayer::onExit();
}
// Add these new methods
bool GameLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	
	return true;
}
void GameLayer::onMouseMove(cocos2d::Event* event)
{
	EventMouse* e = (EventMouse*)event;

	auto p = Vec2(e->getCursorX(), e->getCursorY());

	auto pPlayer = dynamic_cast<LeadingMan*>(this->getChildByTag(kTagPlayer));

}
void GameLayer::onTouchMoved(const std::vector<cocos2d::Touch*>& touches, Event* event)
{
	auto touch = touches[0];

	auto diff = touch->getDelta().getNormalized();
	auto node = getChildByTag(kTagPlayer);
	auto spnode = getChildByTag(kTagSpeciallyEffectLayer);
	auto currentPos = node->getPosition();
	node->setPosition(currentPos + diff);
	spnode->setPosition(spnode->getPosition() + diff);
}


void GameLayer::onTouchEnded(Touch* touch, Event* event)
{
	auto pPlayer = dynamic_cast<LeadingMan*>(this->getChildByTag(kTagPlayer));
	pPlayer->stopAllActions();
	pPlayer->RunLevelAction(2);
	
	auto touchPoint = touch->getLocation();
	//touchPoint = this->convertToNodeSpace(touchPoint);
	

	auto rotation = atan2((touchPoint.x - pPlayer->getPositionX()),
		(touchPoint.y - pPlayer->getPositionY())) * 180 / 3.1415926 + 90;
	auto rotate = RotateTo::create(0.3, rotation);

	pPlayer->runAction(rotate);
	
	Point moveDifference = touchPoint - pPlayer->getPosition();
	float distanceToMove = moveDifference.getLength();

	float moveDuration = distanceToMove / 90;

	auto MoveAction = Sequence::create(MoveTo::create(moveDuration, touchPoint),
		CallFunc::create(CC_CALLBACK_0(GameLayer::onStop, this)),
		NULL);

	pPlayer->runAction(MoveAction);
	
}

bool GameLayer::checkCollision(cocos2d::Point p, float radius)
{
	bool ret = false;
	auto pPlayer = this->getChildByTag(kTagPlayer);
	auto diff = pPlayer->getPosition() - p;
	if (diff.getLength() - radius <= 1.00f){
		log(" diff=>%f", diff.getLength());
		ret = true;
	}
	return ret;
}

bool GameLayer::checkCollisionWithEnergyPoints(EnergyPoints* pEnergyPoint)
{
	bool ret = false;

	// with player 
	auto pPlayer = dynamic_cast<LeadingMan*>(this->getChildByTag(kTagPlayer));
	if ( pPlayer && (pPlayer->getPosition() - pEnergyPoint->getPosition()).getLength() < pEnergyPoint->getContentSize().width / 2)
	{
		auto who = pEnergyPoint->getWhoOwnerThisEnergyPonit();
		if (who == pPlayer)return ret;
		who->removeFromParent();
	}

	//with current Layer Enemy
	for (auto fish : FishMap[m_CurrentLayer])
	{
		if ( fish && (fish->getPosition() - pEnergyPoint->getPosition()).getLength() < pEnergyPoint->getContentSize().width / 2)
		{
			auto who = pEnergyPoint->getWhoOwnerThisEnergyPonit();
			if (who == fish || who == pPlayer)return ret;
				who->removeFromParent();
		}
	}
	for (auto jellyfish : JellyfishFishMap[m_CurrentLayer])
	{
		if (jellyfish && (jellyfish->getPosition() - pEnergyPoint->getPosition()).getLength() < pEnergyPoint->getContentSize().width / 2)
		{
			auto who = pEnergyPoint->getWhoOwnerThisEnergyPonit();
			if (who == jellyfish || who == pPlayer)return ret;
			who->removeFromParent();
		}
	}


	return ret;
}

void GameLayer::onStop()
{
	
	auto pPlayer = dynamic_cast<LeadingMan*>(this->getChildByTag(kTagPlayer));
	

	auto rota = RotateBy::create(30, 360);
	auto fseq = RepeatForever::create(rota);

	pPlayer->runAction(fseq);

	pPlayer->RunLevelAction(1);
}

void GameLayer::onUpdatePlayer(float duration)
{

	auto pPlayer = dynamic_cast<LeadingMan*>(this->getChildByTag(kTagPlayer));
	pPlayer->updateSelf( duration);

}

void GameLayer::onUpdateSpeciallyEffectLayer(float duration)
{
	auto speLayer = dynamic_cast<SpeciallyEffectLayer*>(this->getChildByTag(kTagSpeciallyEffectLayer));
	speLayer->updateSelf( duration);
}

void GameLayer::onUpdatePlayerExperienceValue(float value)
{
	auto pPlayer = dynamic_cast<LeadingMan*>(this->getChildByTag(kTagPlayer));
	pPlayer->onUpdatePlayerExperienceValue(value);
}

void GameLayer::update(float dt)
{
		// this value can read from xml file
		auto duration = 1.5f;
		onUpdatePlayer(duration);
		onUpdateSpeciallyEffectLayer(duration);

		auto pPlayer = dynamic_cast<LeadingMan*>(this->getChildByTag(kTagPlayer));
		Size winSize = Director::getInstance()->getWinSize();

		auto pos = pPlayer->getPosition();

		int x = MAX(pos.x, winSize.width / 2);
		int y = MAX(pos.y, winSize.height / 2);

		x = pos.x;
		y = pos.y;

		Point centerOfView = Vec2(winSize.width / 2, winSize.height / 2);

		Point viewPoint = centerOfView - pos;

		this->setPosition(viewPoint);
		
}