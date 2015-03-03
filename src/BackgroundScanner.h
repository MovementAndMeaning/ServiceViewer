//--------------------------------------------------------------------------------------------------
//
//  File:       BackgroundScanner.h
//
//  Project:    M+M
//
//  Contains:   The class declaration for a thread class to handle background port scanning.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2014 by H Plus Technologies Ltd. and Simon Fraser University.
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
//  Created:    2014-06-11
//
//--------------------------------------------------------------------------------------------------

#if (! defined(__ServiceViewer__BackgroundScanner__))
# define __ServiceViewer__BackgroundScanner__  /* Header guard */

# include "ofThread.h"

// Note that openFrameworks defines a macro called 'check' :( which messes up other header files.
# undef check
# include <mpm/M+MCommon.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 
 @brief The class declaration for a thread class to handle background port scanning. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

class ServiceViewerApp;

/*! @brief A thread class to handle background port scanning. */
class BackgroundScanner : public ofThread
{
public :
    
    /*! @brief The constructor.
     @param owner The application object that manages this thread.
     @param minScanInterval The minimum number of seconds between scans. */
    BackgroundScanner(ServiceViewerApp & owner,
                      const float        minScanInterval);
    
    /*! @brief The destructor. */
    virtual ~BackgroundScanner(void);
    
    /*! @brief The next scan can be initiated. */
    void enableScan(void);
    
    /*! @brief Returns @c true if the scan data is available and @c false otherwise.
     @returns @c true if the scan data is available and @c false otherwise. */
    inline bool scanComplete(void)
    const
    {
        return _scanComplete;
    } // scanComplete
    
protected :
    
    /*! @brief The thread run function. */
    virtual void threadedFunction(void);
    
private :
    
    COPY_AND_ASSIGNMENT_(BackgroundScanner);
    
public :

protected :

private :
    
    /*! @brief The class that this class is derived from. */
    typedef ofThread inherited;
    
    /*! @brief The application object that manages the thread. */
    ServiceViewerApp & _owner;
    
    /*! @brief The time when the last scan occurred. */
    float _lastScanTime;
    
    /*! @brief The minimum number of seconds between scans. */
    float _scanInterval;
    
    /*! @brief @c true if the scan is active and @c false otherwise. */
    bool _scanActive;
    
    /*! @brief @c true if the scan has been finished and the data is available, @c false
     otherwise. */
    bool _scanComplete;
    
    /*! @brief @c true if the scan can be started and @c false otherwise. */
    bool _scanEnabled;
    
# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunused-private-field"
# endif // defined(__APPLE__)
    /*! @brief Filler to pad to alignment boundary */
    char _filler[5];
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)
}; // BackgroundScanner

#endif // ! defined(__ServiceViewer__BackgroundScanner__)
