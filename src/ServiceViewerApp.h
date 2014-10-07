//--------------------------------------------------------------------------------------------------
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
//  Created:    2014-05-08
//
//--------------------------------------------------------------------------------------------------

#if (! defined(__ServiceViewer__ServiceViewerApp__))
# define __ServiceViewer__ServiceViewerApp__  /* Header guard */

# include "PortEntry.h"

# include "ofBaseApp.h"
# include "ofxGui.h"

// Note that openFrameworks defines a macro called 'check' :( which messes up other header files.
# undef check
# include <mpm/M+MUtilities.h>

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

//# define CHECK_FOR_STALE_PORTS /* Check for 'stale' ports in the scanner. */

/*! @brief A slightly longer sleep, in milliseconds. */
# define MIDDLE_SLEEP 35

/*! @brief The minimum time for a thread to sleep, in milliseconds. */
# define SHORT_SLEEP  20

class BackgroundScanner;
class ServiceEntity;

/*! @brief The service viewer application class. */
class ServiceViewerApp : public ofBaseApp
{
public :
    
    /*! @brief The constructor. */
    ServiceViewerApp(void);
    
    /*! @brief Add an entity to the list of next-to-be-displayed entities.
     @param anEntity The entity to be added. */
    void addEntityToBackground(ServiceEntity * anEntity);
    
    /*! @brief Add an entity to the list of currently displayed entities.
     @param anEntity The entity to be added. */
    void addEntityToForeground(ServiceEntity * anEntity);
    
    /*! @brief Returns @c true if an add-connection operation is active and @c false otherwise.
     @returns @c true if an add-connection operation is active and @c false otherwise. */
    inline bool addIsActive(void)
    const
    {
        return _addIsActive;
    } // addIsActive
    
    /*! @brief Clear any pending drag actions. */
    void clearDragState(void);
    
    /*! @brief Clear out the background data. */
    void clearOutBackgroundData(void);
    
    /*! @brief Returns the state of the CONTROL modifier key.
     @returns @c true if the CONTROL modifier key is pressed and @c false otherwise. */
    inline bool controlActive(void)
    const
    {
        return _controlActive;
    } // controlActive
    
    /*! @brief Returns @c true if a drag operation is active and @c false otherwise.
     @returns @c true if a drag operation is active and @c false otherwise. */
    inline bool dragActive(void)
    const
    {
        return _dragActive;
    } // dragActive
    
    /*! @brief Process a drag event.
     @param dragInfo The attributes of the event. */
    virtual void dragEvent(ofDragInfo dragInfo);
    
    /*! @brief Perform the draw step of the update-draw loop. */
    virtual void draw(void);
    
    /*! @brief Handle an exit request. */
    virtual void exit(void);
    
    /*! @brief Remove a port from the set of known ports.
     @param aPort The port to be removed. */
    void forgetPort(PortEntry * aPort);
    
    /*! @brief Identify the YARP network entities.
     @param checker A function that provides for early exit from loops.
     @param checkStuff The private data for the early exit function. */
    void gatherEntitiesInBackground(MplusM::Common::CheckFunction checker = NULL,
                                    void *                        checkStuff = NULL);
    
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
    
    /*! @brief Move an entity to the end of the entity list so that it will be the last drawn.
     @param anEntity The entity to be moved. */
    void moveEntityToEndOfForegroundList(ServiceEntity * anEntity);
    
    /*! @brief Indicate that an entity move has begun. */
    inline void movementStarted(void)
    {
        _movementActive = true;
    } // movementStarted
    
    /*! @brief Returns @c true if a remove-connection operation is active and @c false otherwise.
     @returns @c true if a remove-connection operation is active and @c false otherwise. */
    inline bool removeIsActive(void)
    const
    {
        return _removeIsActive;
    } // removeIsActive
    
    /*! @brief Handle the drag operation for an 'add-connection' operation.
     @param xPos The current horizontal mouse position.
     @param yPos The current vertical mouse position. */
    void reportConnectionDrag(const float xPos,
                              const float yPos);
    
    /*! @brief Process a click on a Port Entry with a modifier set.
     @param aPort The port being handled. */
    void reportPortEntryClicked(PortEntry * aPort);
    
    /*! @brief Setup the parameters of the application. */
    virtual void setup(void);
    
    /*! @brief Perform the update step of the update-draw loop. */
    virtual void update(void);
    
    /*! @brief Process a window-resized event.
     @param w The new window width.
     @param h The new window height. */
    virtual void windowResized(int w,
                               int h);
    
    /*! @brief Return the color to be used for markers.
     @returns The color to be used for markers. */
    static ofColor getMarkerColor(void);
    
    /*! @brief Return the line width for an input/output connection.
     @returns The line width for an input/output connection. */
    static float getInputOutputConnectionWidth(void);
    
