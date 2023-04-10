#define _CRT_SECURE_NO_WARNINGS

#include <array>
#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace std;

#include "Trainer.h"

Trainer player;

//void OpenBagInMain()
//{
//	printf("1. 내 포켓몬 보기");
//}
void ShowHangingPokemon()
{
	for (int i = 0; i < MAX_HANGING_POKEMON; i++)
	{
		IndivPokemon p = player.m_hangingPokeList[i];

		printf("%d: ", i + 1);
		if (!p.IsEmpty())
		{
			printf("%s [ 전투 %s ]\n", p.m_name.c_str(), !p.IsDead() ? "가능" : "불능");
			printf("Lv: %d\n", p.m_level);
			printf("HP: %d / %d\n", p.m_currentHealth, p.m_stats.health);
		}
		else
			printf("지정된 포켓몬이 없습니다.\n");
		printf("\n");
	}
}
void SwapFightPokemon(IndivPokemon& fightPokemon)
{
	ShowHangingPokemon();

	printf("교체할 포켓몬을 선택해주십시오: ");
	while (true)
	{
		int choice;
		scanf("%d", &choice);
		choice--; // 눈에 보이는 번호와 실제 인덱스는 1차이
		if(player.m_hangingPokeList[choice].IsEmpty())
			printf("지정된 포켓몬이 없습니다. 다시 선택해주세요.\n");
		else if (player.m_hangingPokeList[choice].IsDead())
			printf("전투 불능인 포켓몬입니다. 다시 선택해주세요.\n");
		else if (choice == player.m_fightPokemonIndex)
			printf("현재 전투 중인 포켓몬입니다. 다시 선택해주세요.\n");
		else
		{
			player.m_hangingPokeList[player.m_fightPokemonIndex] = fightPokemon;
			player.m_fightPokemonIndex = choice;
			fightPokemon = player.m_hangingPokeList[choice];
			break;
		}
	}
	
}
int MyAttackAndCheckWhileCaptureMode(IndivPokemon& fightPokemon, IndivPokemon& enemyPokemon)
{
	printf("가랏 %s!!! 공격해!!!\n", fightPokemon.m_name.c_str());
	fightPokemon.Attack(enemyPokemon);
	if (enemyPokemon.m_currentHealth <= 0)
	{
		enemyPokemon.m_currentHealth = 0;
		printf("%s를 물리쳤다\n", enemyPokemon.m_tribe.m_name.c_str());
		int getExp = enemyPokemon.m_tribe.m_baseExpYield * enemyPokemon.m_level / 7;
		fightPokemon.GetExp(getExp);
		player.m_hangingPokeList[player.m_fightPokemonIndex] = fightPokemon;
		return 0;
	}
	return 1;
}
int EnemyAttackAndCheckWhileCaptureMode(IndivPokemon& fightPokemon, IndivPokemon& enemyPokemon)
{
	printf("적 %s(이)가 %s(을)를 공격했다..!\n", enemyPokemon.m_tribe.m_name.c_str(), fightPokemon.m_name.c_str());
	enemyPokemon.Attack(fightPokemon);
	
	if (fightPokemon.m_currentHealth <= 0)
	{
		fightPokemon.m_currentHealth = 0;
		player.m_hangingPokeList[player.m_fightPokemonIndex] = fightPokemon;
		printf("%s(이)가 쓰러졌다..\n", fightPokemon.m_name.c_str());

		if (player.IsAllDead())
		{
			printf("더 이상 싸울 수 있는 포켓몬이 없다..\n");
			printf("당신은 눈 앞이 깜깜해져 정신 없이 도망치며 포켓몬 센터로 향했다...\n");
			
			return 0;
		}

		printf("포켓몬을 교체하시겠습니까?\n");
		printf("1. 교체\n");
		printf("2. 도망\n");

		int choice;
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			SwapFightPokemon(fightPokemon);
			return 2;
			break;

		case 2:
			printf("당신은 비겁하게 도망쳤습니다..\n");
			player.m_hangingPokeList[player.m_fightPokemonIndex] = fightPokemon;
			return 0;
			break;
		}
	}
	return 1;
}

