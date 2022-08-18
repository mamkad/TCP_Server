#include "String.hpp"

#include <cstring>
#include <iterator>

using std::make_shared;
using std::exchange;
using std::move;
using std::logic_error;
using std::invalid_argument;
using std::ostream_iterator;
using std::copy;


String::String() : len_(0), buff_(nullptr)
{
	
}


String::String(char const* CstyleString) : len_(strlen(CstyleString) + 1), buff_(make_shared<char[]>(len_))
{
	strncpy(*buff_, CstyleString, len_ - 1);
	buff_[len_] = '\0';
}

String::String(size_t count, char chr) : len_(count + 1), buff_(make_shared<char[]>(len_))
{
	memset(*buff_, chr, len_ - 1);
	//buff_[len_] = '\0';
	//buff_.get() + len_ = '\0';
}

String::String(size_t sze) : len_(sze + 1), buff_(make_shared<char[]>(len_))
{
	//buff_[0] = '\0';
	//buff_.get() = '\0';
}

String::String(String const& otherString) : len_(otherString.len_), buff_(otherString.buff_)
{
}

String::String(String&& otherString) noexcept : len_(exchange(otherString.len_, 0)), buff_(move(otherString.buff_))
{
}
// --------------------------------------------------------------------------------------------------------------------------------
String& String::operator= (String const& otherString)
{
	if (this != &otherString)
	{
		len_ = otherString.len_;
		buff_ = otherString.buff_;
	}
	return *this;
}

String& String::operator= (String&& otherString) noexcept
{
	if (this != &otherString)
	{
		len_ = exchange(otherString.len_, 0);
		buff_ = move(otherString.buff_);
	}
	return *this;
}
// --------------------------------------------------------------------------------------------------------------------------------
char& String::operator[] (size_t index)
{
	if (isEmpty())
	{
		throw logic_error("string is empty");
	}
	if (index > len_ - 1)
	{
		throw invalid_argument("wrong index. len of string: " + len_);
	}
	return buff_[index];
}

char const& String::operator[] (size_t index) const
{
	if (isEmpty())
	{
		throw logic_error("string is empty");
	}
	if (index > len_ - 1)
	{
		throw invalid_argument("wrong index. len of string: " + len_);
	}
	return buff_[index];
}
// --------------------------------------------------------------------------------------------------------------------------------
size_t String::len() const noexcept
{
	if (isEmpty())
	{
		throw logic_error("string is empty");
	}
	return len_ - 1;
}

bool String::isEmpty() const noexcept
{
	return len_ == 0;
}
// --------------------------------------------------------------------------------------------------------------------------------
void String::clear()
{
	if (isEmpty())
	{
		throw logic_error("string is alreay empty");
	}
	len_ = 0;
	buff_.reset();
}

void String::reserve(size_t sze)
{
	if (!isEmpty())
	{
		throw invalid_argument("string is not empty. clear buffer");
	}
	
	//size_
	//buff_ = make_shared<char[]>(sze + 1);
}

void String::resize(size_t newSize)
{
	if (!newSize)
	{
		throw invalid_argument("new size is 0");
	}
}
// --------------------------------------------------------------------------------------------------------------------------------

std::ostream& operator << (std::ostream & outStream, String const & otherString)
{
	if(!otherString.isEmpty())
	{
		//ostream_iterator<char> outIt (outStream);
		//std::copy ( otherStr.strPtr_, otherStr.strPtr_ + otherStr.strLastIdx_, outIt );
	}
    return outStream;
}

std::istream& operator >> (std::istream & inStream, String & otherString)
{
	if(!otherString.isEmpty())
	{
		//inStream >> otherStr.strPtr_;
	}
    return inStream;
}