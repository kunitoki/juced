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

#include "HostFilterBase.h"
#include "HostFilterComponent.h"


//==============================================================================
int HostFilterBase::numInstances = 0;



//==============================================================================
HostFilterBase::HostFilterBase (const String& commandLine)
  : host (0)
{
    DBG ("HostFilterBase::HostFilterBase");

    int numInputs = JucePlugin_MaxNumInputChannels;
    int numOutputs = JucePlugin_MaxNumOutputChannels;
    String sessionFileString = String::empty;

    // get the global config instance
    Config* config = Config::getInstance ();

    // create the command manager
    CommandManager::getInstance();

    // TODO - this is a hack for a single dummy parameter
    //        make this to follow plugin parameters
    setNumParameters (1);
    registerParameter (0, &dummyParameter.name (T("dummy")).unit (T("%")));

    // parse the command line
    CommandLineTokenizer tokenizer;
    tokenizer.parseCommandLine (commandLine);
    
    printf ("%s \n", (const char*) commandLine);
    
    if (tokenizer.searchToken("--inputs") >= 0)
    {
      numInputs = tokenizer.getOptionInt ("--inputs", JucePlugin_MaxNumInputChannels);
    }

    if (tokenizer.searchToken("--outputs") >= 0)
    {
      numOutputs = tokenizer.getOptionInt ("--outputs", JucePlugin_MaxNumOutputChannels);
    }

    if (tokenizer.searchToken("--session") >= 0)
    {
      sessionFileString = tokenizer.getOptionString ("--session", String::empty);
    }

    // create transport
    transport = new Transport (this);

    // add the default host
    host = new Host (this, numInputs, numOutputs);

    // load a session file !
    File sessionFile (sessionFileString);
    if (sessionFile.existsAsFile ())
    {
        MemoryBlock fileData;
        if (sessionFile.loadFileAsData (fileData))
        {
            setStateInformation (fileData.getData (), fileData.getSize());

            config->addRecentSession (sessionFile);
        }
    }

#if JUCE_LASH
    // initialize lash
    lashManager = new LashManager (this);
#endif
}

HostFilterBase::~HostFilterBase()
{
    DBG ("HostFilterBase::~HostFilterBase");

#if JUCE_LASH
    // delete lash manager
    deleteAndZero (lashManager);
#endif

    // free host and transport
    deleteAndZero (host);
    deleteAndZero (transport);

    // static deallocation
    if (--HostFilterBase::numInstances == 0)
    {
        Config::deleteInstance ();
    }

    // delete command manager instance
    CommandManager::deleteInstance ();
}

//==============================================================================
void HostFilterBase::prepareToPlay (double sampleRate_, int samplesPerBlock_)
{
    DBG ("HostFilterBase::prepareToPlay");

    // prepare host
    host->prepareToPlay (sampleRate_, samplesPerBlock_);

    // change to Realtime priority if in standalone mode !
#if 0
    if (JUCEApplication::getInstance() && Config::getInstance ()->realTime)
        Process::setPriority (Process::LowPriority);
#endif
}

void HostFilterBase::releaseResources()
{
    DBG ("HostFilterBase::releaseResources");

    // change back to Normal priority only if standalone mode !
#if 0
    if (JUCEApplication::getInstance() && Config::getInstance ()->realTime)
        Process::setPriority (Process::NormalPriority);
#endif

    // release host
    host->releaseResources();
}

void HostFilterBase::processBlock (AudioSampleBuffer& buffer,
                                   MidiBuffer& midiMessages)
{
    // process incoming midi
    midiAutomatorManager.handleMidiMessageBuffer (midiMessages);

    // process multi track
    host->processBlock (buffer, midiMessages);
}

//==============================================================================
void HostFilterBase::setExternalTransport (ExternalTransport* externalTransport)
{
    if (transport)
        transport->setExternalTransport (externalTransport);
}


//==============================================================================
void HostFilterBase::getStateInformation (MemoryBlock& destData)
{
    DBG ("HostFilterBase::getStateInformation");

    // we started saving data
    bool wasSuspended = isSuspended ();
    if (! wasSuspended) suspendProcessing (true);

#ifndef JUCE_DEBUG
    try
    {
#endif
        XmlElement xmlState (JOST_PRESET_SESSIONTAG);

        XmlElement* e = new XmlElement (JOST_PRESET_TRACKTAG);
        host->saveToXml (e);
        xmlState.addChildElement (e);

        copyXmlToBinary (xmlState, destData);

#ifndef JUCE_DEBUG
    }
    catch (...)
    {
        AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                     T("Error !"),
                                     T("Something bad occurred while saving session XML !"));
    }
#endif

    // end saving data
    if (! wasSuspended) suspendProcessing (false);
}

void HostFilterBase::setStateInformation (const void* data, int sizeInBytes)
{
    DBG ("HostFilterBase::setStateInformation");

    // we started saving data
    bool wasSuspended = isSuspended ();
    if (! wasSuspended) suspendProcessing (true);

#ifndef JUCE_DEBUG
    try
    {
#endif
        // use this helper function to get the XML from this binary blob..
        XmlElement* const xmlState = getXmlFromBinary (data, sizeInBytes);
        if (xmlState != 0)
        {
            // check that it's the right type of xml..
            if (xmlState->hasTagName (JOST_PRESET_SESSIONTAG))
            {
                // load from XML and notify GUI
                XmlElement* e = xmlState->getChildByName (JOST_PRESET_TRACKTAG);
                if (e)
                {
                    // notify GUI about the new session
                    if (getEditor())
                        getEditor()->closePluginEditorWindows ();

                    host->loadFromXml (e);

                    // notify GUI about the new session
                    sendChangeMessage (this);
                }

                delete xmlState;
            }
            else
            {
                printf ("Error parsing session XML\n");
            }
        }

#ifndef JUCE_DEBUG
    }
    catch (...)
    {
        AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                     T("Error !"),
                                     T("Something bad occurred while restoring session XML !"));
    }
#endif

    // we finished saving data
    if (! wasSuspended) suspendProcessing (false);
}


//==============================================================================
HostFilterComponent* HostFilterBase::getEditor()
{
    return (HostFilterComponent*) getActiveEditor();
}

AudioProcessorEditor* HostFilterBase::createEditor()
{
    return new HostFilterComponent (this);
}

//==============================================================================
AudioProcessor* JUCE_CALLTYPE createPluginFilter (const String& commandLine)
{
    if (HostFilterBase::numInstances == 0)
    {
        // create the config
        Config::getInstance ();

        // create the filter
        HostFilterBase::numInstances++;

        return new HostFilterBase (commandLine);
    }
    else
    {
        AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                     T("Error !"),
                                     T("You can't load more than one JOST instance..."));
        return 0;
    }
}
