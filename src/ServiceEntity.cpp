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

//#include "ODEnableLogging.h"
#include "ODLogging.h"

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

/*! @brief The width and height of the marker displayed during movement. */
const float kMarkerSide = 12;

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
    OD_LOG_ENTER();//####
    OD_LOG_P4("startPoint = ", &startPoint, "endPoint = ", &endPoint, "startCentre = ", &startCentre,//####
              "endCentre = ", &endCentre);//####
    ofPolyline bLine;
    float      controlLength = (ofDist(startPoint.x, startPoint.y, endPoint.x, endPoint.y) * kControlLengthScale);
    float      startAngle = atan2(startPoint.y - startCentre.y, startPoint.x - startCentre.x);
    float      endAngle = atan2(endPoint.y - endCentre.y, endPoint.x - endCentre.x);
    ofPoint    controlPoint1(controlLength * cos(startAngle), controlLength * sin(startAngle));
    ofPoint    controlPoint2(controlLength * cos(endAngle), controlLength * sin(endAngle));
    
    bLine.addVertex(startPoint);
    bLine.bezierTo(startPoint + controlPoint1, endPoint + controlPoint2, endPoint);
    bLine.draw();
    OD_LOG_EXIT();//####
} // drawBezier

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

float ServiceEntity::connectionWidth(2);

ofColor ServiceEntity::connectionColor(0, 0, 255);

#if defined(__APPLE__)
# pragma mark Constructors and destructors
#endif // defined(__APPLE__)

ServiceEntity::ServiceEntity(const PortPanel::EntityKind kind,
                             const string                description,
                             ServiceViewerApp *          owner) :
            inherited(), _panel(kind, description, owner), _drawConnectMarker(false), _drawDisconnectMarker(false),
            _drawMoveMarker(false), _selected(false)
{
    OD_LOG_ENTER();//####
    OD_LOG_S1("description = ", description.c_str());//####
    OD_LOG_P1("owner = ", owner);//####
	_thisConnectionColor = connectionColor;
    _thisConnectionWidth = connectionWidth;
    OD_LOG_EXIT_P(this);//####
} // ServiceEntity::ServiceEntity

ServiceEntity::~ServiceEntity(void)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_OBJEXIT();//####
} // ServiceEntity::~ServiceEntity

#if defined(__APPLE__)
# pragma mark Actions
#endif // defined(__APPLE__)

void ServiceEntity::draw(void)
{
    OD_LOG_OBJENTER();//####
    _panel.draw();
    if (_drawConnectMarker)
    {
        ofPoint markerPos(_panel.getWidth() / 2, _panel.getHeader());
        
        ofSetColor(ofColor::yellow);
        ofFill();
        ofCircle(markerPos + getShape().getTopLeft(), kMarkerSide / 2);
    }
    else if (_drawDisconnectMarker)
    {
        ofPoint markerPos(_panel.getWidth() / 2, _panel.getHeader());
        
        ofSetColor(ofColor::yellow);
        ofNoFill();
        ofSetLineWidth(2);
        ofCircle(markerPos + getShape().getTopLeft(), kMarkerSide / 2);
    }
    else if (_drawMoveMarker)
    {
        ofPoint markerPos(_panel.getWidth() / 2, _panel.getHeader());
        
        ofSetColor(ofColor::yellow);
        ofFill();
        markerPos += getShape().getTopLeft() - ofPoint(kMarkerSide / 2, kMarkerSide / 2);
        ofRect(markerPos, kMarkerSide, kMarkerSide);
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
    OD_LOG_OBJEXIT();//####
} // ServiceEntity::draw

void ServiceEntity::handlePositionChange(void)
{
    OD_LOG_OBJENTER();//####
    // Here we re-adjust any lines attached to the entity.
    _selected = _drawMoveMarker = true;
    OD_LOG_OBJEXIT();//####
} // ServiceEntity::handlePositionChange

bool ServiceEntity::hasPort(const PortEntry * aPort)
{
    OD_LOG_OBJENTER();//####
    bool result = false;
    
    for (int ii = 0, mm = _panel.getNumPorts(); mm > ii; ++ii)
    {
        PortEntry * anEntry = _panel.getPort(ii);
        
        if (aPort == anEntry)
        {
            result = true;
            break;
        }
        
    }
    OD_LOG_OBJEXIT_B(result);//####
    return result;
} // ServiceEntity::hasPort

void ServiceEntity::positionChangeComplete(void)
{
    OD_LOG_OBJENTER();//####
    _panel.getOwner()->updateEntityList(this);
    _selected = _drawMoveMarker = false;
    // something to do??
    OD_LOG_OBJEXIT();//####
} // ServiceEntity::positionChangeComplete

void ServiceEntity::setup(string      entityName,
                          const float xx,
                          const float yy)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_S1("entityName = ", entityName.c_str());//####
    OD_LOG_D2("xx = ", xx, "yy = ", yy);//####
    _panel.setup();
    _panel.setName(entityName);
    setPosition(xx, yy);
    _panel.setTracker(this);
    OD_LOG_OBJEXIT();//####
} // ServiceEntity::setup

#if defined(__APPLE__)
# pragma mark Accessors
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

