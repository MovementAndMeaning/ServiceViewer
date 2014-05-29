//--------------------------------------------------------------------------------------
//
//  File:       PortEntry.cpp
//
//  Project:    M+M
//
//  Contains:   The class definition for a GUI element to represent ports.
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

#include "PortEntry.h"
#include "ServiceViewerApp.h"
#include "Utilities.h"

//#include "ODEnableLogging.h"
#include "ODLogging.h"

#include "ofGraphics.h"

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 
 @brief The class definition for a GUI element to represent ports. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

/*! @brief The horizontal and vertical length of the arrow 'arm'. */
static const float kArrowSize = 7;

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and destructors
#endif // defined(__APPLE__)

PortEntry::PortEntry(IconlessPanel *     parent,
                     const PortUsage     portKind,
                     const PortDirection direction) :
            inherited(parent), _direction(direction), _usage(portKind), _isLastPort(true)
{
    OD_LOG_ENTER();//####
    OD_LOG_P1("parent = ", parent);//####
    OD_LOG_L2("portKind = ", portKind, "direction = ", direction);//####
    OD_LOG_EXIT_P(this);//####
} // PortEntry::PortEntry

PortEntry::~PortEntry(void)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_OBJEXIT();//####
} // PortEntry::~PortEntry

#if defined(__APPLE__)
# pragma mark Actions
#endif // defined(__APPLE__)

/*! @brief Add an input connection to the port.
 @param other The port that is to be connected. */
void PortEntry::addInputConnection(PortEntry * other)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_P1("other = ", other);//####
    if (other)
    {
        _inputConnections.insert(other);
    }
    OD_LOG_OBJEXIT();//####
} // PortEntry::addInputConnection

/*! @brief Add an output connection to the port.
 @param other The port that is to be connected. */
void PortEntry::addOutputConnection(PortEntry * other)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_P1("other = ", other);//####
    if (other)
    {
        _outputConnections.insert(other);
    }
    OD_LOG_OBJEXIT();//####
} // PortEntry::addOutputConnection

PortEntry::AnchorSide PortEntry::calculateClosestAnchor(ofPoint &       result,
                                                        const bool      isSource,
                                                        const ofPoint & pp)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_P2("result = ", result, "pp = ", &pp);//####
    OD_LOG_B1("isSource = ", isSource);//####
    // Check each anchor point - the two side centres and optionally the bottom - to find the shortest distance.
    AnchorSide  anchor = kAnchorUnknown;
    float       soFar = 1e23; // Ridiculously big, just in case.
    ofRectangle outer(getShape());
    
    if (CalculateMinDistance(soFar, pp, outer.x, outer.y + (outer.height / 2), result))
    {
        anchor = kAnchorLeft;
        if (isSource)
        {
            // Adjust the anchor position if an output.
            result.x -= kArrowSize;
        }
    }
    if (CalculateMinDistance(soFar, pp, outer.x + outer.width, outer.y + (outer.height / 2), result))
    {
        anchor = kAnchorRight;
        if (isSource)
        {
            // Adjust the anchor position if an output.
            result.x += kArrowSize;
        }
    }
    if (_isLastPort)
    {
        if (CalculateMinDistance(soFar, pp, outer.x + (outer.width / 2), outer.y + outer.height, result))
        {
            anchor = kAnchorBottomCentre;
            if (isSource)
            {
                // Adjust the anchor position if an output.
                result.y += kArrowSize;
            }
        }
#if defined(SUPPORT_BOTTOM_DIAGONALS_)
        if (CalculateMinDistance(soFar, pp, outer.x, outer.y + outer.height, result))
        {
            anchor = kAnchorBottomLeft;
            if (isSource)
            {
                // Adjust the anchor position if an output.
                result.x -= kArrowSize;
                result.y += kArrowSize;
            }
        }
        if (CalculateMinDistance(soFar, pp, outer.x + outer.width, outer.y + outer.height, result))
        {
            anchor = kAnchorBottomRight;
            if (isSource)
            {
                // Adjust the anchor position if an output.
                result.x += kArrowSize;
                result.y += kArrowSize;
            }
        }
#endif // defined(SUPPORT_BOTTOM_DIAGONALS_)
    }
    OD_LOG_OBJEXIT_L(static_cast<int>(anchor));//####
    return anchor;
} // PortEntry::calculateClosestAnchor

void PortEntry::drawSourceAnchor(const AnchorSide anchor,
                                 const ofPoint &  anchorPos)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_L1("anchor = ", static_cast<int>(anchor));//####
    OD_LOG_P1("anchorPos = ", &anchorPos);//####
    ofPoint     first;
    ofPoint     second;
    ofRectangle outer(getShape());
    
    switch (anchor)
    {
        case kAnchorLeft:
            first = anchorPos + ofPoint(kArrowSize, - kArrowSize);
            second = anchorPos + ofPoint(kArrowSize, kArrowSize);
            break;
            
        case kAnchorRight:
            first = anchorPos + ofPoint(- kArrowSize, - kArrowSize);
            second = anchorPos + ofPoint(- kArrowSize, kArrowSize);
            break;
            
        case kAnchorBottomCentre:
            first = anchorPos + ofPoint(- kArrowSize, - kArrowSize);
            second = anchorPos + ofPoint(kArrowSize, - kArrowSize);
            break;
            
#if defined(SUPPORT_BOTTOM_DIAGONALS_)
        case kAnchorBottomLeft:
            first = anchorPos + ofPoint(0, - kArrowSize);
            second = anchorPos + ofPoint(kArrowSize, 0);
            break;
#endif // defined(SUPPORT_BOTTOM_DIAGONALS_)
            
#if defined(SUPPORT_BOTTOM_DIAGONALS_)
        case kAnchorBottomRight:
            first = anchorPos + ofPoint(- kArrowSize, 0);
            second = anchorPos + ofPoint(0, kArrowSize);
            break;
#endif // defined(SUPPORT_BOTTOM_DIAGONALS_)
            
        default:
            break;
            
    }
    if (kAnchorUnknown != anchor)
    {
        ofLine(anchorPos, first);
        ofLine(anchorPos, second);
    }
    OD_LOG_OBJEXIT();//####
} // PortEntry::drawSourceAnchor

