#include <iostream>
#include <string>

using namespace std;

// Implementor interface
class MessageSender {
public:
    virtual void sendMessage(string text) = 0; 
    virtual ~MessageSender() {}
};

// Concrete Implementors
class EmailSender : public MessageSender {
public:
    void sendMessage(string text) override {
        cout << "[Email] " << text << endl;
    }
};

class SMSSender : public MessageSender {
public:
    void sendMessage(string text) override {
        cout << "[SMS] " << text << endl;
    }
};

// Abstraction
class Notification {
protected:
    MessageSender* sender; // the "bridge" to the implementation
public:
    Notification(MessageSender* s) : sender(s) {}
    virtual void send(string text) = 0;
    virtual ~Notification() {}
};

// Refined Abstractions
class SimpleNotification : public Notification {
public:
    SimpleNotification(MessageSender* s) : Notification(s) {}
    void send(string text) override {
        sender->sendMessage(text);
    }
};

class UrgentNotification : public Notification {
public:
    UrgentNotification(MessageSender* s) : Notification(s) {}
    void send(string text) override {
        sender->sendMessage("URGENT: " + text);
    }
};

int main() {
    EmailSender email;
    SMSSender sms;

    Notification* n1 = new SimpleNotification(&email);
    Notification* n2 = new UrgentNotification(&sms);
    Notification* n3 = new UrgentNotification(&email);

    n1->send("Your order has been shipped.");
    n2->send("Server CPU usage is above 90 percent.");
    n3->send("Password changed successfully.");

    delete n1;
    delete n2;
    delete n3;
    
    return 0;
}