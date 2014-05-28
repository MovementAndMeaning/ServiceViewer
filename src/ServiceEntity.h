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

class ServiceViewerApp;

/*! @brief A moveable GUI element to represent a set of ports. */
class ServiceEntity : MovementTracker
{
public:
    
    /*! @brief The constructor.
     @param owner The application object that manages this entity. */
	ServiceEntity(ServiceViewerApp * owner);
    
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
    
    /*! @brief Deselect the entity. */
    inline void deselect(void)
    {
        _selected = false;
    } // deselect
    
    /*! @brief Display the entity. */
    void draw(void);
    
    /*! @brief Return the color used for connections from this entity.
     @returns The color used for connections from this entity. */
    inline ofColor getConnectionColor(void)
    const
    {
        return _thisConnectionColor;
    } // getConnectionColor
    
    /*! @brief Return the width of connections from this entity.
     @returns The width of connections from this entity. */
    inline float getConnectionWidth(void)
    const
    {
        return _thisConnectionWidth;
    } // getConnectionWidth

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
    
    /*! @brief Set the color used for connections from this entity.
     @param color The color to be used for connections from this entity. */
    inline void setConnectionColor(const ofColor & color)
    {
        _thisConnectionColor = color;
    } // setConnectionColor
    
    /*! @brief Set the width of connections from this entity.
     @param width The width of connections from this entity. */
    inline void setConnectionWidth(const float width)
    {
        _thisConnectionWidth = width;
    } // setConnectionWidth
    
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

    /*! @brief Set the default color for connections from entities.
     @param color The default color for connections from entities. */
	static void setDefaultConnectionColor(const ofColor & color)
    {
        connectionColor = color;
    } // setDefaultConnectionColor
        
    /*! @brief Set the default width for connections from entities.
     @param width The default width for connections from entities. */
	static void setDefaultConnectionWidth(const float width)
    {
        connectionWidth = width;
    } // setDefaultConnectionWidth
    
    /*! @brief Return the default color for connections from entities.
     @returns The default color for connections from entities. */
	static ofColor getDefaultConnectionColor(void)
    {
        return connectionColor;
    } // getDefaultConnectionColor
    
    /*! @brief Return the default width for connections from entities.
     @returns The default width for connections from entities. */
	static float getDefaultConnectionWidth(void)
    {
        return connectionWidth;
    } // getDefaultConnectionWidth
    
protected:
    
    /*! @brief The default connection color. */
	static ofColor connectionColor;
    
    /*! @brief The default connection width. */
    static float   connectionWidth;
    
    /*! @brief The connection color for this entity. */
	ofColor _thisConnectionColor;
    
    /*! @brief The connection width for this entity. */
    float   _thisConnectionWidth;
    
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
    PortPanel          _panel;
    
    /*! @brief The application object that manages the entity. */
    ServiceViewerApp * _owner;
    
    /*! @brief @c true if the selection dot is to be displayed and @c false otherwise. */
    bool               _drawDot;

    /*! @brief @c true if the entity is selected and @c false otherwise. */
    bool               _selected;
    
}; // ServiceEntity

#endif // ! defined(__ServiceViewer__ServiceEntity__)
