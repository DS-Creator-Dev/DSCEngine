#include "oam_pool.hpp"

#include "DSCEngine/types/bits_array.hpp"

using namespace DSC;






namespace
{
	char init_flags = 0;
	
	constexpr int inited_main = 1<<0;
	constexpr int inited_sub = 1<<1;
	
	// OamPool is private for safety reasons so we will manually create the 
	// Main & Sub instances inside these buffers and make them available as pointers to OamPool.
	char _oam_main_slot[sizeof(OamPool)];
	char _oam_sub_slot[sizeof(OamPool)];
}

OamPool* const DSC::OamPool::main()
{
	if(!(init_flags & inited_main))
	{		
		*((OamPool*)_oam_main_slot) = OamPool();		
		init_flags |= inited_main;
	}	
	return (OamPool* const)&_oam_main_slot;
}

OamPool* const DSC::OamPool::sub()
{
	if(!(init_flags & inited_sub))
	{
		*((OamPool*)_oam_sub_slot) = OamPool();		
		init_flags |= inited_sub;
	}	
	return (OamPool* const)&_oam_sub_slot;
}