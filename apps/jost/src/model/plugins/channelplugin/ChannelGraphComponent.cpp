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

#include "ChannelGraphComponent.h"
#include "../../../HostFilterComponent.h"

//==============================================================================
void ChannelGraphComponentSelectedModules::itemSelected (GraphNodeComponent* item)
{
    item->repaint ();
}

void ChannelGraphComponentSelectedModules::itemDeselected (GraphNodeComponent* item)
{
    item->repaint ();
}


//==============================================================================
ChannelGraphComponent::ChannelGraphComponent (ChannelEditor* owner_)
    : host (0),
      owner (owner_),
      inputs (0),
      outputs (0),
	  track (0),
      lassoComponent (0),
      currentClickedNode (0),
      currentFont (11.0f, Font::plain),
      defaultNodeWidth (50),
      defaultNodeHeight (50),
      leftToRight (true),
      somethingIsBeingDraggedOver (false),
      dragStartX (0),
      dragStartY (0)
{
    DBG ("ChannelGraphComponent::ChannelGraphComponent");

    setOpaque (true);
    //setBufferedToImage (true);
    setWantsKeyboardFocus (true);

    // setup config options
    leftToRight = Config::getInstance ()->graphLeftToRight;

    if (leftToRight)
    {
        defaultNodeWidth = JOST_GRAPH_NODE_HEIGHT;
        defaultNodeHeight = JOST_GRAPH_NODE_WIDTH;
    }
    else
    {
        defaultNodeWidth = JOST_GRAPH_NODE_WIDTH;
        defaultNodeHeight = JOST_GRAPH_NODE_HEIGHT;
    }
}

ChannelGraphComponent::~ChannelGraphComponent()
{
    DBG ("ChannelGraphComponent::~ChannelGraphComponent");

    cleanInternalGraph ();
    
    deleteAndZero (lassoComponent);
}

//==============================================================================
void ChannelGraphComponent::resized ()
{
}

void ChannelGraphComponent::paint (Graphics& g)
{
    g.fillAll (findColour (GraphComponent::mainBackColourId));

    if (somethingIsBeingDraggedOver)
    {
        g.setColour (findColour (GraphComponent::nodeBorderColourId));
        g.drawRect (0, 0, getWidth (), getHeight(), 2);
    }
}

//==============================================================================
bool ChannelGraphComponent::isInterestedInFileDrag (const StringArray&)
{
    return true;
}

void ChannelGraphComponent::filesDropped (const StringArray& filenames,
                                   int mouseX,
                                   int mouseY)
{
    if (filenames.size())
        dropPluginOnTrack (filenames[0], mouseX, mouseY);
}

bool ChannelGraphComponent::keyPressed (const KeyPress& key)
{
    if (key.isKeyCode (KeyPress::leftKey))
    {
        for (int i = 0; i < selectedNodes.getNumSelected (); i++)
        {
            GraphNodeComponent* selected = selectedNodes.getSelectedItem (i);
            if (selected != inputs && selected != outputs)
                selected->setTopLeftPosition (selected->getX() - 1, selected->getY());
        }
    }
    else if (key.isKeyCode (KeyPress::rightKey))
    {
        for (int i = 0; i < selectedNodes.getNumSelected (); i++)
        {
            GraphNodeComponent* selected = selectedNodes.getSelectedItem (i);
            if (selected != inputs && selected != outputs)
                selected->setTopLeftPosition (selected->getX() + 1, selected->getY());
        }
    }
    else if (key.isKeyCode (KeyPress::upKey))
    {
        for (int i = 0; i < selectedNodes.getNumSelected (); i++)
        {
            GraphNodeComponent* selected = selectedNodes.getSelectedItem (i);
            if (selected != inputs && selected != outputs)
                selected->setTopLeftPosition (selected->getX(), selected->getY() - 1);
        }
    }
    else if (key.isKeyCode (KeyPress::downKey))
    {
        for (int i = 0; i < selectedNodes.getNumSelected (); i++)
        {
            GraphNodeComponent* selected = selectedNodes.getSelectedItem (i);
            if (selected != inputs && selected != outputs)
                selected->setTopLeftPosition (selected->getX(), selected->getY() + 1);
        }
    }
    else if (key.isKeyCode (KeyPress::deleteKey))
    {
		

        closeSelectedPlugins ();
		 
    }
    else
    {
        return Component::keyPressed (key);
    }

    return true;
}

//==============================================================================
void ChannelGraphComponent::mouseDown (const MouseEvent& e)
{
    if (e.mods.isLeftButtonDown())
    {
        selectedNodes.deselectAll ();
        
        lassoComponent->beginLasso (e, this);
    }
    else if (e.mods.isMiddleButtonDown ())
    {
        Viewport* parent = findParentComponentOfClass ((Viewport*) 0);
        if (parent)
        {
            dragStartX = parent->getViewPositionX ();
            dragStartY = parent->getViewPositionY ();
            
            setMouseCursor (MouseCursor::DraggingHandCursor);
        }
    }
    else if (e.mods.isRightButtonDown ())
    {
    }
}

