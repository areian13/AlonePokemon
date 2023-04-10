#pragma once

#include "PokemonTribe.h"

class IndivPokemon
{
private:
	
public:
	int m_dicNum;
	bool m_isCustomName;

	int m_level;
	int m_exp;
	int m_maxExp;
	PokemonTribe m_tribe;
	TribeValue m_stats; // 결과론적인 능력치이지만 TribeValue 구조체랑 똑같이 생겨서 갖다 썼어요

	int m_currentHealth;
	string m_name;

	IndivPokemon()
	{
		m_dicNum = 0;
		m_currentHealth = 0;
	}
	// 레벨 설정을 안하고 부를 경우 자동으로 5레벨로 인스턴스 생성
	IndivPokemon(int dicNum) 
	{
		m_dicNum = dicNum;
		m_level = 5;
		m_exp = 0;

		m_tribe = pokemonDic[dicNum];
		m_maxExp = m_tribe.MaxExpByLevel(m_level);
		m_stats = m_tribe.StatsByLevel(m_level);

		m_currentHealth = m_stats.health;

		m_name = m_tribe.m_name;
		m_isCustomName = false;
	}
	// 레벨 설정 가능
	IndivPokemon(int dicNum, int level)
	{
		m_dicNum = dicNum;
		m_level = level;
		m_exp = 0;

		m_tribe = pokemonDic[dicNum];
		m_maxExp = m_tribe.MaxExpByLevel(m_level);
		m_stats = m_tribe.StatsByLevel(m_level);

		m_currentHealth = m_stats.health;

		m_name = m_tribe.m_name;
		m_isCustomName = false;
	}

	// m_dicNum == 0일 경우, 즉 할당된 포켓몬이 없는 경우 비어있다고 표현
	bool IsEmpty()
	{
		return m_dicNum == 0;
	}
	void GetExp(int exp)
	{
		if (m_level == 100)
			exp = 0;
		m_exp += exp;
		printf("%d만큼의 경험치를 얻었다!\n", exp);
		if (m_exp >= m_maxExp)
			LevelUp();
	}
	void LevelUp(bool isUsedCandy = false)
	{
		if (isUsedCandy)
		{
			m_level++;
			return;
		}

		while (m_exp >= m_maxExp)
		{
			m_level++;
			printf("레벨이 %d로 올랐다!\n", m_level);
			m_exp -= m_maxExp;

			if (m_level >= m_tribe.GetEvoValue().evoLevel && !m_tribe.IsLastEvo())
			{
				printf("엇?! %s의 모습이???\n", m_name.c_str());
				printf("진화시키겠습니까?(y,n)\n");
				char cond;
				cin >> cond;

				if (cond == 'y' || cond == 'Y')
				{
					printf("%s(이)가 ", m_tribe.m_name.c_str());
					m_tribe.Evolution(pokemonDic);
					printf("%s(으)로 진화했다!\n", m_tribe.m_name.c_str());

					m_dicNum = m_tribe.m_dicNum;
					if (!m_isCustomName)
						m_name = m_tribe.m_name;
				}
				else
				{
					printf("아무 일도 없었다~\n");
				}
			}
			m_maxExp = m_tribe.MaxExpByLevel(m_level);
			m_stats = m_tribe.StatsByLevel(m_level);

			if (m_level == 100)
			{
				m_exp = 0;
				break;
			}
		}
	}

	void Attack(IndivPokemon& other)
	{
		float coef = GetTypeMachingCoef(other); // 타입상성 계수

		if (coef >= NICE)
			printf("효과가 굉장했다!\n");
		else if (coef == DONT)
			printf("효과가 없는 것 같다...\n");
		else if (coef <= POOR)
			printf("효과가 별로인 듯 하다...\n");
		
		// 앞에 40은 기술에 따른 위력이지만, 몸통박치기밖에 없으니 걍 40 고정

		int damage = 40 * coef * m_stats.attack / other.m_stats.block; 
		other.m_currentHealth -= damage;
	}
	float GetTypeMachingCoef(IndivPokemon other)
	{
		float result = 1.0F;
		for (PokemonType attackType : m_tribe.m_types)
		{
			for (PokemonType defenseType : other.m_tribe.m_types)
			{
				result *= typeMatchingTable[attackType][defenseType];
			}
		}
		return result;
	}

	int GetCurrentHealth()
	{
		return m_currentHealth;
	}
	bool IsDead()
	{
		return m_currentHealth == 0;
	}
	TribeValue GetStats()
	{
		return m_stats;
	}
	string GetName()
	{
		return m_name;
	}
	void FullRestore()
	{
		m_currentHealth = m_stats.health;
	}
	
	void SetCustomName(string name)
	{
		m_name = name;
		m_isCustomName = true;
	}
	void DeleteCustomName()
	{
		m_name = m_tribe.m_name;
		m_isCustomName = false;
	}

	void PrintThisPokemonDetailInfo()
	{
		printf("No.%d %s\n", m_dicNum, m_name.c_str());
		printf("Lv: %d\n", m_level);
		printf("Type: ");
		for (PokemonType type : m_tribe.m_types)
		{
			printf("%s ", stringType[type].c_str());
		}
		printf("\n\n");
	}

	friend ostream& operator<<(ostream& os, IndivPokemon indivPokemon)
	{
		if (indivPokemon.IsEmpty())
		{
			os << "지정된 포켓몬이 없습니다.";
			return os;
		}

		os << indivPokemon.m_dicNum << ' ';
		os << indivPokemon.m_name << ' ';
		os << indivPokemon.m_level << ' ';
		os << indivPokemon.m_stats << '\n';
		os << indivPokemon.m_tribe;
		return os;
	}
};