//--------------------------------------------------------------------------------------
//
//  File:       ServiceViewerApp.h
//
//  Project:    M+M
//
//  Contains:   The class declaration for the service viewer application class.
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
//  Created:    2014-05-08
//
//--------------------------------------------------------------------------------------

#if (! defined(__ServiceViewer__ServiceViewerApp__))
# define __ServiceViewer__ServiceViewerApp__

# include "ofBaseApp.h"
# include "ofxGui.h"
# include <list>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 
 @brief The class declaration for the service viewer application class. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

class PortEntry;
class ServiceEntity;

/*! @brief The service viewer application class. */
class ServiceViewerApp : public ofBaseApp
{
public:
    
    /*! @brief The constructor. */
    ServiceViewerApp(void);
    
    /*! @brief Add an entity to the list of displayed entities.
     @param anEntity The entity to be added. */
    void addEntity(ServiceEntity * anEntity);
    
    /*! @brief Returns the state of the ALT/OPTION modifier key.
     @returns @c true if the ALT/OPTION modifier key is pressed and @c false otherwise. */
    inline bool altActive(void)
    const
    {
        return _altActive;
    } // altActive
    
    /*! @brief Returns the state of the COMMAND modifier key.
     @returns @c true if the COMMAND modifier key is pressed and @c false otherwise. */
    inline bool commandActive(void)
    const
    {
        return _commandActive;
    } // commandActive
    
    /*! @brief Returns the state of the CONTROL modifier key.
     @returns @c true if the CONTROL modifier key is pressed and @c false otherwise. */
    inline bool controlActive(void)
    const
    {
        return _controlActive;
    } // controlActive
    
    /*! @brief Process a drag event.
     @param dragInfo The attributes of the event. */
    virtual void dragEvent(ofDragInfo dragInfo);
    
    /*! @brief Perform the draw step of the update-draw loop. */
    virtual void draw(void);
    
    /*! @brief Handle an exit request. */
    virtual void exit(void);
    
    /*! @brief Find an entity by name.
     @param name The name of the entity.
     @returns @c NULL if the entity cannot be found and non-@c NULL if it is found. */
    ServiceEntity * findEntity(string name);
    
    /*! @brief Find an entity by the name of a port within it.
     @param name The name of the port.
     @returns @c NULL if the entity cannot be found and non-@c NULL if it is found. */
    ServiceEntity * findEntityForPort(string name);
    
    /*! @brief Find an entity by a port within it.
     @param aPort The port of interest.
     @returns @c NULL if the entity cannot be found and non-@c NULL if it is found. */
    ServiceEntity * findEntityForPort(const PortEntry * aPort);
    
    /*! @brief Find a port by name.
     @param name The name of the port.
     @returns @c NULL if the port cannot be found and non-@c NULL if it is found. */
    PortEntry * findPort(string name);
    
    /*! @brief Remove a port from the set of known ports.
     @param aPort The port to be removed. */
    void forgetPort(PortEntry * aPort);
    
    /*! @brief Process a message event.
     @param msg The message details. */
    virtual void gotMessage(ofMessage msg);
    
    /*! @brief Process a key-pressed event.
     @param key The key that was pressed. */
    virtual void keyPressed(int key);
    
    /*! @brief Process a key-released event.
     @param key The key that was released. */
    virtual void keyReleased(int key);
    
    /*! @brief Process a mouse-dragged event.
     @param x The current horizontal mouse position.
     @param y The current vertical mouse position.
     @param button The button that is active. */
    virtual void mouseDragged(int x,
                              int y,
                              int button);
    
    /*! @brief Process a mouse-moved event.
     @param x The current horizontal mouse position.
     @param y The current vertical mouse position. */
    virtual void mouseMoved(int x,
                            int y);
    
    /*! @brief Process a mouse-pressed event.
     @param x The current horizontal mouse position.
     @param y The current vertical mouse position.
     @param button The button that is active. */
    virtual void mousePressed(int x,
                              int y,
                              int button);
    
    /*! @brief Process a mouse-released event.
     @param x The current horizontal mouse position.
     @param y The current vertical mouse position.
     @param button The button that was active. */
    virtual void mouseReleased(int x,
                               int y,
                               int button);
    