void ChannelGraphComponent::mouseDrag (const MouseEvent& e)
{
    if (e.mods.isLeftButtonDown())
    {
        lassoComponent->toFront (false);
        lassoComponent->dragLasso (e);
    }
    else if (e.mods.isMiddleButtonDown ())
    {
        Viewport* parent = findParentComponentOfClass ((Viewport*) 0);
        if (parent)
        {
            int x = dragStartX - e.getDistanceFromDragStartX ();
            int y = dragStartY - e.getDistanceFromDragStartY ();

            Component* comp = parent->getViewedComponent ();
            if (comp)
            {
                x = jmax (0, jmin (comp->getWidth () - parent->getViewWidth (), x));
                y = jmax (0, jmin (comp->getHeight () - parent->getViewHeight (), y));
            }
            
            parent->setViewPosition (x, y);
            
            setMouseCursor (MouseCursor::DraggingHandCursor);
        }
    }
    else if (e.mods.isRightButtonDown ())
    {
    }
}

void ChannelGraphComponent::mouseUp (const MouseEvent& e)
{
    if (e.mods.isLeftButtonDown())
    {
        lassoComponent->endLasso ();
    }
    else if (e.mods.isMiddleButtonDown ())
    {
    }
    else if (e.mods.isRightButtonDown ())
    {
        // try to open internal plugins
        BasePlugin* newPlugin = PluginLoader::handlePopupMenu (true, owner->getFilter(), 0);

        // now open plugin
        if (host && newPlugin)
        {
			DBG(String(T("opening plug")))
            host->openPlugin (newPlugin);
            host->addPlugin (newPlugin);

            newPlugin->setValue (PROP_GRAPHXPOS, e.x);
            newPlugin->setValue (PROP_GRAPHYPOS, e.y);

            createPluginNode (newPlugin);
        }
    }
    
    lassoComponent->endLasso ();
    setMouseCursor (MouseCursor::NormalCursor);
}

//==============================================================================
void ChannelGraphComponent::nodePaint (GraphNodeComponent* node, Graphics& g)
{
    int width = node->getWidth(),
        height = node->getHeight();

    bool selected = selectedNodes.isSelected (node),
         locked = node->isLocked();

    // background
    Colour background; 
#if 0
    if (selected)
        background = findColour (ChannelGraphComponent::nodeBackBrightColourId);
    else
        background = findColour (ChannelGraphComponent::nodeBackColourId);
#endif
    background = node->getNodeColour ();
    
    if (selected)
        background = background.brighter (0.3f);

#if 0
    g.setColour (background);
    g.fillRect (0, 0, width, height);
#else
    g.setGradientFill (ColourGradient(background, 0.0f, 0.0f,
                                      background.darker (0.3f),
                                      0.0f,
                                      height - 1.0f,
                                      false));
    g.fillAll();
#endif

    // plugin text
    if (selected)
        g.setColour (findColour (GraphComponent::nodeTextBrightColourId));
    else
        g.setColour (findColour (GraphComponent::nodeTextColourId));

    String textToDisplay = node->getText ();
    if (textToDisplay != String::empty)
    {
        g.setFont (currentFont);
        
        if (leftToRight)
        {
            int stringWidth = currentFont.getStringWidth (textToDisplay);
            int offX = width / 2 - (int) currentFont.getHeight () / 2;
            int offY = height / 2 - stringWidth / 2 ;
            
            g.drawTextAsPath (textToDisplay,
                              AffineTransform::rotation (double_Pi / 2.0)
                                              .translated (offX, offY));
        }
        else
        {
            g.drawText (textToDisplay,
                        0, 0, width, height,
                        Justification::centred,
                        false);
        }
    }

    // border
    Colour borderColour; 
    if (selected)
        borderColour = findColour (GraphComponent::nodeBorderBrightColourId);
    else
        borderColour = findColour (GraphComponent::nodeBorderColourId);

    if (locked)
        borderColour = borderColour.overlaidWith (Colours::red.withAlpha (0.3f));

    g.setColour (borderColour);
    g.drawRect (0, 0, width, height, 2);
}

void ChannelGraphComponent::nodeMoved (GraphNodeComponent* node, const int deltaX, const int deltaY)
{
//    DBG ("GraphComponent::nodeMoved " + String (deltaX) + " " + String (deltaY));

    jassert (node != 0);

    for (int i = 0; i < selectedNodes.getNumSelected (); i++)
    {
        GraphNodeComponent* selected = selectedNodes.getSelectedItem (i);
        if (selected
            && selected != node
            && ! selected->isLocked ())
        {
            BasePlugin* plugin = (BasePlugin*) selected->getUserData ();
            if (plugin)
            {
                int x = selected->getX() + deltaX;
                int y = selected->getY() + deltaY;

                x = jmax (0, jmin (getWidth () - selected->getWidth(), x));
                y = jmax (0, jmin (getHeight () - selected->getHeight(), y));
            
                plugin->setValue (PROP_GRAPHXPOS, x);
                plugin->setValue (PROP_GRAPHYPOS, y);
                
                selected->setTopLeftPosition (x, y);
            }
        }
    }

    BasePlugin* plugin = (BasePlugin*) node->getUserData ();
    if (plugin)
    {
        plugin->setValue (PROP_GRAPHXPOS, node->getX());
        plugin->setValue (PROP_GRAPHYPOS, node->getY());
    }

    Viewport* parent = findParentComponentOfClass ((Viewport*) 0);
    if (parent)
    {
        parent->notifyComponentChanged ();
    }
}

