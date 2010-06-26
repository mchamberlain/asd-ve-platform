/*
This file is part of the ASD Assist VE Platform.

For the latest info, see http://asd-ve-platform.sourceforge.net/

Copyright (c) 2009 Morné Chamberlain & Stellenbosch University

The ASD Assist VE Platform is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License (with the added restriction
that this work and any derivative works may only be used for non-commercial purposes)
as published by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

The ASD Assist VE Platform is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file VideoTask.cpp
 * @author ME Chamberlain
 * @date April 2008
 */

#include <sstream>

#include "Poco/RWLock.h"
#include "Poco/Exception.h"

#include "NxOgre.h"

#include "VideoTask.h"
#include "Constants.h"
#include "GlobalLocks.h"
#include "Config.h"
#include "EngineLog.h"
#include "Exception.h"
#include "NotificationManager.h"
#include "SceneFactory.h"
#include "Scene.h"
#include "TimerTask.h"

namespace Myoushu
{
	CLASS_NAME(VideoTask, "Myoushu::VideoTask");

	const unsigned int VideoTask::TIME_BETWEEN_FPS_UPDATES_IN_MILLIS = 1000;

	VideoTask::VideoTask(int priority, const std::string& name, unsigned long executionInterval, unsigned int iterationLimit) : Task(name, priority, executionInterval, iterationLimit), mpFPSOverlay(NULL), mpFPSContainer(NULL), mpFPSTextArea(NULL), mFPSLastUpdateTime(0), mLastUpdateFrameNumber(0), mFrameCnt(0)
	{
	}

	VideoTask::VideoTask() : Task(0), mpFPSOverlay(NULL), mpFPSContainer(NULL), mpFPSTextArea(NULL), mFPSLastUpdateTime(0), mLastUpdateFrameNumber(0), mFrameCnt(0)
	{
	}

	VideoTask::~VideoTask()
	{
		LOG(EngineLog::LM_INFO_ENGINE, "Deleting " << this->getClassName() << ": " << this->getName());

		// Destroy any message queues for this task
		NotificationManager::getSingleton().removeQueue(reinterpret_cast<memUInt>(this));
	}

