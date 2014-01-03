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

#include "JackedGraph.h"
#include "JackedWindow.h"
#include "JackedDevice.h"

//==============================================================================
JackedGraph::JackedGraph (JackedWindow* owner)
    : parentWindow (owner),
      client (0),
      somethingIsBeingDraggedOver (false),
      currentFont (12.0f, Font::plain)
{
    DBG ("JackedGraph::JackedGraph");

    setOpaque (true);
    setWantsKeyboardFocus (true);

    setColour (JackedGraph::mainBackColourId,           Colours::white);
    setColour (JackedGraph::nodeBackBrightColourId,     Colours::slategrey.brighter (1.0f));
    setColour (JackedGraph::nodeBackColourId,           Colours::slategrey.brighter (0.5f));
    setColour (JackedGraph::nodeTextBrightColourId,     Colours::white);
    setColour (JackedGraph::nodeTextColourId,           Colours::white.darker (0.15f));
    setColour (JackedGraph::nodeBorderBrightColourId,   Colours::slategrey.brighter (0.5f));
    setColour (JackedGraph::nodeBorderColourId,         Colours::slategrey);
    setColour (JackedGraph::wireAudioBrightColourId,    Colours::green);
    setColour (JackedGraph::wireAudioColourId,          Colours::green.darker (0.5f));
    setColour (JackedGraph::wireMidiBrightColourId,     Colours::orange);
    setColour (JackedGraph::wireMidiColourId,           Colours::orange.darker (0.5f));
}

JackedGraph::~JackedGraph()
{
    DBG ("JackedGraph::~JackedGraph");

    deactivateClient ();

    cleanNodes ();
}

//==============================================================================
void JackedGraph::resized ()
{
    for (int i = 0; i < inputNodes.size (); i++)
    {
        GraphNodeComponent* component = inputNodes.getUnchecked (i);
        if (component)
            component->setTopLeftPosition (0, component->getY());
    }

    for (int i = 0; i < outputNodes.size (); i++)
    {
        GraphNodeComponent* component = outputNodes.getUnchecked (i);
        if (component)
            component->setTopRightPosition (getWidth(), component->getY());
    }
}

void JackedGraph::paint (Graphics& g)
{
    g.fillAll (findColour (JackedGraph::mainBackColourId));

    if (somethingIsBeingDraggedOver)
    {
        g.setColour (findColour (JackedGraph::nodeBorderColourId));
        g.drawRect (0, 0, getWidth (), getHeight(), 2);
    }
}

void JackedGraph::filesDropped (const StringArray& filenames,
                                int mouseX,
                                int mouseY)
{
}

bool JackedGraph::keyPressed (const KeyPress& key)
{
    return true;
}

void JackedGraph::mouseUp (const MouseEvent& e)
{
}

//==============================================================================
void JackedGraph::nodePaint (GraphNodeComponent* node, Graphics& g)
{
    int width = node->getWidth(),
        height = node->getHeight();

    // background
    Colour background;
#if 0
//    if (node->isSelected ())
//        background = findColour (JackedGraph::nodeBackBrightColourId);
//    else
#endif
    background = findColour (JackedGraph::nodeBackColourId);

#if 0
    GradientBrush gb (background, 0.0f, 0.0f,
                      background.darker (0.2f),
                      0.0f,
                      height - 1.0f,
                      false);

    g.setBrush (&gb);
#endif
    g.fillAll();

#if 0
    g.setColour (background);
    g.fillRect (0, 0, width, height);
#endif

    // TODO - draw image if any ?

    // plugin text
#if 0
    if (node->isSelected ())
        g.setColour (findColour (JackedGraph::nodeTextBrightColourId));
    else
#endif
        g.setColour (findColour (JackedGraph::nodeTextColourId));

    String textToDisplay = node->getText ();
    if (textToDisplay != String::empty)
    {
        g.setFont (currentFont);
        g.drawText (textToDisplay,
                    0, 0, width, height,
                    Justification::centred,
                    false);
    }

    // border
#if 0
    if (node->isSelected ())
        g.setColour (findColour (JackedGraph::nodeBorderBrightColourId));
    else
#endif
        g.setColour (findColour (JackedGraph::nodeBorderColourId));

    g.drawRect (0, 0, width, height, 2);
}

