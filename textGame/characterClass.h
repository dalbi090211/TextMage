#pragma once

enum CharacterClass {
	NormalMage,
	BlackMage,
	WildMage
};

inline const char* CharacterClassToString(CharacterClass type)
{
	switch (type)
	{
		case NormalMage:
			return "NormalMage";
		case BlackMage:
			return "BlackMage";
		case WildMage:
			return "WildMage";
	}
}

inline const char* CharacterClassToString( int idx )
{
	switch ( idx )
	{
	case 0:
		return "NormalMage";
	case 1:
		return "BlackMage";
	case 2:
		return "WildMage";
	}
}