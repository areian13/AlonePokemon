#pragma once

#include "IndivPokemon.h"

#define MAX_HANGING_POKEMON 3

class Trainer
{
private:
	struct Potion
	{
		string m_name;
		int m_healValue;
		int m_count;
		int m_cost;

		Potion()
		{

		}
		Potion(string name, int healValue, int count, int cost)
		{
			m_name = name;
			m_healValue = healValue;
			m_count = count;
			m_cost = cost;
		}
	};
	struct MonsterBall
	{
		string m_name;
		float m_catchRate;
		int m_count;
		int m_cost;

		MonsterBall()
		{

		}
		MonsterBall(string name, float catchRate, int count, int cost)
		{
			m_name = name;
			m_catchRate = catchRate;
			m_count = count;
			m_cost = cost;
		}
	};
	
public:
	array<IndivPokemon, MAX_HANGING_POKEMON> m_hangingPokeList;
	int m_fightPokemonIndex;
	vector<IndivPokemon> m_pokemonCenterList;
	int m_hangingPokeCnt;

	array<Potion, 4> m_potions;
	array<MonsterBall, 4> m_balls;
	int m_candys;

	Trainer()
	{
		m_potions =
		{
			Potion
			{     "상처약", 20, 5, 200 },
			{ "좋은상처약", 60, 0, 700 },
			{ "고급상처약",120, 0,1500 },
			{   "풀회복약", -1, 0,2500 },
		};
		m_balls =
		{
			MonsterBall
			{ "몬스터볼",1.0F, 5, 200 },
			{   "슈퍼볼",1.5F, 0, 600 },
			{ "하이퍼볼",2.0F, 0,1500 },
			{ "마스터볼", 255, 0,2500 },
		};
		m_candys = 0;
		m_hangingPokeCnt = 0;
		m_fightPokemonIndex = 0;
	}
	bool IsAllDead()
	{
		for (int i = 0; i < m_hangingPokeCnt; i++)
		{
			if (m_hangingPokeList[i].m_currentHealth > 0)
				return false;
		}
		return true;
	}
	void TakeNewPokemon(int dicNum, int level = 5)
	{
		IndivPokemon newPokemon = IndivPokemon(dicNum, level);
		printf("%s!!! 넌 내꺼야!!!\n", newPokemon.GetName().c_str());
		if (m_hangingPokeCnt == MAX_HANGING_POKEMON)
		{
			printf("들고 다닐 수 있는 포켓몬의 수를 넘어 %s(을)를 포켓몬 센터로 전송합니다.\n", newPokemon.GetName().c_str());
			m_pokemonCenterList.push_back(newPokemon);
			return;
		}
		m_hangingPokeList[m_hangingPokeCnt++] = newPokemon;
	}
	void TakeNewPokemon(IndivPokemon newPokemon)
	{
		printf("%s!!! 넌 내꺼야!!!\n", newPokemon.GetName().c_str());
		if (m_hangingPokeCnt == MAX_HANGING_POKEMON)
		{
			printf("들고 다닐 수 있는 포켓몬의 수를 넘어 %s(을)를 포켓몬 센터로 전송합니다.\n", newPokemon.GetName().c_str());
			m_pokemonCenterList.push_back(newPokemon);
			return;
		}
		m_hangingPokeList[m_hangingPokeCnt++] = newPokemon;
	}
	void PrintHangingPokemonList()
	{
		cout << "현재 데리고 있는 포켓몬: \n";
		for (int i = 0; i < MAX_HANGING_POKEMON; i++)
		{
			cout << m_hangingPokeList[i] << '\n';
		}
	}
	void PrintPokemonCenterList()
	{
		int idx = 1;
		for (IndivPokemon& indivPokemon : m_pokemonCenterList)
		{
			printf("[%d]\n", idx++);
			indivPokemon.PrintThisPokemonDetailInfo();
		}
	}

