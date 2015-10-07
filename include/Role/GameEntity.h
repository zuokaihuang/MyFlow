//
//  GameEntity.h
//  Flow
//
//  Created by ade.li on 10/7/15.
//
//

#ifndef GameEntity_h
#define GameEntity_h

#include "cocos2d.h"

namespace tds {
    class GameEntity : public cocos2d::Sprite{
    public:
        static GameEntity* create();
        virtual bool init() override;
        
        
        cocos2d::GLProgram* loadShader(const char* key, const char* vsh, const char* fsh);
        void graySprite(cocos2d::Sprite* sprite);
        void blurSprite(cocos2d::Sprite* sprite);
        
    private:
        cocos2d::CustomCommand _customCommand;
        
    };
}


#endif /* GameEntity_h */