void ChannelGraphComponent::nodeSelected (GraphNodeComponent* node)
{
    DBG ("ChannelGraphComponent::nodeSelected");

    jassert (node != 0)

    switch (selectedNodes.getNumSelected ())
    {
    case 0: // no items selected
        {
            BasePlugin* plugin = (BasePlugin*) node->getUserData ();
            if (plugin)
                plugin->setValue (PROP_GRAPHSELECTED, 1);

            selectedNodes.addToSelection (node);

            node->repaint ();
        }
        break;
    default: // one or more items selected
        {
            if (! selectedNodes.isSelected (node))
            {
                for (int i = 0; i < selectedNodes.getNumSelected (); i++)
                {
                    GraphNodeComponent* selected = selectedNodes.getSelectedItem (i);

                    BasePlugin* plugin = (BasePlugin*) selected->getUserData ();
                    if (plugin)
                        plugin->setValue (PROP_GRAPHSELECTED, 0);

                    selected->repaint ();
                }

                selectedNodes.deselectAll ();

                BasePlugin* plugin = (BasePlugin*) node->getUserData ();
                if (plugin)
                    plugin->setValue (PROP_GRAPHSELECTED, 1);

                selectedNodes.addToSelection (node);

                node->repaint ();
            }
        }
        break;
    }
}

void ChannelGraphComponent::nodeDoubleClicked (GraphNodeComponent* node,
                                        const MouseEvent& e)
{
    DBG ("ChannelGraphComponent::nodeDoubleClicked");

    jassert (node != 0);

    if (e.mods.isLeftButtonDown ())
    {
        BasePlugin* plugin = (BasePlugin*) node->getUserData ();
        if (plugin && (plugin->hasEditor ()
                       || plugin->wantsEditor ()
                       || plugin->isEditorInternal ()))
        {
            if (owner->isPluginEditorWindowOpen (plugin))
            {
                owner->closePluginEditorWindow (plugin);
            }
            else
            {

				if (plugin->hasEditor() || plugin->wantsEditor ())
			    {
                    owner->openPluginEditorWindow (plugin);
                }

            }
        }
    }
}

void ChannelGraphComponent::nodePopupMenuSelected (GraphNodeComponent* node)
{
    DBG ("ChannelGraphComponent::nodePopupMenuSelected");

    jassert (node != 0);

    currentClickedNode = node;

    bool addFirstSeparator = false;
    PopupMenu menu, subMenu;

    BasePlugin* plugin = (BasePlugin*) node->getUserData ();

    if (plugin->hasEditor ()
        || plugin->wantsEditor ()
        || plugin->isEditorInternal ())
    {
        menu.addItem (1, "Open editor");
        addFirstSeparator = true;
    }

    if (node != inputs && node != outputs && node != track)
    {
        menu.addItem (2, "Remove " + plugin->getName());
        addFirstSeparator = true;
    }

    if (addFirstSeparator)
        menu.addSeparator ();

    menu.addItem (3, "Lock", true, node->isLocked ());

    // node colour..
    ColourSelector colourSelector;
    colourSelector.setName (T("background"));
    colourSelector.setCurrentColour (node->getNodeColour ());
    colourSelector.addChangeListener (this);

    subMenu.addCustomItem (1234, &colourSelector, 300, 300, false);
    menu.addSubMenu (T("Colour"), subMenu);
    menu.addSeparator ();

    menu.addItem (4, "Mute", true, plugin->isMuted ());
    menu.addItem (5, "Bypass", true, plugin->isBypass ());
    menu.addItem (6, "Solo", false, false);
    menu.addSeparator ();

    int inputLinks = node->getInputLinksCount ();
    int outputLinks = node->getOutputLinksCount ();

    if (inputLinks > 0 && outputLinks > 0)
        menu.addItem (7, "Disconnect all");
    if (inputLinks > 0)
        menu.addItem (8, "Disconnect inputs");
    if (outputLinks > 0)
        menu.addItem (9, "Disconnect outputs");

    const int result = menu.show();
    switch (result)
    {
    case 1: // Open editor
        {
			if (plugin->getType() != JOST_PLUGINTYPE_TRACK)
            owner->openPluginEditorWindow (plugin);

			else if (plugin->getType() == JOST_PLUGINTYPE_TRACK)
			//owner->openTrackEditorContainer (plugin);

            break;
        }

    case 2: // Close
        {
			if (plugin->getType() != JOST_PLUGINTYPE_TRACK)
			{
				if (owner->isPluginEditorWindowOpen (plugin))
                owner->closePluginEditorWindow (plugin);

				if (plugin)
				{
                host->closePlugin (plugin);

                selectedNodes.deselect (node);
                deletePluginNode (node);

                graphChanged ();
				}
			}

			else if (plugin->getType() == JOST_PLUGINTYPE_TRACK)
			{
				if (owner->isPluginEditorWindowOpen (plugin))
                owner->closePluginEditorWindow (plugin);

				if (plugin)
				{
                host->closePlugin (plugin);

                selectedNodes.deselect (node);
                deletePluginNode (node);

                graphChanged ();
				}
			}

            break;
        }
    case 3: // Lock / unlock
        {
            bool lockedState = ! node->isLocked ();

            if (plugin)
                plugin->setValue (PROP_GRAPHLOCKED, lockedState);

            node->setLocked (lockedState);
            node->repaint ();
        }
        break;
    case 4: // Mute
        {
            if (plugin)
                plugin->setMuted (! plugin->isMuted());
        }
        break;
    case 5: // Bypass
        {
            if (plugin)
                plugin->setBypass (! plugin->isBypass());
        }
        break;
    case 6: // Solo (TODO)
        break;
    case 7: // Disconnect all
        node->breakAllLinks();
        break;
    case 8: // Disconnect inputs
        node->breakInputLinks();
        break;
    case 9: // Disconnect outputs
        node->breakOutputLinks();
        break;
    default:
        break;
    }
    
    currentClickedNode = 0;
}

