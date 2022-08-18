#pragma once

#include <cstddef>
#include <iostream>
//#include <memory>

//using std::shared_ptr;

class String final
{
private:
	size_t len_;
	//shared_ptr<char[]> buff_;
	char* buff_;
public:
	String();
	String(char const*);
	String(size_t, char);
	explicit String(size_t);
	String(String const&);
	String(String&&) noexcept;
	~String();
public:
	String& operator= (String const&);
	String& operator= (String&&) noexcept;
public:
	char& operator[] (size_t);
	char const& operator[] (size_t) const;
public:
	size_t len()     const noexcept;
	bool   empty() const noexcept;
public:
	void clear();
	void reserve(size_t);
	void resize(size_t);
public:
	friend std::ostream& operator << (std::ostream&, String const&);
    //friend std::istream& operator >> (std::istream&, String&);
private:
	void swap();
};