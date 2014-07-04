//--------------------------------------------------------------------------------------
//
//  File:       PortEntry.h
//
//  Project:    M+M
//
//  Contains:   The class declaration for a GUI element to represent ports.
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

#if (! defined(__ServiceViewer__PortEntry__))
# define __ServiceViewer__PortEntry__ /* Header guard */

# include "LabelWithShadow.h"

// Note that openFrameworks defines a macro called 'check' :( which messes up other header files.
# undef check
# include "M+MCommon.h"

# include <set>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 
 @brief The class declaration for a GUI element to represent ports. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

class PortPanel;
class ServiceViewerApp;

/*! @brief A GUI element to represent ports. */
class PortEntry : public LabelWithShadow
{
public:
    
    /*! @brief The anchor position for a connection between ports. */
    enum AnchorSide
    {
        /*! @brief The connection is to the left edge of the port entry. */
        kAnchorLeft,
        
        /*! @brief The connection is to the right edge of the port entry. */
        kAnchorRight,
        
        /*! @brief The connection is to the bottom edge of the port entry. */
        kAnchorBottomCentre,
        
        /*! @brief The connection is to the top edge of the port entry. */
        kAnchorTopCentre,
        
        /*! @brief The connection point is unknown. */
        kAnchorUnknown
        
    }; // AnchorSide
    
    /*! @brief The primary direction of the port. */
    enum PortDirection
    {
        /*! @brief The port direction is input. */
        kPortDirectionInput,
        
        /*! @brief The port direction is both input and output. */
        kPortDirectionInputOutput,
        
        /*! @brief The port direction is output. */
        kPortDirectionOutput,
        
        /*! @brief The port direction is unknown. */
        kPortDirectionUnknown
        
    }; // PortDirection
    
    /*! @brief What the port will be used for. */
    enum PortUsage
    {
        /*! @brief The port is for a client or adapter. */
        kPortUsageClient,
        
        /*! @brief The port is for a service. */
        kPortUsageService,
        
        /*! @brief The port has no specific characterization. */
        kPortUsageOther
        
    }; // PortUsage
    
    /*! @brief The form of a connection. */
    struct PortConnection
    {
        /*! @brief The 'other-end' of a connection. */
        PortEntry *                 _otherPort;
        
        /*! @brief The kind of connection. */
        MplusM::Common::ChannelMode _connectionMode;
        
    }; // PortConnection
    
    /*! @brief The set of connections to the port. */
    typedef vector<PortConnection> Connections;

    /*! @brief The constructor.
     @param parent The GUI element containing this element.
     @param portProtocol The protocol of the port.
     @param portKind What the port will be used for.
     @param direction The primary direction of the port. */
	PortEntry(IconlessPanel *     parent,
              const string &      portProtocol,
              const PortUsage     portKind,
              const PortDirection direction = kPortDirectionInput);
    
    /*! @brief The destructor. */
	virtual ~PortEntry(void);
    
    /*! @brief Add an input connection to the port.
     @param other The port that is to be connected.
     @param mode The mode of the connection. */
    void addInputConnection(PortEntry *                 other,
                            MplusM::Common::ChannelMode mode);
    
    /*! @brief Add an output connection to the port.
     @param other The port that is to be connected.
     @param mode The mode of the connection. */
    void addOutputConnection(PortEntry *                 other,
                             MplusM::Common::ChannelMode mode);
    
    /*! @brief Determine the anchor point that is the minimum distance from a given point.
     @param result The coordinates of the anchor point.
     @param isSource @c true if the anchor is for an outgoing line and @c false otherwise.
     @param disallowBottom @c true if the anchor cannot be bottom-centre.
     @param xx The horizontal coordinate for the point of interest.
     @param yy The vertical coordinate for the point of interest.
     @returns The side to which the anchor is attached. */
    inline AnchorSide calculateClosestAnchor(ofPoint &   result,
                                             const bool  isSource,
                                             const bool  disallowBottom,
                                             const float xx,
                                             const float yy)
    {
        return calculateClosestAnchor(result, isSource, disallowBottom, ofPoint(xx, yy));
    } // calculateClosestAnchor
    
    /*! @brief Determine the anchor point that is the minimum distance from a given point.
     @param result The coordinates of the anchor point.
     @param isSource @c true if the anchor is for an outgoing line and @c false otherwise.
     @param disallowBottom @c true if the anchor cannot be bottom-centre.
     @param pp The point of interest.
     @returns The side to which the anchor is attached. */
    AnchorSide calculateClosestAnchor(ofPoint &       result,
                                      const bool      isSource,
                                      const bool      disallowBottom,
                                      const ofPoint & pp);
    
    /*! @brief Display the 'drag-line' from this port entry to the given coordinates.
     @param xPos The horizontal coordinate of the destination.
     @param yPos The vertical coordinate of the destination.
     @param isUDP @c true if the connection will be UDP and @c false otherwise. */
    void drawDragLine(const float xPos,
                      const float yPos,
                      const bool  isUDP);
    
    /*! @brief Return the location of the centre of the port entry.
     @returns The location of the centre of the port entry. */
    ofPoint getCentre(void);
    
    /*! @brief Return the direction of the port entry.
     @returns The direction of the port entry. */
    PortDirection getDirection(void)
    const
    {
        return _direction;
    } // getDirection
    
    /*! @brief Return the set of input connections to the port.
     @returns The set of input connections to the port. */
    inline const Connections & getInputConnections(void)
    const
    {
        return _inputConnections;
    } // getInputConnections
    
    /*! @brief Return the set of output connections to the port.
     @returns The set of output connections to the port. */
    inline const Connections & getOutputConnections(void)
    const
    {
        return _outputConnections;
    } // getOutputConnections
    
