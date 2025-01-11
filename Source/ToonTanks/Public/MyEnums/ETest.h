#pragma once

enum class ETest : uint8
{
	Up UMETA(DisplayName = "Up"),
	Down UMETA(DisplayName = "Down"),
	Left UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right"),
	Count UMETA(Hidden),
};
ENUM_RANGE_BY_COUNT(ETest, ETest::Count);
//Iterable ENUM