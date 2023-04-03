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
			printf("���ͺ� %d���� �����.\n", n);
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
				printf("���� ���ͺ�~!\n");
				ballCnt--;
			}
			else
			{
				printf("���ͺ��� ������ ������ ����� �� �����ϴ�.\n");
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
				printf("ĵ�� %d�� ����Ͽ����ϴ�.\n", n);
				candyCnt -= n;
			}
			else
			{
				printf("ĵ�� �����մϴ�.\n");
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