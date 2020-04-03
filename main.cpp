#include <iostream>
#include "my_events/event_handler.h"

class MyHandlerA: public HandlerWS {
public:
    MyHandlerA() {
        this->eventType = EVENT_TYPE_A;
    }

    void handleEventWS(EventWS& event) {
        std::cout << "Nothing happens A" << event.getEventID() << std::endl;
    }
};

class MyHandlerB: public HandlerWS {
public:
    MyHandlerB() {
        this->eventType = EVENT_TYPE_B;
    }

    void handleEventWS(EventWS& event) {
        std::cout << "Nothing happens B" << event.getEventID() << std::endl;
    }
};

int main( int argc, char *argv[] ){
    MyHandlerA* handlerA = new MyHandlerA();
    MyHandlerB* handlerB = new MyHandlerB();

    DelegateWS* delegateWs = DelegateWS::getInstance();
    EventWS* eventWs = new EventWS(EVENT_HAVE_NO_CLIENT, EVENT_TYPE_A);
    EventWS* eventWs1 = new EventWS(EVENT_HAVE_CLIENT, EVENT_TYPE_B);


    delegateWs->addHandler((HandlerWS&) *handlerA);
    delegateWs->addHandler((HandlerWS&) *handlerB);

    delegateWs->addEvent(*eventWs);
    delegateWs->addEvent(*eventWs1);

    delegateWs->handleEvens();

    std::cout << "OK_1" << std::endl;
    return 0;
}
