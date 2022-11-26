#pragma once

#include "DSCEngine/types/point.hpp"
#include "DSCEngine/sprites/hitbox.hpp"
#include "DSCEngine/sprites/obj_allocator.hpp"
#include "DSCEngine/sprites/obj_visual.hpp"
#include "DSCEngine/world/localizable.hpp"
#include "DSCEngine/system/hardware.hpp"

namespace DSC
{	
	class Sprite : public Localizable
	{
	private:
		void* oam_pool;
		void* attr;
				
		// internal layout
		Hitbox hitbox;
		Point<char> anchor, theoretical_anchor;
		
		Point<sf24> pos;
		
		ObjVisual* visual;
				
		ObjAllocator* obj_allocator = nullptr;
	public:				
		Sprite(ObjSize size, Engine engine);
		

		ObjVisual* get_visual() const;

		Size<char> get_size() const;
	
		void update_visual();
		void update_position();
	
		virtual sf24 x() const override;
		virtual sf24 y() const override;
		~Sprite();
		
		
		void set_default_allocator(ObjAllocator* obj_allocator);
		int add_frame(ObjFrame* frame);
		
		static void oam_deploy_main();
		static void oam_deploy_sub();		
	};
}