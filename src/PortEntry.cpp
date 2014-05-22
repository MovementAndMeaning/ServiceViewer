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
#include "Utilities.h"

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
                     const bool          isService,
                     const PortDirection direction) :
            inherited(parent), _direction(direction), _isLastPort(true), _isService(isService)
{
} // PortEntry::PortEntry

PortEntry::~PortEntry(void)
{
} // PortEntry::~PortEntry

#if defined(__APPLE__)
# pragma mark Actions
#endif // defined(__APPLE__)

/*! @brief Add an input connection to the port.
 @param other The port that is to be connected. */
void PortEntry::addInputConnection(PortEntry * other)
{
    if (other)
    {
        _inputConnections.insert(other);
    }
} // PortEntry::addInputConnection

/*! @brief Add an output connection to the port.
 @param other The port that is to be connected. */
void PortEntry::addOutputConnection(PortEntry * other)
{
    if (other)
    {
        _outputConnections.insert(other);
    }
} // PortEntry::addOutputConnection

PortEntry::AnchorSide PortEntry::calculateClosestAnchor(ofPoint &       result,
                                                        const bool      isSource,
                                                        const ofPoint & pp)
{
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
    return anchor;
} // PortEntry::calculateClosestAnchor

void PortEntry::drawSourceAnchor(const AnchorSide anchor,
                                 const ofPoint &  anchorPos)
{
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
} // PortEntry::drawSourceAnchor

void PortEntry::drawTargetAnchor(const AnchorSide anchor,
                                 const ofPoint &  anchorPos)
{
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
} // PortEntry::drawTargetAnchor

void PortEntry::removeInputConnection(PortEntry * other)
{
    if (other)
    {
        Connections::iterator match(_inputConnections.find(other));
        
        if (_inputConnections.end() != match)
        {
            _inputConnections.erase(match);
        }
    }
} // PortEntry::removeInputConnection

void PortEntry::removeOutputConnection(PortEntry * other)
{
    if (other)
    {
        Connections::iterator match(_outputConnections.find(other));
        
        if (_outputConnections.end() != match)
        {
            _outputConnections.erase(match);
        }
    }
} // PortEntry::removeOutputConnection

PortEntry * PortEntry::setup(string      label,
                             const float width,
                             const float height)
{
    string tag;
    
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
    return static_cast<PortEntry *>(inherited::setup(tag, label, width, height));
} // PortEntry::setup

#if defined(__APPLE__)
# pragma mark Accessors
#endif // defined(__APPLE__)

ofPoint PortEntry::getCentre(void)
{
    ofRectangle outer(getShape());
    
    return ofPoint(outer.x + (outer.width / 2), outer.y + (outer.height / 2));
} // PortEntry::getCentre

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

