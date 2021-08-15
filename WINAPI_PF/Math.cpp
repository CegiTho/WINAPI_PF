#include "Framework.h"

int Math::Random(int min, int max)
{
	return (rand() % (max - min)) + min;
	//min <= value < max ..... max는 포함 안시키는게 인덱스같은걸로 쓰기 좋음.
}

double Math::Random(double min, double max)
{
	double random = (double)rand() / (double)RAND_MAX;
	return min + (max - min) * random;
}

Vector2 Math::RandomPoint(double min, double max)
{
	return Vector2(Math::Random(min, max), Math::Random(min, max));
}
