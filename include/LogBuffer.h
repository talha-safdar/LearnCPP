#pragma once
#include <vector>

class LogBuffer
{
public:
	std::vector<int> data;

	LogBuffer();
	LogBuffer(const LogBuffer& other);
	LogBuffer(LogBuffer&& other) noexcept;
};