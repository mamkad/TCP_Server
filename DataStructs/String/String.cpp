#include "String.hpp"

#include <cstring>
#include <iterator>
#include <utility>

//using std::make_shared;
using std::exchange;
using std::move;
using std::logic_error;
using std::invalid_argument;
using std::ostream_iterator;
using std::ostream;
using std::istream;
using std::copy;

using namespace std;

String::String() : len_(0), buff_(nullptr)
{
	cout << "std String"<< endl;
}

String::String(char const* CstyleString) : len_(strlen(CstyleString) + 1) , buff_(new char[len_])
{
	cout << "cstryle String"<< endl;
	strncpy(buff_, CstyleString, len_ - 1);
	buff_[len_ - 1] = '\0';
}


String::String(size_t count, char chr) : len_(count + 1), buff_(new char[len_])
{
	memset(buff_, chr, len_ - 1);
	buff_[len_ - 1] = '\0';
}

String::String(size_t sze) : len_(sze + 1), buff_(new char[len_])
{
	buff_[0] = '\0';
}

String::String(String const& otherString) : len_(otherString.len_), buff_(new char[len_])
{
	cout << "const& String"<< endl;
	strncpy(buff_, otherString.buff_, len_ - 1);
	buff_[len_ - 1] = '\0';
}


String::String(String&& otherString) noexcept : len_(0), buff_(nullptr)
{
	cout << "&& String"<< endl;
	*this = move(otherString);
}

String::~String()
{
	cout << "~ String";
	clear();
}
// --------------------------------------------------------------------------------------------------------------------------------
String& String::operator= (String const& otherString)
{
	if (this != &otherString)
	{
		cout << "=& String"<< endl;
		clear();
		
		len_ = otherString.len_;
		buff_ = new char [len_];
		
		strncpy(buff_, otherString.buff_, len_ - 1);
		buff_[len_ - 1] = '\0';
	}
	return *this;
}


String& String::operator= (String&& otherString) noexcept
{
	if (this != &otherString)
	{
		cout << "=&& String"<< endl;
		clear();
		
		len_ = otherString.len_;
		buff_ = otherString.buff_;
		
		otherString.buff_ = nullptr;
		otherString.len_ = 0;
	}
	return *this;
}
// --------------------------------------------------------------------------------------------------------------------------------
char& String::operator[] (size_t index)
{
	if (empty())
	{
		throw logic_error("string is empty");
	}
	if (index > len_ - 1)
	{
		throw invalid_argument("wrong index. len of string: " + to_string(len_ - 1));
	}
	return buff_[index];
}

char const& String::operator[] (size_t index) const
{
	if (empty())
	{
		throw logic_error("string is empty");
	}
	if (index > len_ - 1)
	{
		throw invalid_argument("wrong index. len of string: " + to_string(len_ - 1));
	}
	return buff_[index];
}
// --------------------------------------------------------------------------------------------------------------------------------
inline size_t String::len() const noexcept
{
	if (empty())
	{
		//throw logic_error("string is empty");
		return 0;
	}
	return len_ - 1;
}

inline bool String::empty() const noexcept
{
	return len_ == 0 && buff_ == nullptr;
}

char const* const String::getPtr() const noexcept
{
	return buff_;
}
// --------------------------------------------------------------------------------------------------------------------------------
void String::clear()
{
	if (empty())
	{
		cout << endl;
		//throw logic_error("string is alreay empty");
		return;
	}
	cout << "deleting String" << endl;
	len_ = 0;
	delete[] buff_;
	buff_ = nullptr;
}

void String::reserve(size_t sze)
{
	if (!empty())
	{
		throw invalid_argument("string is not empty. clear buffer");
	}
	if (!sze)
	{
		throw invalid_argument("size is zero");
	}
	
	len_ = sze + 1;
	buff_ = new char [len_];
	
	memset(buff_, '\0', len_ - 1);
}

void String::resize(size_t newSize)
{
	if (!newSize)
	{
		throw invalid_argument("new size is 0");
	}
	if (newSize == len_)
	{
		memset(buff_, '\0', len_ - 1);
		return;
	}
	
	size_t copyLength = newSize < len_ - 1 ? newSize : len_ - 1;
	len_ = newSize + 1;
	char* newBuff = new char [len_];
	
	strncpy(newBuff, buff_, copyLength);
	buff_[len_ - 1] = '\0';
}
// --------------------------------------------------------------------------------------------------------------------------------

ostream& operator << (ostream & outStream, String const & stringClass)
{
	if(!stringClass.empty())
	{
		copy ( stringClass.buff_, stringClass.buff_ + stringClass.len_, ostream_iterator<char> (outStream) );
	}
    return outStream;
}

/*
istream& operator >> (istream & inStream, String & otherString)
{
	if(!otherString.empty())
	{
		//inStream >> otherStr.strPtr_;
	}
    return inStream;
}*/