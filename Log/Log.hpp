#pragma once 

#include "../Base/nonAssignNonCopy.hpp"

#include <fstream>
#include <string>

using std::string;
using std::ofstream;

enum logType_t   {INFO = 0, WARNING = 1, ERROR = 2};
enum levelType_t {MAIN = 0, STEP = 1, RESULT = 2};

class Log final : private NonAssignable, private NonCopyable
{
private:
	string 	logFileName_;
	bool isWritingAllowed_;
	ofstream logFile_;
	bool isEvent_;

public:
    Log(string const&, bool = true);
    ~Log();

public:	
	inline void setWriteAllow(bool isWritingAllowed) noexcept;

public:
    void startEvent(logType_t,   string const&);
	void endEvent(logType_t,     string const&);
    void writeToLog(levelType_t, string const&);

public:	
	static string getDate();

private:
	inline bool isCorrectLogType(logType_t logType) 	  noexcept;
	inline bool isCorrectlevelType(levelType_t levelType) noexcept;
};
