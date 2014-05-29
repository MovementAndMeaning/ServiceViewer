//--------------------------------------------------------------------------------------
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
//              All rights reserved. Redistribution and use in source and binary forms,
//              with or without modification, are permitted provided that the following
//              conditions are met:
//                * Redistributions of source code must retain the above copyright
//                  notice, this list of conditions and the following disclaimer.
//                * Redistributions in binary form must reproduce the above copyright
//                  notice, this list of conditions and the following disclaimer in the
//                  documentation and/or other materials provided with the
//                  distribution.
//                * Neither the name of the copyright holders nor the names of its
//                  contributors may be used to endorse or promote products derived
//                  from this software without specific prior written permission.
//
//              THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//              "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//              LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
//              PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//              OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//              SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//              LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//              DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//              THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//              (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//              OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//  Created:    2014-05-12
//
//--------------------------------------------------------------------------------------

#include "PortPanel.h"
#include "MovementTracker.h"
#include "ServiceViewerApp.h"

//#include "ODEnableLogging.h"
#include "ODLogging.h"

#include "ofSystemUtils.h"

// Note that openFrameworks defines a macro called 'check' :( which messes up other header files.
#undef check
#include "M+MUtilities.h"

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
# pragma mark Constructors and destructors
#endif // defined(__APPLE__)

PortPanel::PortPanel(const EntityKind   kind,
                     const string       description,
                     ServiceViewerApp * owner) :
            inherited(), _tracker(NULL), _owner(owner), _description(description), _kind(kind), _grabbed(false)
{
    OD_LOG_ENTER();//####
    OD_LOG_S1("description = ", description.c_str());//####
    OD_LOG_P1("owner = ", owner);//####
    OD_LOG_EXIT_P(this);//####
} // PortPanel::PortPanel

PortPanel::PortPanel(const EntityKind         kind,
                     const string             description,
                     ServiceViewerApp *       owner,
                     const ofParameterGroup & parameters,
                     string                   filename,
                     const float              xx,
                     const float              yy) :
            inherited(parameters, filename, xx, yy), _tracker(NULL), _owner(owner), _description(description),
            _kind(kind), _grabbed(false)
{
    OD_LOG_ENTER();//####
    OD_LOG_S2("description = ", description.c_str(), "filename = ", filename.c_str());//####
    OD_LOG_P2("owner = ", owner, "parameters = ", &parameters);//####
    OD_LOG_D2("xx = ", xx, "yy = ", yy);//####
    OD_LOG_EXIT_P(this);//####
} // PortPanel::PortPanel

PortPanel::~PortPanel(void)
{
    OD_LOG_OBJENTER();//####
    for (int ii = 0, mm = getNumPorts(); mm > ii; ++ii)
    {
        PortEntry * aPort = getPort(ii);
        
        if (aPort)
        {
            _owner->forgetPort(aPort);
            delete aPort;
        }
    }
    OD_LOG_OBJEXIT();//####
} // PortPanel::~PortPanel

#if defined(__APPLE__)
# pragma mark Actions
#endif // defined(__APPLE__)

void PortPanel::addPort(string                         portName,
                        const PortEntry::PortUsage     portKind,
                        const PortEntry::PortDirection direction)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_S1("portName = ", portName.c_str());//####
    int         countBefore = getNumPorts();
    PortEntry * aPort = new PortEntry(this, portKind, direction);
    
    add(aPort->setup(portName));
    _owner->rememberPort(aPort);
    if (0 < countBefore)
    {
        aPort = getPort(countBefore - 1);
        if (aPort)
        {
            aPort->unsetAsLastPort();
        }
    }
    OD_LOG_OBJEXIT();//####
} // PortPanel::addPort

PortEntry * PortPanel::getPort(const int num)
{
//    OD_LOG_OBJENTER();//####
//    OD_LOG_L1("num = ", num);//####
    PortEntry * result;
    
    if (0 <= num)
    {
        result = reinterpret_cast<PortEntry *>(inherited::getControl(num));
    }
    else
    {
        result = NULL;
    }
//    OD_LOG_OBJEXIT_P(result);//####
    return result;
} // getPort

bool PortPanel::mouseDragged(ofMouseEventArgs & args)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_P1("args = ", &args);//####
    OD_LOG_L1("args.button = ", args.button);//####
    bool result = false;
    
    if (_owner)
    {
        bool altWasActive = _owner->altActive();
        bool commandWasActive = _owner->commandActive();
        bool controlWasActive = _owner->controlActive();
        bool shiftWasActive = _owner->shiftActive();
        
        OD_LOG_B4("altWasActive = ", altWasActive, "commandWasActive = ", commandWasActive,//####
                  "controlWasActive = ", controlWasActive, "shiftWasActive = ", shiftWasActive);//####
        if (controlWasActive || (OF_MOUSE_BUTTON_3 == args.button))
        {
            result = true;
        }
        else if (shiftWasActive)
        {
            result = true;
        }
        else if (commandWasActive)
        {
            result = true;
        }
        else if (altWasActive)
        {
            result = true;
        }
    }
    if (! result)
    {
        result = inherited::mouseDragged(args);
    }
    OD_LOG_OBJEXIT_B(result);//####
    return result;
} // PortPanel::mouseDragged

