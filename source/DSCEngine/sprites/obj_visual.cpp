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
