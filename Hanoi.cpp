//////////////////////////
// Towers of Hanoi Game
// using Cocos2dX engine
// created by Brandon McCowan
// 4/29/13
/////////////////////////

#include "HelloWorldScene.h"

using namespace cocos2d;

int selectedPillar;
int selectedBlock;
int bHeight;
int numBlockP1;
int numBlockP2;
int numBlockP3;
int numBlock[3];
int topBlockP1;
int topBlockP2;
int topBlockP3;
int topBlock[3];

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// initialize instance
bool HelloWorld::init()
{
    bool bRet = false;
    do 
    {
        // super init first
        CC_BREAK_IF(! CCLayer::init());
	
	// no pillar/block initially selected	
	selectedPillar = 0;
	selectedBlock = 0;
	// number of blocks on each pillar
	numBlock[0] = (numBlockP1 = 7);
	numBlock[1] = (numBlockP2 = 0);
	numBlock[2] = (numBlockP3 = 0);
	// stores pillar's current top block's tag
	topBlock[0] = (topBlockP1 = 9);
	topBlock[1] = (topBlockP2 = 20);
	topBlock[2] = (topBlockP3 = 20);

	CCMenuItemImage* pillar1 = createPillar(-150,0);
	CCMenuItemImage* pillar2 = createPillar(0,1);
	CCMenuItemImage* pillar3 = createPillar(150,2);
	
	CCMenuItemImage* block1 = createBlock(-150,-150,float(.27),3); // .035 difference btwn blocks
	// block height
	bHeight = (block1->boundingBox().getMaxY()) - (block1->boundingBox().getMinY());
	CCMenuItemImage* block2 = createBlock(-150,(-150+bHeight),float(.27-.035),4);
	CCMenuItemImage* block3 = createBlock(-150,(-150+(bHeight*2)),float(.27-(.035*2)),5);
	CCMenuItemImage* block4 = createBlock(-150,(-150+(bHeight*3)),float(.27-(.035*3)),6);
	CCMenuItemImage* block5 = createBlock(-150,(-150+(bHeight*4)),float(.27-(.035*4)),7);
	CCMenuItemImage* block6 = createBlock(-150,(-150+(bHeight*5)),float(.27-(.035*5)),8);
	CCMenuItemImage* block7 = createBlock(-150,(-150+(bHeight*6)),float(.27-(.035*6)),9);

        bRet = true;
    } while (0);

    return bRet;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

CCMenuItemImage* HelloWorld::createPillar(int posX, int tag)
{
	CCMenu* menu = CCMenu::create();
	CCMenuItemImage* pillar = CCMenuItemImage::create("/pillar.png","/pillar.png",this,menu_selector(HelloWorld::selectPillar));
	pillar->setScaleX(float(0.2));
	pillar->setScaleY(float(0.4));
	pillar->setPosition(ccp(posX,-75));
	pillar->setTag(tag);
	pillar->setEnabled(false);
	menu->setTag(tag);
	menu->addChild(pillar);
	this->addChild(menu);
	return pillar;
}

CCMenuItemImage* HelloWorld::createBlock(int posX, int posY, float sizeY, int tag)
{
	CCMenu* menu = CCMenu::create();
	CCMenuItemImage* block = CCMenuItemImage::create("/block.png","/block.png",this,menu_selector(HelloWorld::selectBlock));
	block->setScale(float(0.3));
	block->setPosition(ccp(posX,posY));
	block->setScaleX(sizeY);
	block->setTag(tag);
	menu->setTag(tag);
	menu->addChild(block);
	this->addChild(menu);
	return block;
}

void HelloWorld::selectPillar(CCObject* target)
{
	bool bTopBlock = true;
	float topBlockSize;
	float selectedBlockSize;
	// set all pillar colors to default
	for (int i=0 ; i<3 ; i++)
	{
		((CCMenuItemImage*)((this->getChildByTag(i))->getChildByTag(i)))->setOpacity(255);
	}

	// set selected pillar
	CCMenuItemImage* pillar = (CCMenuItemImage*)(target);
	selectedPillar = pillar->getTag();
	//pillar->setOpacity(140);
	//CCLog("selectedPillar is %i",selectedPillar);

	if (topBlock[selectedPillar] == 20)
	{
		topBlockSize = 0;
	}
	else
	{
		topBlockSize = ((CCMenuItemImage*)(this->getChildByTag(topBlock[selectedPillar])->getChildByTag(topBlock[selectedPillar])))->getScaleX();
	}
	selectedBlockSize = ((CCMenuItemImage*)(this->getChildByTag(selectedBlock)->getChildByTag(selectedBlock)))->getScaleX();

	// if selected block size is < top block on pillar OR no block on pillar OR no block above it, run move block fxn
	CCMenuItemImage* block = ((CCMenuItemImage*)(this->getChildByTag(selectedBlock)->getChildByTag(selectedBlock)));
	float aboveBlock = block->getPositionY() + bHeight;
	for (int x=3 ; x<10 ; x++)
	{
		if (((CCMenuItemImage*)(this->getChildByTag(x)->getChildByTag(x)))->boundingBox().containsPoint(ccp(block->getPositionX(),aboveBlock)) == true)
		{
			//CCLog("block exists above selected block");
			bTopBlock = false;
			break;
		}
	}

	//CCLog("topBlockSize is %f\nselectedBlockSize is %f",topBlockSize,selectedBlockSize);
	if ((numBlock[selectedPillar] == 0) || (selectedBlockSize < topBlockSize))
	{
		if (bTopBlock == true)
			moveBlock();
	}

	// winning condition - 7 blocks,top block is tag 9
	for (int y=1 ; y<3 ; y++)
	{
		if (numBlock[y] == 7)
		{
			if (topBlock[y] == 9)
			{
				CCSprite* winMsg = CCSprite::create("/winMsg.png");
				winMsg->setPosition(ccp(240,150));
				winMsg->setScale(float(.5));
				this->addChild(winMsg);

				CCMenu* restartM = CCMenu::create();
				CCMenuItemImage* restartB = CCMenuItemImage::create("/restartB.png","/restartB.png",this,menu_selector(HelloWorld::restartGame));
				(restartB->getSelectedImage())->setScale(.75);
				(restartB->getSelectedImage())->setPosition(ccp(restartB->getPositionX()+20,restartB->getPositionY()+20));
				restartB->setScale(float(.5));
				restartB->setPositionY(-50);
				restartM->addChild(restartB);
				this->addChild(restartM);
				
				break;
			}
		}
	}
}

void HelloWorld::selectBlock(CCObject* target)
{
	// enable pillars
	for (int i=0 ; i<3 ; i++)
	{
		((CCMenuItemImage*)((this->getChildByTag(i))->getChildByTag(i)))->setEnabled(true);
	}

	// set all block colors to default
	for (int x=3 ; x<10 ; x++)
	{
		((CCMenuItemImage*)((this->getChildByTag(x))->getChildByTag(x)))->setOpacity(255);
	}

	// set selected block color
	CCMenuItemImage* block = (CCMenuItemImage*)(target);
	selectedBlock = block->getTag();
	block->setOpacity(140);
	//CCLog("selectedBlock is %i",selectedBlock);
}

void HelloWorld::moveBlock()
{
	int pPillar = 20; // prior pillar (block-containing pillar)
	int newTopBlock = 20;
	CCMenuItemImage* pillar = ((CCMenuItemImage*)(this->getChildByTag(selectedPillar)->getChildByTag(selectedPillar)));
	CCMenuItemImage* block = ((CCMenuItemImage*)(this->getChildByTag(selectedBlock)->getChildByTag(selectedBlock)));

	// disable pillars, set to default
	for (int i=0 ; i<3 ; i++)
	{
		//((CCMenuItemImage*)((this->getChildByTag(i))->getChildByTag(i)))->setEnabled(false);
		//((CCMenuItemImage*)((this->getChildByTag(i))->getChildByTag(i)))->setOpacity(255);
		// determine block-containing pillar via boundingBox containsPoint fxn
		if (((CCMenuItemImage*)(this->getChildByTag(i)->getChildByTag(i)))->boundingBox().containsPoint(block->getPosition()) == true)
		{
			//CCLog("block-containing pillar is %i",i);
			pPillar = i;
			break;
		}
	}

	// loop through blocks for belowBlock
	float belowBlock = block->getPositionY() - bHeight;
	for (int x=3 ; x<10 ; x++)
	{
		if (((CCMenuItemImage*)((this->getChildByTag(x))->getChildByTag(x)))->boundingBox().containsPoint(ccp(block->getPositionX(),belowBlock)) == true)
		{
			//CCLog("belowBlock is block tag %i",x);
			newTopBlock = x;
			break;
		}
	}
	block->setPosition(ccp(pillar->getPositionX(),(-150+(bHeight*numBlock[selectedPillar]))));
	
	// add to number of blocks on selectedPillar
	numBlock[selectedPillar]++;
	//CCLog("pillar %i has %i blocks",selectedPillar,numBlock[selectedPillar]);
	
	// subtract number of blocks from priorPillar
	numBlock[pPillar]--;
	//CCLog("pillar %i has %i blocks",pPillar,numBlock[pPillar]);
	
	// set topBlock for selectedPillar
	topBlock[selectedPillar] = selectedBlock;
	//CCLog("pillar %i's top block is tag %i",selectedPillar,selectedBlock);
	
	// set topBlock for priorPillar
	topBlock[pPillar] = newTopBlock;
	//CCLog("pillar %i's top block is tag %i",pPillar,newTopBlock);
}

void HelloWorld::restartGame(CCObject* button)
{
	CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}
