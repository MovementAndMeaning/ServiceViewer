//--------------------------------------------------------------------------------------------------
//
//  File:       MovementTracker.h
//
//  Project:    M+M
//
//  Contains:   The class declaration for a mixin class to handle movements of GUI elements.
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
//  Created:    2014-05-09
//
//--------------------------------------------------------------------------------------------------

#if (! defined(__ServiceViewer__MovementTracker__))
# define __ServiceViewer__MovementTracker__  /* Header guard */

// Note that openFrameworks defines a macro called 'check' :( which messes up other header files.
# undef check
# include <mpm/M+MCommon.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 
 @brief The class declaration for a mixin class to handle movements of GUI elements. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

/*! @brief A mixin class to handle movements of GUI elements. */
class MovementTracker
{
public :
    
    /*! @brief The constructor. */
    MovementTracker(void);
    
    /*! @brief The destructor. */
    virtual
    ~MovementTracker(void);
    
    /*! @brief Handle a position change notification for the GUI element. */
    virtual void
    handlePositionChange(void) = 0;
    
    /*! @brief The GUI element has completed its movement. */
    virtual void
    positionChangeComplete(void) = 0;
    
protected :
    
private :
    
    COPY_AND_ASSIGNMENT_(MovementTracker);
    
public :

protected :

private :
        
}; // MovementTracker

#endif // ! defined(__ServiceViewer__MovementTracker__)