	void VideoTask::init() throw (Exception)
	{
		Ogre::Root *root;
		Ogre::RenderWindow *window;
		SceneFactory *sceneFactory;
		Scene *scene;
		Ogre::SceneManager *sceneMgr;
		NxOgre::SceneParams sceneParams;
		Ogre::Camera *camera;
		Config *cfg;

		LOG(EngineLog::LM_INFO_ENGINE, "Initializing VideoTask.");

		rwLock.readLock();

		root = Ogre::Root::getSingletonPtr();
		cfg = Config::getSingletonPtr();
		window = NULL;

		if ((root == NULL) || (cfg == NULL))
		{
			rwLock.unlock();
			throw Exception(Exception::E_NULL_POINTER, "VideoTask::init() root or config is NULL!");
		}

		try {
			GlobalLocks::rwLockOgreRoot.writeLock();
			//Load the renderer and the CG plugin for Windows or Linux
			#if defined(__WIN32__) || defined(_WIN32) || defined(_WIN64)
				#ifdef MYOUSHU_DEBUG
					LOG(EngineLog::LM_INFO_ENGINE, "loading Ogre D3D9 plugin.");
					root->loadPlugin("ogred3d9_d");
					LOG(EngineLog::LM_INFO_ENGINE, "loading Ogre CG plugin.");
					root->loadPlugin("ogrecg_d");
				#else
					LOG(EngineLog::LM_INFO_ENGINE, "loading Ogre D3D9 plugin.");
					root->loadPlugin("ogred3d9");
					LOG(EngineLog::LM_INFO_ENGINE, "loading Ogre CG plugin.");
					root->loadPlugin("ogrecg");
				#endif
			#else
				#ifdef MYOUSHU_DEBUG
					LOG(EngineLog::LM_INFO_ENGINE, "loading Ogre GL plugin.");
					root->loadPlugin("libogregl_d");
					LOG(EngineLog::LM_INFO_ENGINE, "loading Ogre CG plugin.");
					root->loadPlugin("libogrecg_d");
				#else
					LOG(EngineLog::LM_INFO_ENGINE, "loading Ogre GL plugin.");
					root->loadPlugin("libogregl");
					LOG(EngineLog::LM_INFO_ENGINE, "loading Ogre CG plugin.");
					root->loadPlugin("libogrecg");
				#endif
			#endif

			Ogre::RenderSystemList *renderSystems = NULL;
			Ogre::RenderSystemList::iterator r_it;

			//we do this step just to get an iterator that we can use with setRenderSystem.
			//The iterator can used to traverse a list of possible renderers.
			renderSystems = root->getAvailableRenderers();
			r_it = renderSystems->begin();
			root->setRenderSystem(*r_it);

			root->initialise(false);
			GlobalLocks::rwLockOgreRoot.unlock();

			//Setup main window.
			Ogre::NameValuePairList opts;
	 		opts["vsync"] = cfg->getBool(Config::VID_VSYNC);
			opts["title"] = Constants::APPLICATION_TITLE;
			opts["border"] = "fixed";

			LOG(EngineLog::LM_INFO_ENGINE, "creating Render window.");

			GlobalLocks::rwLockOgreRoot.writeLock();

			window = root->createRenderWindow(Constants::MAIN_RENDER_TARGET,
  											  cfg->getInt(Config::VID_WIDTH),
											  cfg->getInt(Config::VID_HEIGHT),
											  cfg->getBool(Config::VID_FULLSCREEN), &opts);

			GlobalLocks::rwLockOgreRoot.unlock();

			LOG(EngineLog::LM_INFO_ENGINE, "render window created.");
			LOG(EngineLog::LM_INFO_ENGINE, "Creating default scene manager.");

			// Create the default, generic scene manager
			// Get the sceneFactory singleton pointer
			sceneFactory = SceneFactory::getSingletonPtr();

			// Setup the scene parameters for nxogre
			sceneParams.setToDefault();
			sceneParams.time_step_method = NxOgre::SceneParams::CN_VARIABLE;
			sceneParams.flags &= ~NX_SF_SIMULATE_SEPARATE_THREAD;
			sceneParams.thread_mask = 0;
			sceneParams.background_thread_mask = 0;

			// Create the default scene
			scene = sceneFactory->make(Constants::DEFAULT_SCENE_MANAGER, Ogre::ST_GENERIC, sceneParams);
			sceneMgr = scene->getOgreSceneManager();

			// Create the default camera
			camera = sceneMgr->createCamera(Constants::DEFAULT_CAMERA);

			// Create a viewport for the render window
			window->addViewport(camera);
		}
		catch (Ogre::Exception& e)
		{
			GlobalLocks::rwLockOgreRoot.unlock();
			rwLock.unlock();
			throw Exception(Exception::E_OGRE_EXCEPTION, e.what());
		}
		catch (Poco::Exception& e)
		{
			GlobalLocks::rwLockOgreRoot.unlock();
			rwLock.unlock();
			throw Exception(Exception::E_POCO_EXCEPTION, e.displayText());
		}
		catch (Exception& e)
		{
			GlobalLocks::rwLockOgreRoot.unlock();
			rwLock.unlock();
			throw e;
		}
		catch (std::exception& e)
		{
			GlobalLocks::rwLockOgreRoot.unlock();
			rwLock.unlock();
			throw e;
		}

		rwLock.unlock();
		rwLock.writeLock();

		mFrameCnt = 0;
		state = TS_INITIALIZED;

		// Create the Ogre::Overlay for the frame rate statistics
		createFPSOverlay();

		rwLock.unlock();

		// Setup message handling
		NotificationManager::getSingleton().addObserver(this, &VideoTask::receiveVideoTaskMessage);
	}

