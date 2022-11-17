#pragma once

namespace DSC
{
	class String
	{
	private:
		const char* buffer = nullptr;		
		short len = 0;
	public:
		String();
		String(const char* text);
		
		operator const char*() const;
		
		int size() const;

		char operator[] (int index) const;
		
		bool operator == (const String& other) const;
		
		~String();
	};
}
