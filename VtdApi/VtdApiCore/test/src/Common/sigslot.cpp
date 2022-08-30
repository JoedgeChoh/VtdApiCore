#include <gtest/gtest.h>

#include <cstdio>
#include <string>
//#define SIGSLOT_PURE_ISO 1 // TODO [BB]: think about it, threading shouldn't be a problem
#include <sigslot/sigslot.h>

#define __signals //Definition enables usage in class declaration
#define __slots   //Definition enables usage in class declaration

#define DBG(FMT,...) printf("%s: " FMT "\n", __PRETTY_FUNCTION__, ##__VA_ARGS__)


/**************** SigSlotGeneralTest ****************/
class A: public sigslot::has_slots<>, public sigslot::has_signals<A> {
public:
    A()
    {
        connect(signalIntEmission, this, &A::slotIntEmission);
        connect(signalSomethingHappened, this, &A::slotHandleSomething);
    }

    void doStuff() {
        DBG("");
        signalIntEmission(42);
    }

public __slots:
    void slotIntEmission(int i) {
        DBG("i = %d", i);
        signalSomethingHappened();
    }

    void slotHandleSomething() {
        DBG("");
    }

public __signals:
    sigslot::signal<int> signalIntEmission;
    sigslot::signal<> signalSomethingHappened;
    sigslot::signal<std::string&> signalStringEmission;
};

class B: public sigslot::has_slots<> {
public:
    B(A* a) :
        signalProxySignal(a->signalIntEmission)
    {
        a->signalIntEmission.connect(this, &B::slotIntEmission);
        a->signalStringEmission.connect(this, &B::slotStringEmission);
    }

public __slots:
    void slotIntEmission(int i) {
        DBG("i = %d", i);
    }

    void slotStringEmission(std::string& str) {
        DBG("str = %s", str.c_str());
        str += ", World!";
    }

public __signals:
    sigslot::signal<int> signalProxySignal;
};

TEST(VtdApiTest, SigSlotGeneralTest) {
    A a;
    B b(&a);

    a.doStuff();

    std::string str = "Hello";
    a.signalStringEmission(str);

    DBG("str = %s", str.c_str());
    EXPECT_TRUE(strcmp (str.c_str(),"Hello, World!") == 0);

    printf("\n");

    b.signalProxySignal(1);
}



/**************** SigSlotApiMockTest ****************/
class NetworkHandlerMock : public sigslot::has_signals<NetworkHandlerMock> {
public __signals:
    sigslot::signal<std::string&> signalMessageEmission;
};

class VtdApiMock : public sigslot::has_signals<VtdApiMock> {
public:
    VtdApiMock(NetworkHandlerMock* networkHandler) :
        networkHandler_(networkHandler)
    {
    }

    void StartReceiveRdbMessages() {  // TODO [BB]: ugly solution, necessary to finally get emitted signals, but it hides NetworkHandler away from Receiver
        networkHandler_->signalMessageEmission = signalMessageEmission;
    }

private:
    NetworkHandlerMock* networkHandler_;
public __signals:
    sigslot::signal<std::string&> signalMessageEmission;
};

class ReceiverMock : public sigslot::has_slots<> {
public:
    ReceiverMock(VtdApiMock* vtdApi)
    {
        vtdApi->signalMessageEmission.connect(this, &ReceiverMock::slotStringEmission);
        vtdApi->StartReceiveRdbMessages();   // TODO [BB]: ugly solution, necessary to finally get emitted signals, but it hides NetworkHandler away from Receiver
    }

public __slots:
    void slotStringEmission(std::string& str) {
        DBG("str = %s", str.c_str());
        str += ", VTD!";
    }
};

TEST(VtdApiTest, SigSlotApiMockTest) {
    NetworkHandlerMock* networkHandler = new NetworkHandlerMock();
    VtdApiMock* vtdApi = new VtdApiMock(networkHandler);
    ReceiverMock receiver(vtdApi);

    std::string str = "Hello";
    networkHandler->signalMessageEmission(str);
    DBG("str = %s", str.c_str());

    EXPECT_TRUE(strcmp (str.c_str(),"Hello, VTD!") == 0);
}
