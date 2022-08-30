#include <VtdNetwork/MessageCallback.h>
#include <boost/lexical_cast.hpp>

namespace VTD
{
    MessageCallback::MessageCallback() : directModeActive_(false) {}

    MessageCallback::~MessageCallback(){}

    void MessageCallback::updateRDBdeque(const std::vector<char>& bufferRDBData, const ConnectionHandle& handle)
    {
        //fprintf(stderr, "  updateRDBdeque: %zd\n", rdbDeque_.size());
        if (!directModeActive_)
        {
            // don't actually take the locks yet
            boost::unique_lock<boost::mutex> lock1(mutex1_, boost::defer_lock);
            boost::unique_lock<boost::mutex> lock2(mutex2_, boost::defer_lock);
            boost::lock(lock1, lock2);
            rdbDeque_.push_back(boost::shared_ptr<ReceiveRDB>(new ReceiveRDB (bufferRDBData, handle)));
        }
        else
        {
            //Call registered callbacks directly (callbacks are running in the thread-context of the boost::asio::service)
            const ReceiveRDB msg(bufferRDBData, handle);
            for (std::multimap<ConnectionHandle, MessageHandler>::iterator itr = handleRDBMessages_.begin(); itr != handleRDBMessages_.end(); ++itr)
            {
                if (itr->first == handle)
                {
                    itr->second(&msg);
                }
            }
        }
    }

    void MessageCallback::updateSCPdeque(const std::vector<char>& bufferSCPData, const boost::array<char, SCP_HEADER_SIZE>& bufferSCPHdr, const ConnectionHandle& handle)
    {
        //fprintf(stderr, "  updateSCPdeque1: %zd\n", scpDeque_.size());
        if (!directModeActive_)
        {
            // don't actually take the locks yet
            boost::unique_lock<boost::mutex> lock1(mutex1_, boost::defer_lock);
            boost::unique_lock<boost::mutex> lock2(mutex2_, boost::defer_lock);
            boost::lock(lock1, lock2);
            // message done - update should handle data with callback from outside [TODO]
            scpDeque_.push_back(boost::shared_ptr<ReceiveSCP>(new ReceiveSCP(bufferSCPData.size(), bufferSCPData, bufferSCPHdr, handle)));
        }
        else
        {
            //Call registered callbacks directly (callbacks are running in the thread-context of the boost::asio::ioservice)
            const ReceiveSCP msg(bufferSCPData.size(), bufferSCPData, bufferSCPHdr, handle);
            for (std::vector<MessageHandler>::iterator itr = callbackScp_.begin(); itr != callbackScp_.end(); ++itr)
            {
                (*itr) (&msg);
            }
       }
    }

    void MessageCallback::update()
    {
        if (directModeActive_)
        {
            //In directMode all messages are delivered directly by boost::asio::ioservice-thread, so this update() is a no-op
            return;
        }

        // call all rdb callback function
        updateRDB();
        // call all scp callback function
        updateSCP();
    }

    void MessageCallback::updateSCP()
    {
        // don't actually take the locks yet
        boost::unique_lock<boost::mutex> lock1(mutex1_, boost::defer_lock);
        boost::unique_lock<boost::mutex> lock2(mutex2_, boost::defer_lock);
        boost::lock(lock1, lock2);
        if (scpDeque_.empty())
            return;
        // call all callback function
        while(!scpDeque_.empty())
        {
            for (std::vector<MessageHandler>::iterator itr = callbackScp_.begin(); itr != callbackScp_.end(); ++itr)
            {
                (*itr)(scpDeque_.front().get());
            }
            // delete first data in deque
            scpDeque_.pop_front();
        }
    }

    void MessageCallback::updateRDB()
    {
        // To be change with asio work and strand, and with post, also mutex to be remove B.Zivanov und replace with for example spin lock
        boost::unique_lock<boost::mutex> lock1(mutex1_, boost::defer_lock);
        boost::unique_lock<boost::mutex> lock2(mutex2_, boost::defer_lock);
        boost::lock(lock1, lock2);
        if (rdbDeque_.empty())
            return;
        // call all callback function
        while(!rdbDeque_.empty())
        {
            for (std::multimap<ConnectionHandle, MessageHandler>::iterator itr = handleRDBMessages_.begin(); itr != handleRDBMessages_.end(); ++itr)
            {
                if (itr->first == rdbDeque_.front()->partner_)
                {
                    itr->second(rdbDeque_.front().get());
                }
            }
            // delete first data in deque
            rdbDeque_.pop_front();
        }
    }
}
