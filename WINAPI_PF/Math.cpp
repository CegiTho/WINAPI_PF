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

Vector2 Math::SineInterpolation(Vector2 start, Vector2 end, double period, double time)
{
	Vector2 diff = end - start;
	double per = 0.5 * (1 - (cos((PI / period) * time)));
	return start + diff * per;
}
