/**
 * @file SampleGameLog.h
 * @author ME Chamberlain
 * @date June 2008
 */

#ifndef SAMPLE_GAME_LOG_H
#define SAMPLE_GAME_LOG_H

#include "Application.h"

class SampleGameLog : public Myoushu::Application
{
	public:
		/** Nullary Constructor. */
		SampleGameLog();

		/** Destructor */
		~SampleGameLog();

		/**
		 * Start the sample application.
		 * Calls the main() and init() in Myoushu::Application.
		 * @param argc Number of command line parameters including the filename that was executed
		 * @param argv Array of null terminiated C-style strings containing the command line parameters.
		 */
		void start(int argc, char **argv);
};

#endif
