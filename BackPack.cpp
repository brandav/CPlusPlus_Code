#include "BackPack.h"

using namespace cocos2d;

BackPack::m_sItems BackPack::m_asItems[TOTAL_ITEMS];
const char* BackPack::m_aActionList[TOTAL_ACTIONS];

// Store the category data in a char array, 
// then load them into a ccarray when we need them! 

CCArray* BackPack::getItmArray(bool zeros)
{
	// create array for transferring purposes
	CCArray* aItm = CCArray::create();

	for (int i=0 ; i < sizeof(m_asItems)/TOTAL_ITEMS ; i++) // divide by the size of the struct to get length
	{
		if (zeros == true) // items with no stock will be included in array
		{
			if (m_asItems[i].filename == NULL);
			else
			{
				aItm->addObject(CCString::create(m_asItems[i].filename));
				//CCLog("filename object added to array");
			}
		}
		else if (zeros == false) // items with no stock will NOT be included in array
			if (m_asItems[i].filename == NULL || m_asItems[i].stock <= 0);
			else
			{
				aItm->addObject(CCString::create(m_asItems[i].filename));
				//CCLog("filename object added to array");
			}
	}
	return aItm;
}

CCArray* BackPack::getAxnArray()
{
	const int BASIC_SIZE = 4;
	const char* basic_actions[BASIC_SIZE] = {"Break","Climb","Push","Leap"};
	for (int i=0 ; i < BASIC_SIZE ; i++)
		m_aActionList[i] = basic_actions[i];
	// create array for transferring purposes
	CCArray* actionArray = CCArray::create();
	
	// load string objects into array
	for (int i=0 ; i < sizeof(m_aActionList)/BASIC_SIZE ; i++)
	{
		if (m_aActionList[i] == NULL);
		else
			actionArray->addObject(CCString::create(m_aActionList[i]));
	}

	return actionArray;
}

void BackPack::addAxn(int position, const char* text)
{
	// store action names in array
	// bypass first four default actions before adding
	m_aActionList[position+4] = text;
	//CCLog("added to action array");
}

int BackPack::getItmStock(const char* filename, bool zeros)
{
	//return item amount currently in stock
	int check = 0;
	CCString* nameCheck;
	//CCLog("filename is %s",filename);
	
	// run loop to find matching filename in m_asItems
	for (int i=0 ; i < sizeof(m_asItems)/TOTAL_ITEMS ; i++) // divide by the size of a struct to get length
	{
		nameCheck = CCString::createWithFormat("%s",m_asItems[i].filename);
		//CCLog("%s",m_asItems[i].filename);
		
		if (zeros == true)
			if (m_asItems[i].filename == NULL);
			else
			{
				// use compare fxn for strings
				if (nameCheck->compare(filename) == 0)
				{
					//CCLog("got a match");
					check = m_asItems[i].stock;
				}
			}
		else if (zeros == false)
			if (m_asItems[i].filename == NULL || m_asItems[i].stock == 0);
			else
			{
				// use compare fxn for strings
				if (nameCheck->compare(filename) == 0)
				{
					//CCLog("got a match");
					check = m_asItems[i].stock;
				}
			}
	}
	return check;
}

void BackPack::useItmStock(const char* filename)
{
	// Use an item
	CCString* nameCheck;
	//CCLog("filename is %s",filename);
	
	// run loop to find matching filename in m_asItems
	for (int i=0 ; i < sizeof(m_asItems)/TOTAL_ITEMS ; i++) // divide by the size of the struct to get length
	{
		nameCheck = CCString::createWithFormat("%s",m_asItems[i].filename);
		//CCLog("%s",m_asItems[i].filename);
		//if (m_asItems[i].filename == NULL || m_asItems[i].stock == 0);
		
		// use compare fxn for strings
		if (nameCheck->compare(filename) == 0)
		{
			//CCLog("got a match");
			// reduce stock by 1
			m_asItems[i].stock-=1;
		}
	}
}

const char* BackPack::getItmType(const char* filename)
{
	// return monster, obstacle, or health type item
	CCString* nameCheck;
	//CCLog("filename is %s",filename);
	
	// run loop to find matching filename in m_asItems
	for (int i=0 ; i < sizeof(m_asItems)/TOTAL_ITEMS ; i++) // divide by the size of the struct to get length
	{
		nameCheck = CCString::createWithFormat("%s",m_asItems[i].filename);
		//CCLog("%s",m_asItems[i].filename);
		//if (m_asItems[i].filename == NULL || m_asItems[i].stock == 0);
		
		// use compare fxn for strings
		if (nameCheck->compare(filename) == 0)
		{
			//CCLog("got a match");
			// return type (monster, obstacle, or "")
			if (m_asItems[i].type == NULL)
				return "";
			else
				return m_asItems[i].type;
		}
	}
	return NULL;
}

int BackPack::getItmDice(const char* filename)
{
  // return dice bonus amount
	CCString* nameCheck;
	//CCLog("filename is %s",filename);
	
	// run loop to find matching filename in m_asItems
	for (int i=0 ; i < sizeof(m_asItems)/TOTAL_ITEMS ; i++) // divide by the size of the struct to get length
	{
		nameCheck = CCString::createWithFormat("%s",m_asItems[i].filename);
		//CCLog("%s",m_asItems[i].filename);
		//if (m_asItems[i].filename == NULL || m_asItems[i].stock == 0);
		
		// use compare fxn for strings
		if (nameCheck->compare(filename) == 0)
		{
			//CCLog("got a match");
			// return dice number
			return m_asItems[i].dice;
		}
	}
	return NULL;
}

void BackPack::addItm(int position, const char* filename, const char* type, int dice)
{
	// add to item inventory array
	// determines if item needs to be created or it's stock increased
	int inStock = 0;

	// if filename is in m_asItems array, increase stock by 1
	for (int i=0 ; i < TOTAL_ITEMS ; i++)
	{
		if (m_asItems[i].filename == filename)
		{
			m_asItems[i].stock++;
			//CCLog("item's stock increased by 1");
			inStock++;
		}
	}
	// if item's filename is not in m_asItems array, create and add it
	if (inStock == 0)
	{
		m_sItems item; 
		item.filename = filename;
		item.type = type;
		item.dice = dice;
		item.stock = 1;
		// create and store item information in struct array
		m_asItems[position] = item;
		//CCLog("position is %i",position);
		//CCLog("added to temporary item array");
	}
	//CCLog("item's stock is currently: %i",m_asItems[position].stock);
}
