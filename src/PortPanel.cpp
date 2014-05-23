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

PortPanel::PortPanel(ServiceViewerApp * owner) :
            inherited(), _tracker(NULL), _owner(owner), _grabbed(false)
{
} // PortPanel::PortPanel

PortPanel::PortPanel(ServiceViewerApp *       owner,
                     const ofParameterGroup & parameters,
                     string                   filename,
                     const float              xx,
                     const float              yy) :
            inherited(parameters, filename, xx, yy), _tracker(NULL), _owner(owner), _grabbed(false)
{
} // PortPanel::PortPanel

PortPanel::~PortPanel(void)
{
    for (int ii = 0, mm = getNumPorts(); mm > ii; ++ii)
    {
        PortEntry * aPort = getPort(ii);
        
        if (aPort)
        {
            _owner->forgetPort(aPort);
            delete aPort;
        }
    }
} // PortPanel::~PortPanel

#if defined(__APPLE__)
# pragma mark Actions
#endif // defined(__APPLE__)

void PortPanel::addPort(string                         portName,
                        const bool                     isService,
                        const PortEntry::PortDirection direction)
{
    int         countBefore = getNumPorts();
    PortEntry * aPort = new PortEntry(this, isService, direction);
    
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
} // PortPanel::addPort

PortEntry * PortPanel::getPort(const int num)
{
    PortEntry * result;
    
    if (0 <= num)
    {
        result = reinterpret_cast<PortEntry *>(inherited::getControl(num));
    }
    else
    {
        result = NULL;
    }
    return result;
} // getPort

bool PortPanel::mousePressed(ofMouseEventArgs & args)
{
    bool result = false;
    
    if (inherited::mousePressed(args))
    {
        // The mouse event was already processed.
        result = true;
    }
    else if (_owner)
    {
        if (_owner->controlActive())
        {
            cout << "got here" << endl;
            result = true; // process a popup here...
        }
        else if (_owner->shiftActive())
        {
            //??
        }
    }
    return result;
} // PortPanel::mousePressed

bool PortPanel::mouseReleased(ofMouseEventArgs & args)
{
    bool result;
    
    if (_tracker && _grabbed)
    {
        _tracker->positionChangeComplete();
    }
    _grabbed = false;
    if (inherited::mouseReleased(args))
    {
        result = true;
    }
    else if (isGuiDrawing() && b.inside(ofPoint(args.x, args.y)))
    {
    	result = true;
    }
    else
    {
    	result = false;
    }
    return result;
} // PortPanel::mouseReleased

PortPanel * PortPanel::setup(string      collectionName,
                             string      filename,
                             const float xx,
                             const float yy)
{
	registerMouseEvents();
    return static_cast<PortPanel *>(inherited::setup(collectionName, filename, xx, yy));
} // PortPanel::setup

PortPanel * PortPanel::setup(const ofParameterGroup & parameters,
                             string                   filename,
                             const float              xx,
                             const float              yy)
{
	registerMouseEvents();
    return static_cast<PortPanel *>(inherited::setup(parameters, filename, xx, yy));
} // PortPanel::setup

bool PortPanel::setValue(float mx,
                         float my,
                         bool  bCheck)
{
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
    return result;
} // PortPanel::setValue

#if defined(__APPLE__)
# pragma mark Accessors
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

