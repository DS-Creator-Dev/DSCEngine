#include "DSCEngine/sprites/obj_visual.hpp"

using namespace DSC;

DSC::ObjVisual::ObjVisual(DSC::ObjSize obj_size)
{
	size = obj_get_size(obj_size);
}

int DSC::ObjVisual::add_frame(ObjFrame* frame)
{
	frames.push_back(frame);
	return frames.size()-1;
}


void* DSC::ObjVisual::get_crt_gfx() const
{
	return frames[crt_gfx_id]->gfx_ptr;
}

int DSC::ObjVisual::set_crt_gfx(int gfx_index)
{
	nds_assert(0<gfx_index && gfx_index<frames.size());
	gfx_changed = (crt_gfx_id != gfx_index);
	crt_gfx_id = gfx_index;
	nds_assert(frames[crt_gfx_id]->asset!=nullptr);
	return get_crt_color_depth();
}

Size<char> DSC::ObjVisual::get_size() const { return size; }

int DSC::ObjVisual::get_crt_color_depth() const
{
	return frames[crt_gfx_id]->asset->get_color_depth();
}

void DSC::ObjVisual::update()
{
	if(!gfx_changed) return;	
	
	gfx_changed = false;
	
}