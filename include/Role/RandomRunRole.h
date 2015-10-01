
#ifndef _RANDOMRUNROLE_H__
#define _RANDOMRUNROLE_H__

#include "Role.h"

namespace tds{

	class RandomRunRole : public Role
	{
	protected:
		RandomRunRole(std::string name = "");
		virtual bool init(std::string name = "");
		virtual std::string getPath(){ return ""; }
		void onMoveCallBack();

		bool initWithTexture(cocos2d::Texture2D* texture, const cocos2d::Rect&  rect);
		void initGLProgram();
		float		m_blurRadius;
		float		m_blurSampleNum;

	public:
		CC_SYNTHESIZE(bool, m_CanRun,CanRun);
	
		virtual void setBlurRadius(float radius);
		virtual void setBlurSampleNum(float num);
		virtual void beginRandomRun();
		virtual void checkCollision();
		virtual void update(float dt);
	};

};



#endif