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

#include "SurfaceComponent.h"
#include "SurfaceObjects.h"
#include "SurfaceProperties.h"
#include "../../HostFilterComponent.h"

//==============================================================================
class InternalSurfaceComponent  : public Component
{
public:

    InternalSurfaceComponent (SurfaceComponent* parent_)
        : parent (parent_)
    {
        setInterceptsMouseClicks (false, true);
    }
    
    ~InternalSurfaceComponent ()
    {
        deleteAllChildren ();
    }

    void addSlider ()
    {
        SurfaceSlider* slider;

        addAndMakeVisible (slider = new SurfaceSlider (parent));
        slider->setRange (0.0, 1.0, 0.000001);
        slider->setSliderStyle (Slider::LinearBar);
        slider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
        slider->setBounds (100, 100, 200, 20);
        slider->setValue (0.5);

        slider->addListener (parent);
    }

    void addLabel ()
    {
        SurfaceLabel* label;

        addAndMakeVisible (label = new SurfaceLabel (parent));
        label->setBounds (100, 100, 200, 20);
    }

    void addJoystick ()
    {
        SurfaceJoystick* joy;

        addAndMakeVisible (joy = new SurfaceJoystick (parent));
        joy->setRanges (0, 1, 0, 1, 0.000001);
        joy->setValues (0.5, 0.5, false);
        joy->setBounds (100, 100, 100, 100);

        joy->addListener (parent);
    }

protected:

    SurfaceComponent* parent;
};


//==============================================================================
SurfaceComponent::SurfaceComponent (HostFilterComponent* owner_)
    : host (0),
      owner (owner_)
{
    setOpaque (true);
    setBufferedToImage (false);

    addAndMakeVisible (properties = new SurfaceProperties (this));
    addAndMakeVisible (internal = new InternalSurfaceComponent (this));
    addAndMakeVisible (editor = new ComponentLayoutManager ());

    horizontalLayout.setItemLayout (0, -0.8, -1.0, 350);   // internal surface
    horizontalLayout.setItemLayout (1, 2, 2, 2);          // divider bar
    horizontalLayout.setItemLayout (2, 100, 100, 100); // properties editor

    horizontalDividerBar = new StretchableLayoutResizerBar (&horizontalLayout, 1, false);
    addAndMakeVisible (horizontalDividerBar);

    editor->setTargetComponent (internal);
    editor->setEnabled (true);
}

SurfaceComponent::~SurfaceComponent()
{
    setHost (0);
    
    deleteAndZero (editor);
    deleteAndZero (internal);
    deleteAndZero (properties);
    deleteAndZero (horizontalDividerBar);
}

//==============================================================================
void SurfaceComponent::resized ()
{
    Component* vcomps[] = { internal, horizontalDividerBar, properties };
    
    horizontalLayout.layOutComponents (vcomps, 3,
                                       0, 0, getWidth(), getHeight(),
                                       true,     // lay out side-by-side
                                       true);     // resize the components' heights as well as widths
                                     
    editor->setBounds (0, 0, internal->getWidth(), internal->getHeight());
}

void SurfaceComponent::paint (Graphics& g)
{
    Colour backgroundColour = Config::getInstance ()->getColour (T("mainBackground"));

    g.fillAll (backgroundColour);
}

//==============================================================================
void SurfaceComponent::setHost (Host* hostToDisplay)
{
    host = hostToDisplay;
}

//==============================================================================
void SurfaceComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    SurfaceSlider* slider = dynamic_cast<SurfaceSlider*> (sliderThatWasMoved);
    if (slider)
    {
        BasePlugin* plugin = host->getPluginByUniqueHash (slider->getPlugin ());
        if (plugin)
        {
            plugin->setParameter (slider->getParameter (0), slider->getValue ());
        }
    }
}

void SurfaceComponent::joystickValueChanged (Joystick* joystickThatWasMoved)
{
    SurfaceJoystick* joystick = dynamic_cast<SurfaceJoystick*> (joystickThatWasMoved);
    if (joystick)
    {
        BasePlugin* plugin = host->getPluginByUniqueHash (joystick->getPlugin ());
        if (plugin)
        {
            plugin->setParameter (joystick->getParameter (0), joystick->getHorizontalValue ());
            plugin->setParameter (joystick->getParameter (1), joystick->getVerticalValue ());
        }
    }
}

