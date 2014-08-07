//--------------------------------------------------------------------------------------------------
//
//  File:       PortPanel.cpp
//
//  Project:    M+M
//
//  Contains:   The class definition for a GUI element to represent a set of ports.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2014 by HPlus Technologies Ltd. and Simon Fraser University.
//
//              All rights reserved. Redistribution and use in source and binary forms, with or
//              without modification, are permitted provided that the following conditions are met:
//                * Redistributions of source code must retain the above copyright notice, this list
//                  of conditions and the following disclaimer.
//                * Redistributions in binary form must reproduce the above copyright notice, this
//                  list of conditions and the following disclaimer in the documentation and/or
//                  other materials provided with the distribution.
//                * Neither the name of the copyright holders nor the names of its contributors may
//                  be used to endorse or promote products derived from this software without
//                  specific prior written permission.
//
//              THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
//              EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//              OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
//              SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//              INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
//              TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//              BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//              CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//              ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//              DAMAGE.
//
//  Created:    2014-05-12
//
//--------------------------------------------------------------------------------------------------

#include "PortPanel.h"
#include "MovementTracker.h"
#include "ServiceViewerApp.h"
#include "Utilities.h"

//#include <odl/ODEnableLogging.h>
#include <odl/ODLogging.h>

#include "ofSystemUtils.h"

#define CAN_GRAB_OUTSIDE_HEADER_ /* */

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 
 @brief The class definition for a GUI element to represent a set of ports. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

PortPanel::PortPanel(const EntityKind   kind,
                     const string &     behaviour,
                     const string &     description,
                     ServiceViewerApp & owner,
                     ServiceEntity &    within) :
    inherited(), _tracker(NULL), _owner(owner), _within(within), _behaviour(behaviour),
    _description(description), _kind(kind), _grabbed(false)
{
    OD_LOG_ENTER(); //####
    OD_LOG_S2s("behaviour = ", behaviour, "description = ", description); //####
    OD_LOG_P2("owner = ", &owner, "within = ", &within); //####
    OD_LOG_EXIT_P(this); //####
} // PortPanel::PortPanel

PortPanel::PortPanel(const EntityKind         kind,
                     const string &           behaviour,
                     const string &           description,
                     ServiceViewerApp &       owner,
                     ServiceEntity &          within,
                     const ofParameterGroup & parameters,
                     string                   filename,
                     const float              xx,
                     const float              yy) :
    inherited(parameters, filename, xx, yy), _tracker(NULL), _owner(owner), _within(within),
    _behaviour(behaviour), _description(description), _kind(kind), _grabbed(false)
{
    OD_LOG_ENTER(); //####
    OD_LOG_S3s("behaviour = ", behaviour, "description = ", description, "filename = ", //####
              filename); //####
    OD_LOG_P3("owner = ", &owner, "within = ", &within, "parameters = ", &parameters); //####
    OD_LOG_D2("xx = ", xx, "yy = ", yy); //####
    OD_LOG_EXIT_P(this); //####
} // PortPanel::PortPanel

PortPanel::~PortPanel(void)
{
    OD_LOG_OBJENTER(); //####
    unregisterMouseEvents();
    for (int ii = 0, mm = getNumPorts(); mm > ii; ++ii)
    {
        PortEntry * aPort = getPort(ii);
        if (aPort)
        {
            _owner.forgetPort(aPort);
            delete aPort;
        }
    }
    OD_LOG_OBJEXIT(); //####
} // PortPanel::~PortPanel

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

PortEntry * PortPanel::addPort(const string &                 portName,
                               const string &                 portProtocol,
                               const PortEntry::PortUsage     portKind,
                               const PortEntry::PortDirection direction)
{
    OD_LOG_OBJENTER(); //####
    OD_LOG_S2s("portName = ", portName, "portProtocol = ", portProtocol); //####
    int         countBefore = getNumPorts();
    PortEntry * aPort = new PortEntry(this, portProtocol, portKind, direction);
    
    add(aPort->setup(portName));
    if (0 < countBefore)
    {
        PortEntry * bPort = getPort(countBefore - 1);
        
        if (bPort)
        {
            bPort->unsetAsLastPort();
        }
    }
    OD_LOG_OBJEXIT_P(aPort); //####
    return aPort;
} // PortPanel::addPort

