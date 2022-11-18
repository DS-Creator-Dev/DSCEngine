#pragma once

#include "DSCEngine/types/point.hpp"

namespace DSC
{
	class Sprite
	{
	private:
		void* _attr;		
				
		// internal layout
		Hitbox hitbox;
		Point<char> anchor, theoretical_anchor;
		
		
		
				
	public:
	};
}