#include "DSCEngine/sprites/sprite.hpp"
#include "DSCEngine/video/measure.hpp"

#include "obj_attribute.hpp"
#include "oam_pool.hpp"

using namespace DSC;

namespace
{
	// pointer dispatcher function
	// we don't want direct access to OamPool and ObjAttribute
	template<typename T> T* _(void* x) { return (T*)x;}	
}

DSC::Sprite::Sprite(ObjSize size, Engine engine)
{		
	oam_pool = (engine == Engine::Main) ? OamPool::main() : OamPool::sub();

	attr = _<OamPool>(oam_pool)->add_obj(ObjAttribute::create16(size)); // bpp will be changed anyway when loading the graphics
	_<ObjAttribute>(attr)->set_priority(0);
	
	visual = new ObjVisual(size);	
}

Size<char> DSC::Sprite::get_size() const
{
	return visual->get_size();
}

ObjVisual* DSC::Sprite::get_visual() const { return visual; }

void DSC::Sprite::update_visual()
{
	visual->update();
	
	_<ObjAttribute>(attr)->set_color_depth(visual->get_crt_color_depth());
	
	Debug::log("Sprite address = %x", visual->get_crt_gfx());	
			
	int tile_id = Measure()
		.bpp(visual->get_crt_color_depth())
		.tile_id(visual->get_crt_gfx(), 
			_<OamPool>(oam_pool)->is_main() 
				? Hardware::MainEngine::ObjVram
				: Hardware::SubEngine::ObjVram,
			_<OamPool>(oam_pool)->is_main() 
				? Hardware::MainEngine::objGetMappingSize()
				: Hardware::SubEngine::objGetMappingSize());
			
	Debug::log("Tile = %i", tile_id);
	
	_<ObjAttribute>(attr)->set_tile_index(tile_id);
}

void DSC::Sprite::update_position()
{
	//Debug::log("%i %i %i",x(), hitbox.left, anchor.x);
	_<ObjAttribute>(attr)->set_x((short)(x() - hitbox.left - anchor.x));
	_<ObjAttribute>(attr)->set_y((short)(y() - hitbox.top  - anchor.y));
}

void Sprite::set_default_allocator(ObjAllocator* obj_allocator)
{
	this->obj_allocator = obj_allocator;
}

int Sprite::add_frame(ObjFrame* frame)
{
	if(obj_allocator)
	{
		if(!obj_allocator->allocate(frame))
		{
			Debug::error("Failed allocation");
			return -1;			
		}
	}
	if(frame->gfx_ptr==nullptr)
	{
		Debug::warn("Frame not allocated!");
	}
	return visual->add_frame(frame);
}

sf24 DSC::Sprite::x() const { return pos.x; }
sf24 DSC::Sprite::y() const { return pos.y; }

void DSC::Sprite::oam_deploy_main()
{	
	OamPool::main()->deploy();	
}

void DSC::Sprite::oam_deploy_sub()
{	
	OamPool::sub()->deploy();	
}

Engine DSC::Sprite::get_engine() const
{
	return _<OamPool>(oam_pool) == OamPool::main() ? Engine::Main : Engine::Sub;
}

void DSC::Sprite::set_position(sf24 x, sf24 y)
{
	pos.x = x;
	pos.y = y;
}

void DSC::Sprite::move(sf24 x, sf24 y)
{
	pos.x += x;
	pos.y += y;
}