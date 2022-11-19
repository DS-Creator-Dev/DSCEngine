#include "DSCEngine/system/hardware.hpp"

#include "DSCEngine/types/templates.hpp"

using namespace DSC;
using namespace DSC::Hardware;


ExtendedPalette* DSC::Hardware::MainEngine::BgExtendedPalette()
{
	if(VramBank('E').is_enabled())	
		return (ExtendedPalette*)VramBank('E').lcd_offset();			
	
	int _f = 0, _g = 0xF000000;
	
	if(VramBank('F').is_enabled())	
		_f = (int)VramBank('F').lcd_offset();			
	
	if(VramBank('G').is_enabled())	
		_g = (int)VramBank('G').lcd_offset();			
	
	if(_f==0 && _g==0)
		return nullptr;		
	
	if(_f==0) 
		return (ExtendedPalette*)_g;
	if(_g==0)
		return (ExtendedPalette*)_f;
	return (ExtendedPalette*)min(_f, _g);
}

ExtendedPalette* DSC::Hardware::MainEngine::ObjExtendedPalette()
{
	if(VramBank('F').is_enabled())	
		return (ExtendedPalette*)VramBank('F').lcd_offset();		
	if(VramBank('G').is_enabled())	
		return (ExtendedPalette*)VramBank('G').lcd_offset();		
	return nullptr;
}


ExtendedPalette* DSC::Hardware::SubEngine::BgExtendedPalette()
{
	if(VramBank('H').is_enabled())	
		return (ExtendedPalette*)VramBank('H').lcd_offset();	
	return nullptr;
}

ExtendedPalette* DSC::Hardware::SubEngine::ObjExtendedPalette()
{
	if(VramBank('I').is_enabled())	
		return (ExtendedPalette*)VramBank('I').lcd_offset();
	return nullptr;
}

ExtendedPalette* DSC::Hardware::MainEngine::BgExtendedPalette(int index)
{
	return MainEngine::BgExtendedPalette() + 256*index;
}

ExtendedPalette* DSC::Hardware::MainEngine::ObjExtendedPalette(int index)
{
	return MainEngine::ObjExtendedPalette() + 256*index;
}

ExtendedPalette* DSC::Hardware::SubEngine::BgExtendedPalette(int index)
{
	return SubEngine::BgExtendedPalette() + 256*index;
}

ExtendedPalette* DSC::Hardware::SubEngine::ObjExtendedPalette(int index)
{
	return SubEngine::ObjExtendedPalette() + 256*index;
}