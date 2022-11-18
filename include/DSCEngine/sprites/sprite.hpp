#pragma once

#include "DSCEngine/types/point.hpp"
#include "DSCEngine/world/localizable.hpp"

namespace DSC
{
	class Sprite : public Localizable
	{
	private:
		void* _attr;		
				
		// internal layout
		Hitbox hitbox;
		Point<char> anchor, theoretical_anchor;
		
		Point<sf24> pos;
		
	
	public:
		

	
		virtual sf24 x() const override;
		virtual sf24 y() const override;
		~Sprite();
	};
}