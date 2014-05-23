//--------------------------------------------------------------------------------------
//
//  File:       ServiceEntity.cpp
//
//  Project:    M+M
//
//  Contains:   The class definition for a moveable GUI element to represent a set of ports.
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
//  Created:    2014-05-09
//
//--------------------------------------------------------------------------------------

#include "ServiceEntity.h"
#include "ServiceViewerApp.h"
#include "Utilities.h"

#include "ofGraphics.h"

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 
 @brief The class definition for a moveable GUI element to represent a set of ports. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

/*! @brief The scale factor to apply to get the lenght of the control vector. */
const float kControlLengthScale = 0.25;

/*! @brief The diameter of the central red dot displayed during movement. */
const float kRedDotRadius = 6;

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

/*! @brief Draw a bezier curve between two points.
 @param startPoint The beginning of the curve.
 @param endPoint The end of the curve.
 @param startCentre A reference point for the beginning of the curve, used to calculate the beginning tangent.
 @param endCentre A reference point for the end of the curve, used to calculate the ending tangent. */
static void drawBezier(const ofPoint & startPoint,
                       const ofPoint & endPoint,
                       const ofPoint & startCentre,
                       const ofPoint & endCentre)
{
    ofPolyline bLine;
    float      controlLength = (ofDist(startPoint.x, startPoint.y, endPoint.x, endPoint.y) * kControlLengthScale);
    float      startAngle = atan2(startPoint.y - startCentre.y, startPoint.x - startCentre.x);
    float      endAngle = atan2(endPoint.y - endCentre.y, endPoint.x - endCentre.x);
    ofPoint    controlPoint1(controlLength * cos(startAngle), controlLength * sin(startAngle));
    ofPoint    controlPoint2(controlLength * cos(endAngle), controlLength * sin(endAngle));
    
    bLine.addVertex(startPoint);
    bLine.bezierTo(startPoint + controlPoint1, endPoint + controlPoint2, endPoint);
    bLine.draw();
} // drawBezier

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

float ServiceEntity::connectionWidth(2);

ofColor ServiceEntity::connectionColor(0, 0, 255);

#if defined(__APPLE__)
# pragma mark Constructors and destructors
#endif // defined(__APPLE__)

ServiceEntity::ServiceEntity(ServiceViewerApp * owner) :
            inherited(), _panel(owner), _owner(owner), _drawDot(false), _selected(false)
{
	_thisConnectionColor = connectionColor;
    _thisConnectionWidth = connectionWidth;
} // ServiceEntity::ServiceEntity

ServiceEntity::~ServiceEntity(void)
{
} // ServiceEntity::~ServiceEntity

#if defined(__APPLE__)
# pragma mark Actions
#endif // defined(__APPLE__)

void ServiceEntity::draw(void)
{
    _panel.draw();
    if (_drawDot)
    {
        ofPoint dotPos(_panel.getWidth() / 2, _panel.getHeader());//_panel.getHeight() - (_panel.getGapHeight() / 2));
        
        ofSetColor(ofColor::red);
        ofCircle(dotPos + getShape().getTopLeft(), kRedDotRadius);
    }
    ofSetColor(_thisConnectionColor);
    for (int ii = 0, mm = _panel.getNumPorts(); mm > ii; ++ii)
    {
        PortEntry * anEntry = _panel.getPort(ii);
        
        if (anEntry)
        {
            ofPoint                        aCentre(anEntry->getCentre());
            const PortEntry::Connections & connex = anEntry->getOutputConnections();
            
            for (PortEntry::Connections::iterator walker(connex.begin()); connex.end() != walker; ++walker)
            {
                PortEntry *           otherEntry = *walker;
                ofPoint               otherCentre(otherEntry->getCentre());
                ofPoint               fromHere;
                PortEntry::AnchorSide anchorHere = anEntry->calculateClosestAnchor(fromHere, true, otherCentre);
                ofPoint               toThere;
                PortEntry::AnchorSide anchorThere = otherEntry->calculateClosestAnchor(toThere, false, aCentre);
                
                if (otherEntry->isService())
                {
                    ofSetLineWidth(2 * _thisConnectionWidth);
                }
                else
                {
                    ofSetLineWidth(_thisConnectionWidth);
                }
                drawBezier(fromHere, toThere, aCentre, otherCentre);
                ofSetLineWidth(1);
                anEntry->drawSourceAnchor(anchorHere, fromHere);
                otherEntry->drawTargetAnchor(anchorThere, toThere);
            }
        }
    }
} // ServiceEntity::draw

void ServiceEntity::handlePositionChange(void)
{
    // Here we re-adjust any lines attached to the entity.
    _selected = _drawDot = true;
} // ServiceEntity::handlePositionChange

void ServiceEntity::positionChangeComplete(void)
{
    _owner->updateEntityList(this);
    _selected = _drawDot = false;
    
    // something to do??
    
} // ServiceEntity::positionChangeComplete

void ServiceEntity::setup(string      entityName,
                          const float xx,
                          const float yy)
{
    _panel.setup();
    _panel.setName(entityName);
    setPosition(xx, yy);
    
    _panel.setTracker(this);
} // ServiceEntity::setup

#if defined(__APPLE__)
# pragma mark Accessors
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

