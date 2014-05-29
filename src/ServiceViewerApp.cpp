//--------------------------------------------------------------------------------------
//
//  File:       ServiceViewerApp.cpp
//
//  Project:    M+M
//
//  Contains:   The class definition for the service viewer application class.
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

#include "ServiceViewerApp.h"
#include "PortEntry.h"
#include "ServiceEntity.h"

//#include "ODEnableLogging.h"
#include "ODLogging.h"

#include "ofAppRunner.h"
#include "ofBitmapFont.h"
#include "ofGraphics.h"
#include "ofMesh.h"

// Note that openFrameworks defines a macro called 'check' :( which messes up other header files.
#undef check
#include "M+MUtilities.h"

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wc++11-extensions"
# pragma clang diagnostic ignored "-Wdocumentation"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# pragma clang diagnostic ignored "-Wpadded"
# pragma clang diagnostic ignored "-Wshadow"
# pragma clang diagnostic ignored "-Wunused-parameter"
# pragma clang diagnostic ignored "-Wweak-vtables"
#endif // defined(__APPLE__)
#include <yarp/os/Network.h>
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 
 @brief The class definition for the service viewer application class. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

/*! @brief Add connections between detected ports.
 @param theApp The application object.
 @param detectedPorts The set of detected YARP ports. */
static void addPortConnections(ServiceViewerApp *                    theApp,
                               const MplusM::Utilities::PortVector & detectedPorts)
{
    OD_LOG_ENTER();//####
    OD_LOG_P2("theApp = ", theApp, "detectedPorts = ", &detectedPorts);//####
    for (size_t ii = 0, mm = detectedPorts.size(); mm > ii; ++ii)
    {
        const MplusM::Utilities::PortDescriptor & aDescriptor = detectedPorts[ii];
        MplusM::Common::StringVector              inputs;
        MplusM::Common::StringVector              outputs;
        PortEntry *                               thisPort = theApp->findPort(aDescriptor._portName);
        
        if (thisPort)
        {
            MplusM::Utilities::GatherPortConnections(aDescriptor._portName, inputs, outputs,
                                                     MplusM::Utilities::kInputAndOutputOutput, true);
            for (int jj = 0, mm = outputs.size(); mm > jj; ++jj)
            {
                PortEntry * otherPort = theApp->findPort(outputs[jj]);
                
                if (otherPort)
                {
                    thisPort->addOutputConnection(otherPort);
                    otherPort->addInputConnection(thisPort);
                }
            }
        }
    }
    OD_LOG_EXIT();//####
} // addPortConnections

/*! @brief Add ports that have associates as 'adapter' entities.
 @param theApp The application object.
 @param detectedPorts The set of detected YARP ports. */
static void addPortsWithAssociates(ServiceViewerApp *                    theApp,
                                   const MplusM::Utilities::PortVector & detectedPorts)
{
    OD_LOG_ENTER();//####
    OD_LOG_P2("theApp = ", theApp, "detectedPorts = ", &detectedPorts);//####
    for (int ii = 0, mm = detectedPorts.size(); mm > ii; ++ii)
    {
        const MplusM::Utilities::PortDescriptor & aDescriptor = detectedPorts[ii];
        yarp::os::ConstString                     aPort(aDescriptor._portName);
        
        
        if (! theApp->findPort(aDescriptor._portName.c_str()))
        {
            MplusM::Common::StringVector inputs;
            MplusM::Common::StringVector outputs;
            bool                         isPrimary;
            
            if (MplusM::Utilities::GetAssociatedPorts(aDescriptor._portName, inputs, outputs, isPrimary, true))
            {
                if (isPrimary)
                {
                    ServiceEntity * anEntity = new ServiceEntity(PortPanel::kEntityKindClientOrAdapter, "", theApp);
                    
                    anEntity->setup((aDescriptor._portIpAddress + ":" + aDescriptor._portPortNumber).c_str());
                    for (int jj = 0, nn = inputs.size(); nn > jj; ++jj)
                    {
                        anEntity->addPort(inputs[jj], PortEntry::kPortUsageOther, PortEntry::kPortDirectionInput);
                    }
                    for (int jj = 0, nn = outputs.size(); nn > jj; ++jj)
                    {
                        anEntity->addPort(outputs[jj], PortEntry::kPortUsageOther, PortEntry::kPortDirectionOutput);
                    }
                    anEntity->addPort(aDescriptor._portName, PortEntry::kPortUsageClient,
                                      PortEntry::kPortDirectionInputOutput);
                    theApp->addEntity(anEntity);
                }
            }
        }
    }
    OD_LOG_EXIT();//####
} // addPortsWithAssociates

