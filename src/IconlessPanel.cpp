//--------------------------------------------------------------------------------------
//
//  File:       IconlessPanel.cpp
//
//  Project:    M+M
//
//  Contains:   The class definition for a GUI panel without save / restore icons.
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

#include "IconlessPanel.h"
#include "LabelWithShadow.h"
#include "MovementTracker.h"
#include "Utilities.h"

#include "ofGraphics.h"

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 
 @brief The class definition for a GUI panel without save / restore icons. */
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

IconlessPanel::IconlessPanel(void) :
            inherited()
{
} // IconlessPanel::IconlessPanel

IconlessPanel::IconlessPanel(const ofParameterGroup & parameters,
                             string                   filename,
                             const float              xx,
                             const float              yy) :
            inherited(parameters, filename, xx, yy)
{
} // IconlessPanel::IconlessPanel

IconlessPanel::~IconlessPanel(void)
{
} // IconlessPanel::~IconlessPanel

#if defined(__APPLE__)
# pragma mark Actions
#endif // defined(__APPLE__)

float IconlessPanel::calculateTextWidth(void)
{
    ofRectangle bbox = getTextBoundingBox(getName(), 0, 0);
    
    return ((0 < bbox.width) ? (bbox.width + (2 * textPadding)) : 0);
} // IconlessPanel::calculateTextWidth

void IconlessPanel::generateDraw(void)
{
	border.clear();
	border.setStrokeColor(thisBorderColor);
	border.setStrokeWidth(1);
	border.setFilled(false);
	border.rectangle(b.x, b.y, b.width + 1, b.height - spacingNextElement);
#if defined(SHOW_PANEL_HEADER_)
	headerBg.clear();
	headerBg.setFillColor(ofColor(thisHeaderBackgroundColor, 180));
	headerBg.setFilled(true);
	headerBg.rectangle(b.x, b.y + 1, b.width, header);
#endif // defined(SHOW_PANEL_HEADER_)
	textMesh = getTextMesh(getName(), textPadding + b.x, (header / 2) + (4 + b.y));
    float newWidth = calculateTextWidth();
    
    if (newWidth > getWidth())
    {
        setWidth(newWidth);
    }
} // IconlessPanel::generateDraw

void IconlessPanel::render(void)
{
	border.draw();
#if defined(SHOW_PANEL_HEADER_)
	headerBg.draw();
#endif // defined(SHOW_PANEL_HEADER_)
	ofBlendMode blendMode = ofGetStyle().blendingMode;
    
	if (OF_BLENDMODE_ALPHA != blendMode)
    {
		ofEnableAlphaBlending();
	}
	ofColor cc = ofGetStyle().color;
    
	ofSetColor(thisTextColor);
	bindFontTexture();
	textMesh.draw();
	unbindFontTexture();
	bool texHackEnabled = ofIsTextureEdgeHackEnabled();
    
	ofDisableTextureEdgeHack();
	if (texHackEnabled)
    {
		ofEnableTextureEdgeHack();
	}
	for(int ii = 0; static_cast<int>(collection.size()) > ii; ++ii)
    {
		collection[ii]->draw();
	}
	ofSetColor(cc);
	if (OF_BLENDMODE_ALPHA != blendMode)
    {
		ofEnableBlendMode(blendMode);
	}
} // IconlessPanel::render

IconlessPanel * IconlessPanel::setup(string      collectionName,
                                     string      filename,
                                     const float xx,
                                     const float yy)
{
    return static_cast<IconlessPanel *>(inherited::setup(collectionName, filename, xx, yy));
} // IconlessPanel::setup

IconlessPanel * IconlessPanel::setup(const ofParameterGroup & parameters,
                                     string                   filename,
                                     const float              xx,
                                     const float              yy)
{
    return static_cast<IconlessPanel *>(inherited::setup(parameters, filename, xx, yy));
} // IconlessPanel::setup

void IconlessPanel::setWidth(const float newWidth)
{
    if (b.width < newWidth)
    {
        b.width = newWidth;
        for (int ii = 0, mm = collection.size(); mm > ii; ++ii)
        {
            LabelWithShadow * aLabel = static_cast<LabelWithShadow *>(collection[ii]);
            
            aLabel->setSize(newWidth, aLabel->getHeight());
            aLabel->generateDraw();
        }
        sizeChangedCB();
        generateDraw();
    }
} // IconlessPanel::setWidth

#if defined(__APPLE__)
# pragma mark Accessors
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)