PortEntry * PortPanel::getPort(const int num)
{
    OD_LOG_OBJENTER(); //####
    OD_LOG_L1("num = ", num); //####
    PortEntry * result;
    
    if (0 <= num)
    {
        result = reinterpret_cast<PortEntry *> (inherited::getControl(num));
    }
    else
    {
        result = NULL;
    }
    OD_LOG_OBJEXIT_P(result); //####
    return result;
} // PortPanel::getPort

bool PortPanel::isPointInside(const ofPoint & aPoint)
const
{
    OD_LOG_OBJENTER(); //####
    OD_LOG_P1("aPoint = ", &aPoint); //####
    bool result = b.inside(aPoint);
    
    OD_LOG_OBJEXIT_B(result); //####
    return result;
} // PortPanel::isPointInside

bool PortPanel::isPointInside(const float xPos,
                              const float yPos)
const
{
    OD_LOG_OBJENTER(); //####
    OD_LOG_D2("xPos = ", xPos, "yPos = ", yPos); //####
    bool result = b.inside(xPos, yPos);
    
    OD_LOG_OBJEXIT_B(result); //####
    return result;
} // PortPanel::isPointInside

bool PortPanel::mouseDragged(ofMouseEventArgs & args)
{
    OD_LOG_OBJENTER(); //####
    OD_LOG_P1("args = ", &args); //####
    OD_LOG_L1("args.button = ", args.button); //####
    bool result = false;
    bool addIsActive = _owner.addIsActive();
    bool controlWasActive = _owner.controlActive();
    bool removeIsActive = _owner.removeIsActive();
    
    OD_LOG_B3("addIsActive = ", addIsActive, "controlWasActive = ", controlWasActive, //####
              "removeIsActive = ", removeIsActive); //####
    if (controlWasActive || (OF_MOUSE_BUTTON_3 == args.button))
    {
        result = true;
    }
    else if (removeIsActive)
    {
        result = true;
    }
    else if (addIsActive)
    {
        // If we don't catch the drag, the initially clicked-on panel gets dragged around!
        _owner.reportConnectionDrag(args.x, args.y);
        result = true;
    }
    if (! result)
    {
        result = inherited::mouseDragged(args);
    }
    OD_LOG_OBJEXIT_B(result); //####
    return result;
} // PortPanel::mouseDragged

bool PortPanel::mouseMoved(ofMouseEventArgs & args)
{
    OD_LOG_OBJENTER(); //####
    OD_LOG_P1("args = ", &args); //####
    bool result = inherited::mouseMoved(args);
    
    OD_LOG_OBJEXIT_B(result); //####
    return result;
} // PortPanel::mouseMoved

bool PortPanel::mousePressed(ofMouseEventArgs & args)
{
    OD_LOG_OBJENTER(); //####
    OD_LOG_P1("args = ", &args); //####
    OD_LOG_L1("args.button = ", args.button); //####
    bool result = inherited::mousePressed(args);
    
    if (! result)
    {
        if (b.inside(args.x, args.y))
        {
            bool addIsActive = _owner.addIsActive();
            bool controlWasActive = _owner.controlActive();
            bool removeIsActive = _owner.removeIsActive();
            
            OD_LOG_B3("addIsActive = ", addIsActive, "controlWasActive = ", controlWasActive, //####
                      "removeIsActive = ", removeIsActive); //####
            if (OF_MOUSE_BUTTON_3 == args.button)
            {
                string thePanelDescription;
                
                switch (_kind)
                {
                    case kEntityKindClientOrAdapter :
                        thePanelDescription = "A client or adapter";
                        break;
                        
                    case kEntityKindService :
                        thePanelDescription = _description;
                        break;
                        
                    case kEntityKindOther :
                        thePanelDescription = "A standard port";
                        break;
                        
                }
                ofSystemAlertDialog(thePanelDescription);
                result = true;
            }
            else if (controlWasActive)
            {
                result = true;
            }
            else if (addIsActive || removeIsActive)
            {
                _owner.reportPortEntryClicked(NULL);
                result = true;
            }
        }
    }
    OD_LOG_OBJEXIT_B(result); //####
    return result;
} // PortPanel::mousePressed