void ChannelGraphComponent::connectorPopupMenuSelected (GraphConnectorComponent* connector)
{
    DBG ("ChannelGraphComponent::connectorPopupMenuSelected");

    jassert (connector != 0);

    PopupMenu menu;

    Array<GraphConnectorComponent*> links;
    connector->getLinkedConnectors (links);

    int startCount = 0;
    
    if (links.size () > 0)
    {
        menu.addItem (1, "Break all wires");
        menu.addSeparator ();
        
        GraphConnectorComponent* conn;
        BasePlugin* linkedPlugin;
        
        for (int i = 0; i < links.size (); i++)
        {
            conn = links.getUnchecked (i);
            linkedPlugin = (BasePlugin*) conn->getParentGraphComponent ()->getUserData ();
            
            String itemString;
            itemString << "Unwire " 
                       << linkedPlugin->getName () 
                       << " (";

            switch (conn->getType ()) {
                case JOST_LINKTYPE_AUDIO: // audio
                    itemString << "audio port ";
                    break;
                case JOST_LINKTYPE_MIDI:
                    itemString << "midi port ";
                    break;
            }

            itemString << (conn->getConnectorID () + 1)
                       << ")";
            
            menu.addItem (10 + startCount, itemString);
            
            ++startCount;
        }
    }
    
    if (menu.getNumItems () > 0)
    {
        const int result = menu.show();
        switch (result)
        {
        case 1:
            connector->destroyAllLinks();
            connector->notifyGraphChanged ();
            break;
        default:
            if (result >= 10 && result < 10 + startCount)
            {
                connector->removeLinkWith (links.getUnchecked (result - 10));
                connector->notifyGraphChanged ();
            }
            break;
        }
    }
}

Colour ChannelGraphComponent::getConnectorColour (GraphConnectorComponent* connector, const bool isSelected)
{
    jassert (connector != 0);

    switch (connector->getType ())
    {
    case JOST_LINKTYPE_AUDIO: // audio
        return isSelected ? findColour (GraphComponent::wireAudioBrightColourId)
                          : findColour (GraphComponent::wireAudioColourId);

    case JOST_LINKTYPE_MIDI: // midi
        return isSelected ? findColour (GraphComponent::wireMidiBrightColourId)
                          : findColour (GraphComponent::wireMidiColourId);
    }

    return isSelected ? Colours::red : Colours::black;
}

