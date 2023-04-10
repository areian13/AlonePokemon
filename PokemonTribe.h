// 고정된 종족값을 설정하는 클래스
#pragma once

#include "PokemonType.h";

#define NUMBER_OF_POKEMON 14


struct Evo
{
	int evoLevel;
	int evoPokeIndex;
};
struct TribeValue
{
	int health; // 체력
	int attack; // 공격
	int block; // 방어
	int contact; // 특공
	int defense; // 특방
	int speed; // 속도

	friend ostream& operator<<(ostream& os, TribeValue tribeValue)
	{
		os << tribeValue.health << ' ';
		os << tribeValue.attack << ' ';
		os << tribeValue.block << ' ';
		os << tribeValue.contact << ' ';
		os << tribeValue.defense << ' ';
		os << tribeValue.speed << ' ';
		return os;
	}
};
enum ExpFormulaIndex
{
	FAST, // 빠름
	MDFA, // 중간빠름
	MDSL, // 중간느림
	SLOW,  // 느림
};

class PokemonTribe
{
public:
	int m_dicNum; // 도감 번호
	vector<PokemonType> m_types; // 갖고 있는 타입(들)
	string m_name; // 종족 이름 ex) 이상해씨
	TribeValue m_tribeValue; // 종족치 HABCDS
	Evo m_evo; // 진화를 할 레벨 + 진화될 포켓몬의 도감 번호
	ExpFormulaIndex m_expFormulaIndex; // '레벨에 따른 필요 경험치 공식'에 대한 인덱스
	int m_baseExpYield; // 종족별 패배하였을 때 상대에게 주는 경험치량
	int m_catchRate; // 종족별 포획률
private:
	

public:
	PokemonTribe()
	{

	}
	PokemonTribe(int dicNum, vector<PokemonType> types, string name, TribeValue tribeValue, Evo evo, ExpFormulaIndex expFormulaIndex, int baseExpYield, int catchRate)
	{
		m_dicNum = dicNum;
		m_types = types;
		m_name = name;
		m_tribeValue = tribeValue;
		m_evo = evo;
		m_expFormulaIndex = expFormulaIndex;
		m_baseExpYield = baseExpYield;
		m_catchRate = catchRate;
	}

	int MaxExpByLevel(int level)
	{
		int powN3 = level * level * level;
		switch (m_expFormulaIndex)
		{
		case FAST:
			return 4 * powN3 / 5;
			break;
		case MDFA:
			return powN3;
			break;
		case MDSL:
			return 6 * powN3 / 5 - 15 * level * level + 100 * level - 140;
			break;
		case SLOW:
			return 5 * powN3 / 4;
			break;
		}
	}
	TribeValue StatsByLevel(int level)
	{
		int health  = (2 * m_tribeValue.health + 100) * level / 100 + 10;
		int attack  = (2 * m_tribeValue.attack  + 31) * level / 100 +  5;
		int block   = (2 * m_tribeValue.block   + 31) * level / 100 +  5;
		int contact = (2 * m_tribeValue.contact + 31) * level / 100 +  5;
		int defense = (2 * m_tribeValue.defense + 31) * level / 100 +  5;
		int speed   = (2 * m_tribeValue.speed   + 31) * level / 100 +  5;

		return { health,attack,block,contact,defense,speed };
	}
	Evo GetEvoValue()
	{
		return m_evo;
	}
	void Evolution(vector<PokemonTribe>& pokemonDic)
	{
		*this = pokemonDic[m_evo.evoPokeIndex];
	}
	bool IsLastEvo()
	{
		return m_evo.evoLevel == -1;
	}
	friend ostream& operator<<(ostream& os, PokemonTribe tribe)
	{
		os << tribe.m_dicNum << ' ' << tribe.m_name << ' ';
		for (PokemonType type : tribe.m_types)
			os << stringType[type] << ' ';
		return os;
	}
};

enum PokemonDicNum
{
	김뮤진,

	이상해씨,
	이상해풀,
	이상해꽃,

	파이리,
	리자드,
	리자몽,

	꼬부기,
	어니부기,
	거북왕,

	캐터피,
	단데기,
	버터플,

	구구,
	피죤,
	피죤투,

	피카츄,
	라이츄
};

vector<PokemonTribe> pokemonDic =
{
	{     김뮤진,       { PSYSHC },    "김뮤진",{ 999,999,999,999,999,999 },{ -1,        -1 },FAST,999,255 },
																								  	  
	{   이상해씨, { GRASS,POISON },  "이상해씨",{  45, 49, 49, 65, 65, 45 },{ 16,  이상해풀 },MDSL, 64, 45 },
	{   이상해풀, { GRASS,POISON },  "이상해풀",{  60, 62, 63, 80, 80, 60 },{ 32,  이상해꽃 },MDSL,141, 45 },
	{   이상해꽃, { GRASS,POISON },  "이상해꽃",{  80, 82, 83,100,100, 80 },{ -1,        -1 },MDSL,208, 45 },
																								  	  
	{     파이리,         { FIRE },    "파이리",{  39, 52, 43, 60, 50, 65 },{ 16,    리자드 },MDSL, 65, 45 },
	{     리자드,         { FIRE },    "리자드",{  58, 64, 58, 80, 65, 80 },{ 36,    리자몽 },MDSL,142, 45 },
	{     리자몽,  { FIRE,FLYING },    "리자몽",{  78, 84, 78,109, 85,100 },{ -1,        -1 },MDSL,209, 45 },
																								  	  
	{     꼬부기,        { WATER },    "꼬부기",{  44, 48, 65, 50, 64, 43 },{ 16,  어니부기 },MDSL, 66, 45 },
	{   어니부기,        { WATER },  "어니부기",{  59, 63, 80, 65, 80, 58 },{ 36,    거북왕 },MDSL,143, 45 },
	{     거북왕,        { WATER },    "거북왕",{  79, 83,100, 85,105, 78 },{ -1,        -1 },MDSL,210, 45 },
																								  	  
	{     캐터피,          { BUG },    "캐터피",{  45, 30, 35, 20, 20, 45 },{  7,    단데기 },MDFA, 53,255 },
	{     단데기,          { BUG },    "단데기",{  50, 20, 55, 25, 25, 30 },{ 10,    버터플 },MDFA, 72,120 },
	{     버터플,   { BUG,FLYING },    "버터플",{  60, 45, 50, 80, 80, 70 },{ -1,        -1 },MDFA,160, 45 },
																								  	  
	{       구구,{ NORMAL,FLYING },      "구구",{  40, 45, 40, 35, 35, 56 },{ 18,      피죤 },MDSL, 55,255 },
	{       피죤,{ NORMAL,FLYING },      "피죤",{  63, 60, 55, 50, 50, 71 },{ 36,    피죤투 },MDSL,113,120 },
	{     피죤투,{ NORMAL,FLYING },    "피죤투",{  83, 80, 75, 70, 70,101 },{ -1,        -1 },MDSL,172, 45 },
																								 	  
	{     피카츄,       { ELECTR },    "피카츄",{  35, 55, 30, 50, 50, 90 },{ 36,    라이츄 },MDFA, 82,190 },
	{     라이츄,       { ELECTR },    "라이츄",{  60, 90, 55, 90, 80,100 },{ -1,        -1 },MDFA,122, 75 },
};
// { ,{  },"",{ ,,,,, },{ , }, },