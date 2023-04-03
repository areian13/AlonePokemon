// 고정된 종족값을 설정하는 클래스
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
	int health; // 체력
	int attack; // 공격
	int block; // 방어
	int contact; // 특공
	int defense; // 특방
	int speed; // 속도
};

class PokemonTribe
{
public:
	int m_index; // 도감 번호
	vector<PokemonType> m_types;
	string m_name; // 종족 이름 ex) 이상해씨

private:
	TribeValue m_tribeValue; // 종족치
	Evo m_evo;

public:
	PokemonTribe()
	{

	}
	// 도감번호, 타입(들), 이름, HABCDS, 진화 레벨
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
		// 도감번호, 속성(들), 이름, HABCDS, 진화레벨
		pokemonTribeList[ 1] = {  1,      { GRASS },"이상해씨",{  45, 49, 49, 65, 65, 45 },{ 16,  2 } };
		pokemonTribeList[ 2] = {  2,      { GRASS },"이상해풀",{  60, 62, 63, 80, 80, 60 },{ 32,  3 } };
		pokemonTribeList[ 3] = {  3,      { GRASS },"이상해꽃",{  80, 82, 83,100,100, 80 },{ -1, -1 } };
						  		  							     	 	 		 	 	   
		pokemonTribeList[ 4] = {  4,       { FIRE },  "파이리",{  39, 52, 43, 60, 50, 65 },{ 16,  5 } };
		pokemonTribeList[ 5] = {  5,       { FIRE },  "리자드",{  58, 64, 58, 80, 65, 80 },{ 36,  6 } };
		pokemonTribeList[ 6] = {  6,{ FIRE,FLYING },  "리자몽",{  78, 84, 78,109, 85,100 },{ -1, -1 } };

		pokemonTribeList[ 7] = {  7,      { WATER },  "꼬부기",{  44, 48, 65, 50, 64, 43 },{ 16,  8 } };
		pokemonTribeList[ 8] = {  8,      { WATER },"어니부기",{  59, 63, 80, 65, 80, 58 },{ 36,  9 } };
		pokemonTribeList[ 9] = {  9,      { WATER },  "거북왕",{  79, 83,100, 85,105, 78 },{ -1, -1 } };
						  									     	 					
		pokemonTribeList[10] = { 10,     { ELECTR },  "피카츄",{  35, 55, 30, 50, 50, 90 },{ 36, 11 } };
		pokemonTribeList[11] = { 11,     { ELECTR },  "라이츄",{  60, 90, 55, 90, 80,100 },{ -1, -1 } };
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

