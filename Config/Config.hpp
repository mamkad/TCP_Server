#pragma once

#include "../Json/Json.hpp"

class Config final
{
private:
	Json jsonFile;
public:
	Config();
};