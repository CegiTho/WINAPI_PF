#include "Framework.h"

int Math::Random(int min, int max)
{
	return (rand() % (max - min)) + min;
	//min <= value < max ..... max�� ���� �Ƚ�Ű�°� �ε��������ɷ� ���� ����.
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