void ChannelGraphComponent::graphChanged ()
{
    DBG ("ChannelGraphComponent::graphChanged");

    jassert (host != 0); // just to be sure !

    // AUDIO -
    ProcessingGraph* audioGraph = new ProcessingGraph ();

    // starting from inputs
    recalculateConnectionsRecursive (inputs,
                                     audioGraph,
                                     0,
                                     true);

    // then adding outputs if not already
    recalculateConnectionsRecursive (outputs,
                                     audioGraph,
                                     audioGraph->getNodeCount (),
                                     true);

    // all the others that are not connected (add them after input)
    for (int i = 0; i < nodes.size (); i++)
    {
        recalculateConnectionsRecursive (nodes.getUnchecked (i),
                                         audioGraph,
                                         1,
                                         true);
    }

    host->changePluginAudioGraph (audioGraph);

#if JUCE_DEBUG
/*
    printf ("MIDI > \n");
    for (int i = 0; i < audioGraph->getNodeCount (); i++)
    {
        BasePlugin* plugin = (BasePlugin*) audioGraph->getData (i);
        printf ("%s > ", (const char*) plugin->getName());
    }
    printf ("\n");

    printf ("MIDI CONNECTIONS > \n");
    for (int i = 0; i < audioGraph->getNodeCount (); i++)
    {
        ProcessingNode* node = audioGraph->getNode (i);
        if (node)
        {
            for (int j = 0; j < node->getLinksCount (JOST_LINKTYPE_MIDI); j++)
            {
                ProcessingLink* conn = node->getLink (JOST_LINKTYPE_MIDI, j);
                printf ("%s,%d > %s,%d \n",
                        (const char*) ((BasePlugin*)node->getData())->getName(),
                        conn->sourcePort,
                        (const char*) ((BasePlugin*)conn->destination->getData())->getName(),
                        conn->destinationPort);
            }
        }
    }
    printf ("\n");

    printf ("AUDIO > \n");
    for (int i = 0; i < audioGraph->getNodeCount (); i++)
    {
        BasePlugin* plugin = (BasePlugin*) audioGraph->getData (i);
        printf ("%s > ", (const char*) plugin->getName());
    }
    printf ("\n");

    printf ("AUDIO CONNECTIONS > \n");
    for (int i = 0; i < audioGraph->getNodeCount (); i++)
    {
        ProcessingNode* node = audioGraph->getNode (i);
        if (node)
        {
            for (int j = 0; j < node->getLinksCount (JOST_LINKTYPE_AUDIO); j++)
            {
                ProcessingLink* conn = node->getLink (JOST_LINKTYPE_AUDIO, j);
                printf ("%s,%d > %s,%d \n",
                        (const char*) ((BasePlugin*)node->getData())->getName(),
                        conn->sourcePort,
                        (const char*) ((BasePlugin*)conn->destination->getData())->getName(),
                        conn->destinationPort);
            }
        }
    }
    printf ("\n");
*/
#endif

    Viewport* parent = findParentComponentOfClass ((Viewport*) 0);
    if (parent)
    {
        parent->notifyComponentChanged ();
    }
}

//==============================================================================
void ChannelGraphComponent::setHost (ChannelHost* hostToDisplay)
{
    DBG ("ChannelGraphComponent::setHost");

    host = hostToDisplay;

    updateDisplayPlugins ();
}

void ChannelGraphComponent::updateDisplayPlugins ()
{
    DBG ("ChannelGraphComponent::updateDisplayPlugins");

    jassert (host != 0);

    cleanInternalGraph ();

    // rebuild nodes !
    for (int i = 0; i < host->getPluginsCount (); i++)
    {
        createPluginNode (host->getPluginByIndex (i));
    }

    // update audio / midi connection links !
    ProcessingGraph* audioGraph = host->getAudioGraph ();

    for (int i = 0; i < audioGraph->getNodeCount (); i++)
    {
        ProcessingNode* source = audioGraph->getNode (i);
        BasePlugin* sourceData = (BasePlugin*) source->getData ();
        GraphNodeComponent* sourceNode = findNodeByUserData (sourceData);

        if (sourceNode != 0)
        {
            for (int j = source->getLinksCount (JOST_LINKTYPE_AUDIO); --j >= 0;)
            {
                ProcessingLink* link = source->getLink (JOST_LINKTYPE_AUDIO, j);
                BasePlugin* destData = (BasePlugin*) link->destination->getData ();
                GraphNodeComponent* destNode = findNodeByUserData (destData);

                if (destNode != 0)
                {
                    sourceNode->connectToNode (link->sourcePort,
                                               destNode,
                                               link->destinationPort,
                                               false);
                }
            }
        }
    }

    for (int i = 0; i < audioGraph->getNodeCount (); i++)
    {
        ProcessingNode* source = audioGraph->getNode (i);
        BasePlugin* sourceData = (BasePlugin*) source->getData ();
        GraphNodeComponent* sourceNode = findNodeByUserData (sourceData);

        if (sourceNode != 0)
        {
            for (int j = source->getLinksCount (JOST_LINKTYPE_MIDI); --j >= 0;)
            {
                ProcessingLink* link = source->getLink (JOST_LINKTYPE_MIDI, j);
                BasePlugin* destData = (BasePlugin*) link->destination->getData ();
                GraphNodeComponent* destNode = findNodeByUserData (destData);

                if (destNode != 0)
                {
                    sourceNode->connectToNode (link->sourcePort + sourceNode->getFirstOutputOfType (JOST_LINKTYPE_MIDI),
                                               destNode,
                                               link->destinationPort + destNode->getFirstInputOfType (JOST_LINKTYPE_MIDI),
                                               false);
                }
            }
        }
    }

    // update connectors
    graphChanged ();

    // update fixed node size and position
    resized ();
}

//==============================================================================
bool ChannelGraphComponent::dropPluginOnTrack (const File& pluginFile,
                                        int mouseX,
                                        int mouseY)
{
	if (pluginFile.hasFileExtension(T(".dll")))
	{
		return loadAndAppendPlugin (pluginFile, mouseX, mouseY);
	}
	else {return false;}
	
}

