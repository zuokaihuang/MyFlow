
#include "SpeciallyEffectLayer.h"
#include "GameManager.h"
USING_NS_CC;
using namespace tds;


Color4B level_bgColor[] =
{
	{ 0x00, 0xBF, 0xFF, 255 },
	{ 0x00, 0x9E, 0xE7, 255 },
	{ 0x00, 0x8D, 0xD8, 255 },
	{ 0x00, 0x7C, 0xC9, 255 },
	{ 0x00, 0x6D, 0xBB, 255 },
	{ 0x00, 0x66, 0xAD, 255 },
	{ 0x00, 0x60, 0x9E, 255 },
	{ 0x00, 0x5C, 0x8F, 255 },
	{ 0x00, 0x57, 0x80, 255 },
	{ 0x00, 0x51, 0x6F, 255 }
};


SpeciallyEffectLayer::SpeciallyEffectLayer():
m_nextLayerColorIndex(0)
{
	g_GameManager->m_SpeciallyEffectLayer = this;
	this->retain();
}

SpeciallyEffectLayer::~SpeciallyEffectLayer()
{
	//this->unschedule(CC_SCHEDULE_SELECTOR(SpeciallyEffectLayer::onSetColor));
}

bool SpeciallyEffectLayer::init()
{
	bool ret = false;
	do
	{
		CC_BREAK_IF(!BaseLayer::init());
		//this->setColor(Color3B(0x00, 0xBF, 0xFF));


	

		ret = true;
	} while (0);

	return ret;
}

void SpeciallyEffectLayer::onSetColor(bool next_or_pre)
{
	auto index = next_or_pre ? ++m_nextLayerColorIndex : --m_nextLayerColorIndex;
	m_layer->setColor(Color3B(level_bgColor[index]));

	//test
	if (m_nextLayerColorIndex == 9 || m_nextLayerColorIndex==-1){
		m_nextLayerColorIndex = 0;
	}

}

void SpeciallyEffectLayer::onEnter()
{
	BaseLayer::onEnter();
	m_layer = LayerColor::create(Color4B(0x00, 0xBF, 0xFF,255));
	auto s = Director::getInstance()->getWinSize();

	m_layer->setContentSize(Size(400,s.height));
	m_layer->setPosition(s.width/2 - m_layer->getContentSize().width/2,0);
	this->addChild(m_layer);

	//this->schedule(CC_SCHEDULE_SELECTOR(SpeciallyEffectLayer::onSetColor),1.0f);
}


void SpeciallyEffectLayer::onExit()
{
	BaseLayer::onExit();
}


