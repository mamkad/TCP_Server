#include "Log.hpp"

#include <chrono> 
#include <sstream> // stringstream
#include <ctime>   // localtime
#include <iomanip> // put_time

using std::logic_error;
using std::invalid_argument;

static string const HEADLINEINFO[3] = {"INFO", "WARNING", "ERROR"};
static string const CHARLINES[3] = { string(160, '-'), string(160, '*'), string(160, '/') };
static string const EVENTS[2] = { "START", "END" };
static string const PREFIXS[3] = { "\t - ",  "\t\t * ", "\t\t\t > "};

Log::Log(string const& logFileName, bool isWritingAllowed/* = true*/) : logFileName_(logFileName), isWritingAllowed_(isWritingAllowed), isEvent_(false)
{
	logFile_.open(logFileName_, std::ios_base::app);
}

Log::~Log()
{
	logFile_.close();
}

void Log::startEvent(logType_t logType, string const& message)
{
	if (!isCorrectLogType(logType))
	{
		throw invalid_argument("wrong log type");
	}
	
	string dataToLog;
	dataToLog.append(CHARLINES[logType] + '\n');
	dataToLog.append(" # [" + getDate() + "] - " + HEADLINEINFO[logType] + " - " + message + " - " + EVENTS[0] + '\n');
	
	logFile_.write(dataToLog.c_str(), dataToLog.size());
	logFile_.flush();
	
	isEvent_ = true;
}

void Log::endEvent(logType_t logType, string const& message)
{
	if (!isCorrectLogType(logType))
	{
		throw invalid_argument("wrong log type");
	}
	
	string dataToLog;
	dataToLog.append(" # [" + getDate() + "] - " + HEADLINEINFO[logType] + " - " + message + " - " + EVENTS[1] + '\n');
	dataToLog.append(CHARLINES[logType] + '\n');
	
	logFile_.write(dataToLog.c_str(), dataToLog.size());
	logFile_.flush();
	
	isEvent_ = false;
}

void Log::writeToLog(levelType_t levelType, string const& message)
{
	if (!isEvent_)
	{
		throw logic_error("event not set");
	}
	if (!isCorrectlevelType(levelType))
	{
		throw invalid_argument("wrong level type");
	}
	
	string dataToLog;
	dataToLog.append(PREFIXS[levelType] +  message + '\n');
	
	logFile_.write(dataToLog.c_str(), dataToLog.size());
	logFile_.flush();
}

string Log::getDate()
{
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);

  std::stringstream ss;
  ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
  return ss.str();
}