    /*! @brief Return the line width for a normal connection.
     @returns The line width for a normal connection. */
    static float getNormalConnectionWidth(void);
    
    /*! @brief Return the color to be used for non-TCP/non-UDP connections.
     @returns The color to be used for non-TCP/non-UDP connection. */
    static ofColor getOtherConnectionColor(void);
    
    /*! @brief Return the line width for a service connection.
     @returns The line width for a service connection. */
    static float getServiceConnectionWidth(void);
    
    /*! @brief Return the color to be used for TCP connections.
     @returns The color to be used for TCP connections. */
    static ofColor getTcpConnectionColor(void);
    
    /*! @brief Return the color to be used for UDP connections.
     @returns The color to be used for UDP connections. */
    static ofColor getUdpConnectionColor(void);
    
protected :
    
private :
    
    COPY_AND_ASSIGNMENT_(ServiceViewerApp);
    
    /*! @brief Add connections between detected ports in the to-be-displayed list.
     @param detectedPorts The set of detected YARP ports.
     @param checker A function that provides for early exit from loops.
     @param checkStuff The private data for the early exit function. */
    void addPortConnectionsToBackground(const MplusM::Utilities::PortVector & detectedPorts,
                                        MplusM::Common::CheckFunction         checker = NULL,
                                        void *                                checkStuff = NULL);
    
    /*! @brief Add ports that have associates as 'adapter' entities to the to-be-displayed list.
     @param detectedPorts The set of detected YARP ports.
     @param checker A function that provides for early exit from loops.
     @param checkStuff The private data for the early exit function. */
    void addPortsWithAssociatesToBackground(const MplusM::Utilities::PortVector & detectedPorts,
                                            MplusM::Common::CheckFunction         checker = NULL,
                                            void *                                checkStuff =
                                                                                            NULL);
    
    /*! @brief Add regular YARP ports as distinct entities to the to-be-displayed list.
     @param detectedPorts The set of detected YARP ports.
     @param checker A function that provides for early exit from loops.
     @param checkStuff The private data for the early exit function. */
    void addRegularPortEntitiesToBackground(const MplusM::Utilities::PortVector & detectedPorts,
                                            MplusM::Common::CheckFunction         checker = NULL,
                                            void *                                checkStuff =
                                                                                            NULL);
    
    /*! @brief Add services as distinct entities to the to-be-displayed list.
     @param services The set of detected services.
     @param checker A function that provides for early exit from loops.
     @param checkStuff The private data for the early exit function. */
    void addServicesToBackground(const MplusM::Common::StringVector & services,
                                 MplusM::Common::CheckFunction        checker = NULL,
                                 void *                               checkStuff = NULL);
    
    /*! @brief Find a port in the to-be-displayed list by name.
     @param name The name of the port.
     @returns @c NULL if the port cannot be found and non-@c NULL if it is found. */
    PortEntry * findBackgroundPort(const string & name);
    
    /*! @brief Find an entity in the currently-displayed list by name.
     @param name The name of the entity.
     @returns @c NULL if the entity cannot be found and non-@c NULL if it is found. */
    ServiceEntity * findForegroundEntity(const string & name);
    
    /*! @brief Find an entity by the name of a port within it.
     @param name The name of the port.
     @returns @c NULL if the entity cannot be found and non-@c NULL if it is found. */
    ServiceEntity * findForegroundEntityForPort(const string & name);
    
    /*! @brief Find an entity by a port within it.
     @param aPort The port of interest.
     @returns @c NULL if the entity cannot be found and non-@c NULL if it is found. */
    ServiceEntity * findForegroundEntityForPort(const PortEntry * aPort);
    
    /*! @brief Find a port in the currently-displayed list by name.
     @param name The name of the port.
     @returns @c NULL if the port cannot be found and non-@c NULL if it is found. */
    PortEntry * findForegroundPort(const string & name);
    
    /*! @brief Add a port to the set of known ports in the to-be-displayed list.
     @param aPort The port to be added. */
    void rememberPortInBackground(PortEntry * aPort);
    
    /*! @brief Set the entity positions. */
    void setEntityPositions(void);
    
    /*! @brief Swap the background and foreground data structures. */
    void swapBackgroundAndForeground(void);
    
public :

protected :

private :
    
    /*! @brief The class that this class is derived from. */
    typedef ofBaseApp inherited;
    
    /*! @brief The information for a connection. */
    struct ConnectionDetails
    {
        /*! @brief The name of the destination port. */
        string _inPortName;
        
        /*! @brief The name of the source port. */
        string _outPortName;
        
        /*! @brief The mode of the connection. */
        MplusM::Common::ChannelMode _mode;
        
    }; // ConnectionDetails
    
