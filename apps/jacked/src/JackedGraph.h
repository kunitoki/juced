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

#ifndef __JUCETICE_JACKED_GRAPH_HEADER__
#define __JUCETICE_JACKED_GRAPH_HEADER__

#include "JackedStandardHeader.h"

#include <jack/jack.h>
#include <jack/types.h>
#include <jack/transport.h>

class JackedWindow;
class JackedDevice;


//==============================================================================
/**
     A graph component for manipulate plugin graph
*/
class JackedGraph  : public Component,
//                     public DragAndDropTarget,
                     public AsyncUpdater,
                     public Timer,
                     public GraphNodeListener
{
public:

    //==============================================================================
    JackedGraph (JackedWindow* owner);
    ~JackedGraph ();

    //==============================================================================
    bool activateClient ();
    bool deactivateClient ();

    //==============================================================================
    /** This is called when a node needs to be paint */
    void nodePaint (GraphNodeComponent* node, Graphics& g);

    /** Callback whenever a node is moved */
    void nodeMoved (GraphNodeComponent* node);

    /** Callback whenever a node is selected */
    void nodeSelected (GraphNodeComponent* node);

    /** Callback whenever a node is double clicked */
    void nodeDoubleClicked (GraphNodeComponent* node,
                            const MouseEvent& e);

    //==============================================================================
    /** Callback whenever a node is right clicked */
    void nodePopupMenuSelected (GraphNodeComponent* node);

    /** Callback whenever a connector is right clicked */
    void connectorPopupMenuSelected (GraphConnectorComponent* connector);

    /** This is called whenever a node is right clicked */
    void linkPopupMenuSelected (GraphLinkComponent* link);

    //==============================================================================
    /** Callback ifor getting right connector colour */
    Colour getConnectorColour (GraphConnectorComponent* connector, const bool isSelected);

    //==============================================================================
    /** This is called whenever a node is right clicked */
    void linkConnected (GraphLinkComponent* newLink);

    /** This is called whenever a node is right clicked */
    void linkDisconnected (GraphLinkComponent* oldLink);

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
    /*
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
    */

    //==============================================================================
    /**
        Calling this after you have created a filter streamer will start checking
        for some JACK server daemon in background. If a server is found and running,
        then your client filter will be activated.

        @see timerCallback
    */
    void startCheckForServer ();
    
    //==============================================================================
    /** @internal */
    void mouseUp (const MouseEvent& e);
    /** @internal */
    bool keyPressed (const KeyPress& key);
    /** @internal */
    void resized ();
    /** @internal */
    void paint (Graphics& g);
    /** @internal */
    void handleAsyncUpdate ();
    /** @internal */
    void timerCallback ();
    /** @internal */
    void filesDropped (const StringArray& filenames,
                       int mouseX,
                       int mouseY);

protected:

    //==============================================================================
    /** Callbacks

        These are the jack's callbacks (these are ok for now)
    */
    static void ClientRegistrationCallback (const char* name, int regist, void *arg);
    static void PortRegistrationCallback (jack_port_id_t port, int regist, void *arg);    
    static void PortConnectCallback (jack_port_id_t a, jack_port_id_t b, int connect, void* arg);
    static int  GraphOrderCallback (void *arg);

    //==============================================================================
    JackedDevice* findInputNodeByName (const String& name);
    JackedDevice* findOutputNodeByName (const String& name);
    
    void cleanConnections ();
    void cleanNodes ();
    //==============================================================================
    JackedWindow* parentWindow;
    
    OwnedArray<JackedDevice> inputNodes, outputNodes;
    StringArray inputNames, outputNames;

    jack_client_t* client;

    bool somethingIsBeingDraggedOver;

    Font currentFont;
};


#endif // __JUCETICE_JOSTGRAPHCOMPONENT_HEADER__

