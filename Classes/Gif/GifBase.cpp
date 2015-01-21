#include "GifBase.h"
using namespace cocos2d;

Texture2D* GifBase::createTexture(Bitmap* bm, int index, bool getCache)
{
	std::string textureName = getGifFrameName(index);
	Texture2D* texture = NULL;

	if(getCache)
	{
        texture = Director::getInstance()->getTextureCache()->getTextureForKey(textureName.c_str());
		if(texture) return texture;
	}

	if(bm == NULL
		|| ! bm->isValid()
		|| index == UNINITIALIZED_UINT)
	{
		return NULL;
	}

	Image* img = new Image();
	do 
	{
		bool res = true;
		const uint32_t* RgbaData = bm->getRGBA();
        res = img->initWithRawData((const unsigned char*)RgbaData,bm->getPixelLenth(), bm->m_width, bm->m_hight, 8);
		if(!res) break;

		Director::getInstance()->getTextureCache()->removeTextureForKey(textureName.c_str());
        
        //Adding texture to CCTextureCache  to ensure that on the Android platform, when cut into the foreground from the background, the VolatileTexture can reload our texture
		texture = Director::getInstance()->getTextureCache()->addImage(img, textureName.c_str());
	} while (0);

	CC_SAFE_RELEASE(img);

	return texture;
}