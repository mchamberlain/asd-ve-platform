/**
 * @file SampleNetwork.h
 * @author ME Chamberlain
 * @date June 2008
 */

#ifndef SAMPLE_NETWORK_H
#define SAMPLE_NETWORK_H

#include "Application.h"

class SampleNetwork : public Myoushu::Application
{
	public:
		/** Nullary Constructor. */
		SampleNetwork();

		/** Destructor */
		~SampleNetwork();

		/**
		 * Start the sample application.
		 * Calls the main() and init() in Myoushu::Application.
		 * @param argc Number of command line parameters including the filename that was executed
		 * @param argv Array of null terminiated C-style strings containing the command line parameters.
		 */
		void start(int argc, char **argv);
};

#endif
