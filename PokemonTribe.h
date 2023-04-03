// ������ �������� �����ϴ� Ŭ����
#pragma once

#include <string>
#include <vector>
#include <array>

#include "PokemonType.h";

#define NUMBER_OF_POKEMON 11

using namespace std;

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
};

class PokemonTribe
{
public:
	int m_index; // ���� ��ȣ
	vector<PokemonType> m_types;
	string m_name; // ���� �̸� ex) �̻��ؾ�

private:
	TribeValue m_tribeValue; // ����ġ
	Evo m_evo;

public:
	PokemonTribe()
	{

	}
	// ������ȣ, Ÿ��(��), �̸�, HABCDS, ��ȭ ����
	PokemonTribe(int index, vector<PokemonType> types, string name, TribeValue tribeValue, Evo evo)
	{
		m_index = index;
		m_types = types;
		m_name = name;
		m_tribeValue = tribeValue;
		m_evo = evo;
	}

	friend void MakePokemonTribeList(vector<PokemonTribe>& pokemonTribeList)
	{
		pokemonTribeList.resize(NUMBER_OF_POKEMON + 1);
		// ������ȣ, �Ӽ�(��), �̸�, HABCDS, ��ȭ����
		pokemonTribeList[ 1] = {  1,      { GRASS },"�̻��ؾ�",{  45, 49, 49, 65, 65, 45 },{ 16,  2 } };
		pokemonTribeList[ 2] = {  2,      { GRASS },"�̻���Ǯ",{  60, 62, 63, 80, 80, 60 },{ 32,  3 } };
		pokemonTribeList[ 3] = {  3,      { GRASS },"�̻��ز�",{  80, 82, 83,100,100, 80 },{ -1, -1 } };
						  		  							     	 	 		 	 	   
		pokemonTribeList[ 4] = {  4,       { FIRE },  "���̸�",{  39, 52, 43, 60, 50, 65 },{ 16,  5 } };
		pokemonTribeList[ 5] = {  5,       { FIRE },  "���ڵ�",{  58, 64, 58, 80, 65, 80 },{ 36,  6 } };
		pokemonTribeList[ 6] = {  6,{ FIRE,FLYING },  "���ڸ�",{  78, 84, 78,109, 85,100 },{ -1, -1 } };

		pokemonTribeList[ 7] = {  7,      { WATER },  "���α�",{  44, 48, 65, 50, 64, 43 },{ 16,  8 } };
		pokemonTribeList[ 8] = {  8,      { WATER },"��Ϻα�",{  59, 63, 80, 65, 80, 58 },{ 36,  9 } };
		pokemonTribeList[ 9] = {  9,      { WATER },  "�źϿ�",{  79, 83,100, 85,105, 78 },{ -1, -1 } };
						  									     	 					
		pokemonTribeList[10] = { 10,     { ELECTR },  "��ī��",{  35, 55, 30, 50, 50, 90 },{ 36, 11 } };
		pokemonTribeList[11] = { 11,     { ELECTR },  "������",{  60, 90, 55, 90, 80,100 },{ -1, -1 } };
	}
	friend ostream& operator<<(ostream& os, PokemonTribe tribe)
	{
		os << tribe.m_index << ' ' << tribe.m_name << ' ';
		for (PokemonType type : tribe.m_types)
			os << stringType[type] << ' ';
		os << '\n';
		return os;
	}
};

