/**
 * @file JavaFunctorFactory.cpp
 * @author ME Chamberlain
 * @date June 2009
 */

#include "JavaFunctorFactory.h"

namespace Myoushu
{
	JavaFunctorFactory::JavaFunctorFactory()
	{
	}

	JavaFunctorFactory::~JavaFunctorFactory()
	{
	}

	JavaFunctor* JavaFunctorFactory::make(const std::string& name)
	{
		JavaFunctor *pImporter;

		pImporter = new JavaFunctor(ensureUniqueName(name));

		if (pImporter == NULL)
		{
			return NULL;
		}

		add(pImporter);

		return pImporter;
	}

	FunctorBase* JavaFunctorFactory::make(const std::string& className, const std::string& name) throw (Exception)
	{
		FunctorBase *pImporter;

		pImporter = NULL;

		if (className == NamedObject<JavaFunctor>::getStaticClassName())
		{
			pImporter = static_cast<FunctorBase*>(make(name));
		}

		return pImporter;
	}

} // namespace Myoushu
