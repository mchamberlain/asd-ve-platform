/**
 * @file JavaFunctorFactory.h
 * @author ME Chamberlain
 * @date June 2009
 */

#ifndef JAVA_FUNCTOR_FACTORY_H
#define JAVA_FUNCTOR_FACTORY_H

#include "FunctorFactory.h"
#include "Singleton.h"

#include "MyoushuJavaPlatform.h"
#include "JavaFunctor.h"

namespace Myoushu
{
	class MYOUSHU_JAVA_API JavaFunctorFactory : public Ogre::Singleton<JavaFunctorFactory>, public FunctorFactory
	{
		public:
			/** Constructor. */
			JavaFunctorFactory();

			/** Destructor. */
			virtual ~JavaFunctorFactory();

			/** 
			 * Create an instance using with specified name. Extending classes can change
			 * the return type of this function to an appropriate type.
			 * @param name The name for the instance to create.
			 * @return The newly created instance.
			 */
			virtual JavaFunctor* make(const std::string& name);

			/** 
			 * Create an instance of the specified className with the specified instance name. Extending classes can change
			 * the return type of this function to an appropriate type. This function is useful for factories that can
			 * create instances of different classes in an inheritence hierarchy.
			 * @param className The name of the class to create an instance of.
			 * @param name The name for the instance to create.
			 * @return The newly created instance.
			 * @throws Exception::E_INVALID_PARAMETERS if this factory does not support the creation of instances of type className.
			 */
			virtual FunctorBase* make(const std::string& className, const std::string& name) throw (Exception);

	}; // class FunctorFactory
} // namespace Myoushu

#endif
