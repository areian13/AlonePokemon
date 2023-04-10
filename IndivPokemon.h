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
	TribeValue m_stats; // ��������� �ɷ�ġ������ TribeValue ����ü�� �Ȱ��� ���ܼ� ���� ����

	int m_currentHealth;
	string m_name;

	IndivPokemon()
	{
		m_dicNum = 0;
		m_currentHealth = 0;
	}
	// ���� ������ ���ϰ� �θ� ��� �ڵ����� 5������ �ν��Ͻ� ����
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
	// ���� ���� ����
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

	// m_dicNum == 0�� ���, �� �Ҵ�� ���ϸ��� ���� ��� ����ִٰ� ǥ��
	bool IsEmpty()
	{
		return m_dicNum == 0;
	}
	void GetExp(int exp)
	{
		if (m_level == 100)
			exp = 0;
		m_exp += exp;
		printf("%d��ŭ�� ����ġ�� �����!\n", exp);
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
			printf("������ %d�� �ö���!\n", m_level);
			m_exp -= m_maxExp;

			if (m_level >= m_tribe.GetEvoValue().evoLevel && !m_tribe.IsLastEvo())
			{
				printf("��?! %s�� �����???\n", m_name.c_str());
				printf("��ȭ��Ű�ڽ��ϱ�?(y,n)\n");
				char cond;
				cin >> cond;

				if (cond == 'y' || cond == 'Y')
				{
					printf("%s(��)�� ", m_tribe.m_name.c_str());
					m_tribe.Evolution(pokemonDic);
					printf("%s(��)�� ��ȭ�ߴ�!\n", m_tribe.m_name.c_str());

					m_dicNum = m_tribe.m_dicNum;
					if (!m_isCustomName)
						m_name = m_tribe.m_name;
				}
				else
				{
					printf("�ƹ� �ϵ� ������~\n");
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
		float coef = GetTypeMachingCoef(other); // Ÿ�Ի� ���

		if (coef >= NICE)
			printf("ȿ���� �����ߴ�!\n");
		else if (coef == DONT)
			printf("ȿ���� ���� �� ����...\n");
		else if (coef <= POOR)
			printf("ȿ���� ������ �� �ϴ�...\n");
		
		// �տ� 40�� ����� ���� ����������, �����ġ��ۿ� ������ �� 40 ����

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
			os << "������ ���ϸ��� �����ϴ�.";
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