bool PortPanel::mouseReleased(ofMouseEventArgs & args)
{
    OD_LOG_OBJENTER(); //####
    OD_LOG_P1("args = ", &args); //####
    OD_LOG_L1("args.button = ", args.button); //####
    bool result = false;
    
    if (b.inside(args.x, args.y))
    {
        bool addIsActive = _owner.addIsActive();
        bool controlWasActive = _owner.controlActive();
        bool removeIsActive = _owner.removeIsActive();
        
        OD_LOG_B3("addIsActive = ", addIsActive, "controlWasActive = ", controlWasActive, //####
                  "removeIsActive = ", removeIsActive); //####
        if (controlWasActive || (OF_MOUSE_BUTTON_3 == args.button))
        {
            result = true;
        }
        else if (removeIsActive)
        {
            result = true;
        }
        else if (addIsActive)
        {
            // Check if one of the entries would pick this up, and eat it otherwise.
            bool wouldHit = false;
            
            for (int ii = 0, mm = getNumPorts(); (mm > ii) && (! wouldHit); ++ii)
            {
                PortEntry * aPort = getPort(ii);
                
                if (aPort && aPort->isPointInside(args.x, args.y))
                {
                    wouldHit = true;
                }
            }
            if (! wouldHit)
            {
                // If the mouse is released outside a port entry, make sure to stop the
                // drag.
                _owner.clearDragState();
            }
            //result = true;
        }
    }
    if (! result)
    {
        if (_tracker && _grabbed)
        {
            _tracker->positionChangeComplete();
        }
        _grabbed = result = false;
        if (inherited::mouseReleased(args)) // <-- this clears bGuiActive
        {
            result = true;
        }
        else if (isGuiDrawing() && b.inside(args.x, args.y))
        {
            result = true;
        }
    }
    OD_LOG_OBJEXIT_B(result); //####
    return result;
} // PortPanel::mouseReleased

void PortPanel::setName(string name)
{
    OD_LOG_OBJENTER(); //####
    string prefix;
    
    switch (MplusM::Utilities::MapStringToServiceKind(_behaviour))
    {
	    case MplusM::Common::kServiceKindFilter :
            prefix = "Filter ";
            break;
            
	    case MplusM::Common::kServiceKindInput :
            prefix = "Input ";
            break;
            
	    case MplusM::Common::kServiceKindOutput :
            prefix = "Output ";
            break;
            
	    default :
            prefix = "";
            break;
            
    }
    inherited::setName(prefix + name);
    OD_LOG_OBJEXIT(); //####
} // PortPanel::setName

PortPanel * PortPanel::setup(string      collectionName,
                             string      filename,
                             const float xx,
                             const float yy)
{
    OD_LOG_OBJENTER(); //####
    registerMouseEvents();
    PortPanel * result = static_cast<PortPanel *> (inherited::setup(collectionName, filename, xx,
                                                                    yy));
    
    OD_LOG_OBJEXIT_P(result); //####
    return result;
} // PortPanel::setup

PortPanel * PortPanel::setup(const ofParameterGroup & parameters,
                             string                   filename,
                             const float              xx,
                             const float              yy)
{
    OD_LOG_OBJENTER(); //####
    registerMouseEvents();
    PortPanel * result = static_cast<PortPanel *> (inherited::setup(parameters, filename, xx, yy));
    
    OD_LOG_OBJEXIT_P(result); //####
    return result;
} // PortPanel::setup

bool PortPanel::setValue(float mx,
                         float my,
                         bool  bCheck)
{
    OD_LOG_OBJENTER(); //####
    OD_LOG_D2("mx = ", mx, "my = ", my); //####
    OD_LOG_B1("bCheck = ", bCheck); //####
    bool result = false;
    
    if (! isGuiDrawing())
    {
        _grabbed = bGuiActive = false;
    }
    else if (bCheck)
    {
        if (b.inside(mx, my))
        {
            bGuiActive = true;
#if defined(CAN_GRAB_OUTSIDE_HEADER_)
            _grabbed = true;
            _grabPt.set(mx - b.x, my - b.y);
#else // ! defined(CAN_GRAB_OUTSIDE_HEADER_)
            if ((my > b.y) && (my <= (b.y + getHeader())))
            {
                _grabbed = true;
                _grabPt.set(mx - b.x, my - b.y);
            }
            else
            {
                _grabbed = false;
            }
#endif // ! defined(CAN_GRAB_OUTSIDE_HEADER_)
            OD_LOG_B1("_grabbed <- ", _grabbed); //####
        }
    }
    else if (_grabbed)
    {
        setPosition(mx - _grabPt.x, my - _grabPt.y);
        if (_tracker)
        {
            _tracker->handlePositionChange();
        }
        result = true;
    }
    OD_LOG_OBJEXIT_B(result); //####
    return result;
} // PortPanel::setValue

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)
