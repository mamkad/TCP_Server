#pragma once

#include "../Json/Json.hpp"
#include "../DataStructs/String/String.hpp"

struct HostSettings
{

};

struct ConnectionSettings
{

};

class Config final
{
private:
	String jsonFile;
public:
	explicit Config(String const&);
	Config(Config const&)  = delete;
	Config(Config&&)  = delete;
	~Config();
public:
	Config& operator = (Config const&)  = delete;
	Config& operator = (Config&&) = delete;;
};
