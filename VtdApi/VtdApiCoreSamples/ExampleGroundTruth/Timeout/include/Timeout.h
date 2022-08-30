#ifndef  _TIMEOUT_H
#define  _TIMEOUT_H

#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/chrono.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>

class Timeout
{
  public:
    // callback to be called after time out
    typedef boost::function<void()> Callback_f;
    /**
     * default constructor set time to 10 sec
     */
    Timeout();

    /**
     * @brief Timeout
     * @param time - time in sec
     */
    Timeout(const unsigned int& timeSec);

    /**
      * destructor
      */
    ~Timeout();

    /**
     * @brief setTimer - set timer
     * @param time - time in sec
     */
    void setTimer(const int& time);

    /**
     * @brief startTimer - async timer
     */
    void startTimer();

    /**
     * @brief stopTimer - stop async timer
     */
    void stopTimer();

    /**
     * @brief on_timeout
     * @param e - error code
     */
    void on_timeout(const boost::system::error_code& e);

    /**
     * @brief registerCallback
     * @param callback callback function type of void()
     */
    void registerCallback(const Callback_f& callback);
    // io service
    boost::asio::io_service io_;
    // staedy timer
    boost::asio::steady_timer timer_;
    // callback function
    Callback_f callback_;
};

#endif //_TIMEOUT_H