bool ChannelGraphComponent::loadAndAppendPlugin (const File& file, int mouseX,
                                        int mouseY)
{
    DBG ("ChannelGraphComponent::loadAndAppendPlugin");

    jassert (host != 0);

    BasePlugin* plugin = host->loadPlugin (file);
    if (plugin)
    {
        Config::getInstance ()->addRecentPlugin (file);
        
		plugin->setValue(PROP_GRAPHXPOS, mouseX);
		plugin->setValue(PROP_GRAPHYPOS, mouseY);

		host->addPlugin (plugin);
        createPluginNode (plugin);

        return true;
    }

    return false;
}

bool ChannelGraphComponent::loadAndAppendPlugin ()
{
    DBG ("ChannelGraphComponent::loadAndAppendPlugin (with chooser)");

    FileChooser myChooser (T("Load a plugin..."),
                            Config::getInstance ()->lastPluginDirectory,
                            JOST_PLUGIN_WILDCARD, false);

    if (myChooser.browseForFileToOpen())
    {
        File fileToLoad = myChooser.getResult();
        if (fileToLoad.existsAsFile())
            return loadAndAppendPlugin (fileToLoad, 20, 20);
    }
    return false;
}

bool ChannelGraphComponent::closeSelectedPlugins ()
{
    DBG ("ChannelGraphComponent::closeSelectedPlugins");

    jassert (host != 0);

    if (selectedNodes.getNumSelected () > 0)
    {
        for (int i = 0; i < selectedNodes.getNumSelected (); i++)
        {
            GraphNodeComponent* selected = selectedNodes.getSelectedItem (i);
			if (selected != inputs && selected != outputs && selected != track)
			{
				BasePlugin* plugin = (BasePlugin*) selected->getUserData ();
				if (plugin)
				{
					if (owner->isPluginEditorWindowOpen (plugin))
                    owner->closePluginEditorWindow (plugin);

					host->closePlugin (plugin);

					selectedNodes.deselect (selected);
					deletePluginNode (selected);
				}
			}
        }

        selectedNodes.deselectAll ();

        graphChanged ();
        
        return true;
    }
    
    return false;
}

bool ChannelGraphComponent::closeAllPlugins ()
{
    DBG ("ChannelGraphComponent::closeAllPlugins");

    jassert (host != 0);

    owner->closePluginEditorWindows ();

    host->closeAllPlugins ();

    selectedNodes.deselectAll ();

    updateDisplayPlugins ();
    return true;
}

int ChannelGraphComponent::getPluginsCount () const
{
    return nodes.size ();
}

