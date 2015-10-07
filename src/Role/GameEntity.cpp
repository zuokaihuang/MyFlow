//
//  GameEntity.cpp
//  Flow
//
//  Created by ade.li on 10/7/15.
//
//

#include "GameEntity.h"

using namespace tds;
using namespace cocos2d;

GameEntity* GameEntity::create(){
    auto entity = new (std::nothrow) GameEntity;
    if (entity && entity->init() ){
        entity->autorelease();
        return entity;
    }
    return nullptr;
}
bool GameEntity::init(){
    CCLOG("GameEntity init");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setAnchorPoint(Point(0.5, 0.5));
    sprite->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
    
    this->addChild(sprite);
    
    graySprite(sprite);
//    blurSprite(sprite);
    
    

    return true;
}

GLProgram* GameEntity::loadShader(const char *key, const char *vsh, const char *fsh){
    GLProgram* program = GLProgramCache::getInstance()->getGLProgram(key);
    if ( program) {
        program->reset();
    }else{
        // load shaders
        program = new GLProgram;
        if ( false == program->initWithFilenames( vsh, fsh) ){
            CCLOG("load shader([%s][%s]) error", vsh, fsh);
            CC_SAFE_DELETE(program);
            return nullptr;
        }
    }
    
    CHECK_GL_ERROR_DEBUG();
    program->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    program->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
    program->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
    CHECK_GL_ERROR_DEBUG();
    
    if ( false == program->link() ){
        CCLOG("link shader([%s][%s]) error", vsh, fsh);
        CC_SAFE_DELETE(program);
        return nullptr;
    }
    
    program->updateUniforms();
    CHECK_GL_ERROR_DEBUG();
    
    GLProgramCache::getInstance()->addGLProgram(program, key);
    program->autorelease();
    
    return program;
}

void GameEntity::graySprite(cocos2d::Sprite *sprite){
    if (!sprite) return;
    
    const char* vsh = "GameEntity/shaders/gray.vsh";
    const char* fsh = "GameEntity/shaders/gray.fsh";
    
    GLProgram* p = loadShader("gray", vsh, fsh);
    if (!p) return;
    sprite->setGLProgram(p);
}

void GameEntity::blurSprite(cocos2d::Sprite *sprite){
    if (!sprite) return;
    
    const char* vsh = "GameEntity/shaders/blur.vsh";
    const char* fsh = "GameEntity/shaders/blur.fsh";
    
    GLProgram* p = loadShader("blur", vsh, fsh);
    if (!p) return;
    sprite->setGLProgram(p);
}














