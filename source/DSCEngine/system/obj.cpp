#include "DSCEngine/system/hardware.hpp"

#include <nds.h>
#include "DSCEngine/debug/log.hpp"

void DSC::Hardware::MainEngine::objEnable(bool use_ext_palette)
{
	int ext_palette_flag = use_ext_palette ? DISPLAY_SPR_EXT_PALETTE : 0;
	*MainEngine::DISPCNT &= ~DISPLAY_SPRITE_ATTR_MASK;
	*MainEngine::DISPCNT |=  DISPLAY_SPR_ACTIVE | SpriteMapping_1D_32 | ext_palette_flag;
}

void DSC::Hardware::MainEngine::objDisable()
{
	*MainEngine::DISPCNT &= ~DISPLAY_SPRITE_ATTR_MASK;
}

bool DSC::Hardware::MainEngine::objIsEnabled()
{
	return *MainEngine::DISPCNT & DISPLAY_SPR_ACTIVE;
}

bool DSC::Hardware::MainEngine::objIsExtPaletteEnabled()
{
	return *MainEngine::DISPCNT & DISPLAY_SPR_EXT_PALETTE;
}

void DSC::Hardware::SubEngine::objEnable(bool use_ext_palette)
{
	int ext_palette_flag = use_ext_palette ? DISPLAY_SPR_EXT_PALETTE : 0;
	Debug::log("EXTPALFLAG = %x", ext_palette_flag);
	*SubEngine::DISPCNT &= ~DISPLAY_SPRITE_ATTR_MASK;
	*SubEngine::DISPCNT |=  DISPLAY_SPR_ACTIVE | SpriteMapping_1D_32 | ext_palette_flag;
	Debug::log("DISPCNT = %x", *SubEngine::DISPCNT);
}

void DSC::Hardware::SubEngine::objDisable()
{
	*SubEngine::DISPCNT &= ~DISPLAY_SPRITE_ATTR_MASK;
}

bool DSC::Hardware::SubEngine::objIsEnabled()
{
	return *SubEngine::DISPCNT & DISPLAY_SPR_ACTIVE;
}

bool DSC::Hardware::SubEngine::objIsExtPaletteEnabled()
{
	return *SubEngine::DISPCNT & DISPLAY_SPR_EXT_PALETTE;
}