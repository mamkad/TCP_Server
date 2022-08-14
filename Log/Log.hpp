#pragma once 

#include <fstream>
#include <string>

using std::string;
using std::ofstream;

enum logType_t   {INFO = 0, WARNING = 1, ERROR = 2};
enum levelType_t {MAIN = 0, STEP = 1, RESULT = 2};

class Log
{
private:
	string logFileName_;
	bool isWritingAllowed_;
	ofstream logFile_;
	
	bool isEvent_;
public:
    Log(string const&, bool = true);
    Log(Log const&) = delete;
    Log(Log&&)      = delete;
    ~Log();
public:
    Log& operator= (Log const&) = delete;
    Log& operator= (Log&&)      = delete;
public:	
	inline setWriteAllow(bool isWritingAllowed) noexcept
	{
		isWritingAllowed_ = isWritingAllowed;
	}
public:
    void startEvent(logType_t,   string const&);
	void endEvent(logType_t,     string const&);
    void writeToLog(levelType_t, string const&);
public:	
	static string getDate();
private:
	inline bool isCorrectLogType(logType_t logType) 	  noexcept
	{
		return (logType == INFO || logType == WARNING || logType == ERROR);
	}
	inline bool isCorrectlevelType(levelType_t levelType) noexcept
	{
		return (levelType == MAIN || levelType == STEP || levelType == RESULT);
	}
};
