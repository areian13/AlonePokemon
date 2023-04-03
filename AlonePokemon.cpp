#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>

#include "PokemonTribe.h"
#include "Trainer.h"

using namespace std;

int main()
{
	/*vector<PokemonTribe> poke;
	MakePokemonTribeList(poke);
	for (int i = 1; i <= NUMBER_OF_POKEMON; i++)
	{
		cout << poke[i];
	}*/

	/*while (true)
	{
		printf("1. 대전\n");
		printf("2. 수집\n");
		printf("3. 가방\n");
		printf("4. 포켓몬 센터\n");
		printf("0. 게임 종료\n");

		printf("모드를 선택하십시오: ");
		int mode;
		scanf("%d", &mode);
		switch (mode)
		{
		case 1:
			battlemode();
			break;

		case 2:
			collectmode();
			break;

		case 3:
			openbag();
			break;

		case 4:
			gotocenter();
			break;
			
		default:
			printf("잘못 선택하셨습니다. 다시 눌러주세요.\n\n");
			break;
		}
	}*/

	Trainer player;
}