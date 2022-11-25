#pragma once

#include "DSCEngine/resources/asset_data.hpp"
#include "DSCEngine/events/event.hpp"
#include "DSCEngine/sprites/obj_allocator.hpp"


namespace DSC
{
	class ObjFrame
	{
		friend class ObjAllocator;
	private:
		const AssetData* asset = nullptr;
		short metatile_row = 0;
		short metatile_col = 0;
		void* gfx_ptr = nullptr;
		Event unload;
	public:			
		ObjFrame(const AssetData* asset, int metatile_row, int metatile_col);		
		
		~ObjFrame();
	};
}