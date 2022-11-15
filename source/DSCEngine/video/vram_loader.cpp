#include "DSCEngine/video/vram_loader.hpp"

#include "DSCEngine/debug/assert.hpp"
#include "DSCEngine/debug/log.hpp"

#include <nds.h>

using namespace DSC;

void DSC::VramLoader::load(const AssetData* asset, void* dest, short* pal_indices, int map_width)
{
	Debug::log("Loading asset %s (%i,%i)", asset->is_bitmap()?"bitmap":"tileset", 8*asset->width, 8*asset->height);
	//Debug::log("MW = %i, AW = %i",map_width, 8*asset->width);
	if(!asset->is_bitmap() || (asset->is_bitmap() && (map_width == 0 || map_width == 8*asset->width)))
	{
		//Debug::log("first");
		if(pal_indices==nullptr || asset->get_color_depth()!=8)
		{					
			asset->extract(dest, 0, asset->get_gfx_length());									
			return;
		}		
		int len = asset->get_gfx_length();
		//Debug::log("LEN = %i", len);
		unsigned char* buffer = new unsigned char[len];
		//Debug::log("Allocated");
		
		asset->extract(buffer, 0, len);
		
		for(int i=0;i<len;i++)
		{
			if(buffer[i])
				buffer[i] = pal_indices[buffer[i]];
		}		
		
		//Debug::log("Buffered created");
		
		dmaCopy(buffer, dest, len);	// <-- beware for bugs idk	
		
		//Debug::log("dma");
			
		delete[] buffer;
		
		//Debug::log("fin");
	}
	else // if(asset->is_bitmap() && 8*asset->width != map_width
	{		
		//Debug::log("Here?");
		nds_assert(8*asset->width < map_width);
		
		int len = asset->get_gfx_length();
		unsigned char* bufferx = new unsigned char[len];
		asset->extract(bufferx, 0, len);
		
		int stride = asset->width * asset->get_color_depth();
		
		unsigned char* dest8 = (unsigned char*)dest;
		unsigned char* buffer = (unsigned char*)bufferx;
		for(int y=0;y<8*asset->height;y++)
		{
			dmaCopy(buffer, dest8, stride);
			buffer += stride;
			dest8 += map_width * asset->get_color_depth() / 8;
		}
		
		delete[] bufferx;
	}
}