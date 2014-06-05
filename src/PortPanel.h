//--------------------------------------------------------------------------------------
//
//  File:       PortPanel.h
//
//  Project:    M+M
//
//  Contains:   The class declaration for a GUI element to represent a set of ports.
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

#if (! defined(__ServiceViewer__PortPanel__))
# define __ServiceViewer__PortPanel__

# include "IconlessPanel.h"
# include "PortEntry.h"

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 
 @brief The class declaration for a GUI element to represent a set of ports. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

class MovementTracker;
class ServiceViewerApp;

/*! @brief A GUI element to represent a set of ports. */
class PortPanel : protected IconlessPanel
{
public:
    
    /*! @brief What kind of entity. */
    enum EntityKind
    {
        /*! @brief The entity is a client or adapter. */
        kEntityKindClientOrAdapter,
        /*! @brief The entity is a service. */
        kEntityKindService,
        /*! @brief The entity is neither a serice nor a client nor an adapter. */
        kEntityKindOther
    }; // EntityKind
    
    /*! @brief The constructor.
     @param kind The kind of entity.
     @param description A description of the entity.
     @param owner The application object that manages this panel. */
	PortPanel(const EntityKind   kind,
              const string       description,
              ServiceViewerApp & owner);
    
    /*! @brief The constructor.
     @param kind The kind of entity.
     @param description A description of the entity.
     @param owner The application object that manages this panel.
     @param parameters The set of named parameters for the panel.
     @param filename The settings file for the panel.
     @param xx The initial horizontal position of the panel.
     @param yy The initial vertical position of the panel. */
	PortPanel(const EntityKind         kind,
              const string             description,
              ServiceViewerApp &       owner,
              const ofParameterGroup & parameters,
              string                   filename = "settings.xml",
              const float              xx = 10,
              const float              yy = 10);
    
    /*! @brief The destructor. */
	virtual ~PortPanel(void);
    
    /*! @brief Add a port to the panel.
     @param portName The name of the port.
     @param portKind What the port will be used for.
     @param direction The primary direction of the port. */
    void addPort(string                         portName,
                 const PortEntry::PortUsage     portKind = PortEntry::kPortUsageOther,
                 const PortEntry::PortDirection direction = PortEntry::kPortDirectionInputOutput);
    
    /*! @brief Draw the panel. */
	inline void draw(void)
    {
        inherited::draw();
    } // draw

    /*! @brief Return the height of the vertical gap between panel elements.
     @returns The vertical gap between panel elements. */
    inline float getGapHeight(void)
    const
    {
        return inherited::spacingNextElement;
    } // getGapHeight
    
    /*! @brief Return the height of the header for the panel.
     @returns The height of the header for the panel. */
    inline float getHeader(void)
    const
    {
        return inherited::getHeader();
    } // getHeader
    
    /*! @brief Returns the height of the panel.
     @returns The height of the panel. */
	inline float getHeight(void)
    {
        return inherited::getHeight();
    } // getHeight
    
    /*! @brief Returns the name of the panel.
     @returns The name of the panel. */
	inline string getName(void)
    {
        return inherited::getName();
    } // getName
    
    /*! @brief Returns the number of ports in this panel.
     @returns The number of ports in this panel. */
    inline int getNumPorts(void)
    {
        return inherited::getNumControls();
    } // getNumPorts

    inline ServiceViewerApp & getOwner(void)
    const
    {
        return _owner;
    } // getOwner

    /*! @brief Returns a port by index.
     @param num The zero-origin index of the port.
     @returns A port or @c NULL if the index is out of range. */
    PortEntry * getPort(const int num);

    /*! @brief Returns the outline of the panel.
     @returns The outline of the panel. */
	inline ofRectangle getShape(void)
    {
        return inherited::getShape();
    } // getShape

    /*! @brief Returns the width of the panel.
     @returns The width of the panel. */
	inline float getWidth(void)
    {
        return inherited::getWidth();
    } // getWidth
    
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
    
    /*! @brief Set the title string for the panel.
     @param name The new title string for the panel. */
	inline void setName(string name)
    {
        inherited::setName(name);
    } // setName

    /*! @brief Move the panel to a new location.
     @param xx The new horizontal coordinate.
     @param yy The new vertical coordinate. */
	inline virtual void setPosition(float xx,
                                    float yy)
    {
        inherited::setPosition(xx, yy);
    } // setPosition

    /*! @brief Connect a tracking object to the panel, that will receive handlePositionChange and positionChangeComplete
     notifications */
    inline void setTracker(MovementTracker * newTracker)
    {
        _tracker = newTracker;
    } // setTracker
    
    /*! @brief Set the parameters of the panel.
     @param collectionName The name of the panel.
     @param filename The settings file for the panel.
     @param xx The initial horizontal position of the panel.
     @param yy The initial vertical position of the panel. */
	PortPanel * setup(string      collectionName = "",
                      string      filename = "settings.xml",
                      const float xx = 10,
                      const float yy = 10);
    
    /*! @brief Set the parameters of the panel.
     @param parameters The set of named parameters for the panel.
     @param filename The settings file for the panel.
     @param xx The initial horizontal position of the panel.
     @param yy The initial vertical position of the panel. */
	PortPanel * setup(const ofParameterGroup & parameters,
                      string                   filename = "settings.xml",
                      const float              xx = 10,
                      const float              yy = 10);
    
protected:
    
    /*! @brief Process a mouse motion event.
     @param mx The new mouse horizontal position.
     @param my The new mouse vertical position.
     @param bCheck @c true if this is the initial mouse motion event.
     @returns @c true if the event was processed and @c false if it can be further propagated. */
	virtual bool setValue(float mx,
                          float my,
                          bool  bCheck);
    
private:
    
    /*! @brief The class that this class is derived from. */
    typedef IconlessPanel inherited;
    
    /*! @brief Copy constructor.
     
     Note - not implemented and private, to prevent unexpected copying.
     @param other Another object to construct from. */
    PortPanel(const PortPanel & other);
    
    /*! @brief Assignment operator.
     
     Note - not implemented and private, to prevent unexpected copying.
     @param other Another object to construct from. */
    PortPanel & operator=(const PortPanel & other);
    
    /*! @brief The offset of the initial mouse motion, relative to the panel position. */
    ofPoint            _grabPt;

    /*! @brief The tracking object for the panel. */
    MovementTracker *  _tracker;

    /*! @brief The application object that manages the panel. */
    ServiceViewerApp & _owner;

    /*! @brief The description of the entity, if it is a service. */
    string             _description;
    
    /*! @brief The kind of entity. */
    EntityKind         _kind;
    
    /*! @brief @c true if the panel is being dragged and @c false otherwise. */
	bool               _grabbed;
    
# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunused-private-field"
# endif // defined(__APPLE__)
    /*! @brief Filler to pad to alignment boundary */
    char               _filler[7];
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)
    
}; // PortPanel

#endif // ! defined(__ServiceViewer__PortPanel__)
