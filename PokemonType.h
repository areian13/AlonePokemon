#include <array>
#include <string>
using namespace std;

#define NUMBER_OF_TYPE 15

enum PokemonType
{
	NORMAL,
	FIRE,
	WATER,
	GRASS,
	ELECTR,
	ICE,
	FIGTH,
	POISON,
	GROUND,
	FLYING,
	PSYSHC,
	BUG,
	ROCK,
	GHOST,
	DRAGON
};

#define POOR 0.5F
#define NICE 2.0F
#define JUST 1.0F
#define DONT 0.0F

array<array<float, NUMBER_OF_TYPE>, NUMBER_OF_TYPE> typeMatchingTable =
{
	array<float, NUMBER_OF_TYPE>
	{ 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, POOR, DONT, 1.0F },
	{ 1.0F, POOR, POOR, NICE, 1.0F, NICE, 1.0F, 1.0F, POOR, 1.0F, 1.0F, NICE, POOR, 1.0F, POOR },
	{ 1.0F, NICE, POOR, POOR, 1.0F, 1.0F, 1.0F, 1.0F, NICE, 1.0F, 1.0F, 1.0F, NICE, 1.0F, POOR },
	{ 1.0F, POOR, NICE, POOR, 1.0F, 1.0F, 1.0F, POOR, NICE, POOR, 1.0F, 1.0F, NICE, 1.0F, POOR },
	{ 1.0F, 1.0F, NICE, POOR, POOR, 1.0F, 1.0F, 1.0F, DONT, NICE, 1.0F, 1.0F, 1.0F, 1.0F, NICE },
	{ 1.0F, 1.0F, POOR, NICE, 1.0F, POOR, 1.0F, 1.0F, NICE, NICE, 1.0F, 1.0F, 1.0F, 1.0F, NICE },
	{ NICE, 1.0F, 1.0F, 1.0F, 1.0F, NICE, 1.0F, POOR, 1.0F, POOR, POOR, POOR, NICE, DONT, 1.0F },
	{ 1.0F, 1.0F, 1.0F, NICE, 1.0F, 1.0F, 1.0F, POOR, POOR, 1.0F, 1.0F, NICE, POOR, POOR, 1.0F },
	{ 1.0F, NICE, 1.0F, POOR, NICE, 1.0F, 1.0F, NICE, 1.0F, DONT, 1.0F, POOR, NICE, 1.0F, 1.0F },
	{ 1.0F, 1.0F, 1.0F, NICE, POOR, 1.0F, NICE, 1.0F, 1.0F, 1.0F, 1.0F, NICE, POOR, 1.0F, 1.0F },
	{ 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, NICE, NICE, 1.0F, 1.0F, POOR, 1.0F, 1.0F, 1.0F, 1.0F },
	{ 1.0F, POOR, 1.0F, NICE, 1.0F, 1.0F, POOR, NICE, 1.0F, POOR, NICE, 1.0F, 1.0F, POOR, 1.0F },
	{ 1.0F, NICE, 1.0F, 1.0F, 1.0F, NICE, POOR, 1.0F, POOR, NICE, 1.0F, NICE, 1.0F, 1.0F, 1.0F },
	{ DONT, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, DONT, 1.0F, 1.0F, NICE, 1.0F },
	{ 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, NICE },
};

array<string, NUMBER_OF_TYPE> stringType =
{
	"NORMAL",
	"FIRE",
	"WATER",
	"GRASS",
	"ELECTR",
	"ICE",
	"FIGTH",
	"POISON",
	"GROUND",
	"FLYING",
	"PSYSHC",
	"BUG",
	"ROCK",
	"GHOST",
	"DRAGON"
};