void CaptureMode()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> probOfOccur(1, NUMBER_OF_POKEMON); 
	// 그냥 probOfOccur(gen)이라 치면 1~마지막포켓몬 넘버까지 랜덤하게 나오는 코드

	IndivPokemon fightPokemon = player.m_hangingPokeList[player.m_fightPokemonIndex];

	int enemyPokemonLevel = fightPokemon.m_level - 2;
	int enemyPokemonDicNum = probOfOccur(gen);
	IndivPokemon enemyPokemon(enemyPokemonDicNum, enemyPokemonLevel);
	printf("야생의 %s(이)가 나타났다!\n", enemyPokemon.m_name.c_str());
	printf("가랏 %s!!\n", fightPokemon.m_name.c_str());

	// 1은 현재 수집 모드를 진행중, 0은 진행 종료
	// 근데 왜 int냐? 포켓몬을 교체하거나 밥멕이면 상대한테 턴이 넘어가야되는데 교체했다는걸 2로 표시하기 위해서 int 사용
	int captureModeNum = 1;
	while (captureModeNum != 0)
	{
		printf("상대 %s의 HP: %d / %d\n", enemyPokemon.m_tribe.m_name.c_str(), enemyPokemon.m_currentHealth, enemyPokemon.m_stats.health);
		printf("내 %s의 HP: %d / %d\n", fightPokemon.m_name.c_str(), fightPokemon.m_currentHealth, fightPokemon.m_stats.health);
		printf("1. 공격\n");
		printf("2. 가방\n");
		printf("3. 도망\n");
		printf("4. 교체\n");

		int choice;
		scanf("%d", &choice);
		switch (choice)
		{
		case 1: // 공격: 스피드에 따라 누가 먼저 공격하냐가 달라지므로 구별
		{
			bool isFirstAttack = fightPokemon.m_stats.speed >= enemyPokemon.m_stats.speed;
			if (isFirstAttack)
			{
				captureModeNum = MyAttackAndCheckWhileCaptureMode(fightPokemon, enemyPokemon);
				if (captureModeNum == 0)
					break;
			}

			captureModeNum = EnemyAttackAndCheckWhileCaptureMode(fightPokemon, enemyPokemon);
			if (captureModeNum == 0)
				break;

			if (captureModeNum == 2) // 상대가 선빵 때려서 죽었을 때, 교체를 선택하면 교체 자체가 하나의 턴을 소모하므로 바로 내턴이 종료된다.
			{
				captureModeNum = 1;
				break;
			}

			if (!isFirstAttack)
			{
				captureModeNum = MyAttackAndCheckWhileCaptureMode(fightPokemon, enemyPokemon);
				if (captureModeNum == 0)
					break;
			}
			break;
		}
		case 2: 
		{
			bool isOpeningBag = true;
			while (isOpeningBag)
			{
				int choice = player.OpenBag();
				if (choice == 0)
					break;

				// 몬스터볼 던지기
				if (choice == 1) 
				{
					bool isSelecting = true;
					while (isSelecting)
					{
						player.ShowMonsterBallList();
						printf("어떤 볼을 던지겠습니까?(뒤로가기: 0): ");
						int ballIdx;
						scanf("%d", &ballIdx);
						if (ballIdx == 0)
							break;

						ballIdx--;

						if (player.m_balls[ballIdx].m_count <= 0)
						{
							printf("볼의 개수가 부족합니다. 다시 선택하십시오.\n");
							continue;
						}
						player.ThrowMonsterBall(ballIdx, enemyPokemon);
						isOpeningBag = false;
						captureModeNum = 0;
						break;
					}
				}
				// 회복약 먹이기
				if (choice == 2)
				{
					bool isSelecting = true;
					while (isSelecting)
					{
						player.ShowMonsterPotionList();
						printf("어떤 포션을 먹이겠습니까?(뒤로가기: 0): ");
						int potionIdx;
						scanf("%d", &potionIdx);
						if (potionIdx == 0)
							break;

						potionIdx--;

						if (player.m_potions[potionIdx].m_count <= 0)
						{
							printf("포션의 개수가 부족합니다. 다시 선택하십시오.\n");
							continue;
						}
						player.GivePotion(potionIdx, fightPokemon);
						captureModeNum = EnemyAttackAndCheckWhileCaptureMode(fightPokemon, enemyPokemon);
						isOpeningBag = false;
						break;
					}
				}
			}
			break;
		}
		case 3: // 포기
		{
			printf("당신은 비겁하게 도망쳤습니다..\n");
			player.m_hangingPokeList[player.m_fightPokemonIndex] = fightPokemon;
			captureModeNum = 0;
			break;
		}
		case 4: // 교체: 교체 후 턴이 적에게 넘어가기 때문에 공격을 한대 맞는다.
		{
			SwapFightPokemon(fightPokemon);
			captureModeNum = EnemyAttackAndCheckWhileCaptureMode(fightPokemon, enemyPokemon);
			break;
		}
		}
	}
}

void LoadFile()
{
	// 만약 게임을 처음 실행한다면(= 세이브파일이 존재하지 않고)  포켓몬 선택 실행
	if (player.IsAllDead())
	{
		printf("오박사: 무슨 포켓몬을 얻고 싶니?\n");
		printf("1. 이상해씨\n");
		printf("2. 파이리\n");
		printf("3. 꼬부기\n");

		int choice;
		scanf("%d", &choice);
		player.TakeNewPokemon((choice - 1) * 3 + 1);
	}
}
void Gaming()
{
	while (true)
	{
		printf("1. 대전모드\n");
		printf("2. 수집모드\n");
		printf("3. 가방보기\n");
		printf("4. 포켓몬 센터 가기\n");
		printf("0. 게임 종료\n");

		int choice;
		scanf("%d", &choice);

		switch (choice)
		{
			// 대전모드(미구현)
		case 1:
		{

		}
		// 쌉구현
		case 2:
		{
			CaptureMode();
			break;
		}
		//여기에 맞는 OpenBag()가 아님 추후 구현
		case 3:
		{
			// player.OpenBag(); 
			break;
		}

		case 4:
		{
			player.GotoPokemonCenter();
			break;
		}
		case 0:
		{
			printf("게임을 종료합니다.");
			return;
			break;
		}
		}
	}
}
void SaveFile()
{

}

int main()
{
	LoadFile();
	Gaming();
	SaveFile();
}