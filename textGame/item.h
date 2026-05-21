#pragma once

#include <string>

enum ItemName {
	Silver_Sword_of_the_Astral_Plane ,
	Thornwhisper_Staff,
	Necklace_of_Elemental_Augmentation ,
	Soulrender_Axe ,
	Emberveil_Ring,
	Gravemire_Pendant,
	Helldusk_Armor ,
	Stormcaller_Amulet,
	Crybabys_Chocker,
	Duskmantle_Cloak,
	Heart
};

enum ItemType {
	Stat,
	Disposable ,
	Consumable
};

class ItemInfo {
public:
	int price;
	ItemType type;
	ItemName name;
	std::vector<std::wstring> explain;

	ItemInfo() 
		: price( 0 ) , type( ItemType::Stat ), name(ItemName::Heart)
	{
	}

	ItemInfo( int price , ItemType type, ItemName name, std::vector<std::wstring> explain )
		: price( price ) , type( type ) , name(name), explain( explain )
	{
	}
};

inline const std::wstring ItemClassToString( ItemType type )
{
	switch ( type )
	{
	case Stat:
		return L"스탯 증가";

	case Disposable:
		return L"영구";

	case Consumable:
		return L"소모품";
	}
}

inline const std::wstring ItemNameToString( ItemName type )
{
	switch ( type )
	{
	case Silver_Sword_of_the_Astral_Plane :
		return L"영계의 은검";
	case Thornwhisper_Staff:
		return L"가시속삭임 지팡이";
	case Necklace_of_Elemental_Augmentation:
		return L"원소 증강 목걸이";
	case Soulrender_Axe:
		return L"영혼 절단 도끼";
	case Emberveil_Ring:
		return L"불씨장막 반지";
	case Gravemire_Pendant:
		return L"묘지수렁 목걸이";
	case Helldusk_Armor:
		return L"황혼지옥갑옷";
	case Stormcaller_Amulet:
		return L"폭풍소환부적";
	case Duskmantle_Cloak:
		return L"황혼장막망토";
	case Heart : 
		return L"힐링 포션";
	case Crybabys_Chocker:
		return L"울보의 목걸이";
	}
	
}