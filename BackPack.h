// Simple inventory storage class used in a 
// completed dungeons and dragons style game

// Created by Brandon McCowan
// 11/12/12

#include "cocos2d.h"

using namespace cocos2d;

#define TOTAL_ITEMS 16
#define TOTAL_ACTIONS 11

class BackPack : public cocos2d::CCSprite
{
private:
	struct m_sItems
	{
		const char* filename;
		const char* type; // monster, obstacle, health
		int dice;
		int stock; // number of a particular item in stock
	};
	static struct m_sItems m_asItems[TOTAL_ITEMS]; // stores item data
	static const char* m_aActionList[TOTAL_ACTIONS]; // stores actions
public:
	// return item array (with or without zero-stock items)
	CCArray* getItmArray(bool zeros);
	//return action array
	CCArray* getAxnArray();
	// add item to m_asItems
	void addItm(int position, const char* filename, const char* type, int dice);
	// add action to m_aActionList
	void addAxn(int position, const char* text);
	// return item amount currently in stock
	int getItmStock(const char* filename, bool zeros);
	// reduce item stock
	void useItmStock(const char* filename);
	// return item type (monster,obstacle,health)
	const char* getItmType(const char* filename);
	// return dice bonus
	int getItmDice(const char* filename);
};
