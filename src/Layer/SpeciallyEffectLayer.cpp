
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
		this->initBgColorFromConfigure();

	

		ret = true;
	} while (0);

	return ret;
}

void SpeciallyEffectLayer::initBgColorFromConfigure()
{
	const auto &map = g_GameManager->m_levelConfigure;
	const auto maxlayer = map.size();
	GLubyte _r =0 , _g=0, _b=0, _a=255;
	const char* str_rgba = "0xffffffff";
	for (auto layer = 1; layer != maxlayer; ++layer)
	{
		unsigned char rgb_array[3] = {};
		int  rgb_array_index = 0;

		//str_rgba = map.find(layer)->second.find("bgColor")->second.c_str();
		auto layer_iter = map.find(layer);
		if (layer_iter != map.end() ){
			auto bg_iter = layer_iter->second.find("bgColor");
			if (bg_iter != layer_iter->second.end()){
				str_rgba = bg_iter->second.c_str();
			}
		}

		auto rgbindex = 2;
		unsigned char hight, low;

		for (; rgbindex != 8;rgbindex +=2){

			hight = tolower(str_rgba[rgbindex]);
			if (hight > '9'){
				hight = (10 + (tolower(hight) - 'a'));
			}
			else
				hight = (tolower(hight) - '0');

			hight *= 16;

			low = tolower(str_rgba[rgbindex + 1]);
			if (low > '9')
			{
				low = (10 + (tolower(low) - 'a'));
			}else
				low = (tolower(low) - '0');

			rgb_array[rgb_array_index++] = hight + low;
		}

		_level_BgColor[layer] = Color3B(rgb_array[0], rgb_array[1], rgb_array[2]);
		
	}

}


void SpeciallyEffectLayer::onSetColor(int layer)
{
	m_layer->setColor(_level_BgColor[layer]);
}

void SpeciallyEffectLayer::onEnter()
{
	BaseLayer::onEnter();
	m_layer = LayerColor::create(Color4B(0x00, 0xBF, 0xFF,255.0f));
	auto s = Director::getInstance()->getWinSize();
	m_layer->setOpacity(255.0f);
	m_layer->setContentSize(Size(s.width, s.height));
	m_layer->setPosition(s.width/2 - m_layer->getContentSize().width/2,0);
	this->addChild(m_layer);

	//this->schedule(CC_SCHEDULE_SELECTOR(SpeciallyEffectLayer::onSetColor),1.0f);
}


void SpeciallyEffectLayer::onExit()
{
	BaseLayer::onExit();
}

void SpeciallyEffectLayer::updateSelf()
{
	Vec2 currentP = this->getPosition();
	Vec2 expectP = currentP + this->getVelocity();
	Vec2 actualP = expectP;

	this->setPosition(actualP);
}