bool PortPanel::mouseMoved(ofMouseEventArgs & args)
{
//    OD_LOG_OBJENTER();//####
//    OD_LOG_P1("args = ", &args);//####
    bool result = inherited::mouseMoved(args);
    
//    OD_LOG_OBJEXIT_B(result);//####
    return result;
} // PortPanel::mouseMoved

bool PortPanel::mousePressed(ofMouseEventArgs & args)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_P1("args = ", &args);//####
    OD_LOG_L1("args.button = ", args.button);//####
    bool result = inherited::mousePressed(args);
    
    if (! result)
    {
        if (_owner)
        {
            if (b.inside(args.x, args.y))
            {
                bool altWasActive = _owner->altActive();
                bool commandWasActive = _owner->commandActive();
                bool controlWasActive = _owner->controlActive();
                bool shiftWasActive = _owner->shiftActive();

                OD_LOG_B4("altWasActive = ", altWasActive, "commandWasActive = ", commandWasActive,//####
                          "controlWasActive = ", controlWasActive, "shiftWasActive = ", shiftWasActive);//####
                if (OF_MOUSE_BUTTON_3 == args.button)
                {
                    string thePanelDescription;
                    
                    switch (_kind)
                    {
                        case kEntityKindClientOrAdapter:
                            thePanelDescription = "A client or adapter";
                            break;
                            
                        case kEntityKindService:
                            thePanelDescription = _description;
                            break;
                            
                        case kEntityKindOther:
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
                else if (altWasActive || commandWasActive || shiftWasActive)
                {
                    _owner->reportPortEntryClicked(NULL, altWasActive, commandWasActive, shiftWasActive);
                    result = true;
                }
            }
        }
    }
    OD_LOG_OBJEXIT_B(result);//####
    return result;
} // PortPanel::mousePressed

bool PortPanel::mouseReleased(ofMouseEventArgs & args)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_P1("args = ", &args);//####
    OD_LOG_L1("args.button = ", args.button);//####
    bool result = false;
    
    OD_LOG_P1("_owner = ", _owner);//####
    if (_owner)
    {
        if (b.inside(args.x, args.y))
        {
            bool altWasActive = _owner->altActive();
            bool commandWasActive = _owner->commandActive();
            bool controlWasActive = _owner->controlActive();
            bool shiftWasActive = _owner->shiftActive();
            
            OD_LOG_B4("altWasActive = ", altWasActive, "commandWasActive = ", commandWasActive,//####
                      "controlWasActive = ", controlWasActive, "shiftWasActive = ", shiftWasActive);//####
            if (controlWasActive || (OF_MOUSE_BUTTON_3 == args.button))
            {
                result = true;
            }
            else if (shiftWasActive)
            {
                result = true;
            }
            else if (commandWasActive)
            {
                result = true;
            }
            else if (altWasActive)
            {
                result = true;
            }
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
    OD_LOG_OBJEXIT_B(result);//####
    return result;
} // PortPanel::mouseReleased

PortPanel * PortPanel::setup(string      collectionName,
                             string      filename,
                             const float xx,
                             const float yy)
{
    OD_LOG_OBJENTER();//####
	registerMouseEvents();
    PortPanel * result = static_cast<PortPanel *>(inherited::setup(collectionName, filename, xx, yy));
    
    OD_LOG_OBJEXIT_P(result);//####
    return result;
} // PortPanel::setup

PortPanel * PortPanel::setup(const ofParameterGroup & parameters,
                             string                   filename,
                             const float              xx,
                             const float              yy)
{
    OD_LOG_OBJENTER();//####
	registerMouseEvents();
    PortPanel * result = static_cast<PortPanel *>(inherited::setup(parameters, filename, xx, yy));

    OD_LOG_OBJEXIT_P(result);//####
    return result;
} // PortPanel::setup

bool PortPanel::setValue(float mx,
                         float my,
                         bool  bCheck)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_D2("mx = ", mx, "my = ", my);//####
    OD_LOG_B1("bCheck = ", bCheck);//####
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
            OD_LOG_B1("_grabbed <- ", _grabbed);//####
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
    OD_LOG_OBJEXIT_B(result);//####
    return result;
} // PortPanel::setValue

#if defined(__APPLE__)
# pragma mark Accessors
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)