	void GotoPokemonCenter()
	{
		int isInPokemonCenter = true;
		while (isInPokemonCenter)
		{
			printf("1. 포켓몬 회복\n");
			printf("2. 포켓몬PC 보기\n");
			printf("3. 포켓몬 센터 나가기\n");

			printf("선택하십시오: ");
			int choice;
			scanf("%d", &choice);

			switch (choice)
			{
			case 1:
			{
				printf("\n포켓몬을 회복합니다.\n");
				printf("띵-띵- 띠로링~!\n");
				for (int i = 0; i < MAX_HANGING_POKEMON; i++)
				{
					m_hangingPokeList[i].FullRestore();
				}
				printf("회복이 완료되었습니다\n\n");
				break;
			}
			case 2:
			{
				printf("\n포켓몬PC를 열었다.\n");
				PrintPokemonCenterList();

				printf("포켓몬을 교체하시겠습니까?(y/n): ");
				char yn;
				scanf(" %c", &yn);
				if (yn == 'y' || yn == 'Y')
				{
					int idx = 1;
					for (IndivPokemon& indivPokemon : m_hangingPokeList)
					{
						printf("[%d]\n", idx++);
						indivPokemon.PrintThisPokemonDetailInfo();
					}
					printf("\n교체할 두 포켓몬의 인덱스를 입력하십시오.\n");
					printf("포켓몬 센터에 있는 포켓몬의 인덱스: ");
					int centerIdx;
					scanf("%d", &centerIdx);
					centerIdx--;
					printf("가지고 있는 포켓몬의 인덱스: ");
					int hangingIdx;
					scanf("%d", &hangingIdx);
					hangingIdx--;

					m_hangingPokeList[hangingIdx].FullRestore();
					IndivPokemon temp = m_hangingPokeList[hangingIdx];
					m_hangingPokeList[hangingIdx] = m_pokemonCenterList[centerIdx];
					m_pokemonCenterList[centerIdx] = temp;

					printf("포켓몬을 교환하였습니다.\n");
				}
				printf("포켓몬PC를 종료합니다.\n");
				break;
			}

			case 3:
				printf("포켓몬 센터에서 나갔다.\n\n");
				isInPokemonCenter = false;
				break;
			}
		}

	}
	void ShowMonsterBallList()
	{
		int idx = 1;
		for (MonsterBall& ball : m_balls)
		{
			printf("%d %s: %d개\n",idx++, ball.m_name.c_str(), ball.m_count);
		}
	}
	bool IsCatchSuccess(int idx, IndivPokemon& caughtPokemon)
	{
		int a = (3 * caughtPokemon.m_stats.health - 2 * caughtPokemon.m_currentHealth) * caughtPokemon.m_tribe.m_catchRate * m_balls[idx].m_catchRate / (3 * caughtPokemon.m_stats.health);

		int b = 65535 * sqrt(sqrt((double)a / 255)) + 0.5F; // 65535는 포켓몬에서 만든 랜덤 상수임.
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> random(0, 65535);

		for (int i = 0; i < 3; i++) // 4번 돌려서 하나라도 b보다 큰 값이 나오면 실패라 한다
		{
			printf("띵-\n");
			if (random(gen) > b)
				return false;
		}
		return random(gen) <= b;
	}
	void ThrowMonsterBall(int idx, IndivPokemon& caughtPokemon)
	{
		printf("가랏! 몬스터~볼~~!!!\n");
		m_balls[idx].m_count--;
		if (IsCatchSuccess(idx, caughtPokemon))
		{
			printf("찰칵!\n");
			TakeNewPokemon(caughtPokemon);
		}
		else
		{
			printf("펑!\n");
			printf("아 안돼..!\n");
			printf("%s(은)는 도망쳐 버렸다.\n", caughtPokemon.m_tribe.m_name.c_str());
		}
	}

	void ShowMonsterPotionList()
	{
		int idx = 1;
		for (Potion& potion : m_potions)
		{
			printf("%d %s: %d개\n", idx++, potion.m_name.c_str(), potion.m_count);
		}
	}
	void GivePotion(int idx, IndivPokemon& drinkingPokemon)
	{
		m_potions[idx].m_count--;
		drinkingPokemon.m_currentHealth += m_potions[idx].m_healValue;
		printf("%s의 피가 %d만큼 찼다.\n\n", drinkingPokemon.m_name.c_str(), m_potions[idx].m_healValue);
		if (drinkingPokemon.m_currentHealth > drinkingPokemon.m_stats.health) // 만약 최대체력 넘게 체력이 회복되면
			drinkingPokemon.FullRestore(); // 그냥 풀피가 되라.
	}
	int OpenBag()
	{
		printf("1. 몬스터볼\n");
		printf("2. 회복약\n");
		printf("3. 캔디\n");
		printf("0. 가방 닫기\n");
		printf("선택하십시오: ");
		int choice;
		scanf("%d", &choice);

		return choice;
	}
};