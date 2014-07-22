//--------------------------------------------------------------------------------------------------
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
//  Created:    2014-05-09
//
//--------------------------------------------------------------------------------------------------

#include "IconlessPanel.h"
#include "LabelWithShadow.h"
#include "MovementTracker.h"
#include "Utilities.h"

//#include "ODEnableLogging.h"
#include "ODLogging.h"

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

/*! @brief The default width to be used for the panels. */
static const int kOurDefaultPanelWidth = 20;

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
    OD_LOG_ENTER(); //####
    OD_LOG_EXIT_P(this); //####
} // IconlessPanel::IconlessPanel

IconlessPanel::IconlessPanel(const ofParameterGroup & parameters,
                             const string &           filename,
                             const float              xx,
                             const float              yy) :
    inherited(parameters, filename, xx, yy)
{
    OD_LOG_ENTER(); //####
    OD_LOG_S1s("filename = ", filename); //####
    OD_LOG_D2("xx = ", xx, "yy = ", yy); //####
    OD_LOG_EXIT_P(this); //####
} // IconlessPanel::IconlessPanel

IconlessPanel::~IconlessPanel(void)
{
    OD_LOG_OBJENTER(); //####
    OD_LOG_OBJEXIT(); //####
} // IconlessPanel::~IconlessPanel

#if defined(__APPLE__)
# pragma mark Actions
#endif // defined(__APPLE__)

float IconlessPanel::calculateTextWidth(void)
{
    OD_LOG_OBJENTER(); //####
    ofRectangle bbox = getTextBoundingBox(getName(), 0, 0);
    float       result = ((0 < bbox.width) ? (bbox.width + (2 * textPadding)) : 0);
    
    OD_LOG_OBJEXIT_D(result); //####
    return result;
} // IconlessPanel::calculateTextWidth

void IconlessPanel::generateDraw(void)
{
    OD_LOG_OBJENTER(); //####
    border.clear();
    border.setStrokeColor(thisBorderColor);
    border.setStrokeWidth(1);
    border.setFilled(false);
    border.rectangle(b.x, b.y, b.width + 1, b.height - spacingNextElement);
    headerBg.clear();
    headerBg.setFillColor(ofColor(thisHeaderBackgroundColor, 180));
    headerBg.setFilled(true);
    headerBg.rectangle(b.x, b.y + 1, b.width, getHeader());
    textMesh = getTextMesh(getName(), textPadding + b.x, (getHeader() / 2) + (4 + b.y));
    setWidth(calculateTextWidth());
    OD_LOG_OBJEXIT(); //####
} // IconlessPanel::generateDraw

void IconlessPanel::render(void)
{
    OD_LOG_OBJENTER(); //####
    border.draw();
    headerBg.draw();
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
    for (int ii = 0; static_cast<int> (collection.size()) > ii; ++ii)
    {
        collection[ii]->draw();
    }
    ofSetColor(cc);
    if (OF_BLENDMODE_ALPHA != blendMode)
    {
        ofEnableBlendMode(blendMode);
    }
    OD_LOG_OBJEXIT(); //####
} // IconlessPanel::render

IconlessPanel * IconlessPanel::setup(string      collectionName,
                                     string      filename,
                                     const float xx,
                                     const float yy)
{
    OD_LOG_OBJENTER(); //####
    OD_LOG_S2s("collectionName = ", collectionName, "filename = ", filename); //####
    OD_LOG_D2("xx = ", xx, "yy = ", yy); //####
    IconlessPanel * result = static_cast<IconlessPanel *> (inherited::setup(collectionName,
                                                                            filename, xx, yy));
    
    // Override the default width - this will be adjusted later.
    b.width = kOurDefaultPanelWidth;
    sizeChangedCB();
    OD_LOG_OBJEXIT_P(result); //####
    return result;
} // IconlessPanel::setup

IconlessPanel * IconlessPanel::setup(const ofParameterGroup & parameters,
                                     string                   filename,
                                     const float              xx,
                                     const float              yy)
{
    OD_LOG_OBJENTER(); //####
    OD_LOG_S1s("filename = ", filename); //####
    OD_LOG_D2("xx = ", xx, "yy = ", yy); //####
    IconlessPanel * result = static_cast<IconlessPanel *> (inherited::setup(parameters, filename,
                                                                            xx, yy));
    
    // Override the default width - this will be adjusted later.
    b.width = kOurDefaultPanelWidth;
    sizeChangedCB();
    OD_LOG_OBJEXIT_P(result); //####
    return result;
} // IconlessPanel::setup

void IconlessPanel::setWidth(const float newWidth)
{
    OD_LOG_OBJENTER(); //####
    OD_LOG_D1("newWidth = ", newWidth); //####
    if (b.width < newWidth)
    {
        b.width = newWidth;
        for (int ii = 0, mm = collection.size(); mm > ii; ++ii)
        {
            LabelWithShadow * aLabel = static_cast<LabelWithShadow *> (collection[ii]);
            
            aLabel->setSize(newWidth, aLabel->getHeight());
            aLabel->generateDraw();
        }
        sizeChangedCB();
        generateDraw();
    }
    OD_LOG_OBJEXIT(); //####
} // IconlessPanel::setWidth

#if defined(__APPLE__)
# pragma mark Accessors
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)
