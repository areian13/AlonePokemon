// ������ �������� �����ϴ� Ŭ����
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
	int health; // ü��
	int attack; // ����
	int block; // ���
	int contact; // Ư��
	int defense; // Ư��
	int speed; // �ӵ�

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
	FAST, // ����
	MDFA, // �߰�����
	MDSL, // �߰�����
	SLOW,  // ����
};

class PokemonTribe
{
public:
	int m_dicNum; // ���� ��ȣ
	vector<PokemonType> m_types; // ���� �ִ� Ÿ��(��)
	string m_name; // ���� �̸� ex) �̻��ؾ�
	TribeValue m_tribeValue; // ����ġ HABCDS
	Evo m_evo; // ��ȭ�� �� ���� + ��ȭ�� ���ϸ��� ���� ��ȣ
	ExpFormulaIndex m_expFormulaIndex; // '������ ���� �ʿ� ����ġ ����'�� ���� �ε���
	int m_baseExpYield; // ������ �й��Ͽ��� �� ��뿡�� �ִ� ����ġ��
	int m_catchRate; // ������ ��ȹ��
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
	�����,

	�̻��ؾ�,
	�̻���Ǯ,
	�̻��ز�,

	���̸�,
	���ڵ�,
	���ڸ�,

	���α�,
	��Ϻα�,
	�źϿ�,

	ĳ����,
	�ܵ���,
	������,

	����,
	����,
	������,

	��ī��,
	������
};

vector<PokemonTribe> pokemonDic =
{
	{     �����,       { PSYSHC },    "�����",{ 999,999,999,999,999,999 },{ -1,        -1 },FAST,999,255 },
																								  	  
	{   �̻��ؾ�, { GRASS,POISON },  "�̻��ؾ�",{  45, 49, 49, 65, 65, 45 },{ 16,  �̻���Ǯ },MDSL, 64, 45 },
	{   �̻���Ǯ, { GRASS,POISON },  "�̻���Ǯ",{  60, 62, 63, 80, 80, 60 },{ 32,  �̻��ز� },MDSL,141, 45 },
	{   �̻��ز�, { GRASS,POISON },  "�̻��ز�",{  80, 82, 83,100,100, 80 },{ -1,        -1 },MDSL,208, 45 },
																								  	  
	{     ���̸�,         { FIRE },    "���̸�",{  39, 52, 43, 60, 50, 65 },{ 16,    ���ڵ� },MDSL, 65, 45 },
	{     ���ڵ�,         { FIRE },    "���ڵ�",{  58, 64, 58, 80, 65, 80 },{ 36,    ���ڸ� },MDSL,142, 45 },
	{     ���ڸ�,  { FIRE,FLYING },    "���ڸ�",{  78, 84, 78,109, 85,100 },{ -1,        -1 },MDSL,209, 45 },
																								  	  
	{     ���α�,        { WATER },    "���α�",{  44, 48, 65, 50, 64, 43 },{ 16,  ��Ϻα� },MDSL, 66, 45 },
	{   ��Ϻα�,        { WATER },  "��Ϻα�",{  59, 63, 80, 65, 80, 58 },{ 36,    �źϿ� },MDSL,143, 45 },
	{     �źϿ�,        { WATER },    "�źϿ�",{  79, 83,100, 85,105, 78 },{ -1,        -1 },MDSL,210, 45 },
																								  	  
	{     ĳ����,          { BUG },    "ĳ����",{  45, 30, 35, 20, 20, 45 },{  7,    �ܵ��� },MDFA, 53,255 },
	{     �ܵ���,          { BUG },    "�ܵ���",{  50, 20, 55, 25, 25, 30 },{ 10,    ������ },MDFA, 72,120 },
	{     ������,   { BUG,FLYING },    "������",{  60, 45, 50, 80, 80, 70 },{ -1,        -1 },MDFA,160, 45 },
																								  	  
	{       ����,{ NORMAL,FLYING },      "����",{  40, 45, 40, 35, 35, 56 },{ 18,      ���� },MDSL, 55,255 },
	{       ����,{ NORMAL,FLYING },      "����",{  63, 60, 55, 50, 50, 71 },{ 36,    ������ },MDSL,113,120 },
	{     ������,{ NORMAL,FLYING },    "������",{  83, 80, 75, 70, 70,101 },{ -1,        -1 },MDSL,172, 45 },
																								 	  
	{     ��ī��,       { ELECTR },    "��ī��",{  35, 55, 30, 50, 50, 90 },{ 36,    ������ },MDFA, 82,190 },
	{     ������,       { ELECTR },    "������",{  60, 90, 55, 90, 80,100 },{ -1,        -1 },MDFA,122, 75 },
};
// { ,{  },"",{ ,,,,, },{ , }, },