/*! @brief Add regular YARP ports as distinct entities.
 @param theApp The application object.
 @param detectedPorts The set of detected YARP ports. */
static void addRegularPortEntities(ServiceViewerApp *                    theApp,
                                   const MplusM::Utilities::PortVector & detectedPorts)
{
    OD_LOG_ENTER();//####
    OD_LOG_P2("theApp = ", theApp, "detectedPorts = ", &detectedPorts);//####
    for (size_t ii = 0, mm = detectedPorts.size(); mm > ii; ++ii)
    {
        const MplusM::Utilities::PortDescriptor & aDescriptor = detectedPorts[ii];
        
        if (! theApp->findPort(aDescriptor._portName.c_str()))
        {
            ServiceEntity * anEntity = new ServiceEntity(PortPanel::kEntityKindOther, "", theApp);
            
            anEntity->setup((aDescriptor._portIpAddress + ":" + aDescriptor._portPortNumber).c_str());
            anEntity->addPort(aDescriptor._portName, PortEntry::kPortUsageOther, PortEntry::kPortDirectionInputOutput);
            theApp->addEntity(anEntity);
        }
    }
    OD_LOG_EXIT();//####
} // addRegularPortEntities

/*! @brief Add services as distinct entities.
 @param theApp The application object.
 @param services The set of detected services. */
static void addServices(ServiceViewerApp *                   theApp,
                        const MplusM::Common::StringVector & services)
{
    OD_LOG_ENTER();//####
    OD_LOG_P2("theApp = ", theApp, "services = ", &services);//####
    for (size_t ii = 0, mm = services.size(); mm > ii; ++ii)
    {
        yarp::os::ConstString aService = services[ii];
        
        if (! theApp->findEntity(aService.c_str()))
        {
            MplusM::Utilities::ServiceDescriptor descriptor;

            if (MplusM::Utilities::GetNameAndDescriptionForService(aService, descriptor))
            {
                ServiceEntity * anEntity = new ServiceEntity(PortPanel::kEntityKindService,
                                                             descriptor._description.c_str(), theApp);
                
                anEntity->setup(descriptor._canonicalName);
                anEntity->addPort(aService, PortEntry::kPortUsageService, PortEntry::kPortDirectionInput);
                for (int jj = 0, nn = descriptor._inputChannels.size(); nn > jj; ++jj)
                {
                    anEntity->addPort(descriptor._inputChannels[jj], PortEntry::kPortUsageService,
                                      PortEntry::kPortDirectionInput);
                }
                for (int jj = 0, nn = descriptor._outputChannels.size(); nn > jj; ++jj)
                {
                    anEntity->addPort(descriptor._outputChannels[jj], PortEntry::kPortUsageService,
                                      PortEntry::kPortDirectionOutput);
                }
                theApp->addEntity(anEntity);
            }
        }
    }
    OD_LOG_EXIT();//####
} // addServices

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and destructors
#endif // defined(__APPLE__)

ServiceViewerApp::ServiceViewerApp(void) :
            inherited(), _firstAddPort(NULL), _firstRemovePort(NULL), _altActive(false), _commandActive(false),
            _controlActive(false), _networkAvailable(false), _registryAvailable(false), _shiftActive(false)
{
    OD_LOG_ENTER();//####
    OD_LOG_EXIT_P(this);//####
} // ServiceViewerApp::ServiceViewerApp

