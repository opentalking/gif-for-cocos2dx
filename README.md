This project is based on the gif_lib, and some codes reference to the android skia.
In my project, gif_lib library version is 5, and there are some changes to adapt android, ios, win32 platform.
The cocos2dx version number is 2.2.0 


Use Gif widget just like a CCSprite:

	std::string name = "g2.gif";
	name = CCFileUtils::sharedFileUtils()->fullPathForFilename(name.c_str());
	GifBase *gif = InstantGif::create(name);//InstantGif ：While playing, while parsing
	gif->setAnchorPoint(ccp(0,0));
	gif->setPosition(ccp(0,0));
	this->addChild(gif);

	gif = CacheGif::create(name);//CacheGif: onece parse, and cache.
	gif->setPosition(ccp(500,0));
	gif->setScale(2);
	this->addChild(gif);

Special attention should be paid to gif path which must be a absolute path.

