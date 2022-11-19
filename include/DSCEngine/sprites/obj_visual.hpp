/*!
* \file obj_visual.hpp
* \brief Object Visual definition
 */

#pragma once

#include "DSCEngine/types/vector.hpp"
#include "DSCEngine/types/size.hpp"
#include "DSCEngine/sprites/obj_frame.hpp"
#include "DSCEngine/sprites/obj_size.hpp"

namespace DSC
{
	/*! \brief OAM Object graphics handler class	
	 */
	class ObjVisual
	{
		private:
			Size<char> size;
			
			Vector<ObjFrame*> frames;
			unsigned char crt_gfx_id = 0;
			
			Vector<Vector<unsigned char>> framesets;
			
			int visual_stat = 0;
			
			/*// bit  0    : enabled [0..1]
			// bit  1    : loop    [0..1]
			char anim_flags = 0;
						
			char frameset_id = 0;
			char frame_id = 0; // inside frameset			
			
			char anim_ticks = 0;
			char crt_ticks = 0;	*/
		public:
			ObjVisual(DSC::ObjSize obj_size);
			
			int add_frame(ObjFrame* frame);
			
			
			
	};	
}