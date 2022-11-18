#pragma once

#include "DSCEngine/resources/asset_data.hpp"
#include "DSCEngine/Events/event.hpp"

namespace DSC
{
	class ObjFrame
	{
	private:
		AssetData* asset = nullptr;
		short metatile_row = 0;
		short metatile_col = 0;
		void* gfx_ptr = nullptr;
				
		Event unload;
	public:
		ObjFrame(AssetData* asset, int metatile_row, int metatile_col);
		
		~ObjFrame();
	};
}