    /*! @brief Add a port to the set of known ports.
     @param aPort The port to be added. */
    void rememberPort(PortEntry * aPort);
    
    /*! @brief Process a click on a Port Entry with a modifier set.
     @param aPort The port being handled.
     @param altIsActive The ALT key is active.
     @param commandIsActive The COMMAND key is active.
     @param shiftIsActive The SHIFT key is active. */
    void reportPortEntryClicked(PortEntry * aPort,
                                const bool  altIsActive,
                                const bool  commandIsActive,
                                const bool  shiftIsActive);
    
    /*! @brief Setup the parameters of the application. */
    virtual void setup(void);
    
    /*! @brief Returns the state of the SHIFT modifier key.
     @returns @c true if the SHIFT modifier key is pressed and @c false otherwise. */
    inline bool shiftActive(void)
    const
    {
        return _shiftActive;
    } // shiftActive
    
    /*! @brief Perform the update step of the update-draw loop. */
    virtual void update(void);
    
    /*! @brief Add an entity to the entity collection.
     @param anEntity The entity to be added. */
    void updateEntityList(ServiceEntity * anEntity);
    
    /*! @brief Process a window-resized event.
     @param w The new window width.
     @param h The new window height. */
    virtual void windowResized(int w,
                               int h);
    
    /*! @brief Return the color to be used for markers.
     @returns The color to be used for markers. */
    static ofColor getMarkerColor(void);
    
    /*! @brief Return the color to be used for non-TCP/non-UDP connections.
     @returns The color to be used for non-TCP/non-UDP connection. */
    static ofColor getOtherConnectionColor(void);

    /*! @brief Return the color to be used for TCP connections.
     @returns The color to be used for TCP connections. */
    static ofColor getTcpConnectionColor(void);
    
    /*! @brief Return the color to be used for UDP connections.
     @returns The color to be used for UDP connections. */
    static ofColor getUdpConnectionColor(void);
    
private:
    
    /*! @brief The class that this class is derived from. */
    typedef ofBaseApp inherited;
    
    /*! @brief A collection of services and ports. */
    typedef list<ServiceEntity *>    EntityList;

    /*! @brief A mapping from strings to ports. */
    typedef map<string, PortEntry *> PortMap;

    /*! @brief Copy constructor.
     
     Note - not implemented and private, to prevent unexpected copying.
     @param other Another object to construct from. */
    ServiceViewerApp(const ServiceViewerApp & other);
    
    /*! @brief Assignment operator.
     
     Note - not implemented and private, to prevent unexpected copying.
     @param other Another object to construct from. */
    ServiceViewerApp & operator=(const ServiceViewerApp & other);

    /*! @brief Identify the YARP network entities. */
    void gatherEntities(void);
    
    /*! @brief Setup the entity positions. */
    void setInitialEntityPositions(void);
    
    /*! @brief The collection of visible services and ports. */
    EntityList  _entities;

    /*! @brief The set of known ports. */
    PortMap     _ports;
    
    /*! @brief The starting port for a connection being added. */
    PortEntry * _firstAddPort;
    
    /*! @brief The starting port for a connection being removed. */
    PortEntry * _firstRemovePort;
    
    /*! @brief @c true if the ALT/OPTION modifier key is depressed and @c false otherwise. */
    bool        _altActive;
    
    /*! @brief @c true if the COMMAND modifier key is depressed and @c false otherwise. */
    bool        _commandActive;
    
    /*! @brief @c true if the CONTROL modifier key is depressed and @c false otherwise. */
    bool        _controlActive;
    
    /*! @brief @c true if the YARP network is running. */
    bool        _networkAvailable;
    
    /*! @brief @c true if the service registry can be used. */
    bool        _registryAvailable;
    
    /*! @brief @c true if the SHIFT modifier key is depressed and @c false otherwise. */
    bool        _shiftActive;
    
# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunused-private-field"
# endif // defined(__APPLE__)
    /*! @brief Filler to pad to alignment boundary */
    char        _filler[2];
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)
    
}; // ServiceViewerApp

#endif // ! defined(__ServiceViewer__ServiceViewerApp__)