//==============================================================================
bool ChannelGraphComponent::createPluginNode (BasePlugin* plugin)
{
    if (plugin)
    {
        DBG ("ChannelGraphComponent::createPluginNode");
 
        GraphNodeComponent* component;
        addAndMakeVisible (component = new GraphNodeComponent());
        component->setNodeListener (this);

        // set common data
        component->setUserData (plugin);
        component->setUniqueID (plugin->getUniqueHash());
        component->setText (plugin->getName ());
        component->setLeftToRight (leftToRight);
        component->setNodeColour (Colour::fromString (plugin->getValue (PROP_GRAPHCOLOUR, T("0xff808080"))));

        // read properties
        // int maxPortCount = jmax (plugin->getNumInputs () + plugin->getNumMidiInputs (),
        //                          plugin->getNumOutputs () + plugin->getNumMidiOutputs ());
                                 
        // TODO - if (maxPortCount * portWidth > defaultNodeWidth) ...
        int pluginType = plugin->getType();

        int w = defaultNodeWidth, h = defaultNodeHeight;
        int numIns = plugin->getNumInputs () + plugin->getNumMidiInputs ();
        int numOuts = plugin->getNumOutputs () + plugin->getNumMidiOutputs ();

        if (leftToRight)
        {
            h = jmax (h, (jmax (numIns, numOuts) + 1) * 16);

            const int textHeight = currentFont.getStringWidth (plugin->getName());
            h = jmax (h, 16 + jmin (textHeight, 300));
        }
        else
        {
            w = jmax (w, (jmax (numIns, numOuts) + 1) * 16);

            const int textWidth = currentFont.getStringWidth (plugin->getName());
            w = jmax (w, 16 + jmin (textWidth, 300));
        }
        
        int wasLocked = plugin->getIntValue (PROP_GRAPHLOCKED, -1);
        if (wasLocked < 0)  wasLocked = 0;
        int wasSelected = plugin->getIntValue (PROP_GRAPHSELECTED, 0);
        int xPos = plugin->getIntValue (PROP_GRAPHXPOS, -1);
        int yPos = plugin->getIntValue (PROP_GRAPHYPOS, -1);
        int wSize = plugin->getIntValue (PROP_GRAPHWSIZE, w);
        if (wSize < 0) wSize = defaultNodeWidth;
        int hSize = plugin->getIntValue (PROP_GRAPHHSIZE, h);
        if (hSize < 0) hSize = defaultNodeHeight;
        String pluginTooltip = plugin->getName ();

        // input plugin
        if (pluginType == JOST_PLUGINTYPE_CHANNELINPUT)
        {
            inputs = component;
            if (xPos < 0)       xPos = leftToRight ? 2 : (getWidth () - w) / 2;
            if (yPos < 0)       yPos = leftToRight ? (getHeight() - h) / 2 : 2;
        }
        // output plugin
        else if (pluginType == JOST_PLUGINTYPE_CHANNELOUTPUT)
        {
            outputs = component;
            if (xPos < 0)       xPos = leftToRight ? getWidth () - w - 2 : (getWidth () - w) / 2;
            if (yPos < 0)       yPos = leftToRight ? (getHeight() - h) / 2 : getHeight() - h - 2;
        }
		// track plugin
        else if (pluginType == JOST_PLUGINTYPE_TRACK)
        {
            track = component;
            if (xPos < 0)       xPos = leftToRight ? getWidth () - w - 2 : (getWidth () - w) / 2;
            if (yPos < 0)       yPos = leftToRight ? (getHeight() - h) / 2 : getHeight() - h - 2;
        }
        // generic plugin
        else
        {
            if (xPos < 0)       xPos = getBounds().getCentreX();
            if (yPos < 0)       yPos = getBounds().getCentreY();
            pluginTooltip = plugin->getFile ().getFullPathName ();
        }

        component->setBounds (xPos, yPos, wSize, hSize);
        component->setLocked (wasLocked);
        component->setTooltip (pluginTooltip);
        component->setVisible (true);
        if (wasSelected) selectedNodes.addToSelection (component);

        plugin->setValue (PROP_GRAPHXPOS, xPos);
        plugin->setValue (PROP_GRAPHYPOS, yPos);
        plugin->setValue (PROP_GRAPHWSIZE, wSize);
        plugin->setValue (PROP_GRAPHHSIZE, hSize);

        // restore audio input / output ports
        if (pluginType != JOST_PLUGINTYPE_CHANNELINPUT)
            for (int j = 0; j < plugin->getNumInputs (); j++)
                component->addInputConnector (JOST_LINKTYPE_AUDIO); // audio cable

        if (pluginType != JOST_PLUGINTYPE_CHANNELOUTPUT)
            for (int j = 0; j < plugin->getNumOutputs (); j++)
                component->addOutputConnector (JOST_LINKTYPE_AUDIO); // audio cable

        // restore midi input / output ports
        if (pluginType != JOST_PLUGINTYPE_CHANNELINPUT)
            for (int j = 0; j < plugin->getNumMidiInputs (); j++)
                component->addInputConnector (JOST_LINKTYPE_MIDI); // midi cable

        if (pluginType != JOST_PLUGINTYPE_CHANNELOUTPUT)
            for (int j = 0; j < plugin->getNumMidiOutputs (); j++)
                component->addOutputConnector (JOST_LINKTYPE_MIDI); // midi cable

        nodes.add (component);

        Viewport* parent = findParentComponentOfClass ((Viewport*) 0);
        if (parent)
        {
            parent->notifyComponentChanged ();
        }

        return true;
    }

    return false;
}

bool ChannelGraphComponent::deletePluginNode (GraphNodeComponent* node)
{
    if (node)
    {
        DBG ("ChannelGraphComponent::deletePluginNode");

        node->breakAllLinks (false);
        node->deleteConnectors (true);

        nodes.remove (nodes.indexOf (node), true);
        return true;
    }

    return false;
}

//==============================================================================
void ChannelGraphComponent::recalculateConnectionsRecursive (GraphNodeComponent* node,
                                                      ProcessingGraph* graph,
                                                      const int insertIndex,
//                                                      const int connectorType,
                                                      const bool createConnection)
{
    BasePlugin* source = (BasePlugin*) node->getUserData ();

    if (source != 0 && ! graph->contains (source))
    {
        graph->insertNode (insertIndex, source);
        int currentIndex = insertIndex + 1;

        for (int i = 0; i < node->getOutputConnectorCount (); i++)
        {
            int sourceOutputMidiOffset = node->getFirstOutputOfType (JOST_LINKTYPE_MIDI);
            int destOutputMidiOffset = 0;

            GraphConnectorComponent* connector = node->getOutputConnector (i);
//            if (connector->getType () == connectorType)
            {
                // we are the same type, get linked connectors
                Array <GraphConnectorComponent*> linked;
                connector->getLinkedConnectors (linked);

                for (int j = 0; j < linked.size (); j++)
                {
                    GraphConnectorComponent* other = linked.getUnchecked (j);
                    GraphNodeComponent* otherNode = other->getParentGraphComponent();

                    // breath first
                    recalculateConnectionsRecursive (otherNode,
                                                     graph,
                                                     currentIndex,
//                                                     connectorType,
                                                     createConnection);

                    // create link here !
                    if (createConnection)
                    {
                        BasePlugin* destination = (BasePlugin*) otherNode->getUserData ();
                        if (destination != 0)
                        {
                            if (connector->getType () == JOST_LINKTYPE_AUDIO)
                            {
                                graph->connectTo (source,
                                                  connector->getConnectorID(),
                                                  destination,
                                                  other->getConnectorID(),
                                                  JOST_LINKTYPE_AUDIO);
                            }
                            else if (connector->getType () == JOST_LINKTYPE_MIDI)
                            {
                                destOutputMidiOffset = otherNode->getFirstInputOfType (JOST_LINKTYPE_MIDI);

                                graph->connectTo (source,
                                                  connector->getConnectorID() - sourceOutputMidiOffset,
                                                  destination,
                                                  other->getConnectorID() - destOutputMidiOffset,
                                                  JOST_LINKTYPE_MIDI);
                            }
                        }
                    }
                    // end create link !
                }
          }
        }
    }

}

