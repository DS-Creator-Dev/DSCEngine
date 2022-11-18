/*!
* \file obj_visual.hpp
* \brief Object Visual definition
 */

#pragma once

#include "DSCEngine/types/vector.hpp"

namespace DSC
{
	/*! \brief OAM Object graphics handler class	
	 */
	class ObjVisual
	{
		private:
			Vector<short> frames;
			unsigned char crt_gfx_id = 0;
			
			Vector<Vector<unsigned char>> framesets;			
			// bit  0    : enabled [0..1]
			// bit  1    : loop    [0..1]
			// bit  2-7  : frameset id [0..63]
			// bit  7-13 : frame id inside frameset [0..63]
			short anim_stat = 0;
			// bit  0-3 : anim ticks
			// bit  4-8 : current ticks
			short tick_stat = 0;
			
		public:
			/*!
			* \brief Creates an object visual data with a certain number of frames			
			* \param [in] frames_count number of reserved frames for sprite
			 */
			ObjVisual(unsigned short frames_count);
			
			/*!
			* \brief Gets number of frames			
			* \return number of reserved frames for sprite			
			 */
			int get_frames_count() const;
			
			/*!
			* \brief Assigns a frame to some graphics data
			* 
			* \param [in] id Frame id
			* \param [in] obj_tile_address Address of the object tiles			
			 */
			void set_frame(int id, int tile_id);

			/*!
			* \brief Makes animation run one frame at a number of ticks
			* 
			* \param [in] ticks Ticks until the next frame			
			 */
			void set_animation_ticks(int ticks);
			
			/*!
			* \brief Sets animation frames into one of the 8 frame slots
			* 
			* \param [in] frameset_id Animation frame slot [0..7]
			* \param [in] ... List of frame ids [0..frames count]			
			 */
			void set_animation_frames(int frameset_id, ...);
			
			
			/*!
			* \brief Makes animation run one of the 8 frame slots
			* 
			* \param [in] frameset_id Animation frame slot [0..7]
			* \param [in] loop Animation loop			
			 */
			void set_animation_track(int frameset_id, bool loop);
			
			/*!
			* \brief Gets the object current displayed graphics
			* 
			* \return Address of the cuurent displayed graphics data			
			 */			
			const short get_crt_gfx_id() const;
			
			/*!
			* \brief Sets the object current displayed graphics
			* 
			* \param [in] frame_id Frame number to get the current graphics from
			* 			
			* \details **Caution!** Calling set_crt_gfx() disables the animation.
			 */
			void set_crt_gfx_id(int frame_id);
			
			/*!
			* \brief Updates graphics data (run animation etc.)					
			 */
			void update();
	};
	
	
	static constexpr int ANIM_FRAMES_0 = 0; /*!< Literal name for animation frame 0*/
	static constexpr int ANIM_FRAMES_1 = 1; /*!< Literal name for animation frame 1*/
	static constexpr int ANIM_FRAMES_2 = 2; /*!< Literal name for animation frame 2*/
	static constexpr int ANIM_FRAMES_3 = 3; /*!< Literal name for animation frame 3*/
	static constexpr int ANIM_FRAMES_4 = 4; /*!< Literal name for animation frame 4*/
	static constexpr int ANIM_FRAMES_5 = 5; /*!< Literal name for animation frame 5*/
	static constexpr int ANIM_FRAMES_6 = 6; /*!< Literal name for animation frame 6*/
	static constexpr int ANIM_FRAMES_7 = 7; /*!< Literal name for animation frame 7*/
}