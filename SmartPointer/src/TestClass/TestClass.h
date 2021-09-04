#pragma once
#include <cstdint>

static uint32_t s_id = 0;

class TestClass
{
public:
	uint32_t id = ++s_id;
};