GraphNodeComponent* ChannelGraphComponent::findNodeByUserData (void* data)
{
    for (int i = nodes.size(); --i >= 0;)
    {
        GraphNodeComponent* node = nodes.getUnchecked (i);
        if (node->getUserData () == data)
            return node;
    }
    return 0;
}

void ChannelGraphComponent::cleanInternalGraph ()
{
    DBG ("ChannelGraphComponent::cleanInternalGraph < " + String (getNumChildComponents()));

    selectedNodes.deselectAll ();

    deleteAndZero (lassoComponent);

    for (int i = nodes.size (); --i >= 0;)
        nodes.getUnchecked (i)->breakAllLinks (false);
    for (int i = nodes.size (); --i >= 0;)
        nodes.getUnchecked (i)->deleteConnectors (true);

    nodes.clear (true);

    inputs = 0;
    outputs = 0;

    DBG ("ChannelGraphComponent::cleanInternalGraph > " + String (getNumChildComponents()));
    
    addAndMakeVisible (lassoComponent = new LassoComponent<GraphNodeComponent*> (2));
}

//==============================================================================
void ChannelGraphComponent::findLassoItemsInArea (Array<GraphNodeComponent*> &itemsFound, int x, int y, int width, int height)
{
    for (int i = 0; i < nodes.size (); i++)
    {
        GraphNodeComponent* node = nodes.getUnchecked (i);
        if ((node->getX() >= x && node->getX() < x + width)
             && (node->getY() >= y && node->getY() < y + height))
        {       
            itemsFound.addIfNotAlreadyThere (node);
            selectedNodes.addToSelection (node);
        }
        else
        {
            selectedNodes.deselect (node);
        }
    }
}

SelectedItemSet<GraphNodeComponent*>& ChannelGraphComponent::getLassoSelection ()
{
    return selectedNodes;
}

//==============================================================================
void ChannelGraphComponent::changeListenerCallback (void* source)
{
    ColourSelector* cs = (ColourSelector*) source;

    if (currentClickedNode)
    {
        Colour currentColour = cs->getCurrentColour();   
        
        BasePlugin* plugin = (BasePlugin*) currentClickedNode->getUserData ();
        if (plugin)
            plugin->setValue (PROP_GRAPHCOLOUR, currentColour.toString ());
        
        currentClickedNode->setNodeColour (currentColour);
        currentClickedNode->repaint ();

        Viewport* parent = findParentComponentOfClass ((Viewport*) 0);
        if (parent)
        {
            parent->notifyComponentChanged ();
        }
    }
}

//==============================================================================
bool ChannelGraphComponent::isInterestedInDragSource (const String& sourceDescription,
                                               Component* /*source*/)
{
    return sourceDescription.startsWith (T("Plugins: "))
           || sourceDescription.startsWith (T("Sessions: "));
}

void ChannelGraphComponent::itemDragEnter (const String& sourceDescription,
                                    Component* sourceComponent,
                                    int x, int y)
{
    somethingIsBeingDraggedOver = true;
    repaint();
}

void ChannelGraphComponent::itemDragMove (const String& sourceDescription,
                                   Component* sourceComponent,
                                   int x, int y)
{
}

void ChannelGraphComponent::itemDragExit (const String& sourceDescription,
                                   Component* sourceComponent)
{
    somethingIsBeingDraggedOver = false;
    repaint();
}

void ChannelGraphComponent::itemDropped (const String& sourceDescription,
                                  Component* sourceComponent,
                                  int x, int y)
{
    if (sourceDescription.startsWith (T("Plugins: ")))
    {
        StringArray array;
        array.addTokens (sourceDescription.replace (T("Plugins: "), T("")), false);

        if (array.size () > 0)
        {
            for (int i = 0; i < array.size (); i++)
            {
                File file (array [i]);
                if (file.existsAsFile ())
                    dropPluginOnTrack (file, x + i * 5, y + i * 5);
            }
        }
    }
    else if (sourceDescription.startsWith (T("Sessions: ")))
    {
        StringArray array;
        array.addTokens (sourceDescription.replace (T("Sessions: "), T("")), false);

        if (array.size () > 0)
        {
            File file (array [array.size () - 1]);
            
            MemoryBlock data;
            if (file.existsAsFile()
                && file.loadFileAsData (data))
            {
                Config::getInstance()->addRecentSession (file);
                owner->getFilter ()->setStateInformation (data.getData (), data.getSize());

                return;
            }
        }
    }

    somethingIsBeingDraggedOver = false;
    repaint();
}