#if defined(__APPLE__)
# pragma mark Actions
#endif // defined(__APPLE__)

void ServiceViewerApp::addEntity(ServiceEntity * anEntity)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_P1("anEntity = ", anEntity);//####
    _entities.push_back(anEntity);
    OD_LOG_OBJEXIT();//####
} // ServiceViewerApp::addEntity

void ServiceViewerApp::dragEvent(ofDragInfo dragInfo)
{
    OD_LOG_OBJENTER();//####
    inherited::dragEvent(dragInfo);
    OD_LOG_OBJEXIT();//####
} // ServiceViewerApp::dragEvent

void ServiceViewerApp::draw(void)
{
//    OD_LOG_OBJENTER();//####
    ofBackgroundGradient(ofColor::white, ofColor::gray);
    if (_networkAvailable)
    {
        for (EntityList::iterator it(_entities.begin()); _entities.end() != it; ++it)
        {
            ServiceEntity * anEntity = *it;
            
            if (anEntity && (! anEntity->isSelected()))
            {
                anEntity->draw();
            }
        }
        for (EntityList::iterator it(_entities.begin()); _entities.end() != it; ++it)
        {
            ServiceEntity * anEntity = *it;
            
            if (anEntity && anEntity->isSelected())
            {
                anEntity->draw();
            }
        }
    }
    else
    {
        string      title = "The YARP network is not running";
        ofRectangle bbox = ofBitmapStringGetBoundingBox(title, 0, 0);
        ofMesh &    mesh = ofBitmapStringGetMesh(title, (ofGetWidth() - bbox.width) / 2,
                                                 (ofGetHeight() - bbox.height) / 2);
        
        ofEnableAlphaBlending();
        ofSetColor(ofColor::black);
		ofBitmapStringGetTextureRef().bind();
        mesh.draw();
		ofBitmapStringGetTextureRef().unbind();
        ofDisableAlphaBlending();
    }
//    OD_LOG_OBJEXIT();//####
} // ServiceViewerApp::draw

void ServiceViewerApp::exit(void)
{
    OD_LOG_OBJENTER();//####
    inherited::exit();
    OD_LOG_OBJEXIT();//####
} // ServiceViewerApp::exit

ServiceEntity * ServiceViewerApp::findEntity(string name)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_S1("name = ", name.c_str());//####
    ServiceEntity * result = NULL;
    
    for (EntityList::iterator it(_entities.begin()); _entities.end() != it; ++it)
    {
        ServiceEntity * anEntity = *it;
        
        if (anEntity && (name == anEntity->getName()))
        {
            result = anEntity;
            break;
        }
        
    }
    OD_LOG_OBJEXIT_P(result);//####
    return result;
} // ServiceViewerApp::findEntity

ServiceEntity * ServiceViewerApp::findEntityForPort(string name)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_S1("name = ", name.c_str());//####
    PortMap::iterator match(_ports.find(name));
    ServiceEntity *   result = NULL;
    
    if (_ports.end() != match)
    {
        for (EntityList::iterator it(_entities.begin()); _entities.end() != it; ++it)
        {
            ServiceEntity * anEntity = *it;
            
            if (anEntity && anEntity->hasPort(match->second))
            {
                result = anEntity;
                break;
            }
            
        }
    }
    OD_LOG_OBJEXIT_P(result);//####
    return result;
} // ServiceViewerApp::findEntityForPort

ServiceEntity * ServiceViewerApp::findEntityForPort(const PortEntry * aPort)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_P1("aPort = ", aPort);//####
    ServiceEntity *      result = NULL;
    
    for (EntityList::iterator it(_entities.begin()); _entities.end() != it; ++it)
    {
        ServiceEntity * anEntity = *it;
        
        if (anEntity && anEntity->hasPort(aPort))
        {
            result = anEntity;
            break;
        }
        
    }
    OD_LOG_OBJEXIT_P(result);//####
    return result;
} // ServiceViewerApp::findEntityForPort

