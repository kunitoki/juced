/***************************************************************************
 *   Copyright (C) 2009 by Christian Borss                                 *
 *   christian.borss@rub.de                                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#ifndef __EDITORCOMPONENT_H__
#define __EDITORCOMPONENT_H__

// forward declarations
class MasterAndCommander;
class TabMain;
//class TabModulation;
class TabTimbre;
class TabPresetEditor;
class TabPreferences;
class TabAbout;


enum CONST_EDITORCOMPONENT {
    TAB_MAIN = 0,
//    TAB_MODULATION,
    TAB_TIMBRE,
    TAB_PRESETEDITOR,
    TAB_PREFERENCES,
    TAB_ABOUT
};


#include "HybridReverb2Processor.h"


//==============================================================================
/**
    This is the Component that our filter will use as its UI.

    One or more of these is created by the HybridReverb2Processor::createEditor() method,
    and they will be deleted at some later time by the wrapper code.

    To demonstrate the correct way of connecting a filter to its UI, this
    class is a ChangeListener, and our demo filter is a ChangeBroadcaster. The
    editor component registers with the filter when it's created and deregisters
    when it's destroyed. When the filter's parameters are changed, it broadcasts
    a message and this editor responds by updating its display.
*/
class EditorComponent   : public AudioProcessorEditor,
                          public ChangeListener
{

    //==============================================================================
    class MyTabbedComponent : public TabbedComponent
    {
    public:
        MyTabbedComponent(const TabbedButtonBar::Orientation orientation,
                          EditorComponent *editor)
            : TabbedComponent(orientation),
              parent(editor)
        {
        }

        void currentTabChanged(const int newCurrentTabIndex, const String &newCurrentTabName)
        {
            parent->currentTabChanged(newCurrentTabIndex, newCurrentTabName);
        }

    private:
        EditorComponent* parent;
    };
    //==============================================================================

public:
    /** Constructor.

        When created, this will register itself with the filter for changes. It's
        safe to assume that the filter won't be deleted before this object is.
    */
    EditorComponent (HybridReverb2Processor* const ownerFilter);

    /** Destructor. */
    ~EditorComponent();

    //==============================================================================
    /** This method is called whenever the user selects one of the tabs. */
    void currentTabChanged(const int newCurrentTabIndex,
                           const String &newCurrentTabName);

    //==============================================================================
    /** Our demo filter is a ChangeBroadcaster, and will call us back when one of
        its parameters changes.
    */
    void changeListenerCallback (void* source);

//    void sliderValueChanged (Slider*);

    //==============================================================================
    /** Standard Juce paint callback. */
    void paint (Graphics& g);

    /** Standard Juce resize callback. */
    void resized();


private:
    //==============================================================================
//    Slider* gainSlider;

    void updateParametersFromFilter();

    // handy wrapper method to avoid having to cast the filter to a HybridReverb2Processor
    // every time we need it..
    HybridReverb2Processor* getFilter() const throw()       { return (HybridReverb2Processor*) getAudioProcessor(); }

    MasterAndCommander* master;
    MyTabbedComponent* myTabbedComponent;

    TabMain         *tabMain;
//    TabModulation   *tabModulation;
    TabTimbre       *tabTimbre;
    TabPresetEditor *tabPresetEditor;
    TabPreferences  *tabPreferences;
    TabAbout        *tabAbout;
};


#endif
