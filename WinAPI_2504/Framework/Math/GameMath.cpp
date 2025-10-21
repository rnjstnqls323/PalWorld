#include "Framework.h"

bool GameMath::IsPointBetweenVectors(const Vector2& origin, const Vector2& leftPoint, const Vector2& rightPoint, const Vector2& testPoint)
{
	Vector2 leftDir = leftPoint - origin;
	Vector2 rightDir = rightPoint - origin;

	Vector2 pointDir = testPoint - origin;

	float crossLeft = Vector2::Cross(pointDir, leftDir);
	float crossRight = Vector2::Cross(pointDir, rightDir);

	return crossLeft * crossRight < 0;
}

int GameMath::Random(const int& min, const int& max)
{
	return rand() % (max - min) + min;
}

float GameMath::Random(const float& min, const float& max)
{
	float normal = rand() / (float)RAND_MAX; // 0.0f ~ 1.0f

	return min + (max - min) * normal;
}

float GameMath::Clamp(const float& value, const float& min, const float& max)
{
	if (value < min) return min;
	if (value > max) return max;

	return value;
}

bool GameMath::NearlyEqual(const float& s1, const float& s2)
{
	return abs(s1 - s2) < FLT_EPSILON;
}

Vector3 GameMath::ClosestPointOnLineSegment(const Vector3& point, const Vector3& a, const Vector3& b)
{
	Vector3 ab = b - a;
	Vector3 ap = point - a;

	float abLengthSq = Vector3::Dot(ab, ab);  // 선분 길이 제곱

	if (abLengthSq == 0.0f)
		return a;

	float t = Vector3::Dot(ap, ab) / abLengthSq;
	t = Clamp(t, 0.0f, 1.0f);

	return a + ab * t;
}
