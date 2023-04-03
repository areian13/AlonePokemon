#include <vector>
#include <string>

#include "PokemonTribe.h"

using namespace std;

class Trainer
{
private:
	struct MonsterBall
	{
	private:
		int ballCnt;

	public:
		MonsterBall()
		{
			ballCnt = 0;
		}
		MonsterBall(int n)
		{
			ballCnt = n;
		}

		int CountBall()
		{
			return ballCnt;
		}
		void GetNewBall(int n)
		{
			printf("몬스터볼 %d개를 얻었다.\n", n);
			ballCnt += n;
		}

		bool IsAvailBall()
		{
			return ballCnt >= d;
		}
		void ThrowBall()
		{
			if (IsAvailBall())
			{
				printf("가랏 몬스터볼~!\n");
				ballCnt--;
			}
			else
			{
				printf("몬스터볼의 개수가 부족해 사용할 수 없습니다.\n");
			}
		}
	};
	struct Candy
	{
	private:
		int candyCnt;

	public:
		Candy()
		{
			candyCnt = 0;
		}
		Candy(int n)
		{
			candyCnt = n;
		}

		int CountCandy()
		{
			return candyCnt;
		}
		void GetNewCandy(int n)
		{
			candyCnt += n;
		}

		bool IsAvailCandy(int n)
		{
			return candyCnt >= n;
		}
		void UseCandy(int n)
		{
			if (IsAvailCandy(n))
			{
				printf("캔디를 %d개 사용하였습니다.\n", n);
				candyCnt -= n;
			}
			else
			{
				printf("캔디가 부족합니다.\n");
			}
		}

	};
	class TrainerPokemon
	{
		int m_pokeLevel;
		string m_pokeName;
		PokemonTribe m_pokeTribe;


	};

	MonsterBall m_ball;
	Candy m_candy;



};