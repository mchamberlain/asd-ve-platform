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
 * @file MyoushuDotSceneNodeProcessorTreeBuilder.cpp
 * @author ME Chamberlain
 * @date February 2009
 */

#include "MyoushuDotSceneEntityElementProcessor.h"
#include "MyoushuDotSceneNodeProcessorTreeBuilder.h"

namespace Myoushu
{
	MyoushuDotSceneNodeProcessorTreeBuilder::MyoushuDotSceneNodeProcessorTreeBuilder(CommonParamsOfXmlNodeProcessors* commonParams) : Ogre::dsi::DotSceneNodeProcessorTreeBuilder(commonParams)
	{
	}

	MyoushuDotSceneNodeProcessorTreeBuilder::~MyoushuDotSceneNodeProcessorTreeBuilder()
	{
	}

	XmlNodeProcessor* MyoushuDotSceneNodeProcessorTreeBuilder::buildTree()
	{
		// This method is mostly copied from dotSceneNodeProcessorTreeBuilder.cpp, with some minor changes added for the specific functionality
		// we require, such as connecting Ogre::Entities with Myoushu::GameObjects and adding support for user data.

		// ----------------------------------------- Allocate memory for XmlNodeProcessors -----------------------------------------
		mSceneElementProcessor								= new SceneElementProcessor;

		mSceneManagerOptionElementProcessor					= new SceneManagerOptionElementProcessor;
		mShadowSettingsElementProcessor						= new ShadowSettingsElementProcessor;
			mShadowTextureConfigElementProcessor			= new ShadowTextureConfigElementProcessor;

		mResourceGroupElementProcessor						= new ResourceGroupElementProcessor;
			mResourceLocationElementProcessor				= new ResourceLocationElementProcessor;
			mResourceDeclarationElementProcessor			= new ResourceDeclarationElementProcessor;
				mNameValuePairListElementProcessor			= new NameValuePairListElementProcessor;
					mNameValuePairElementProcessor			= new NameValuePairElementProcessor;

		mRenderTargetsElementProcessor						= new RenderTargetsElementProcessor;
		mRenderWindowElementProcessor						= new RenderWindowElementProcessor;

		mEnvironmentElementProcessor						= new EnvironmentElementProcessor;
			mFogElementProcessor							= new FogElementProcessor;
			mSkyBoxElementProcessor							= new SkyBoxElementProcessor;
			mSkyDomeElementProcessor						= new SkyDomeElementProcessor;
			mSkyPlaneElementProcessor						= new SkyPlaneElementProcessor;
			mColourAmbientElementProcessor					= new ColourAmbientElementProcessor;
			mColourBackgroundElementProcessor				= new ColourBackgroundElementProcessor;

		mTrackTargetElementProcessor						= new TrackTargetElementProcessor;
			mLocalDirectionVectorElementProcessor			= new LocalDirectionVectorElementProcessor;
			mOffsetElementProcessor							= new OffsetElementProcessor;

		mLookTargetElementProcessor							= new LookTargetElementProcessor;

		mLightElementProcessor								= new LightElementProcessor;
			mColourDiffuseElementProcessor					= new ColourDiffuseElementProcessor;
			mColourSpecularElementProcessor					= new ColourSpecularElementProcessor;
			mSpotLightRangeElementProcessor					= new SpotLightRangeElementProcessor;
			mLightAttenuationElementProcessor				= new LightAttenuationElementProcessor;
		mCameraElementProcessor								= new CameraElementProcessor;
			mClippingElementProcessor						= new ClippingElementProcessor;

		mNodesElementProcessor								= new NodesElementProcessor;
		mNodeElementProcessor								= new NodeElementProcessor;
			mEntityElementProcessor							= new MyoushuDotSceneEntityElementProcessor;
				mMeshLODBiasElementProcessor				= new MeshLODBiasElementProcessor;
				mMaterialLODBiasElementProcessor			= new MaterialLODBiasElementProcessor;
			mParticleSystemElementProcessor					= new ParticleSystemElementProcessor;
			mBillboardSetElementProcessor					= new BillboardSetElementProcessor;
				mBillboardElementProcessor					= new BillboardElementProcessor;
				mCommonDirectionElementProcessor			= new CommonDirectionElementProcessor;
				mCommonUpVectorElementProcessor				= new CommonUpVectorElementProcessor;
				mTextureCoordsElementProcessor				= new TextureCoordsElementProcessor;
					mFloatRectElementProcessor				= new FloatRectElementProcessor;
				mTextureStacksAndSlicesElementProcessor 	= new TextureStacksAndSlicesElementProcessor;


		mViewportsElementProcessor							= new ViewportsElementProcessor;
			mViewportElementProcessor						= new ViewportElementProcessor;
				mCompositorInstancesElementProcessor		= new CompositorInstancesElementProcessor;
					mCompositorInstanceElementProcessor		= new CompositorInstanceElementProcessor;
					mHDRCompositorInstanceElementProcessor	= new HDRCompositorInstanceElementProcessor;



		mAnimationsElementProcessor							= new AnimationsElementProcessor;
			mAnimationElementProcessor						= new AnimationElementProcessor;
				mNodeAnimationTrackElementProcessor			= new NodeAnimationTrackElementProcessor;
					mTransformKeyFrameElementProcessor		= new TransformKeyFrameElementProcessor;
				mVertexAnimationTrackElementProcessor		= new VertexAnimationTrackElementProcessor;
					mVertexPoseKeyFrameElementProcessor		= new VertexPoseKeyFrameElementProcessor;
						mPoseReferenceElementProcessor		= new PoseReferenceElementProcessor;
		mAnimationStatesElementProcessor					= new AnimationStatesElementProcessor;
			mAnimationStateElementProcessor					= new AnimationStateElementProcessor;


		mCommonMovableObjectParamsElementProcessor			= new CommonMovableObjectParamsElementProcessor;

		mPositionElementProcessor							= new PositionElementProcessor;
		mOrientationElementProcessor						= new OrientationElementProcessor;
			mQuaternionElementProcessor						= new QuaternionElementProcessor;
			mAngle_AxisElementProcessor						= new Angle_AxisElementProcessor;
			mAxisXYZElementProcessor						= new AxisXYZElementProcessor;
			mDirectionElementProcessor						= new DirectionElementProcessor;
		mScaleElementProcessor								= new ScaleElementProcessor;

		mUserDataElementProcessor							= new MyoushuDotSceneUserDataElementProcessor;
		mPropertyElementProcessor							= new MyoushuDotScenePropertyElementProcessor;

#ifdef _USE_DOT_OCTREE
		mOctreeElementProcessor								= new OctreeElementProcessor;
#endif
		// -------------------------------------------------------------------------------------------------------------------------

		// --------------------------------------- Notify XmlNodeProcessors of tree builder ----------------------------------------
		mSceneElementProcessor->							_notifyTreeBuilder(this);

		mSceneManagerOptionElementProcessor->				_notifyTreeBuilder(this);
		mShadowSettingsElementProcessor->					_notifyTreeBuilder(this);
			mShadowTextureConfigElementProcessor->			_notifyTreeBuilder(this);

		mResourceGroupElementProcessor->					_notifyTreeBuilder(this);
			mResourceLocationElementProcessor->				_notifyTreeBuilder(this);
			mResourceDeclarationElementProcessor->			_notifyTreeBuilder(this);
				mNameValuePairListElementProcessor->		_notifyTreeBuilder(this);
					mNameValuePairElementProcessor->		_notifyTreeBuilder(this);

		mRenderTargetsElementProcessor->					_notifyTreeBuilder(this);
		mRenderWindowElementProcessor->						_notifyTreeBuilder(this);

		mEnvironmentElementProcessor->						_notifyTreeBuilder(this);
			mFogElementProcessor->							_notifyTreeBuilder(this);
			mSkyBoxElementProcessor->						_notifyTreeBuilder(this);
			mSkyDomeElementProcessor->						_notifyTreeBuilder(this);
			mSkyPlaneElementProcessor->						_notifyTreeBuilder(this);
			mColourAmbientElementProcessor->				_notifyTreeBuilder(this);
			mColourBackgroundElementProcessor->				_notifyTreeBuilder(this);

		mTrackTargetElementProcessor->						_notifyTreeBuilder(this);
			mLocalDirectionVectorElementProcessor->			_notifyTreeBuilder(this);
			mOffsetElementProcessor->						_notifyTreeBuilder(this);

		mLookTargetElementProcessor->						_notifyTreeBuilder(this);

		mLightElementProcessor->							_notifyTreeBuilder(this);
			mColourDiffuseElementProcessor->				_notifyTreeBuilder(this);
			mColourSpecularElementProcessor->				_notifyTreeBuilder(this);
			mSpotLightRangeElementProcessor->				_notifyTreeBuilder(this);
			mLightAttenuationElementProcessor->				_notifyTreeBuilder(this);
		mCameraElementProcessor->							_notifyTreeBuilder(this);
			mClippingElementProcessor->						_notifyTreeBuilder(this);

		mNodesElementProcessor->							_notifyTreeBuilder(this);
		mNodeElementProcessor->								_notifyTreeBuilder(this);
			mEntityElementProcessor->						_notifyTreeBuilder(this);
				mMeshLODBiasElementProcessor->				_notifyTreeBuilder(this);
				mMaterialLODBiasElementProcessor->			_notifyTreeBuilder(this);
			mParticleSystemElementProcessor->				_notifyTreeBuilder(this);
			mBillboardSetElementProcessor->					_notifyTreeBuilder(this);
				mBillboardElementProcessor->				_notifyTreeBuilder(this);
				mCommonDirectionElementProcessor->			_notifyTreeBuilder(this);
				mCommonUpVectorElementProcessor->			_notifyTreeBuilder(this);
				mTextureCoordsElementProcessor->			_notifyTreeBuilder(this);
					mFloatRectElementProcessor->			_notifyTreeBuilder(this);
				mTextureStacksAndSlicesElementProcessor->	_notifyTreeBuilder(this);

		mViewportsElementProcessor->						_notifyTreeBuilder(this);
			mViewportElementProcessor->						_notifyTreeBuilder(this);
				mCompositorInstancesElementProcessor->		_notifyTreeBuilder(this);
					mCompositorInstanceElementProcessor->	_notifyTreeBuilder(this);
					mHDRCompositorInstanceElementProcessor->_notifyTreeBuilder(this);


		mAnimationsElementProcessor->						_notifyTreeBuilder(this);
			mAnimationElementProcessor->					_notifyTreeBuilder(this);
				mNodeAnimationTrackElementProcessor->		_notifyTreeBuilder(this);
					mTransformKeyFrameElementProcessor->	_notifyTreeBuilder(this);
				mVertexAnimationTrackElementProcessor->		_notifyTreeBuilder(this);
					mVertexPoseKeyFrameElementProcessor->	_notifyTreeBuilder(this);
						mPoseReferenceElementProcessor->	_notifyTreeBuilder(this);
		mAnimationStatesElementProcessor->					_notifyTreeBuilder(this);
			mAnimationStateElementProcessor->				_notifyTreeBuilder(this);


		mCommonMovableObjectParamsElementProcessor->		_notifyTreeBuilder(this);

		mPositionElementProcessor->							_notifyTreeBuilder(this);
		mOrientationElementProcessor->						_notifyTreeBuilder(this);
			mQuaternionElementProcessor->					_notifyTreeBuilder(this);
			mAngle_AxisElementProcessor->					_notifyTreeBuilder(this);
			mAxisXYZElementProcessor->						_notifyTreeBuilder(this);
			mDirectionElementProcessor->					_notifyTreeBuilder(this);
		mScaleElementProcessor->							_notifyTreeBuilder(this);

		mUserDataElementProcessor->							_notifyTreeBuilder(this);
		mPropertyElementProcessor->							_notifyTreeBuilder(this);

#ifdef _USE_DOT_OCTREE
		mOctreeElementProcessor->							_notifyTreeBuilder(this);
#endif
		// -------------------------------------------------------------------------------------------------------------------------



		// ---------------------------------------------- Register XmlNodeProcessors -----------------------------------------------

		// Register the root processor first.
			registerRootProcessor( "/root", mSceneElementProcessor );

		// Since orientation has sub-elements and it is used as a sub-element processor for many dotScene elements, add element
		// processors for it before registering sub-element processors for other processors.
		// <orientation>
			registerElementProcessor( "quaternion", mOrientationElementProcessor, mQuaternionElementProcessor );
			registerElementProcessor( "angle_axis", mOrientationElementProcessor, mAngle_AxisElementProcessor );
			registerElementProcessor( "axisXYZ", mOrientationElementProcessor, mAxisXYZElementProcessor );
			registerElementProcessor( "direction", mOrientationElementProcessor, mDirectionElementProcessor );
		// </orientation>

		// Register the sub-elements of userData
		// <userData>
			registerElementProcessor( "property", mUserDataElementProcessor, mPropertyElementProcessor );
		// </userData>

		// <scene>
			
			// <sceneManagerOption>
			registerElementProcessor( "sceneManagerOption", mSceneElementProcessor, mSceneManagerOptionElementProcessor );
			// </sceneManagerOption>

			// <shadowSettings>
			registerElementProcessor( "shadowSettings", mSceneElementProcessor, mShadowSettingsElementProcessor );

				// <colourDiffuse>
				registerElementProcessor( "colourDiffuse", mShadowSettingsElementProcessor, mColourDiffuseElementProcessor );
				// </colourDiffuse>

				// <shadowTextureConfig>
				registerElementProcessor( "shadowTextureConfig", mShadowSettingsElementProcessor, mShadowTextureConfigElementProcessor );
				// </shadowTextureConfig>
			// </shadowSettings>
			
			// <resourceGroup>
			registerElementProcessor( "resourceGroup", mSceneElementProcessor, mResourceGroupElementProcessor );

				// <resourceLocation>
				registerElementProcessor( "resourceLocation", mResourceGroupElementProcessor, mResourceLocationElementProcessor );
				// </resourceLocation>

				// <resourceDeclaration>
				registerElementProcessor( "resourceDeclaration", mResourceGroupElementProcessor, mResourceDeclarationElementProcessor );
					
					// <NameValuePairList>
					registerElementProcessor( "NameValuePairList", mResourceDeclarationElementProcessor, mNameValuePairListElementProcessor );
						// <NameValuePair>
						registerElementProcessor( "NameValuePair", mNameValuePairListElementProcessor, mNameValuePairElementProcessor );
						// </NameValuePair>
					// </NameValuePairList>
				// </resourceDeclaration>

			// </resourceGroup>

		
			// <renderTargets>
			registerElementProcessor( "renderTargets", mSceneElementProcessor, mRenderTargetsElementProcessor );

				// <renderWindow>
				registerElementProcessor( "renderWindow", mRenderTargetsElementProcessor, mRenderWindowElementProcessor );

				// </renderWindow>

				// <renderTexture>

				// </renderTexture>

				// <multiRenderTarget>

					// <renderTexture>
					// </renderTexture>
				// </multiRenderTarget>
			// </renderTargets>


			// <environment>
			registerElementProcessor( "environment", mSceneElementProcessor, mEnvironmentElementProcessor );

				// <fog>
				registerElementProcessor( "fog", mEnvironmentElementProcessor, mFogElementProcessor );
				// </fog>

				// <skyBox>
				registerElementProcessor( "skyBox", mEnvironmentElementProcessor, mSkyBoxElementProcessor );
					// <orientation>
					registerElementProcessor( "orientation", mSkyBoxElementProcessor, mOrientationElementProcessor );
					// </orientation>
				// </skyBox>

				// <skyDome>
				registerElementProcessor( "skyDome", mEnvironmentElementProcessor, mSkyDomeElementProcessor );
					// <orientation>
					registerElementProcessor( "orientation", mSkyDomeElementProcessor, mOrientationElementProcessor );
					// </orientation>
				// </skyDome>

				// <skyPlane>
				registerElementProcessor( "skyPlane", mEnvironmentElementProcessor, mSkyPlaneElementProcessor );
				// </skyPlane>

				// <colourAmbient>
				registerElementProcessor( "colourAmbient", mEnvironmentElementProcessor, mColourAmbientElementProcessor );
				// </colourAmbient>

				// <colourBackground>
				registerElementProcessor( "colourBackground", mEnvironmentElementProcessor, mColourBackgroundElementProcessor );
				// </colourBackground>
			// </environment>


			// <light>
			registerElementProcessor( "light", mSceneElementProcessor, mLightElementProcessor );

					// <commonMovableObjectParams>
					registerElementProcessor( "commonMovableObjectParams", mLightElementProcessor, mCommonMovableObjectParamsElementProcessor );
					// </commonMovableObjectParams>

					// <position>
					registerElementProcessor( "position", mLightElementProcessor, mPositionElementProcessor );
					// </position>

					// <direction>
					registerElementProcessor( "direction", mLightElementProcessor, mDirectionElementProcessor );
					// </direction>

					// TODO: uncomment this if Ogre starts to support arbitrary light shapes. (E.g. used with cubic-attenution maps.)
					// <orientation>
//					registerElementProcessor( "orientation", mLightElementProcessor, mOrientationElementProcessor );
					// </orientation>

					// <colourDiffuse>
					registerElementProcessor( "colourDiffuse", mLightElementProcessor, mColourDiffuseElementProcessor );
					// </colourDiffuse>

					// <colourSpecular>
					registerElementProcessor( "colourSpecular", mLightElementProcessor, mColourSpecularElementProcessor );
					// </colourSpecular>

					// <spotLightRange>
					registerElementProcessor( "spotLightRange", mLightElementProcessor, mSpotLightRangeElementProcessor );
					// </spotLightRange>

					// <lightAttenuation>
					registerElementProcessor( "lightAttenuation", mLightElementProcessor, mLightAttenuationElementProcessor );
					// </lightAttenuation>

					// <userData>
					registerElementProcessor( "userData", mLightElementProcessor, mUserDataElementProcessor );
					// </userData>
			// </light>

			// <camera>
			registerElementProcessor( "camera", mSceneElementProcessor, mCameraElementProcessor );

					// <commonMovableObjectParams>
					registerElementProcessor( "commonMovableObjectParams", mCameraElementProcessor, mCommonMovableObjectParamsElementProcessor );
					// </commonMovableObjectParams>

					// <clipping>
					registerElementProcessor( "clipping", mCameraElementProcessor, mClippingElementProcessor );
					// </clipping>

					// <position>
					registerElementProcessor( "position", mCameraElementProcessor, mPositionElementProcessor );
					// </position>

					// <orientation>
					registerElementProcessor( "orientation", mCameraElementProcessor, mOrientationElementProcessor );
					// </orientation>

					// <trackTarget>
					registerElementProcessor( "trackTarget", mCameraElementProcessor, mTrackTargetElementProcessor );

						// <localDirectionVector>
						registerElementProcessor( "localDirectionVector", mTrackTargetElementProcessor, mLocalDirectionVectorElementProcessor );
						// </localDirectionVector>

						// <offset>
						registerElementProcessor( "offset", mTrackTargetElementProcessor, mOffsetElementProcessor );
						// </offset>
					// </trackTarget>					

					// <lookTarget>
					registerElementProcessor( "lookTarget", mCameraElementProcessor, mLookTargetElementProcessor );

						// <position>
						registerElementProcessor( "position", mLookTargetElementProcessor, mPositionElementProcessor );
						// </position>

						// <localDirectionVector>
						registerElementProcessor( "localDirectionVector", mLookTargetElementProcessor, mLocalDirectionVectorElementProcessor );
						// </localDirectionVector>
					// </lookTarget>					

					// <userData>
					registerElementProcessor( "userData", mCameraElementProcessor, mUserDataElementProcessor );
					// </userData>
			// </camera>

			// <nodes>
				registerElementProcessor( "nodes", mSceneElementProcessor, mNodesElementProcessor );
				
				// <position>
				registerElementProcessor( "position", mNodesElementProcessor, mPositionElementProcessor );
				// </position>

				// <orientation>
				registerElementProcessor( "orientation", mNodesElementProcessor, mOrientationElementProcessor );
				// </orientation>

				// <scale>
				registerElementProcessor( "scale", mNodesElementProcessor, mScaleElementProcessor );
				// </scale>

				// <light>
				registerElementProcessor( "light", mNodesElementProcessor, mLightElementProcessor );
				// </light>

				// <camera>
				registerElementProcessor( "camera", mNodesElementProcessor, mCameraElementProcessor );
				// </camera>

				// <node>
				registerElementProcessor( "node", mNodesElementProcessor, mNodeElementProcessor );

					// <position>
					registerElementProcessor( "position", mNodeElementProcessor, mPositionElementProcessor );
					// </position>

					// <orientation>
					registerElementProcessor( "orientation", mNodeElementProcessor, mOrientationElementProcessor );
					// </orientation>

					// <scale>
					registerElementProcessor( "scale", mNodeElementProcessor, mScaleElementProcessor );
					// </scale>

					// <trackTarget>
					registerElementProcessor( "trackTarget", mNodeElementProcessor, mTrackTargetElementProcessor );
					// </trackTarget>

					// <lookTarget>
					registerElementProcessor( "lookTarget", mNodeElementProcessor, mLookTargetElementProcessor );
					// </lookTarget>

					// <node>
					registerElementProcessor( "node", mNodeElementProcessor, mNodeElementProcessor );
					// </node>

					// <entity>
					registerElementProcessor( "entity", mNodeElementProcessor, mEntityElementProcessor );
						// <commonMovableObjectParams>
						registerElementProcessor( "commonMovableObjectParams", mEntityElementProcessor, mCommonMovableObjectParamsElementProcessor );
						// </commonMovableObjectParams>

						// <animations>
						registerElementProcessor( "animations", mEntityElementProcessor, mAnimationsElementProcessor );
						
							// <animation>
							registerElementProcessor( "animation", mAnimationsElementProcessor, mAnimationElementProcessor );

								// <nodeAnimationTrack>
								registerElementProcessor( "nodeAnimationTrack", mAnimationElementProcessor, mNodeAnimationTrackElementProcessor );

									// <transformKeyFrame>
									registerElementProcessor( "transformKeyFrame", mNodeAnimationTrackElementProcessor, mTransformKeyFrameElementProcessor );

										// <translate>
										registerElementProcessor( "translation", mTransformKeyFrameElementProcessor, mPositionElementProcessor );
										// </translate>

										// <orientation>
										registerElementProcessor( "orientation", mTransformKeyFrameElementProcessor, mOrientationElementProcessor );
										// </orientation>

										// <scale>
										registerElementProcessor( "scale", mTransformKeyFrameElementProcessor, mScaleElementProcessor );
										// </scale>
									// </transformKeyFrame>
								// </nodeAnimationTrack>

								// <vertexAnimationTrack>				
								registerElementProcessor( "vertexAnimationTrack", mAnimationElementProcessor, mVertexAnimationTrackElementProcessor );

									// <vertexPoseKeyFrame>
									registerElementProcessor( "vertexPoseKeyFrame", mVertexAnimationTrackElementProcessor, mVertexPoseKeyFrameElementProcessor );

										// <poseReference>
										registerElementProcessor( "poseReference", mVertexPoseKeyFrameElementProcessor, mPoseReferenceElementProcessor );
										// </poseReference>
									// </vertexPoseKeyFrame>
								// </vertexAnimationTrack>
							// </animation>
						// </animations>

						// <animationStates>
						registerElementProcessor( "animationStates", mEntityElementProcessor, mAnimationStatesElementProcessor );
							// <animationState>
							registerElementProcessor( "animationState", mAnimationStatesElementProcessor, mAnimationStateElementProcessor );
							// </animationState>
						// </animationStates>

						// <meshLODBias>
						registerElementProcessor( "meshLODBias", mEntityElementProcessor, mMeshLODBiasElementProcessor );
						// </meshLODBias>

						// <materialLODBias>
						registerElementProcessor( "materialLODBias", mEntityElementProcessor, mMaterialLODBiasElementProcessor );
						// </materialLODBias>

						// <userData>
						registerElementProcessor( "userData", mEntityElementProcessor, mUserDataElementProcessor );
						// </userData>
					// </entity>

					// <light>
					registerElementProcessor( "light", mNodeElementProcessor, mLightElementProcessor );
					// </light>

					// <camera>
					registerElementProcessor( "camera", mNodeElementProcessor, mCameraElementProcessor );
					// </camera>

					// <particleSystem>
					registerElementProcessor( "particleSystem", mNodeElementProcessor, mParticleSystemElementProcessor );
						// <commonMovableObjectParams>
						registerElementProcessor( "commonMovableObjectParams", mParticleSystemElementProcessor, mCommonMovableObjectParamsElementProcessor );
						// </commonMovableObjectParams>
					// </particleSystem>

					// <billboardSet>
					registerElementProcessor( "billboardSet", mNodeElementProcessor, mBillboardSetElementProcessor );

						// <commonMovableObjectParams>
						registerElementProcessor( "commonMovableObjectParams", mBillboardSetElementProcessor, mCommonMovableObjectParamsElementProcessor );
						// </commonMovableObjectParams>

						// <billboard>
						registerElementProcessor( "billboard", mBillboardSetElementProcessor, mBillboardElementProcessor );

							// <position>
							registerElementProcessor( "position", mBillboardElementProcessor, mPositionElementProcessor );
							// </position>

							// <colourDiffuse>
							registerElementProcessor( "colourDiffuse", mBillboardElementProcessor, mColourDiffuseElementProcessor );
							// </colourDiffuse>

							// <textureCoords>
							registerElementProcessor( "textureCoords", mBillboardElementProcessor, mTextureCoordsElementProcessor );
							// </textureCoords>
						// </billboard>

						// <commonDirection>
						registerElementProcessor( "commonDirection", mBillboardSetElementProcessor, mCommonDirectionElementProcessor );
						// </commonDirection>

						// <commonUpVector>
						registerElementProcessor( "commonUpVector", mBillboardSetElementProcessor, mCommonUpVectorElementProcessor );
						// </commonUpVector>

						// <textureCoords>
						registerElementProcessor( "textureCoords", mBillboardSetElementProcessor, mTextureCoordsElementProcessor );
							// <floatRect>
							registerElementProcessor( "floatRect", mTextureCoordsElementProcessor, mFloatRectElementProcessor );
							// </floatRect>
						// </textureCoords>

						// <textureStacksAndSlices>
						registerElementProcessor( "textureStacksAndSlices", mBillboardSetElementProcessor, mTextureStacksAndSlicesElementProcessor );
						// </textureStacksAndSlices>
					// </billboardSet>

				// </node>
			// </nodes>


			// <viewports>
			registerElementProcessor( "viewports", mSceneElementProcessor, mViewportsElementProcessor );
				// <viewport>
				registerElementProcessor( "viewport", mViewportsElementProcessor, mViewportElementProcessor );
					
					// <compositorInstances>
					registerElementProcessor( "compositorInstances", mViewportElementProcessor, mCompositorInstancesElementProcessor );
						
						// <compositorInstance>
						registerElementProcessor( "compositorInstance", mCompositorInstancesElementProcessor, mCompositorInstanceElementProcessor );
						// </compositorInstance>

						// <HDRCompositorInstance>
						registerElementProcessor( "HDRCompositorInstance", mCompositorInstancesElementProcessor, mHDRCompositorInstanceElementProcessor );
						// </HDRCompositorInstance>
					// </compositorInstances>

				// </viewport>
			// </viewports>

			// <animations>
			registerElementProcessor( "animations", mSceneElementProcessor, mAnimationsElementProcessor );
			// </animations>

			// <animationStates>
			registerElementProcessor( "animationStates", mSceneElementProcessor, mAnimationStatesElementProcessor );
			// </animationStates>

#ifdef _USE_DOT_OCTREE
			// <octree>
			registerElementProcessor( "octree", mSceneElementProcessor, mOctreeElementProcessor );
			// </octree>
#endif

		// </scene>

		// -------------------------------------------------------------------------------------------------------------------------

		return mSceneElementProcessor;
	}

} // namespace Myoushu