PortEntry * ServiceViewerApp::findPort(string name)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_S1("name = ", name.c_str());//####
    PortEntry *       result;
    PortMap::iterator match(_ports.find(name));
    
    if (_ports.end() == match)
    {
        result = NULL;
    }
    else
    {
        result = match->second;
    }
    OD_LOG_OBJEXIT_P(result);//####
    return result;
} // ServiceViewerApp::findPort

void ServiceViewerApp::forgetPort(PortEntry * aPort)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_P1("aPort = ", aPort);//####
    if (aPort)
    {
        PortMap::iterator match(_ports.find(aPort->getName()));
        
        if (_ports.end() != match)
        {
            _ports.erase(match);
        }
    }
    OD_LOG_OBJEXIT();//####
} // ServiceViewerApp::forgetPort

void ServiceViewerApp::gatherEntities(void)
{
    OD_LOG_OBJENTER();//####
    MplusM::Common::StringVector services;
    
    MplusM::Utilities::GetServiceNames(services, true);
    addServices(this, services);
    MplusM::Utilities::PortVector detectedPorts;
    
    MplusM::Utilities::GetDetectedPortList(detectedPorts);
    // Identify and add ports that have associated ports, as they are adapters
    addPortsWithAssociates(this, detectedPorts);
    // Add regular YARP ports as distinct entities
    addRegularPortEntities(this, detectedPorts);
    // Add the connections
    addPortConnections(this, detectedPorts);
    OD_LOG_OBJEXIT();//####
} // ServiceViewerApp::gatherEntities

void ServiceViewerApp::gotMessage(ofMessage msg)
{
    OD_LOG_OBJENTER();//####
    inherited::gotMessage(msg);
    OD_LOG_OBJEXIT();//####
} // ServiceViewerApp::gotMessage

void ServiceViewerApp::keyPressed(int key)
{
//    OD_LOG_OBJENTER();//####
//    OD_LOG_L1("key = ", key);//####
    if (OF_KEY_ALT == (key & OF_KEY_ALT))
    {
        _altActive = true;
    }
    if (OF_KEY_COMMAND == (key & OF_KEY_COMMAND))
    {
        _commandActive = true;
    }
    if (OF_KEY_CONTROL == (key & OF_KEY_CONTROL))
    {
        _controlActive = true;
    }
    if (OF_KEY_SHIFT == (key & OF_KEY_SHIFT))
    {
        _shiftActive = true;
    }
    inherited::keyPressed(key);
//    OD_LOG_OBJEXIT();//####
} // ServiceViewerApp::keyPressed

void ServiceViewerApp::keyReleased(int key)
{
//    OD_LOG_OBJENTER();//####
//    OD_LOG_L1("key = ", key);//####
    if (OF_KEY_ALT == (key & OF_KEY_ALT))
    {
        _altActive = false;
    }
    if (OF_KEY_COMMAND == (key & OF_KEY_COMMAND))
    {
        _commandActive = false;
    }
    if (OF_KEY_CONTROL == (key & OF_KEY_CONTROL))
    {
        _controlActive = false;
    }
    if (OF_KEY_SHIFT == (key & OF_KEY_SHIFT))
    {
        _shiftActive = false;
    }
    inherited::keyReleased(key);
//    OD_LOG_OBJEXIT();//####
} // ServiceViewerApp::keyReleased

void ServiceViewerApp::mouseDragged(int x,
                                    int y,
                                    int button)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_L3("x = ", x, "y = ", y, "button = ", button);//####
    inherited::mouseDragged(x, y, button);
    OD_LOG_OBJEXIT();//####
} // ServiceViewerApp::mouseDragged

