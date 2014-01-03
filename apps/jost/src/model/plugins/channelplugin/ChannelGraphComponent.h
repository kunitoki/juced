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

#ifndef __JUCETICE_JOSTCHANNELGRAPHCOMPONENT_HEADER__
#define __JUCETICE_JOSTCHANNELGRAPHCOMPONENT_HEADER__

#include "../../../Config.h"
#include "ChannelHost.h"
#include "ChannelEditor.h"

class ChannelEditor;

//==============================================================================
/** Used internally by the LassoComponent

*/
class ChannelGraphComponentSelectedModules   : public SelectedItemSet<GraphNodeComponent*>
{
public:
    void itemSelected (GraphNodeComponent* item);
    void itemDeselected (GraphNodeComponent* item);
};


//==============================================================================
/**
     A graph component for manipulate plugin graph
*/
class ChannelGraphComponent  : public Component,
                        public DragAndDropTarget,
                        public GraphNodeListener,
                        public LassoSource<GraphNodeComponent*>,
                        public ChangeListener,
						public FileDragAndDropTarget,
						public DragAndDropContainer
{
public:

    //==============================================================================
    ChannelGraphComponent (ChannelEditor* owner_);

    ~ChannelGraphComponent();

    //==============================================================================
    /** Set the track that this component will handle

        The component will not refresh its gui, the caller must issue that call.
        Internally, it will call automatically updateDisplayPlugins for the new
        track.
    */
    void setHost (ChannelHost* hostToDisplay);

    /** Recreate the internal graph structure */
    void updateDisplayPlugins ();

    /** To be used the first time for displace i/o plugins */
    //void updateInputOutputPosition ();

    //==============================================================================
    /** This is called when a node needs to be paint */
    void nodePaint (GraphNodeComponent* node, Graphics& g);

    /** Callback whenever a node is moved */
    void nodeMoved (GraphNodeComponent* node, const int deltaX, const int deltaY);

    /** Callback whenever a node is selected */
    void nodeSelected (GraphNodeComponent* node);

    /** Callback whenever a node is double clicked */
    void nodeDoubleClicked (GraphNodeComponent* node,
                            const MouseEvent& e);

    /** Callback whenever a node is right clicked */
    void nodePopupMenuSelected (GraphNodeComponent* node);

    /** Callback whenever a connector is right clicked */
    void connectorPopupMenuSelected (GraphConnectorComponent* connector);

    /** Callback ifor getting right connector colour */
    Colour getConnectorColour (GraphConnectorComponent* connector, const bool isSelected);

    /** Callback when there is a change in the graph */
    void graphChanged ();

    //==============================================================================
    /** Returns the number of plugins handled internally

        These should be equal the number of nodes actually in the graph.
    */
    int getPluginsCount () const;
    bool dropPluginOnTrack (const File& pluginFile,
                            int mouseX,
                            int mouseY);
    bool loadAndAppendPlugin (const File& file, 
							  int mouseX,
                              int mouseY);
    bool loadAndAppendPlugin ();
    bool closeSelectedPlugins ();
    bool closeAllPlugins ();

    //==============================================================================
    enum ColourIds
    {
        mainBackColourId         = 0x99001001,
        nodeBackBrightColourId   = 0x99001002,
        nodeBackColourId         = 0x99001003,
        nodeTextBrightColourId   = 0x99001004,
        nodeTextColourId         = 0x99001005,
        nodeBorderBrightColourId = 0x99001006,
        nodeBorderColourId       = 0x99001007,
        wireAudioBrightColourId  = 0x99001008,
        wireAudioColourId        = 0x99001009,
        wireMidiBrightColourId   = 0x9900100A,
        wireMidiColourId         = 0x9900100B
    };

    //==============================================================================
    void findLassoItemsInArea (Array<GraphNodeComponent*> &itemsFound, int x, int y, int width, int height);
    SelectedItemSet<GraphNodeComponent*> & getLassoSelection ();

    //==============================================================================
    bool isInterestedInDragSource (const String& sourceDescription, Component* source);
    void itemDragEnter (const String& sourceDescription,
                        Component* sourceComponent,
                        int x, int y);
    void itemDragMove (const String& sourceDescription,
                       Component* sourceComponent,
                       int x, int y);
    void itemDragExit (const String& sourceDescription,
                       Component* sourceComponent);
    void itemDropped (const String& sourceDescription,
                      Component* sourceComponent,
                      int x, int y);

    //==============================================================================
    /** @internal */
    void mouseDown (const MouseEvent& e);
    /** @internal */
    void mouseDrag (const MouseEvent& e);
    /** @internal */
    void mouseUp (const MouseEvent& e);
    /** @internal */
    bool keyPressed (const KeyPress& key);
    /** @internal */
    void resized ();
    /** @internal */
    void paint (Graphics& g);
    /** @internal */
    bool isInterestedInFileDrag (const StringArray&);
    /** @internal */
    void filesDropped (const StringArray& filenames, int mouseX, int mouseY);
    /** @internal */
    void changeListenerCallback (void* source);

protected:

    //==============================================================================
    void recalculateConnectionsRecursive (GraphNodeComponent* node,
                                          ProcessingGraph* graph,
                                          const int insertIndex,
//                                          const int connectorType,
                                          const bool createConnection);

    GraphNodeComponent* findNodeByUserData (void* data);

    bool createPluginNode (BasePlugin* plugin);
    bool deletePluginNode (GraphNodeComponent* node);

    void cleanInternalGraph ();

    //==============================================================================
    ChannelHost* host;
    ChannelEditor* owner;

    GraphNodeComponent* inputs;
    GraphNodeComponent* outputs;
	GraphNodeComponent* track;
    OwnedArray<GraphNodeComponent> nodes;

    ChannelGraphComponentSelectedModules selectedNodes;
    LassoComponent<GraphNodeComponent*>* lassoComponent;

    GraphNodeComponent* currentClickedNode;
    
    Font currentFont;
    int defaultNodeWidth;
    int defaultNodeHeight;
    bool leftToRight;
    bool somethingIsBeingDraggedOver;
    
    int dragStartX, dragStartY;
};


#endif // __JUCETICE_JOSTCHANNELGRAPHCOMPONENT_HEADER__

