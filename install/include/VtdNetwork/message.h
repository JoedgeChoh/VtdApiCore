#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <iostream>
#include <deque>
#include <stdio.h>
#include <boost/signals2.hpp>
#include <boost/array.hpp>

#include <VtdToolkit/viRDBIcd.h>
#include <VtdToolkit/scpIcd.h>

namespace VTD
{
    // common ports used by VTD
    static const unsigned int DEFAULT_SCP_PORT = 48179;
    static const unsigned int DEFAULT_RDB_PORT = 48190;
    static const unsigned int DEFAULT_UDP_RX_PORT = 48190;
    static const unsigned int DEFAULT_UDP_TX_PORT = 48191;
    // Comunication handle
    typedef uint32_t ConnectionHandle;
    // Typedef connection
    typedef boost::signals2::connection connection;
    // MessageId
    typedef int MessageId;
    // Header sizes
    static const int SCP_HEADER_SIZE = sizeof(SCP_MSG_HDR_t);
    static const int RDB_HEADER_SIZE = sizeof(RDB_MSG_HDR_t);
    // Base Message class
    class MessageBase
    {
        public:
            // Default constructors and destructors
            explicit MessageBase() {}
            virtual ~MessageBase() {}
        public:
           // Abstract method
           virtual MessageId getMessageId() const = 0;
           // Partner or handle
           ConnectionHandle partner_;
    };
    // Templated message class
    template<MessageId ID>
    class Message : public MessageBase
    {
        public:
            explicit Message () : MessageBase() {}
            virtual ~Message() {}
        public:
            // return message ID
            MessageId getMessageId() const { return MsgId;}
        public:
            static const MessageId MsgId = ID;
    };
    // types of messages
    /* add new enum for each new type of event*/
    enum MessageTypes : MessageId
    {
        MESSAGE_RDB,
        MESSAGE_SCP,
        MESSAGE_CONNECTION_EVENT,
        MESSAGES_VIRES
    };
    // class wrapper for reg. request
    template<typename REGREQUEST,typename MSG>
    class regRequest_wrapper
    {
        public:
            typedef REGREQUEST request;
            typedef MSG msg;

        public:
            explicit regRequest_wrapper(const request& req) : request_(req) {}

            ~regRequest_wrapper() {}

        public:
            void operator()(const msg* mes) { request_(mes);}
        private:
            request request_;
    };

    class OperWrapper
    {
        public:
            explicit OperWrapper() {}
            virtual ~OperWrapper() {}

        public:
            virtual void call(const MessageBase* msg) = 0;
            virtual void disconnect_all_slots() = 0;
        protected:
    };

    template<typename MSG>
    class OperWrapper_Templ : public OperWrapper
    {
        public:
            typedef MSG msg;

            typedef typename boost::signals2::signal<void(const msg*)> registration_manager;
            typedef typename registration_manager::slot_type registration_request;
            typedef regRequest_wrapper<registration_request,msg> request_wrapper;
            typedef typename boost::signals2::connection connection;

        public:
            connection connect(const registration_request&req)
            {
                return subscribers_.connect(request_wrapper(req));
            }

            void call(const MessageBase *message)
            {
                subscribers_(static_cast<const msg*>(message));
            }
            void disconnect_all_slots()
            {
                subscribers_.disconnect_all_slots();
            }
            connection disConnect(const registration_request&req)
            {
                return subscribers_.disconnect(request_wrapper(req));
            }
        private:
            registration_manager subscribers_;
    };

    class MessageHandler
    {
        public:

            typedef boost::signals2::connection connection;
            // Define the signal handlers
            OperWrapper* messageHandlers_[MESSAGES_VIRES];

        public:
            explicit MessageHandler()
            {
                for (size_t i=0; i < MESSAGES_VIRES; ++i)
                {
                    messageHandlers_[i] = NULL;
                }
            }

            virtual ~MessageHandler() {}