    inline PortPanel * getParent(void)
    const
    {
        return reinterpret_cast<PortPanel *>(_parent);
    } // getParent
    
    /*! @brief Return the name of the associated port.
     @returns The name of the associated port. */
    inline string getPortName(void)
    const
    {
        return _portName;
    } // getPortName
    
    /*! @brief Return the protocol of the associated port.
     @returns The protocol of the associated port. */
    inline string getProtocol(void)
    const
    {
        return _portProtocol;
    } // getProtocol
    
    /*! @brief Return the usage of the port entry.
     @returns The usage of the port entry. */
    PortUsage getUsage(void)
    const
    {
        return _usage;
    } // getUsage
    
    /*! @brief Returns @c true if the port entry is the bottom-most (last) port entry in a panel and @c false otherwise.
     @returns @c true if the port is the last port entry in a panel and @c false otherwise. */
    inline bool isLastPort(void)
    const
    {
        return _isLastPort;
    } // isLastPort
    
    /*! @brief Returns @c true if the given point is within the displayed region of the entry and @c false otherwise.
     @param aPoint The point of interest.
     @returns @c true if the given point is within the displayed region of the entry and @c false otherwise. */
    bool isPointInside(const ofPoint & aPoint)
    const;
    
    /*! @brief Returns @c true if the given point is within the displayed region of the entry and @c false otherwise.
     @param xPos The horizontal coordinate of the point of interest.
     @param yPos The vertical coordinate of the point of interest.
     @returns @c true if the given point is within the displayed region of the entry and @c false otherwise. */
    bool isPointInside(const float xPos,
                       const float yPos)
    const;
    
    /*! @brief Returns @c true if the port entry is part of a service and @c false otherwise.
     @returns @c true if the port is part of a service and @c false otherwise. */
    inline bool isService(void)
    const
    {
        return (kPortUsageService == _usage);
    } // isService
    
    /*! @brief Process a mouse-dragged event.
     @param args The attributes of the event.
     @returns @c true if the event was processed and @c false if it can be further propagated. */
	virtual bool mouseDragged(ofMouseEventArgs & args);

    /*! @brief Process a mouse-moved event.
     @param args The attributes of the event.
     @returns @c true if the event was processed and @c false if it can be further propagated. */
	virtual bool mouseMoved(ofMouseEventArgs & args);

    /*! @brief Process a mouse-pressed event.
     @param args The attributes of the event.
     @returns @c true if the event was processed and @c false if it can be further propagated. */
	virtual bool mousePressed(ofMouseEventArgs & args);

    /*! @brief Process a mouse-released event.
     @param args The attributes of the event.
     @returns @c true if the event was processed and @c false if it can be further propagated. */
	virtual bool mouseReleased(ofMouseEventArgs & args);

    /*! @brief Remove an input connection from a port.
     @param other The port that is to be disconnected. */
    void removeInputConnection(PortEntry * other);
    
    /*! @brief Remove an output connection from a port.
     @param other The port that is to be disconnected. */
    void removeOutputConnection(PortEntry * other);
    
    /*! @brief Mark the port entry as the bottom-most (last) port entry in a panel. */
    inline void setAsLastPort(void)
    {
        _isLastPort = true;
    } // setAsLastPort
    
    /*! @brief Set the parameters of the entry.
     @param label The port name for the entry.
     @param width The visual width of the entry.
     @param height The visual height of the entry. */
    PortEntry * setup(string      label,
                      const float width = defaultWidth,
                      const float height = defaultHeight);
    
    /*! @brief Mark the port entry as not being the bottom-most port entry in a panel. */
    inline void unsetAsLastPort(void)
    {
        _isLastPort = false;
    } // unsetAsLastPort
    
    /*! @brief Displays an anchor leaving the given location.
     @param anchor The side to which the anchor is attached.
     @param anchorPos The coordinates of the anchor point. */
    static void drawSourceAnchor(const AnchorSide anchor,
                                 const ofPoint &  anchorPos);
    
    /*! @brief Displays an anchor arriving at the given location.
     @param anchor The side to which the anchor is attached.
     @param anchorPos The coordinates of the anchor point. */
    static void drawTargetAnchor(const AnchorSide anchor,
                                 const ofPoint &  anchorPos);
    
protected:
    
private:
    
    /*! @brief The class that this class is derived from. */
    typedef LabelWithShadow inherited;
    
    /*! @brief Copy constructor.
     
     Note - not implemented and private, to prevent unexpected copying.
     @param other Another object to construct from. */
    PortEntry(const PortEntry & other);
    
    /*! @brief Assignment operator.
     
     Note - not implemented and private, to prevent unexpected copying.
     @param other Another object to construct from. */
    PortEntry & operator=(const PortEntry & other);
    
    /*! @brief The connections to the port. */
    Connections   _inputConnections;
    
    /*! @brief The connections to the port. */
    Connections   _outputConnections;
    
    /*! @brief The name of the associated port. */
    string        _portName;
    
    /*! @brief The protocol of the associated port. */
    string        _portProtocol;
    
    /*! @brief The primary direction for connections to the port. */
    PortDirection _direction;
    
    /*! @brief The primary usage for the port. */
    PortUsage     _usage;
    
    /*! @brief @c true if the port entry is the bottom-most (last) port entry in a panel and @c false otherwise. */
    bool          _isLastPort;
    
# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunused-private-field"
# endif // defined(__APPLE__)
    /*! @brief Filler to pad to alignment boundary */
    char          _filler[7];
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)
    
}; // PortEntry

#endif // ! defined(__ServiceViewer__PortEntry__)
