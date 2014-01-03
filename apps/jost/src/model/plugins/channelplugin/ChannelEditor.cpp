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

#include "ChannelEditor.h"
#include "ChannelPlugin.h"


//==============================================================================
ChannelEditor::ChannelEditor (ChannelPlugin* owner_)
    : PluginEditorComponent (owner_),
	  graph(0),
      owner (owner_),
	  graphViewport (0)
{
	getFilter()->addChangeListener (this);

	addAndMakeVisible (graph = new ChannelGraphComponent(this));

	addAndMakeVisible (graphViewport = new Viewport (String::empty));
	graphViewport->setScrollBarsShown (true, true);
	graphViewport->setScrollBarThickness (12);
	graphViewport->setViewedComponent (graph);

	graph->setHost (getChannelHost());
	graph->setBounds(0, 0, 480, 480);

    getFilter()->getTransport()->addChangeListener(this);

//	openTrackEditorContainer(getChannelHost()->getTrackPlug());
}

ChannelEditor::~ChannelEditor()
{
	getFilter()->getTransport()->removeChangeListener(this);
	owner->lastUIWidth = getWidth();
    owner->lastUIHeight = getHeight();

}

//==============================================================================
bool ChannelEditor::isPluginEditorWindowOpen (BasePlugin* plugin) const
{
    for (int i = pluginWindows.size(); --i >= 0;)
    {
        VstPluginWindow* window = pluginWindows.getUnchecked (i);
        if (window && window->getPlugin() == plugin)
            return window->isVisible ();
    }
    return false;
}

void ChannelEditor::openPluginEditorWindow (BasePlugin* plugin)
{
    DBG ("ChannelEditor::openPluginEditorWindow");

    if (plugin)
    {
		
        VstPluginWindow* pluginWindow = 0;
        for (int i = pluginWindows.size(); --i >= 0;)
        {
            VstPluginWindow* window = pluginWindows.getUnchecked (i);
            if (window && window->getPlugin() == plugin)
            {
                pluginWindow = window;
                break;
            }
        }
		
		if (! pluginWindow && plugin->getType() != JOST_PLUGINTYPE_TRACK)
        {
			pluginWindow = new VstPluginWindow (this/*getFilter()->getBaseHost()->getEditor()*/, plugin);
			//pluginWindow->setAlwaysOnTop(true);
            pluginWindows.add (pluginWindow);
        }
        else
        {
            if (pluginWindow->getPlugin () != plugin)
                pluginWindow->setPlugin (plugin);

            if (! pluginWindow->isVisible ())
                pluginWindow->setVisible (true);
            pluginWindow->toFront (false);
        }

        // save property with plugin
        plugin->setValue (PROP_WINDOWOPEN, 1);
    }
}

void ChannelEditor::closePluginEditorWindow (BasePlugin* plugin)
{
    DBG ("ChannelEditor::closePluginEditorWindow");

    for (int i = pluginWindows.size(); --i >= 0;)
    {
        VstPluginWindow* window = pluginWindows.getUnchecked (i);
        if (window && window->getPlugin() == plugin)
        {
            // save property with plugin
            plugin->setValue (PROP_WINDOWOPEN, 0);

            pluginWindows.removeObject (window, true);
            break;
        }
    }
}

void ChannelEditor::closePluginEditorWindows()
{
    DBG ("ChannelEditor::closePluginEditorWindows");

    pluginWindows.clear (true);
}

void ChannelEditor::resizePluginEditorWindow (BasePlugin* plugin,
                                               const int width,
                                               const int height)
{
    DBG ("ChannelEditor::resizePluginEditorWindow");

    for (int i = pluginWindows.size(); --i >= 0;)
    {
        VstPluginWindow* window = pluginWindows.getUnchecked (i);
        if (window && window->getPlugin() == plugin)
        {
            window->resizeContentComponent (width, height);
			
            break;
        }
    }
}

void ChannelEditor::updatePluginEditorWindowDisplay ()
{
    for (int i = pluginWindows.size(); --i >= 0;)
        pluginWindows.getUnchecked (i)->repaint ();
}

//==============================================================================
void ChannelEditor::clearComponents ()
{
    DBG ("ChannelEditor::clearComponents");

    closePluginEditorWindows ();
}

void ChannelEditor::rebuildComponents ()
{
    DBG ("ChannelEditor::rebuildComponents");
/*
    // update navigator with an empty view !
    if (navigator)
        navigator->setViewedViewport (0);

    // recreate main components !
    main->rebuildComponents ();
    
    // update navigator with the main area viewport !
    if (navigator) 
    {
        navigator->setViewedViewport (main->getGraphViewport ());
        navigator->updateVisibleArea (false);
    }*/
}

//==============================================================================
void ChannelEditor::changeListenerCallback (void* source)
{
    if (source == this)
    {
       // closePluginEditorWindows ();
    }
    else if (source == getFilter())
    {
        clearComponents ();
        rebuildComponents ();

        // reopen windows saved with session
        ChannelHost* host = getFilter()->hoster;
        for (int j = 0; j < host->getPluginsCount(); j++)
        {
            BasePlugin* plugin = host->getPluginByIndex (j);
            if (plugin && plugin->getIntValue (PROP_WINDOWOPEN, 0))
                openPluginEditorWindow (plugin);
        }

        resized ();
    }
    else if (source == getFilter()->getTransport())
    {
        // update transport !
        CommandManager::getInstance()->commandStatusChanged ();
    }
    else
    {
        for (int i = pluginWindows.size(); --i >= 0;)
        {
            VstPluginWindow* window = pluginWindows.getUnchecked (i);
            if (window)
                window->updateParameters ();
        }
    }
}

void ChannelEditor::parameterChanged (AudioParameter* parameter, const int index)
{
     DBG (T("PARAMETER ") + String (index) + T(" changed"));
}


//==============================================================================
void ChannelEditor::paint (Graphics& g)
{
    
}

//==============================================================================
void ChannelEditor::resized()
{
   graph->setSize(2000, 2000);
   graphViewport->setBounds(0, 0, getWidth(), getHeight());

   getFilter()->setValue(PROP_WINDOWWSIZE, getWidth());
   getFilter()->setValue(PROP_WINDOWHSIZE, getHeight()); 
}

void ChannelEditor::updateParameters ()
{

}

int ChannelEditor::getPreferredWidth()
{
	return owner->lastUIWidth;
}

int ChannelEditor::getPreferredHeight ()
{
    return owner->lastUIHeight;
}

//==============================================================================
/*void ChannelEditor::openTrackEditorContainer(BasePlugin* plugin)
{
	if (plugin)
    {
		TrackEditorContainer* trackWindow = 0;
		for (int i = trackEditors.size(); --i >= 0;)
        {
            TrackEditorContainer* window = trackEditors.getUnchecked (i);
            if (window && window->getPlugin() == plugin)
            {
                trackWindow = window;
                break;
            }
        }


		if (! trackWindow && plugin->getType() == JOST_PLUGINTYPE_TRACK)

		{
			trackWindow = new TrackEditorContainer (getFilter()->base->getEditor(), plugin, this);
			trackEditors.add (trackWindow);

			// Da qui chiamare hostfiltercomponent e dirgli di aggiungere un TrackEditorContainer
			// nella finestra multitrackwindow.
			getFilter()->base->getEditor()->getTracksWindow()->createTrack(trackWindow);

		}
	}

}*/
