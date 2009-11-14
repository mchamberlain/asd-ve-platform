%module MyGUI
%{
	#include "MyGUI_Platform.h"
	#include "MyGUI_Prerequest.h"
	#include "MyGUI_Common.h"
	#include "MyGUI_InputDefine.h"
	#include "MyGUI_EventPair.h"
	#include "MyGUI_WidgetStyle.h"
	#include "MyGUI_Rtti.h"
	#include "MyGUI_UString.h"
	#include "MyGUI_Align.h"
	#include "MyGUI_ICroppedRectangle.h"
	#include "MyGUI_TPoint.h"
	#include "MyGUI_TSize.h"
	#include "MyGUI_TRect.h"
	#include "MyGUI_TCoord.h"
	#include "MyGUI_Types.h"
	#include "MyGUI_Colour.h"
	#include "MyGUI_Version.h"
	#include "MyGUI_Data.h"
	#include "MyGUI_Enumerator.h"
	#include "MyGUI_RenderTargetInfo.h"
	#include "MyGUI_IRenderTarget.h"
	#include "MyGUI_IDrawItem.h"
	#include "MyGUI_ILayerNode.h"
	#include "MyGUI_ILayer.h"
	//#include "MyGUI_ILayerFactory.h"
	#include "MyGUI_XmlDocument.h"
	//#include "MyGUI_LayerItem.h"
	//#include "MyGUI_LayerItemKeeper.h"
	//#include "MyGUI_LayerKeeper.h"
	#include "MyGUI_LayerManager.h"
	#include "MyGUI_WidgetUserData.h"
	#include "MyGUI_WidgetDefines.h"
	#include "MyGUI_ChildSkinInfo.h"
	#include "MyGUI_WidgetSkinInfo.h"
	#include "MyGUI_IStateInfo.h"
	#include "MyGUI_ISubWidget.h"
	#include "MyGUI_SubWidgetBinding.h"
	#include "MyGUI_ISubWidgetText.h"
	#include "MyGUI_ISubWidgetRect.h"
	#include "MyGUI_IWidgetCreator.h"
	#include "MyGUI_WidgetEvent.h"
	#include "MyGUI_Widget.h"
	#include "MyGUI_StaticText.h"
	#include "MyGUI_Edit.h"
	#include "MyGUI_Button.h"
	#include "MyGUI_Progress.h"
	#include "MyGUI_List.h"
	#include "MyGUI_MultiList.h"
%}

// Proper Java enums
#ifdef SWIGJAVA
%include "enums.swg"
#endif

#ifdef SWIGLUA
	%apply SWIGTYPE *DYNAMIC {MyGUI::Widget *};
	// DYNAMIC CAST of MyGUI::Widget
	%{
	static swig_type_info *
	_cast_MyGUI__Widget(void **ptr) {
	   MyGUI::ComboBox *p7 = dynamic_cast<MyGUI::ComboBox*>(reinterpret_cast<MyGUI::Widget*>(*ptr));
	   if (p7) {
		  *ptr = reinterpret_cast<void*>(p7);
		  return SWIGTYPE_p_MyGUI__ComboBox;
	   }
	   
	   MyGUI::Edit *p1 = dynamic_cast<MyGUI::Edit*>(reinterpret_cast<MyGUI::Widget*>(*ptr));
	   if (p1) {
		  *ptr = reinterpret_cast<void*>(p1);
		  return SWIGTYPE_p_MyGUI__Edit;
	   }
	   
	   MyGUI::Button *p2 = dynamic_cast<MyGUI::Button*>(reinterpret_cast<MyGUI::Widget*>(*ptr));
	   if (p2) {
		  *ptr = reinterpret_cast<void*>(p2);
		  return SWIGTYPE_p_MyGUI__Button;
	   }
	   
	   MyGUI::Progress *p3 = dynamic_cast<MyGUI::Progress*>(reinterpret_cast<MyGUI::Widget*>(*ptr));
	   if (p3) {
		  *ptr = reinterpret_cast<void*>(p3);
		  return SWIGTYPE_p_MyGUI__Progress;
	   }
	   
	   MyGUI::StaticText *p4 = dynamic_cast<MyGUI::StaticText*>(reinterpret_cast<MyGUI::Widget*>(*ptr));
	   if (p4) {
		  *ptr = reinterpret_cast<void*>(p4);
		  return SWIGTYPE_p_MyGUI__StaticText;
	   }
		 
	   MyGUI::MultiList *p6 = dynamic_cast<MyGUI::MultiList*>(reinterpret_cast<MyGUI::Widget*>(*ptr));
	   if (p6) {
		  *ptr = reinterpret_cast<void*>(p6);
		  return SWIGTYPE_p_MyGUI__MultiList;
	   }
		 
	   MyGUI::List *p5 = dynamic_cast<MyGUI::List*>(reinterpret_cast<MyGUI::Widget*>(*ptr));
	   if (p5) {
		  *ptr = reinterpret_cast<void*>(p5);
		  return SWIGTYPE_p_MyGUI__List;
	   }
		 
	   return 0;
	}
	%}
	DYNAMIC_CAST(SWIGTYPE_p_MyGUI__Widget, _cast_MyGUI__Widget);
#endif

%include "std_string.i"

%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_Platform.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_Prerequest.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_Common.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_InputDefine.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_WidgetStyle.h"

// Remove the __declspec(deprecated) or __attribute__(deprecated) since SWIG does not support it
#define MYGUI_OBSOLETE(text)

%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_EventPair.h"
%include "MyGUI_UString.i"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_Align.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_TPoint.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_TSize.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_TRect.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_TCoord.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_Types.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_Colour.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_ICroppedRectangle.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_Version.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_Data.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_Enumerator.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_XmlDocument.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_RenderTargetInfo.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_IRenderTarget.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_IDrawItem.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_ILayerNode.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_ILayer.h"
//%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_ILayerFactory.h"
// Ignore two troublesome functions from MyGUI::UserData: the MyGUI::Any class is difficult to wrap, and we don't really need it
%ignore MyGUI::UserData::setUserData(Any);
%ignore MyGUI::UserData::_setInternalData(Any);
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_WidgetUserData.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_WidgetDefines.h"
//%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_LayerItem.h"
//%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_LayerItemKeeper.h"
//%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_LayerKeeper.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_LayerManager.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_IStateInfo.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_SubWidgetBinding.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_ChildSkinInfo.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_WidgetSkinInfo.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_ISubWidget.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_ISubWidgetText.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_ISubWidgetRect.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_IWidgetCreator.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_WidgetEvent.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_Widget.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_StaticText.h"
%ignore MyGUI::Edit::getTextSelect(size_t& s, size_t& e);
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_Edit.h"
%ignore MyGUI::Button::getStaticImage();
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_Button.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_Progress.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_List.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_MultiList.h"
%include "../../3rdparty/MyGUI_2.0.1_source/MyGUIEngine/include/MyGUI_ComboBox.h"
