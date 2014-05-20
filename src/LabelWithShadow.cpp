//--------------------------------------------------------------------------------------
//
//  File:       LabelWithShadow.cpp
//
//  Project:    M+M
//
//  Contains:   The class definition for a text label with a shadow.
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

#include "LabelWithShadow.h"

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 
 @brief The class definition for a text label with a shadow. */
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

float LabelWithShadow::shadowWidth(3);

ofColor LabelWithShadow::shadowColor(128);

#if defined(__APPLE__)
# pragma mark Constructors and destructors
#endif // defined(__APPLE__)

LabelWithShadow::LabelWithShadow(void) :
            inherited()
{
	_thisShadowColor = shadowColor;
    _thisShadowWidth = shadowWidth;
} // LabelWithShadow::LabelWithShadow

LabelWithShadow::LabelWithShadow(ofParameter<string> label,
                                 const float         width,
                                 const float         height) :
            inherited(label, width, height)
{
	_thisShadowColor = shadowColor;
    _thisShadowWidth = shadowWidth;
} // LabelWithShadow::LabelWithShadow

LabelWithShadow::~LabelWithShadow(void)
{
} // LabelWithShadow::~LabelWithShadow

#if defined(__APPLE__)
# pragma mark Actions
#endif // defined(__APPLE__)

void LabelWithShadow::generateDraw(void)
{
    _shadow.clear();
    _shadow.setFillColor(_thisShadowColor);
    _shadow.setFilled(true);
    _shadow.rectangle(b.x + _thisShadowWidth, b.y + _thisShadowWidth, b.width, b.height);
    inherited::generateDraw();
} // LabelWithShadow::generateDraw

void LabelWithShadow::render(void)
{
    _shadow.draw();
    inherited::render();
} // LabelWithShadow::render

LabelWithShadow * LabelWithShadow::setup(ofParameter<string> label,
                                         const float         width,
                                         const float         height)
{
    return static_cast<LabelWithShadow *>(inherited::setup(label, width, height));
} // LabelWithShadow::setup

LabelWithShadow * LabelWithShadow::setup(string      labelName,
                                         string      label,
                                         const float width,
                                         const float height)
{
    return static_cast<LabelWithShadow *>(inherited::setup(labelName, label, width, height));
} // LabelWithShadow::setup

#if defined(__APPLE__)
# pragma mark Accessors
#endif // defined(__APPLE__)

ofColor LabelWithShadow::getShadowColor(void) const
{
	return _thisShadowColor;
} // LabelWithShadow::getShadowColor

float LabelWithShadow::getShadowWidth(void) const
{
    return _thisShadowWidth;
} // LabelWithShadow::getShadowWidth

void LabelWithShadow::setDefaultShadowColor(const ofColor & color)
{
	shadowColor = color;
} // LabelWithShadow::setDefaultShadowColor

void LabelWithShadow::setDefaultShadowWidth(const float width)
{
    shadowWidth = width;
} // LabelWithShadow::setDefaultShadowWidth

void LabelWithShadow::setShadowColor(const ofColor & color)
{
	generateDraw();
	_thisShadowColor = color;
} // LabelWithShadow::setShadowColor

void LabelWithShadow::setShadowWidth(const float width)
{
    _thisShadowWidth = width;
} // LabelWithShadow::setShadowWidth

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

