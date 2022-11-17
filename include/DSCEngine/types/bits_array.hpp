#pragma once

#include "DSCEngine/debug/assert.hpp"

namespace DSC
{
	template<const int N>
	class BitsArray
	{
	private:
		static constexpr int BUFFER_SIZE = (N+31)/32;
		int buffer[BUFFER_SIZE];		
		
		/*! \brief gets the position of the first unset bit in a number's binary representation */
		static int free_bit_pos(int n, int k=32);		
	public:		
		struct __bit // not safe for Debug::log(...)
		{														
			int& buf_stored;
			int	bit_pos;
								
			__bit(int& buf_stored, int bit_pos) : buf_stored(buf_stored), bit_pos(bit_pos) { value(); }
			
			bool value() const { return buf_stored & (1 << bit_pos); }
			
			operator bool() const { return value(); }	
			operator int() const { return value(); }
			
			void operator = (bool bit) { buf_stored&=~(1 << bit_pos), buf_stored|=(bit << bit_pos); }
			
			bool operator == (bool bit) const { return value() == bit; }
			
			bool operator !() const { return !value();}
		};
	
		BitsArray(bool default_value = false);

		const bool& operator[] (int index) const;
		
		__bit operator[] (int index);
		
		bool at(int index) const;
		
		int find_free_bit() const;
		
		inline int size() const { return N; }
	};	
}

template<const int N>
DSC::BitsArray<N>::BitsArray(bool default_value)
{
	int val = -default_value; // default_value ? 0xFFFFFFFF : 0x00000000;
	for(int i=0;i<BUFFER_SIZE;i++)
	{
		buffer[i] = val;
	}
}

template<const int N>
const bool& DSC::BitsArray<N>::operator[] (int index) const
{
	nds_assert(index>=0);
	nds_assert(index<N);
	
	return __bit(buffer[index>>5], index &31);
}

template<const int N>
typename DSC::BitsArray<N>::__bit DSC::BitsArray<N>::operator[] (int index)
{
	nds_assert(index>=0);
	nds_assert(index<N);
	
	return __bit(buffer[index>>5], index &31);
}

template<const int N>
bool DSC::BitsArray<N>::at(int index) const
{
	return (*this)[index];
}

template<const int N>
int DSC::BitsArray<N>::find_free_bit() const
{
	for(int i=0;i<BUFFER_SIZE;i++)
	{
		int p = free_bit_pos(buffer[i]);
		if(p>=0)
		{
			int result = 32*i+p;
				
			return result<N ? result : -1;						
		}
	}
	return -1;
}

template<const int N>
int DSC::BitsArray<N>::free_bit_pos(int n, int k)
{		
	if((unsigned)n==0xFFFFFFFF) return -1; // full : all bits are set
	if(k==0) return 0;		
	
	k/=2;
	int _0f = (1<<(k-1))-1 + (1<<(k-1)); // build bit-1 masks for the LOW 
	//int _f0 = _0f << (k/2);				 // and HIGH parts
	
	if((n & _0f)==_0f)                   // if the LOW part is full
		return k+free_bit_pos(n>>k, k);  // look in the HIGH part
	else 
		return free_bit_pos(n & _0f, k); // otherwise check the LOW part
}