    /*! @brief The name and direction for a port. */
    struct NameAndDirection
    {
        /*! @brief The name of the port. */
        string _name;
        
        /*! @brief The direction of the port. */
        PortEntry::PortDirection _direction;
        
    }; // NameAndDirection
    
    /*! @brief The name and associates for a port. */
    struct PortAndAssociates
    {
        /*! @brief The name of the port. */
        string _name;
        
        /*! @brief The associates of the port. */
        MplusM::Utilities::PortAssociation _associates;
        
    }; // PortAndAssociates
    
    /*! @brief A mapping from port names to associates. */
    typedef std::map<string, PortAndAssociates> AssociatesMap;
    
    /*! @brief A collection of connections. */
    typedef std::vector<ConnectionDetails> ConnectionList;
    
    /*! @brief A collection of services and ports. */
    typedef std::list<ServiceEntity *> EntityList;
    
    /*! @brief A mapping from strings to ports. */
    typedef std::map<string, PortEntry *> PortEntryMap;
    
    /*! @brief A collection of port names. */
    typedef std::map<string, NameAndDirection> PortMap;
    
    /*! @brief A collection of port names. */
    typedef std::set<string> PortSet;
    
    /*! @brief A mapping from strings to service descriptions. */
    typedef std::map<string, MplusM::Utilities::ServiceDescriptor> ServiceMap;
    
    /*! @brief A collection of visible services and ports. */
    EntityList _entities1;
    
    /*! @brief A collection of visible services and ports. */
    EntityList _entities2;
    
    /*! @brief A set of known ports. */
    PortEntryMap _ports1;
    
    /*! @brief A set of known ports. */
    PortEntryMap _ports2;
    
    /*! @brief A set of known services. */
    ServiceMap _detectedServices;
    
    /*! @brief A set of known ports. */
    PortSet _rememberedPorts;
    
    /*! @brief A set of associated ports. */
    AssociatesMap _associatedPorts;
    
    /*! @brief A set of standalone ports. */
    PortMap _standalonePorts;
    
    /*! @brief A set of connections. */
    ConnectionList _connections;
    
    /*! @brief Control access to the currently-displayed lists. */
    ofMutex _foregroundLock;
    
    /*! @brief The background set of known entities. */
    EntityList * _backgroundEntities;
    
    /*! @brief The foreground set of known entities. */
    EntityList * _foregroundEntities;
    
    /*! @brief The background set of known ports. */
    PortEntryMap * _backgroundPorts;
    
    /*! @brief The foreground set of known ports. */
    PortEntryMap * _foregroundPorts;
    
    /*! @brief The starting port for a connection being added. */
    PortEntry * _firstAddPort;
    
    /*! @brief The starting port for a connection being removed. */
    PortEntry * _firstRemovePort;
    
    /*! @brief The background port scanner. */
    BackgroundScanner * _scanner;
    
    /*! @brief The horizontal coordinate of the current drag location. */
    float _dragXpos;
    
    /*! @brief The vertical coordinate of the current drag location. */
    float _dragYpos;
    
# if defined(CHECK_FOR_STALE_PORTS)
    /*! @brief The time when the last stale removal occurred. */
    float _lastStaleTime;
# endif // defined(CHECK_FOR_STALE_PORTS)
    
    /*! @brief @c true if the connection being added will be UDP and @c false if it will be TCP. */
    bool _addingUDPConnection;
    
    /*! @brief @c true if a connection is being added and @c false otherwise. */
    bool _addIsActive;
    
    /*! @brief @c true if the ALT/OPTION modifier key is depressed and @c false otherwise. */
    bool _altActive;
    
    /*! @brief @c true if the COMMAND modifier key is depressed and @c false otherwise. */
    bool _commandActive;
    
    /*! @brief @c true if the CONTROL modifier key is depressed and @c false otherwise. */
    bool _controlActive;
    
    /*! @brief @c true if a connection is being created by dragging between ports and @c false
     otherwise. */
    bool _dragActive;
    
    /*! @brief @c true if the next scan will be ignored and @c false otherwise. */
    bool _ignoreNextScan;
    
    /*! @brief @c true if an entity is being moved. */
    bool _movementActive;
    
    /*! @brief @c true if the YARP network is running. */
    bool _networkAvailable;
    
    /*! @brief @c true if the service registry can be used. */
    bool _registryAvailable;
    
    /*! @brief @c true if a connection is being removed and @c false otherwise. */
    bool _removeIsActive;
    
    /*! @brief @c true if the SHIFT modifier key is depressed and @c false otherwise. */
    bool _shiftActive;
    
# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunused-private-field"
# endif // defined(__APPLE__)
    /*! @brief Filler to pad to alignment boundary */
    char _filler[4];
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)
    
}; // ServiceViewerApp

#endif // ! defined(__ServiceViewer__ServiceViewerApp__)