void JackedGraph::nodeMoved (GraphNodeComponent* node)
{
    jassert (node != 0);
}

void JackedGraph::nodeSelected (GraphNodeComponent* node)
{
}

void JackedGraph::nodeDoubleClicked (GraphNodeComponent* node,
                                     const MouseEvent& e)
{
    jassert (node != 0);
}

void JackedGraph::nodePopupMenuSelected (GraphNodeComponent* node)
{
    jassert (node != 0);

    int inputLinks = node->getInputLinksCount ();
    int outputLinks = node->getOutputLinksCount ();

    PopupMenu menu;
    if (inputLinks > 0 && outputLinks > 0)
        menu.addItem (1, "Disconnect all");
    if (inputLinks > 0)
        menu.addItem (2, "Disconnect inputs");
    if (outputLinks > 0)
        menu.addItem (3, "Disconnect outputs");

    const int result = menu.show();
    switch (result)
    {
    case 1: // Disconnect all
        node->breakAllLinks();
        break;
    case 2: // Disconnect inputs
        node->breakInputLinks();
        break;
    case 3: // Disconnect outputs
        node->breakOutputLinks();
        break;
    default:
        break;
    }
}

void JackedGraph::connectorPopupMenuSelected (GraphConnectorComponent* connector)
{
    jassert (connector != 0);

    PopupMenu menu;

    Array<GraphConnectorComponent*> links;
    connector->getLinkedConnectors (links);
    
    if (links.size () > 0)
    {
        menu.addItem (1, "Break connections");
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
            break;
        }
    }
}

void JackedGraph::linkPopupMenuSelected (GraphLinkComponent* link)
{
}

Colour JackedGraph::getConnectorColour (GraphConnectorComponent* connector, const bool isSelected)
{
    jassert (connector != 0);

    switch (connector->getType ())
    {
    case JACKED_LINKTYPE_AUDIO: // audio
        return isSelected ? findColour (JackedGraph::wireAudioBrightColourId)
                          : findColour (JackedGraph::wireAudioColourId);
    case JACKED_LINKTYPE_MIDI: // midi
        return isSelected ? findColour (JackedGraph::wireMidiBrightColourId)
                          : findColour (JackedGraph::wireMidiColourId);
    }

    return isSelected ? Colours::red : Colours::black;
}

void JackedGraph::linkConnected (GraphLinkComponent* link)
{
    if (client && link)
    {
        GraphConnectorComponent* from = link->from;
        GraphConnectorComponent* to = link->to;

        JackedDevice* fromNode = (JackedDevice*) from->getParentGraphComponent ();
        JackedDevice* toNode = (JackedDevice*) to->getParentGraphComponent ();

        DBG (fromNode->getOutputConnectorName (from->getConnectorID ()) + " > " + 
             toNode->getInputConnectorName (to->getConnectorID()));

        jack_connect (client,
                      fromNode->getOutputConnectorName (from->getConnectorID ()),
                      toNode->getInputConnectorName (to->getConnectorID()));
    }
}

void JackedGraph::linkDisconnected (GraphLinkComponent* link)
{
    if (client && link)
    {
        GraphConnectorComponent* from = link->from;
        GraphConnectorComponent* to = link->to;

        JackedDevice* fromNode = (JackedDevice*) from->getParentGraphComponent ();
        JackedDevice* toNode = (JackedDevice*) to->getParentGraphComponent ();

        DBG (fromNode->getOutputConnectorName (from->getConnectorID ()) + " > " + 
             toNode->getInputConnectorName (to->getConnectorID()));

        jack_disconnect (client,
                         fromNode->getOutputConnectorName (from->getConnectorID ()),
                         toNode->getInputConnectorName (to->getConnectorID()));
    }
}

