#include "DSCEngine/sprites/obj_allocator.hpp"

#include "DSCEngine/debug/assert.hpp"
#include "DSCEngine/video/measure.hpp"
#include "DSCEngine/utils/math.hpp"

using namespace DSC;

DSC::ObjAllocator::ObjAllocator(Allocator& allocator, int bytes_per_entry) 
	: allocator(allocator), bytes_per_entry(bytes_per_entry)
{
	nds_assert((bytes_per_entry & (bytes_per_entry - 1)) == 0 // bytes_per_entry is a power of 2
		&& 32 <= bytes_per_entry 
		&& bytes_per_entry <=256, "Wrong allocation block size");
}

void DSC::ObjAllocator::remove(const AssetData* asset, Point<short> metatile)
{
	if(!loaded_frames.contains_key(asset)) return;
	if(!loaded_frames[asset].contains_key(metatile)) return;
	loaded_frames[asset].remove_key(metatile);
	if(loaded_frames[asset].size()==0)
		loaded_frames.remove_key(asset);
}
		
bool DSC::ObjAllocator::allocate(ObjFrame* frame)
{
	frame->unload.add_event(&ObjAllocator::on_frame_unload, this);
	
	AssetData* asset = frame->asset;
	Point<short> metatile = { x : frame->metatile_row, y : frame->metatile_col};
	
	loaded_frames[asset][metatile]++;
	
	if(loaded_frames[asset][metatile]==1)
	{
	
		int meta_size = asset->get_metatile_size();
		int alloc_size = MeasureValue(meta_size).fit().blocks(bytes_per_entry).value();	
		void* address = allocator.reserve(alloc_size);
		
		if(address == nullptr) // failed
		{
			remove(asset, metatile);
			return false;
		}
	
		frame->gfx_ptr = address;			
	}
	
	return true;
}

void DSC::ObjAllocator::deallocate(ObjFrame* frame)
{
	AssetData* asset = frame->asset;
	Point<short> metatile = { x : frame->metatile_row, y : frame->metatile_col};
	
	if(!loaded_frames.contains_key(asset)) return;
	if(!loaded_frames[asset].contains_key(metatile)) return;
	
	loaded_frames[asset][metatile]--;
	
	if(loaded_frames[asset][metatile] == 0)
	{
		allocator.release(frame->gfx_ptr);
		frame->gfx_ptr = nullptr;
	}
	
}

void DSC::ObjAllocator::on_frame_unload(void* sender, void* args)
{
	ObjFrame* frame = (ObjFrame*)sender;
	deallocate(frame);
}