//
// Created by vovan on 31.03.2020.
//

#ifndef OBSERVER_TEST_EVENT_H
#define OBSERVER_TEST_EVENT_H

#include <iostream>
#include <functional>

#define EVENT_HAVE_CLIENT           0
#define EVENT_HAVE_NO_CLIENT        1
#define EVENT_DATA_IS_PREPARED      2

#define EVENT_TYPE_A                0
#define EVENT_TYPE_B                1
#define EVENT_TYPE_C                2
#define EVENT_TYPE_D                3


/**these is a class of Event in WS-system, these class contains information about happened an event
 * idEvent - private field used for differ event's
 * eventType - private field used for differ assignment handler's
 *
 * EventWS(...) - public constructor of event
 * int getEventID() - public function for getting the idEvent's value
 * int getEventType() - public function fro getting the eventType's value*/
class EventWS {
private:
    int idEvent;
    int eventType;

public:
    EventWS(int idEvent, int eventType) {
        this->idEvent = idEvent;
        this->eventType = eventType;
    }

    int getEventID() {
        return idEvent;
    }

    int getEventType() {
        return eventType;
    }
};


/**There is the abstract class of an event's handler class in the WS-system
 * eventType - protected field used for differ assignment handler's
 *
 * HandleWS() - a protected constructor of the class HandlerWS
 * virtual void handleEventsWS(...) - public funtion with empty realization for overloading in extended classes
 * int getEventType() - public function fro getting the eventType's value*/
class HandlerWS {
public:
    virtual void handleEventWS(EventWS& event) {}

    int getEventType() {
        return eventType;
    }

protected:
    int eventType;

    HandlerWS() {
        this->eventType = EVENT_TYPE_A;
    }
};

/**These is an event's delegator in WS-system, used for delegating an events and handlers.
 * Builded by singleton pattern, give only one instance of DelegateWS
 *
 * static DelegateWS* getInstance() - only one way to get the instance of DelegateWS object
 * void addEvent(EventWS& eventWS) - function for adding new events in the events' queue
 * void addHandler (HandlerWS& handlerWS) - function for adding new handlers in the handlers' queue */
class DelegateWS {
private:
    static DelegateWS* p_instance;
    std::list<HandlerWS*> m_handlers;
    std::list<EventWS*> m_events;

    DelegateWS() {}
    DelegateWS(const DelegateWS&);
    DelegateWS& operator= (DelegateWS&);

public:
    static DelegateWS* getInstance() {
        if (!p_instance)
            p_instance = new DelegateWS();
        return p_instance;
    }

    void handleEvens(){
        for (EventWS* event: m_events) {
            int eventType = event->getEventType();
            for (HandlerWS* handler: m_handlers) {
                if (eventType == handler->getEventType())
                    handler->handleEventWS(*event);
            }
        }
        m_events.clear();
    }

    void addEvent(EventWS& eventWS) {
        m_events.push_back(&eventWS);
    }

    void addHandler (HandlerWS& handlerWS) {
        m_handlers.push_back(&handlerWS);
    }
};

DelegateWS* DelegateWS::p_instance = 0;

#endif //OBSERVER_TEST_EVENT_H