void ServiceViewerApp::mouseMoved(int x,
                                  int y)
{
//    OD_LOG_OBJENTER();//####
//    OD_LOG_L2("x = ", x, "y = ", y);//####
    inherited::mouseMoved(x, y);
//    OD_LOG_OBJEXIT();//####
} // ServiceViewerApp::mouseMoved

void ServiceViewerApp::mousePressed(int x,
                                    int y,
                                    int button)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_L3("x = ", x, "y = ", y, "button = ", button);//####
    inherited::mousePressed(x, y, button);
    reportPortEntryClicked(NULL, _altActive, _commandActive, _shiftActive);
    OD_LOG_OBJEXIT();//####
} // ServiceViewerApp::mousePressed

void ServiceViewerApp::mouseReleased(int x,
                                     int y,
                                     int button)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_L3("x = ", x, "y = ", y, "button = ", button);//####
    inherited::mouseReleased(x, y, button);
    OD_LOG_OBJEXIT();//####
} // ServiceViewerApp::mouseReleased

void ServiceViewerApp::rememberPort(PortEntry * aPort)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_P1("aPort = ", aPort);//####
    if (aPort)
    {
        _ports.insert(PortMap::value_type(static_cast<string>(*aPort), aPort));
    }
    OD_LOG_OBJEXIT();//####
} // ServiceViewerApp::rememberPort

void ServiceViewerApp::reportPortEntryClicked(PortEntry * aPort,
                                              const bool  altIsActive,
                                              const bool  commandIsActive,
                                              const bool  shiftIsActive)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_P1("aPort = ", aPort);//####
    OD_LOG_B3("altIsActive = ", altIsActive, "commandIsActive = ", commandIsActive, "shiftIsActive = ",//####
              shiftIsActive);//####
    
    if (aPort)
    {
        if (commandIsActive)
        {
            // Process connection delete requests.
            PortEntry::PortDirection direction = aPort->getDirection();
            
            if (_firstRemovePort)
            {
                ServiceEntity * firstEntity = findEntityForPort(_firstRemovePort);
                
                if (_firstRemovePort != aPort)
                {
                    // Check if we can end here.
                    if (PortEntry::kPortDirectionOutput != direction)
                    {
                        ServiceEntity * secondEntity = findEntityForPort(aPort);
                        
                        if (firstEntity && secondEntity)
                        {
                            if (MplusM::Utilities::RemoveConnection(_firstRemovePort->getPortName().c_str(),
                                                                    aPort->getPortName().c_str()))
                            {
                                _firstRemovePort->removeOutputConnection(aPort);
                                aPort->removeInputConnection(_firstRemovePort);
                            }
                        }
                    }
                }
                if (firstEntity)
                {
                    firstEntity->clearDisconnectMarker();
                    _firstRemovePort = NULL;
                }
            }
            else
            {
                // Check if we can start from here.
                if (PortEntry::kPortDirectionInput != direction)
                {
                    ServiceEntity * entity = findEntityForPort(aPort);
                    
                    if (entity)
                    {
                        entity->setDisconnectMarker();
                        _firstRemovePort = aPort;
                    }
                }
            }
        }
        else if (shiftIsActive)
        {
            // Process connection add requests.
            PortEntry::PortDirection direction = aPort->getDirection();
            
            if (_firstAddPort)
            {
                // Check if we can end here.
                ServiceEntity * firstEntity = findEntityForPort(_firstAddPort);
                
                if (_firstAddPort != aPort)
                {
                    if (PortEntry::kPortDirectionOutput != direction)
                    {
                        ServiceEntity * secondEntity = findEntityForPort(aPort);
                        
                        if (firstEntity && secondEntity)
                        {
                            if (MplusM::Utilities::AddConnection(_firstAddPort->getPortName().c_str(),
                                                                 aPort->getPortName().c_str()))
                            {
                                _firstAddPort->addOutputConnection(aPort);
                                aPort->addInputConnection(_firstAddPort);
                            }
                        }
                    }
                }
                if (firstEntity)
                {
                    firstEntity->clearConnectMarker();
                    _firstAddPort = NULL;
                }
            }
            else
            {
                // Check if we can start from here.
                if (PortEntry::kPortDirectionInput != direction)
                {
                    ServiceEntity * entity = findEntityForPort(aPort);
                    
                    if (entity)
                    {
                        entity->setConnectMarker();
                        _firstAddPort = aPort;
                    }
                }
            }
        }
    }
    else
    {
        // Operation being cleared.
        if (commandIsActive)
        {
            // Process connection delete requests.
            if (_firstRemovePort)
            {
                ServiceEntity * entity = findEntityForPort(_firstRemovePort);
                
                if (entity)
                {
                    entity->clearDisconnectMarker();
                }
                _firstRemovePort = NULL;
            }
        }
        else if (shiftIsActive)
        {
            // Process connaction add requests.
            if (_firstAddPort)
            {
                ServiceEntity * entity = findEntityForPort(_firstAddPort);
                
                if (entity)
                {
                    entity->clearConnectMarker();
                }
                _firstAddPort = NULL;
            }
        }
    }
    OD_LOG_OBJEXIT();//####
} // ServiceViewerApp::reportPortEntryClicked