        public:

            void operator()(const MessageBase* basemsg)
            {
                handleMessage(basemsg);
            }

            void handleMessage(const MessageBase *basemsg)
            {
                const MessageId ID = basemsg->getMessageId();
                // Find handler
                OperWrapper*& handler = messageHandlers_[ID];
                if (!handler) return;

                // Call active handler
                handler->call(basemsg);
            }

            template<typename MSG, typename REQ>
            connection setHandler(const REQ& req)
            {
                typedef OperWrapper_Templ<MSG> wrapper;
                // Get message id
                const MessageId ID = MSG::MsgId;
                // Find handler
                OperWrapper*& ptr = messageHandlers_[ID];
                // Check if handler exist if not create new one
                if(!ptr)
                {
                    ptr = new wrapper();
                }

                wrapper* handler = static_cast<wrapper*>(ptr);
                return handler->connect(req);
            }

            template<typename MSG>
            void unsetHandler()
            {
                typedef OperWrapper_Templ<MSG> wrapper;
                // Get message id
                const MessageId ID = MSG::MsgId;
                // Find handler
                OperWrapper*& ptr = messageHandlers_[ID];
                // Check if handler exist if not create new one
                if(!ptr) return;
                // get connection handler
                wrapper* handler = static_cast<wrapper*>(ptr);
                handler->disconnect_all_slots();
            }


            template<typename MSG, typename REQ>
            connection unsetParHandler(const REQ& req)
            {
                typedef OperWrapper_Templ<MSG> wrapper;
                // Get message id
                const MessageId ID = MSG::MsgId;
                // Find handler
                OperWrapper*& ptr = messageHandlers_[ID];
                // get connection handler
                wrapper* handler = static_cast<wrapper*>(ptr);
                return handler->disConnect(req);
            }
    };

    class ReceiveRDB : public Message<MESSAGE_RDB>
    {
        public:
            explicit ReceiveRDB(const std::vector<char>& data, const ConnectionHandle& partner)
                : data_ (data)
            {
                partner_ = partner;
            }

            ReceiveRDB(){}

            virtual ~ReceiveRDB() {}

            size_t size_;
            std::vector<char> data_;
            const RDB_MSG_t& getData() const {return *reinterpret_cast<RDB_MSG_t*>((void*)data_.data());}
            size_t getSize() const {return data_.size();}

    };

    class ReceiveSCP : public Message<MESSAGE_SCP>
    {
    public:
            explicit ReceiveSCP(const size_t& size
                                , const std::vector<char>& data
                                , const boost::array<char, SCP_HEADER_SIZE>& headerData
                                , const ConnectionHandle& partner)
            : size_ (size)
            , data_ (data)
            , headerData_(headerData)
        {
            partner_ = partner;
        }
            virtual ~ReceiveSCP() {}

        boost::array<char, SCP_HEADER_SIZE> getHeaderData() const { return headerData_; }
        std::string getDataString() const { return std::string(data_.data(), data_.size());}



    private:
            size_t size_;
            std::vector<char> data_;
            boost::array<char, SCP_HEADER_SIZE> headerData_;
    };

    class ConnectionEvent : public Message<MESSAGE_CONNECTION_EVENT>
    {
    public:
        ConnectionEvent(const ConnectionHandle& handle, bool isConnected)
            : handle_(handle)
            , type_(isConnected ? CONNECT : DISCONNECT)
        { /**/ }

        enum Enum {
            UNDEFINED = 0,
            CONNECT,
            DISCONNECT
        };

        Enum getType() const { return type_; }

    private:
        const ConnectionHandle& handle_;
        Enum type_;
    };
    // data contaners
    typedef std::deque<boost::shared_ptr<ReceiveRDB> > RDBdeque;
    typedef std::deque<boost::shared_ptr<ReceiveSCP> > SCPdeque;
}
#endif // _MESSAGE_H_
