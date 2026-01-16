#include "../include/LogBuffer.h"
#include <iostream>

// default
LogBuffer::LogBuffer()
{
	std::cout << "LogBuffer: Default Constructor" << std::endl;
}

// copy
LogBuffer::LogBuffer(const LogBuffer& other) : data(other.data)
{
	std::cout << "LogBuffer: Copy Constructor" << std::endl;
}

// move
LogBuffer::LogBuffer(LogBuffer&& other) noexcept : data(std::move(other.data))
{
	std::cout << "LogBuffer: Move Constructor" << std::endl;
}