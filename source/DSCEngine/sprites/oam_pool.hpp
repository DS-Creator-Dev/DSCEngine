#pragma once

#include <nds.h>

namespace DSC
{
	/*! \brief Low level OAM handler
	* 
	 */
	namespace OamPool
	{			
		/*!
		* \brief sets OAM to its original state
		 */
		void reset();
		
		/*!
		* \brief Adds new object to OAM
		* 
		* \param [in] attr new object attributes
		* \return An identificator pointer of the object
		* 
		* \details **Caution!** Use the returned pointer attribute to work with the object. Do not attempt to free the pointer.
		*	 	Use remove_obj() to safely dispose of the object.
		* \details This function operates on a shadow memory zone. Use OamPool::deploy() to make the changes visible on the screen.
		 */
		SpriteEntry* add_obj(SpriteEntry attr);	
		
		/*!
		* \brief Removes object from OAM by its identificator pointer
		* 
		* \param [in] attr pointer to object's attributes
		* 
		* \details **Caution!** Use only the pointers obtained from add_obj() as parameters in this function.
		* \details This function operates on a shadow memory zone. Use OamPool::deploy() to make the changes visible on the screen.
		 */
		void remove_obj(SpriteEntry* attr);
		
		/*!
		* \brief Updates all objects on the screen according to their OAM state.
		 */
		void deploy();
		
		void set_rotation_matrix(int id, int pa, int pb, int pc, int pd);
	}
}