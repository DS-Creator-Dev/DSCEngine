#include "DSCEngine/types/string.hpp"

#include "DSCEngine/debug/assert.hpp"

using namespace DSC;

DSC::String::String() : String("") { }

DSC::String::String(const char* text)
{
	len = 0;
	for(char* i=text; *i; i++,len++);
	
	buffer = new char[len+1];
	
	for(char* s=text, char* d=buffer; *s; *(d++)=*(s++));
	*d = '\0';
}

DSC::String::operator const char*() const
{
	return buffer;
}

int DSC::String::size() const { return len; }

char operator[] (int index) const
{
	nds_assert(0<=index);
	nds_assert(index<size());
	
	return buffer[index];
}

bool operator == (const String& other) const
{
	if(this->size() != other.size()) return false;		
	const char* b1 = this->buffer;
	const char* b2 = other.buffer;	
	
	for(int i=0;i<len;i++)
	{
		if(b1[i]!=b2[i]) 
			return false;
	}
	return true;
}

DSC::String::~String()
{
	delete[] buffer;
}