	void VideoTask::suspend()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		state = TS_SUSPENDED;
	}

	std::string VideoTask::getFPSStatsString(unsigned long cumulativeDelta)
	{
		TimerTask *pTimerTask;
		std::stringstream fpsStringStream;
		double minFPS;
		double maxFPS;
		double avgFPS;
		double curFPS;

		pTimerTask = TimerTask::getSingletonPtr();

		if (pTimerTask == NULL)
		{
			return "";
		}

		minFPS = 1.0 / (static_cast<double>(pTimerTask->getLargestTimeDelta()) / 1000.0);
		maxFPS = 1.0 / (static_cast<double>(pTimerTask->getSmallestTimeDelta()) / 1000.0);
		avgFPS = static_cast<double>(mFrameCnt) / (static_cast<double>(pTimerTask->getAbsTimeMillis()) / 1000.0);
		curFPS = static_cast<double>(mFrameCnt - mLastUpdateFrameNumber) / (static_cast<double>(cumulativeDelta) / 1000.0);

		fpsStringStream.precision(2);
		fpsStringStream.setf(std::ios::fixed);
		fpsStringStream << "Min FPS: " << minFPS << " Max FPS: " << maxFPS << std::endl << "Avg FPS: " << avgFPS << " FPS: " << curFPS;

		return fpsStringStream.str();
	}

	void VideoTask::execute(unsigned long timeDelta)
	{
		Ogre::Root *rootPtr;
		TimerTask *pTimerTask;

		if (getState() != TS_RUNNING)
		{
			setState(TS_RUNNING);
		}

		{
			Poco::ScopedRWLock lock(rwLock, false);

			pTimerTask = TimerTask::getSingletonPtr();

			// Tell the NotificationManager to deliver all queued messages for this task
			NotificationManager::getSingleton().dispatchQueuedNotifications((memUInt) this);

			// If the FPS text overlay is visible, update it with the latest information
			if ((pTimerTask->getAbsTimeMillis() - mFPSLastUpdateTime >= TIME_BETWEEN_FPS_UPDATES_IN_MILLIS) 
				&& (mpFPSOverlay != NULL) && (mpFPSTextArea != NULL) && (mpFPSOverlay->isVisible()))
			{
				mpFPSTextArea->setCaption(getFPSStatsString(pTimerTask->getAbsTimeMillis() - mFPSLastUpdateTime));
				mFPSLastUpdateTime = pTimerTask->getAbsTimeMillis();
				mLastUpdateFrameNumber = mFrameCnt;
			}

			// Process and send OS messages
			Ogre::WindowEventUtilities::messagePump();

			// We have to use our own locks when accessing
			// Ogre since it is not thread safe.
			GlobalLocks::rwLockOgreRoot.readLock();
			rootPtr = Ogre::Root::getSingletonPtr();
			if (rootPtr != NULL)
			{
				rootPtr->renderOneFrame();
			}
			GlobalLocks::rwLockOgreRoot.unlock();
		}

		{
			Poco::ScopedRWLock lock(rwLock, true);
			mFrameCnt++;
		}
	}

	void VideoTask::kill()
	{
		// Stop receiving messages
		NotificationManager::getSingleton().removeObserver(this, &VideoTask::receiveVideoTaskMessage);

		Poco::ScopedRWLock lock(rwLock, true);

		state = TS_KILLED;
	}

	void VideoTask::receiveVideoTaskMessage(const Poco::AutoPtr<VideoTaskMessage>& pMessage) throw (Exception)
	{
		// Check that pMessage is not NULL
		if (pMessage.get() == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "VideoTask::receiveVideoTaskMessage(): pMessage is NULL!");
		}

		Poco::ScopedRWLock lock(rwLock, false);

		switch (pMessage->getMessageType())
		{
			case VideoTaskMessage::VM_SHOW_FPS:
				mpFPSOverlay->show();
				break;
			case VideoTaskMessage::VM_HIDE_FPS:
				mpFPSOverlay->hide();
				break;
			case VideoTaskMessage::VM_UNKNOWN:
			default:
				LOG(EngineLog::LM_WARNING, "VIdeoTask::receiveVideoTaskMessage(): received unknown message...");
				break;
		}
	}

	void VideoTask::createFPSOverlay()
	{
		mpFPSOverlay = Ogre::OverlayManager::getSingleton().create("FPSOverlay");

		mpFPSContainer = static_cast<Ogre::OverlayContainer*>(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "FPSOverlayPanel"));
		mpFPSContainer->setMetricsMode(Ogre::GMM_RELATIVE);
		mpFPSContainer->setTop(0.01);
		mpFPSContainer->setLeft(0.75);
		mpFPSContainer->setDimensions(0.25, 0.1);
		mpFPSOverlay->add2D(mpFPSContainer);

		mpFPSTextArea = static_cast<Ogre::TextAreaOverlayElement*>(Ogre::OverlayManager::getSingleton().createOverlayElement("TextArea", "FPSOverlayTextArea"));
		mpFPSTextArea->setMetricsMode(Ogre::GMM_RELATIVE);
		mpFPSTextArea->setColour(Ogre::ColourValue());
		mpFPSTextArea->setTop(0);
		mpFPSTextArea->setLeft(0);
		mpFPSTextArea->setFontName("DejaVuSans");
		mpFPSTextArea->setCharHeight(0.02);
		mpFPSTextArea->setDimensions(0.9, 0.9);
		mpFPSContainer->addChild(mpFPSTextArea);

		mpFPSOverlay->hide();
	}

} // Myoushu