void ServiceViewerApp::setInitialEntityPositions(void)
{
    OD_LOG_OBJENTER();//####
//#if defined(TEST_GRAPHICS_)
    float fullHeight = ofGetHeight();
    float fullWidth = ofGetWidth();
    
    for (EntityList::iterator it(_entities.begin()); _entities.end() != it; ++it)
    {
        ServiceEntity * anEntity = *it;

        if (anEntity)
        {
            ofRectangle entityShape = anEntity->getShape();
            float       newX = ofRandom(fullWidth - entityShape.width);
            float       newY = ofRandom(fullHeight - entityShape.height);
            
            anEntity->setPosition(newX, newY);
        }
    }
//#else // ! defined(TEST_GRAPHICS_)
//#endif // ! defined(TEST_GRAPHICS_)
    OD_LOG_OBJEXIT();//####
} // ServiceViewerApp::setInitialEntityPositions

void ServiceViewerApp::setup(void)
{
    OD_LOG_OBJENTER();//####
    ofSetWindowTitle("Service Viewer");
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
#if CheckNetworkWorks_
    if (yarp::os::Network::checkNetwork())
#endif // CheckNetworkWorks_
    {
        _networkAvailable = true;
        gatherEntities();
        setInitialEntityPositions();
    }
#if CheckNetworkWorks_
    else
    {
        OD_LOG("! (yarp::os::Network::checkNetwork())");//####
        cerr << "YARP network not running." << endl;
        _networkAvailable = false;
    }
#endif // CheckNetworkWorks_
    OD_LOG_OBJEXIT();//####
} // ServiceViewerApp::setup

void ServiceViewerApp::update(void)
{
//    OD_LOG_OBJENTER();//####
    ofLogVerbose() << "updating";
    inherited::update();
//    OD_LOG_OBJEXIT();//####
} // ServiceViewerApp::update

void ServiceViewerApp::updateEntityList(ServiceEntity * anEntity)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_P1("anEntity = ", anEntity);//####
    if (anEntity->isSelected())
    {
        EntityList::iterator it(_entities.begin());
        
        for ( ; _entities.end() != it; ++it)
        {
            ServiceEntity * anEntity = *it;
            
            if (anEntity && anEntity->isSelected())
            {
                _entities.erase(it);
                addEntity(anEntity);
                break;
            }
            
        }
    }
    OD_LOG_OBJEXIT();//####
} // ServiceViewerApp::updateEntityList

void ServiceViewerApp::windowResized(int w,
                                     int h)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_L2("w = ", w, "h = ", h);//####
    inherited::windowResized(w, h);
    OD_LOG_OBJEXIT();//####
} // ServiceViewerApp::windowResized

#if defined(__APPLE__)
# pragma mark Accessors
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)
