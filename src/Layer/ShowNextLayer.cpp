#include "GameManager.h"
#include "ShowNextLayer.h"

using namespace tds;

ShowNextLayer::ShowNextLayer()
{
	g_GameManager->m_ShowNextLayer = this;
	this->retain();
}

ShowNextLayer::~ShowNextLayer()
{

}

bool ShowNextLayer::init()
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

void ShowNextLayer::onEnter()
{

}

void ShowNextLayer::onExit()
{

}