//==============================================================================
void JackedGraph::handleAsyncUpdate ()
{
    DBG ("JackedGraph::handleAsyncUpdate");

    cleanNodes ();
    cleanConnections ();

    inputNames.clear ();
    outputNames.clear ();

    if (client != 0)
    {
        const char** ports = 0;

        // scan for output devices
        ports = jack_get_ports (client, 0, 0, /* JackPortIsPhysical | */ JackPortIsOutput);
        if (ports)
        {
            int j = 0;
            while (ports [j])
            {
                String clientName (ports [j++]);
                String clientOnlyName = clientName.upToFirstOccurrenceOf (T(":"), false, false);
                String portOnlyName = clientName.fromFirstOccurrenceOf (T(":"), false, false);
                String portType = jack_port_type (jack_port_by_name (client, (const char *) clientName));

                inputNames.add (clientName);

                JackedDevice* component = findInputNodeByName (clientOnlyName);
                if (component == 0)
                {
                    addAndMakeVisible (component = new JackedDevice(clientOnlyName));
                    component->setNodeListener (this);
                    
                    inputNodes.add (component);
                }

                if (component)
                {
                    if (portType == T(JACK_DEFAULT_AUDIO_TYPE))
                        component->addOutputConnector (portOnlyName, JACKED_LINKTYPE_AUDIO);
                    else if (portType == T(JACK_DEFAULT_MIDI_TYPE))
                        component->addOutputConnector (portOnlyName, JACKED_LINKTYPE_MIDI);
                    else
                        printf ("wrong port type\n");
                }
            }

            int hSize = 20, hBorder = 2, yPos = 0;            
            
            for (int i = 0; i < inputNodes.size (); i++)
            {
                JackedDevice* component = inputNodes.getUnchecked (i);
                
                if (component)
                {
                    int numIns = component->getInputConnectorCount ();
                    int numOuts = component->getOutputConnectorCount ();

                    int h = jmax (hSize, (jmax (numIns, numOuts) + 1) * 16);

                    component->setBounds (0, yPos, 100, h);
                    component->setLocked (true);
                    component->setVisible (true);
                    
                    yPos += h + hBorder;
                }
            }

            free (ports);
        }

        // scan for input devices
        ports = jack_get_ports (client, 0, 0, /* JackPortIsPhysical | */ JackPortIsInput);
        if (ports)
        {
            int j = 0;
            while (ports [j])
            {
                String clientName (ports [j++]);
                String clientOnlyName = clientName.upToFirstOccurrenceOf (T(":"), false, false);
                String portOnlyName = clientName.fromFirstOccurrenceOf (T(":"), false, false);
                String portType = jack_port_type (jack_port_by_name (client, (const char *) clientName));
                
                outputNames.add (clientName);
                
                JackedDevice* component = findOutputNodeByName (clientOnlyName);
                
                if (component == 0)
                {
                    addAndMakeVisible (component = new JackedDevice(clientOnlyName));
                    component->setNodeListener (this);
                    
                    outputNodes.add (component);
                }

                if (component)
                {
                    if (portType == T(JACK_DEFAULT_AUDIO_TYPE))
                        component->addInputConnector (portOnlyName, JACKED_LINKTYPE_AUDIO);
                    else if (portType == T(JACK_DEFAULT_MIDI_TYPE))
                        component->addInputConnector (portOnlyName, JACKED_LINKTYPE_MIDI);
                    else
                        printf ("wrong port type\n");
                }
            }

            int hSize = 20, hBorder = 2, yPos = 0;            
            
            for (int i = 0; i < outputNodes.size (); i++)
            {
                JackedDevice* component = outputNodes.getUnchecked (i);
                if (component)
                {
                    int numIns = component->getInputConnectorCount ();
                    int numOuts = component->getOutputConnectorCount ();

                    int h = jmax (hSize, (jmax (numIns, numOuts) + 1) * 16);

                    component->setBounds (getWidth() - 100, yPos, 100, h);
                    component->setLocked (true);
                    component->setVisible (true);
                    
                    yPos += h + hBorder;
                }
            }

            free (ports);
        }

        // connections
        for (int i = 0; i < inputNames.size (); i++)
        {
            String srcName = inputNames [i];
            String srcOnlyName = srcName.upToFirstOccurrenceOf (T(":"), false, false);
            String srcPortOnlyName = srcName.fromFirstOccurrenceOf (T(":"), false, false);
            String srcPortType = jack_port_type (jack_port_by_name (client, (const char *) srcName));                    

            JackedDevice* srcComponent = findInputNodeByName (srcOnlyName);
            if (srcComponent)
            {
                jack_port_t* port = jack_port_by_name (client, (const char *) srcName);
                const char** conn = jack_port_get_all_connections (client, port);
                if (conn)
                {
                    int j = 0;
                    while (conn [j])
                    {
                        String destName (conn [j++]);
                        String destOnlyName = destName.upToFirstOccurrenceOf (T(":"), false, false);
                        String destPortOnlyName = destName.fromFirstOccurrenceOf (T(":"), false, false);
                        String destPortType = jack_port_type (jack_port_by_name (client, (const char *) destName));                    

                        DBG (srcName + " " + srcOnlyName + " " + srcPortOnlyName + " " + srcPortType);
                        DBG (destName + " " + destOnlyName + " " + destPortOnlyName + " " + destPortType);

                        JackedDevice* destComponent = findOutputNodeByName (destOnlyName);
                        if (destComponent)
                        {
                            srcComponent->connectToNode (srcComponent->getOutputConnectorByName (srcPortOnlyName),
                                                         destComponent,
                                                         destComponent->getInputConnectorByName (destPortOnlyName),
                                                         false);
                        }
                    }
                    
                    free (conn);
                }
            }
        }

    }

    // update fixed node size and position
    resized ();
}

