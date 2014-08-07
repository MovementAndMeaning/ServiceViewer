//--------------------------------------------------------------------------------------------------
//
//  File:       Utilities.cpp
//
//  Project:    M+M
//
//  Contains:   The function definitions for common routines for the service viewer.
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

#include "Utilities.h"

//#include <odl/ODEnableLogging.h>
#include <odl/ODLogging.h>

#include "ofGraphics.h"
#include "ofxGui.h"

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 
 @brief The function definitions for common routines for the service viewer. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

/*! @brief The scale factor to apply to get the length of the control vector. */
static const float kControlLengthScale = 0.25;

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

/*! @brief Draw a bezier curve between two points.
 @param startPoint The beginning of the curve.
 @param endPoint The end of the curve.
 @param startCentre A reference point for the beginning of the curve, used to calculate the
 beginning tangent.
 @param endCentre A reference point for the end of the curve, used to calculate the ending
 tangent. */
void DrawBezier(const ofPoint & startPoint,
                const ofPoint & endPoint,
                const ofPoint & startCentre,
                const ofPoint & endCentre)
{
    OD_LOG_ENTER(); //####
    OD_LOG_P4("startPoint = ", &startPoint, "endPoint = ", &endPoint, "startCentre = ", //####
              &startCentre, "endCentre = ", &endCentre); //####
    ofPolyline bLine;
    float      controlLength = (startPoint.distance(endPoint) * kControlLengthScale);
    float      startAngle = atan2(startPoint.y - startCentre.y, startPoint.x - startCentre.x);
    float      endAngle = atan2(endPoint.y - endCentre.y, endPoint.x - endCentre.x);
    ofPoint    controlPoint1(controlLength * cos(startAngle), controlLength * sin(startAngle));
    ofPoint    controlPoint2(controlLength * cos(endAngle), controlLength * sin(endAngle));
    
    bLine.addVertex(startPoint);
    bLine.bezierTo(startPoint + controlPoint1, endPoint + controlPoint2, endPoint);
    bLine.draw();
    OD_LOG_EXIT();//####
} // DrawBezier