void PortEntry::drawTargetAnchor(const AnchorSide anchor,
                                 const ofPoint &  anchorPos)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_L1("anchor = ", static_cast<int>(anchor));//####
    OD_LOG_P1("anchorPos = ", &anchorPos);//####
    ofRectangle outer(getShape());
    ofPoint     first;
    ofPoint     second;
    
    switch (anchor)
    {
        case kAnchorLeft:
            first = anchorPos + ofPoint(- kArrowSize, - kArrowSize);
            second = anchorPos + ofPoint(- kArrowSize, kArrowSize);
            break;
            
        case kAnchorRight:
            first = anchorPos + ofPoint(kArrowSize, - kArrowSize);
            second = anchorPos + ofPoint(kArrowSize, kArrowSize);
            break;
            
        case kAnchorBottomCentre:
            first = anchorPos + ofPoint(- kArrowSize, kArrowSize);
            second = anchorPos + ofPoint(kArrowSize, kArrowSize);
            break;
            
#if defined(SUPPORT_BOTTOM_DIAGONALS_)
        case kAnchorBottomLeft:
            first = anchorPos + ofPoint(- kArrowSize, 0);
            second = anchorPos + ofPoint(0, kArrowSize);
            break;
#endif // defined(SUPPORT_BOTTOM_DIAGONALS_)
            
#if defined(SUPPORT_BOTTOM_DIAGONALS_)
        case kAnchorBottomRight:
            first = anchorPos + ofPoint(kArrowSize, 0);
            second = anchorPos + ofPoint(0, kArrowSize);
            break;
#endif // defined(SUPPORT_BOTTOM_DIAGONALS_)
            
        default:
            break;
            
    }
    if (kAnchorUnknown != anchor)
    {
        ofLine(anchorPos, first);
        ofLine(anchorPos, second);
    }
    OD_LOG_OBJEXIT();//####
} // PortEntry::drawTargetAnchor

bool PortEntry::mouseDragged(ofMouseEventArgs & args)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_P1("args = ", &args);//####
    OD_LOG_L1("args.button = ", args.button);//####
    bool result = false;

    OD_LOG_OBJEXIT_B(result);//####
    return result;
} // PortEntry::mouseDragged

bool PortEntry::mouseMoved(ofMouseEventArgs & args)
{
//    OD_LOG_OBJENTER();//####
//    OD_LOG_P1("args = ", &args);//####
    bool result;

    result = inherited::mouseMoved(args);
//    OD_LOG_OBJEXIT_B(result);//####
    return result;
} // PortEntry::mouseMoved

bool PortEntry::mousePressed(ofMouseEventArgs & args)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_P1("args = ", &args);//####
    OD_LOG_L1("args.button = ", args.button);//####
    bool result = false;
    bool specialClick = false;

    OD_LOG_OBJEXIT_B(result);//####
    return result;
} // PortEntry::mousePressed

bool PortEntry::mouseReleased(ofMouseEventArgs & args)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_P1("args = ", &args);//####
    OD_LOG_L1("args.button = ", args.button);//####
    bool result = false;
    bool specialClick = false;

    OD_LOG_OBJEXIT_B(result);//####
    return result;
} // PortEntry::mouseReleased

void PortEntry::removeInputConnection(PortEntry * other)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_P1("other = ", other);//####
    if (other)
    {
        Connections::iterator match(_inputConnections.find(other));
        
        if (_inputConnections.end() != match)
        {
            _inputConnections.erase(match);
        }
    }
    OD_LOG_OBJEXIT();//####
} // PortEntry::removeInputConnection

void PortEntry::removeOutputConnection(PortEntry * other)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_P1("other = ", other);//####
    if (other)
    {
        Connections::iterator match(_outputConnections.find(other));
        
        if (_outputConnections.end() != match)
        {
            _outputConnections.erase(match);
        }
    }
    OD_LOG_OBJEXIT();//####
} // PortEntry::removeOutputConnection

PortEntry * PortEntry::setup(string      label,
                             const float width,
                             const float height)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_S1("label = ", label.c_str());//####
    OD_LOG_D2("width = ", width, "height = ", height);//####
    string tag;
    
    _portName = label;
    switch (_direction)
    {
        case kPortDirectionInput:
            tag = "In";
            break;
            
        case kPortDirectionInputOutput:
            tag = "I/O";
            break;
            
        case kPortDirectionOutput:
            tag = "Out";
            break;
            
        default:
            tag = "Unk";
            break;
    }
    PortEntry * result = static_cast<PortEntry *>(inherited::setup(tag, label, width, height));
    
    OD_LOG_OBJEXIT_P(result);//####
    return result;
} // PortEntry::setup

#if defined(__APPLE__)
# pragma mark Accessors
#endif // defined(__APPLE__)

ofPoint PortEntry::getCentre(void)
{
    OD_LOG_OBJENTER();//####
    ofRectangle outer(getShape());
    
    OD_LOG_OBJEXIT();//####
    return ofPoint(outer.x + (outer.width / 2), outer.y + (outer.height / 2));
} // PortEntry::getCentre

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