//==============================================================================
/*
bool JackedGraph::createPluginNode (BasePlugin* plugin)
{
    return false;
}

bool JackedGraph::deletePluginNode (GraphNodeComponent* node)
{
    if (node)
    {
        DBG ("GraphComponent::deletePluginNode");

        node->breakAllLinks (false);
        node->deleteConnectors (true);

        nodes.remove (nodes.indexOf (node), true);
        return true;
    }

    return false;
}
*/

//==============================================================================
JackedDevice* JackedGraph::findInputNodeByName (const String& name)
{
    for (int i = inputNodes.size (); --i >= 0;)
    {
        JackedDevice* c = inputNodes.getUnchecked (i);
        if (name == c->getText ())
            return c;
    }
    
    return 0;       
}

JackedDevice* JackedGraph::findOutputNodeByName (const String& name)
{
    for (int i = outputNodes.size (); --i >= 0;)
    {
        JackedDevice* c = outputNodes.getUnchecked (i);
        if (name == c->getText ())
            return c;
    }
    
    return 0;
}

//==============================================================================
void JackedGraph::cleanConnections ()
{
    for (int i = inputNodes.size (); --i >= 0;)
        inputNodes.getUnchecked (i)->breakAllLinks (false);

    for (int i = outputNodes.size (); --i >= 0;)
        outputNodes.getUnchecked (i)->breakAllLinks (false);
}

void JackedGraph::cleanNodes ()
{
    DBG ("JackedGraph::cleanNodes < " + String (getNumChildComponents()));

    cleanConnections ();

    for (int i = inputNodes.size (); --i >= 0;)
        inputNodes.getUnchecked (i)->deleteConnectors (true);
    for (int i = outputNodes.size (); --i >= 0;)
        outputNodes.getUnchecked (i)->deleteConnectors (true);

    inputNodes.clear (true);
    outputNodes.clear (true);

    DBG ("JackedGraph::cleanNodes > " + String (getNumChildComponents()));
}

