//
//
//  	G.L.U.E. by M.C.G. 2015 
//
//  	Glue stands for 
// 	Genetically Led Universal Evaluator.
//
// 		Add some glue in your code... 
//
//


/** \brief The file_manager is an helper (interface) for external file management 
*
*	the files class api aims to manage files operations in c++
*/

#ifndef __FILES_GLUE__
#define __FILES_GLUE__

#include "glue_types.h"
#include <cstdint>

class file_manager
{

	public:

    static bool get_file_bytes(const char* file_name, byte** file_content,std::uint32_t* file_size);
	
    static bool set_file_bytes(const char* file_name, byte* file_content,std::uint32_t file_size);
	
	static bool  file_exists(const char* file_name);
	
	static bool  file_delete(const char* file_name);

};

#endif
