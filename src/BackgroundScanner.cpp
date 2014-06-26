//--------------------------------------------------------------------------------------
//
//  File:       BackgroundScanner.cpp
//
//  Project:    M+M
//
//  Contains:   The class definition for a thread class to handle background port
//              scanning.
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
//  Created:    2014-06-11
//
//--------------------------------------------------------------------------------------

#include "BackgroundScanner.h"
#include "ServiceViewerApp.h"

//#include "ODEnableLogging.h"
#include "ODLogging.h"

#include "ofUtils.h"

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 
 @brief The class definition for a thread class to handle background port scanning. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

/*! @brief The number of milliseconds in a second. */
#define MILLISECONDS_PER_SECOND 1000

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and destructors
#endif // defined(__APPLE__)

BackgroundScanner::BackgroundScanner(ServiceViewerApp & owner,
                                     const float        minScanInterval) :
        inherited(), _owner(owner), _scanActive(false), _scanInterval(minScanInterval), _scanComplete(false),
        _scanEnabled(false)
{
    OD_LOG_ENTER();//####
    _lastScanTime = ofGetElapsedTimef();
    OD_LOG_EXIT_P(this);//####
} // BackgroundScanner::BackgroundScanner

BackgroundScanner::~BackgroundScanner(void)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_OBJEXIT();//####
} // BackgroundScanner::~BackgroundScanner

#if defined(__APPLE__)
# pragma mark Actions
#endif // defined(__APPLE__)

void BackgroundScanner::enableScan(void)
{
    OD_LOG_OBJENTER();//####
    for (bool locked = lock(); ! locked; )
    {
        yield();
    }
    _scanComplete = false;
    _scanEnabled = true;
    unlock();
    OD_LOG_OBJEXIT();//####
} // BackgroundScanner::enableScan

void BackgroundScanner::threadedFunction(void)
{
    OD_LOG_OBJENTER();//####
    
    // start
    while (isThreadRunning())
    {
        if (lock())
        {
            _scanActive = _scanEnabled;
            _scanEnabled = false;
            unlock();
            if (_scanActive)
            {
                float sleepTime = _scanInterval - (ofGetElapsedTimef() - _lastScanTime);

                if (0 < sleepTime)
                {
                    sleep(sleepTime * MILLISECONDS_PER_SECOND);
                }
                else
                {
                    cerr << "actual interval = " << (ofGetElapsedTimef() - _lastScanTime) << endl;
                }
                _lastScanTime = ofGetElapsedTimef();
                _owner.gatherEntitiesInBackground();
                for (bool locked = lock(); ! locked; )
                {
                    sleep(MIDDLE_SLEEP);
                    yield();
                }
                _scanComplete = true;
                _scanActive = false;
                unlock();
                sleep(SHORT_SLEEP);
            }
            else
            {
                sleep(SHORT_SLEEP);
            }
        }
        else
        {
            sleep(SHORT_SLEEP);
        }
    }
    // done
    OD_LOG_OBJEXIT();//####
} // BackgroundScanner::threadedFunction

#if defined(__APPLE__)
# pragma mark Accessors
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)