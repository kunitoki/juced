/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2007 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2007 by Julian Storer.

 ------------------------------------------------------------------------------

 JUCE and JUCETICE can be redistributed and/or modified under the terms of
 the GNU Lesser General Public License, as published by the Free Software
 Foundation; either version 2 of the License, or (at your option) any later
 version.

 JUCE and JUCETICE are distributed in the hope that they will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with JUCE and JUCETICE; if not, visit www.gnu.org/licenses or write to
 Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 Boston, MA 02111-1307 USA

 ==============================================================================
*/

#ifndef __JUCETICE_JOSTCHANNELEDITOR_HEADER__
#define __JUCETICE_JOSTCHANNELEDITOR_HEADER__

#include "../../../StandardHeader.h"
#include "../../../Config.h"
#include "../../../HostFilterComponent.h"
#include "../../../ui/windows/VstPluginWindow.h"
#include "../../../ui/plugins/PluginEditorComponent.h"
#include "../../../ui/plugins/PluginEditorWindowHolder.h"
#include "ChannelGraphComponent.h"
#include "ChannelPlugin.h"

//#include "../TrackEditorContainer.h"

class ChannelPlugin;
class ChannelGraphComponent;
class ChannelHost;


//==============================================================================
/**

    The ChannelPlugin editor: this holds the subgraph component
	@Spankache

*/
class ChannelEditor  : public PluginEditorComponent,
                        public PluginEditorWindowHolder,
						public ChangeListener
{
public:

    //==============================================================================
    ChannelEditor (ChannelPlugin* owner_);
    ~ChannelEditor();

    //==============================================================================
    int getPreferredWidth ();                        
    int getPreferredHeight ();                       
    bool isResizable ()                             { return true; }
    void updateParameters ();

    //==============================================================================
    /** handy wrapper method to avoid having to cast the filter to a DemoJuceFilter
        every time we need it.. */
    ChannelPlugin* getFilter() const { return (ChannelPlugin*) getAudioProcessor(); }

    /** handy wrapper method to avoid having to unprotect the host */
    ChannelHost* getChannelHost() const             { return getFilter()->hoster; }

    //==============================================================================
    void loadPluginFromFile (const File& file);

    //==============================================================================
    /** Return true if the editor is currently open */
    bool isPluginEditorWindowOpen (BasePlugin* plugin) const;

    /** Callback from tracks */
    void openPluginEditorWindow (BasePlugin* plugin);

    /** Callback from plugin window */
    void closePluginEditorWindow (BasePlugin* plugin);

    /** Callback from plugin window */
    void closePluginEditorWindows ();

    /** Callback (from audioMaster) to resize content component */
    void resizePluginEditorWindow (BasePlugin* plugin,
                                   const int width,
                                   const int height);

    /** Callback (from audioMaster) to repaint plugin editor window */
    void updatePluginEditorWindowDisplay ();

    //==============================================================================
	//Special functions for track editors
	//Please don't touch this

	//void openTrackEditorContainer (BasePlugin* plugin);

	//==============================================================================

	void clearComponents ();
    void rebuildComponents ();

    //==============================================================================

	void changeListenerCallback (void* source);

    /** Parameter listener callback */
    void parameterChanged (AudioParameter* parameter, const int index);

    /** @internal */
    void paint (Graphics& g);

	/** @internal */
    void resized ();

    //==============================================================================
    juce_UseDebuggingNewOperator

private:

    //==============================================================================
	friend class ChannelPlugin;

	ChannelGraphComponent* graph;
    ChannelPlugin* owner;

	Viewport* graphViewport;

	// The shared plugin editor window
    OwnedArray<VstPluginWindow> pluginWindows;

	// The shared tracks editor window
 //   OwnedArray<TrackEditorContainer> trackEditors;
    
};


#endif
