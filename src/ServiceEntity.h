//--------------------------------------------------------------------------------------
//
//  File:       ServiceEntity.h
//
//  Project:    M+M
//
//  Contains:   The class declaration for a moveable GUI element to represent a set of ports.
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

#if (! defined(__ServiceViewer__ServiceEntity__))
# define __ServiceViewer__ServiceEntity__

# include "MovementTracker.h"
# include "PortPanel.h"

# include "ofxGui.h"

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 
 @brief The class declaration for a moveable GUI element to represent a set of ports. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

class PortEntry;
class ServiceViewerApp;

/*! @brief A moveable GUI element to represent a set of ports. */
class ServiceEntity : MovementTracker
{
public:
    
    /*! @brief The constructor.
     @param kind The kind of entity.
     @param description The description, if this is a service.
     @param owner The application object that manages this entity. */
	ServiceEntity(const PortPanel::EntityKind kind,
                  const string                description,
                  ServiceViewerApp *          owner);
    
    /*! @brief The destructor. */
	virtual ~ServiceEntity(void);
    
    /*! @brief Add a port to the panel.
     @param portName The name of the port.
     @param portKind What the port will be used for.
     @param direction The primary direction of the port. */
    inline void addPort(string                         portName,
                        const PortEntry::PortUsage     portKind,
                        const PortEntry::PortDirection direction = PortEntry::kPortDirectionInputOutput)
    {
        _panel.addPort(portName, portKind, direction);
    } // addPort
    
    /*! @brief Stop displaying the connect marker. */
    inline void clearConnectMarker(void)
    {
        _drawConnectMarker = false;
    } // clearConnectMarker
    
    /*! @brief Stop displaying the disconnect marker. */
    inline void clearDisconnectMarker(void)
    {
        _drawDisconnectMarker = false;
    } // clearDisconnectMarker
    
    /*! @brief Deselect the entity. */
    inline void deselect(void)
    {
        _selected = false;
    } // deselect
    
    /*! @brief Display the entity. */
    void draw(void);
    
    /*! @brief Return the name of the entity.
     @returns The name of the entity. */
    inline string getName(void)
    {
        return _panel.getName();
    } // getName
    
    /*! @brief Return the bounding box for the entity.
     @returns The bounding box for the entity. */
    inline ofRectangle getShape(void)
    {
        return _panel.getShape();
    } // getShape
    
    /*! @brief The entity position has been changed. */
    virtual void handlePositionChange(void);
    
    /*! @brief Check if a port is part of the entity.
     @param aPort The port to be checked for.
     @returns @c true if the port is contained within the entity and @c false otherwise. */
    bool hasPort(const PortEntry * aPort);
    
    /*! @brief Return @c true is the entity is selected.
     @returns @c true if the entity is selected and @c false otherwise. */
    inline bool isSelected(void)
    const
    {
        return _selected;
    } // isSelected
    
    /*! @brief The entity position changes are complete. */
    virtual void positionChangeComplete(void);

    /*! @brief Select the entity. */
    inline void select(void)
    {
        _selected = true;
    } // select
    
    /*! @brief Start displaying the connect marker. */
    inline void setConnectMarker(void)
    {
        _drawConnectMarker = true;
    } // setConnectMarker
    
    /*! @brief Start displaying the disconnect marker. */
    inline void setDisconnectMarker(void)
    {
        _drawDisconnectMarker = true;
    } // setDisconnectMarker
    
    /*! @brief Move the entity to a new location on the display.
     @param xx The new horizontal position of the entity.
     @param yy The new vertical position of the entity. */
    inline void setPosition(const float xx = 10,
                            const float yy = 10)
    {
        _panel.setPosition(xx, yy);
    } // setPosition
    
    /*! @brief Set the parameters of the entity.
     @param entityName The name of the service or application.
     @param xx The initial horizontal position of the entity.
     @param yy The initial vertical position of the entity. */
	void setup(string      entityName,
               const float xx = 10,
               const float yy = 10);

protected:
    
private:
    
    /*! @brief The class that this class is derived from. */
    typedef MovementTracker inherited;
    
    /*! @brief Copy constructor.
     
     Note - not implemented and private, to prevent unexpected copying.
     @param other Another object to construct from. */
    ServiceEntity(const ServiceEntity & other);
    
    /*! @brief Assignment operator.
     
     Note - not implemented and private, to prevent unexpected copying.
     @param other Another object to construct from. */
    ServiceEntity & operator=(const ServiceEntity & other);
    
    /*! @brief The GUI object that represents the entity. */
    PortPanel _panel;
    
    /*! @brief @c true if the connect marker is to be displayed and @c false otherwise. */
    bool      _drawConnectMarker;
    
    /*! @brief @c true if the disconnect marker is to be displayed and @c false otherwise. */
    bool      _drawDisconnectMarker;
    
    /*! @brief @c true if the movement marker is to be displayed and @c false otherwise. */
    bool      _drawMoveMarker;

    /*! @brief @c true if the entity is selected and @c false otherwise. */
    bool      _selected;
    
# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunused-private-field"
# endif // defined(__APPLE__)
    /*! @brief Filler to pad to alignment boundary */
    char      _filler[4];
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)
    
}; // ServiceEntity

#endif // ! defined(__ServiceViewer__ServiceEntity__)
