#ifndef _MYOUSHU_UTILITY_H_
#define _MYOUSHU_UTILITY_H_

namespace Myoushu
{
	/** A Utility class with various static functions. */
	class Utility
	{
		public:
			/**
			 * This function does a dynamic cast from A to B.
			 * The primary use of this function is a shortcut to navigate a class hierary 
			 * in SWIG wrapper languages that do not support multiple inheritance.
			 */
			template< class A, class B >
			static B* hierarchyCast( A *pInstance );
	};

	template< class A, class B >
	B* Utility::hierarchyCast( A *pInstance )
	{
		return dynamic_cast< B* >( pInstance );
	}
}

#endif