void SurfaceComponent::surfaceObjectChanged (SurfaceObject* object)
{
    properties->setCurrentSurfaceObject (object);
}

//==============================================================================
void SurfaceComponent::fillPluginComboBox (ComboBox* combo)
{
    combo->clear ();

    for (int i = 0; i < host->getPluginsCount (); i++)
    {
        BasePlugin* plugin = host->getPluginByIndex (i);
        combo->addItem (plugin->getName (), plugin->getUniqueHash ());
    }
}

void SurfaceComponent::fillParametersComboBox (ComboBox* combo, const uint32 pluginHash)
{
    combo->clear ();

    BasePlugin* plugin = host->getPluginByUniqueHash (pluginHash);
    if (plugin)
    {
        for (int i = 0; i < plugin->getNumParameters (); i++)
        {
            combo->addItem (plugin->getParameterName (i), i + 1);
        }
    }
}

/*
PopupMenu SurfaceComponent::buildMenuForPluginsParameters ()
{
    jassert (host != 0);

    PopupMenu menu;
    
    for (int i = 0; i < host->getPluginsCount (); i++)
    {
        BasePlugin* plugin = host->getPluginByIndex (i);
        
        PopupMenu subMenu;
        
        int overallCount = i * 10000 + 1;
        for (int j = 0; j < plugin->getNumParameters (); j++)
        {
            subMenu.addItem (overallCount++, plugin->getParameterName (j));
        }
        
        menu.addSubMenu (plugin->getName (), subMenu);
    }

    return menu;
}
*/

//==============================================================================
void SurfaceComponent::mouseDown (const MouseEvent& e)
{
    if (e.mods.isRightButtonDown ())
    {
        bool isEditorEnabled = editor->isEnabled ();

        PopupMenu menu;
        menu.addItem (1, "Locked editing", true, ! isEditorEnabled);
        menu.addSeparator ();
        menu.addItem (2, "Add a slider", isEditorEnabled);
        menu.addItem (3, "Add a label", isEditorEnabled);
        menu.addItem (4, "Add a joystick", isEditorEnabled);
        menu.addSeparator ();
        menu.addItem (10, "Clear components", isEditorEnabled);

        const int result = menu.show();
        switch (result)
        {
        case 1:
            editor->setEnabled (! isEditorEnabled);
            break;
        case 2:
            internal->addSlider ();
            editor->updateFrames ();
            editor->setEnabled (isEditorEnabled);
            break;
        case 3:
            internal->addLabel ();
            editor->updateFrames ();
            editor->setEnabled (isEditorEnabled);
            break;
        case 4:
            internal->addJoystick ();
            editor->updateFrames ();
            editor->setEnabled (isEditorEnabled);
            break;
        case 10:
            internal->deleteAllChildren ();
            editor->updateFrames ();
            editor->setEnabled (isEditorEnabled);
            break;
        default:
            break;
        }
    }
}

void SurfaceComponent::mouseDrag (const MouseEvent& e)
{
}

void SurfaceComponent::mouseUp (const MouseEvent& e)
{
}

void SurfaceComponent::mouseDoubleClick (const MouseEvent& e)
{
}

void SurfaceComponent::filesDropped (const StringArray& filenames,
                                   int mouseX,
                                   int mouseY)
{
}

//==============================================================================
/*
bool SurfaceComponent::isInterestedInDragSource (const String& sourceDescription,
                                                 Component* source)
{
    // normally you'd check the sourceDescription value to see if it's the
    // sort of object that you're interested in before returning true, but for
    // the demo, we'll say yes to anything..
    return true;
}

void SurfaceComponent::itemDragEnter (const String& sourceDescription,
                                      Component* sourceComponent,
                                      int x, int y)
{
}

void SurfaceComponent::itemDragMove (const String& sourceDescription,
                                     Component* sourceComponent,
                                     int x, int y)
{
}

void SurfaceComponent::itemDragExit (const String& sourceDescription,
                                     Component* sourceComponent)
{
}

void SurfaceComponent::itemDropped (const String& sourceDescription,
                                    Component* sourceComponent,
                                    int x, int y)
{
}
*/