//==============================================================================
void JackedGraph::ClientRegistrationCallback (const char* name, int regist, void *arg)
{
    JackedGraph* graph = (JackedGraph*) arg;

    DBG ("JackedGraph::ClientRegistrationCallback");
    
    graph->triggerAsyncUpdate ();
}

void JackedGraph::PortRegistrationCallback (jack_port_id_t port, int regist, void *arg)
{
    JackedGraph* graph = (JackedGraph*) arg;

    DBG ("JackedGraph::PortRegistrationCallback");

    graph->triggerAsyncUpdate ();
}

void JackedGraph::PortConnectCallback (jack_port_id_t a, jack_port_id_t b, int connect, void* arg)
{
    JackedGraph* graph = (JackedGraph*) arg;

    DBG ("JackedGraph::PortConnectCallback");

    graph->triggerAsyncUpdate ();
}

int JackedGraph::GraphOrderCallback (void *arg)
{
//    JackedGraph* graph = (JackedGraph*) arg;
    return 1;
}

//==============================================================================
bool JackedGraph::activateClient ()
{
    if (client)
        return true;

    jack_status_t status;
    client = jack_client_open ("Jacked", JackNoStartServer, &status);
    if (client == 0)
    {
		if (status & JackServerFailed || status & JackServerError)
			printf ("Unable to connect to JACK server\n");
		if (status & JackVersionError)
			printf ("Client's protocol version does not match\n");
		if (status & JackInvalidOption)
			printf ("The operation contained an invalid or unsupported option\n");
		if (status & JackNameNotUnique)
			printf ("The desired client name was not unique\n");
		if (status & JackNoSuchClient)
			printf ("Requested client does not exist\n");
		if (status & JackInitFailure)
			printf ("Unable to initialize client\n");
	    
	    return false;
    }
    else
    {
        jack_set_client_registration_callback (client, JackedGraph::ClientRegistrationCallback, this);
        jack_set_port_registration_callback (client, JackedGraph::PortRegistrationCallback, this);
        jack_set_port_connect_callback (client, JackedGraph::PortConnectCallback, this);
        jack_set_graph_order_callback (client, JackedGraph::GraphOrderCallback, this);
        
        jack_activate (client);
        
        return true;
    }
}

bool JackedGraph::deactivateClient ()
{
    if (! client)
        return false;

    jack_deactivate (client);
    jack_client_close (client);
    client = 0;

    return true;
}

//==============================================================================
void JackedGraph::startCheckForServer ()
{
    DBG ("JackedGraph::startCheckForServer");

    if (activateClient())
    {
        triggerAsyncUpdate ();
    }
    else
    {
        startTimer (1000);
    }
}

void JackedGraph::timerCallback ()
{
    if (activateClient())
    {
        stopTimer();
        triggerAsyncUpdate ();
    }
}

//==============================================================================
/*
bool JackedGraph::isInterestedInDragSource (const String& sourceDescription,
                                               Component* source)
{
    return sourceDescription.startsWith (T("Plugins: "))
           || sourceDescription.startsWith (T("Sessions: "));
}

void JackedGraph::itemDragEnter (const String& sourceDescription,
                                    Component* sourceComponent,
                                    int x, int y)
{
    somethingIsBeingDraggedOver = true;
    repaint();
}

void JackedGraph::itemDragMove (const String& sourceDescription,
                                   Component* sourceComponent,
                                   int x, int y)
{
}

void JackedGraph::itemDragExit (const String& sourceDescription,
                                   Component* sourceComponent)
{
    somethingIsBeingDraggedOver = false;
    repaint();
}

void JackedGraph::itemDropped (const String& sourceDescription,
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
*/
