#include "Config.hpp"

#include <iostream>
using namespace std;

Config::Config(String const& configFileName)
{
  cout << "Config" << endl;
}

Config::~Config()
{
  cout << "~Config" << endl;
}
