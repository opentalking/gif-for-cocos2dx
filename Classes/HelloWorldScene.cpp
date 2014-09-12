#include "HelloWorldScene.h"
#include "Gif/GIFMovie.h"
#include "Gif/CacheGif.h"
#include "Gif/InstantGif.h"

USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define FILE_FORMAT ("/mnt/sdcard/g%d.gif")
#else
#define FILE_FORMAT ("g%d.gif")
#endif

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
      
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(HelloWorld::menuCloseCallback));

	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
		origin.y + pCloseItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

    return true;
}

int count = 1;
void HelloWorld::update(float delta)
{
	count++ ;
	if(count > 240)
	{
		this->removeAllChildren();
	}
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    count++;
	while(this->getChildByTag(1000))
	{
		this->removeChildByTag(1000);
	}
    CCLOG("%s","------after remove gif-----------");
    CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
	if(count % 2 != 0)
    {
        return ;
    }
	std::string name = CCString::createWithFormat(FILE_FORMAT,count/2)->getCString();
	name = CCFileUtils::sharedFileUtils()->fullPathForFilename(name.c_str());
    
	GifBase *gif = InstantGif::create(name.c_str());
	if(gif == NULL)
	{
        CCLOG("%s","create gif failed");
		return ;
	}
	gif->setAnchorPoint(ccp(0,0));
	this->addChild(gif);
	gif->setPosition(ccp(0,0));
	gif->setTag(1000);


	gif = InstantGif::create(name.c_str());
	gif->setAnchorPoint(ccp(0,0));
	this->addChild(gif);
	gif->setPosition(ccp(500,0));
	gif->setScale(2);
	gif->setTag(1000);
	CCLOG("%s","------after add gif-----------");
    CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();

	return ;
}
