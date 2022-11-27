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
		Point<char> anchor={0,0}, theoretical_anchor={0,0};
		
		Point<sf24> pos;
		
		ObjVisual* visual;
				
		ObjAllocator* obj_allocator = nullptr;
	public:				
		Sprite(ObjSize size, Engine engine);
		

		ObjVisual* get_visual() const;

		Size<char> get_size() const;
	
		void update_visual();
		void update_position();
	
		void set_position(sf24 x, sf24 y);
	
		virtual sf24 x() const override;
		virtual sf24 y() const override;
		~Sprite();
		
		Engine get_engine() const;
		
		void set_default_allocator(ObjAllocator* obj_allocator);
		int add_frame(ObjFrame* frame);
		
		static void oam_deploy_main();
		static void oam_deploy_sub();				
	};
}