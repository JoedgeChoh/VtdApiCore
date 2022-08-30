#include "Timeout.h"

Timeout::Timeout() : timer_(io_)
{
    setTimer(10);
    callback_ = 0;
}

Timeout::Timeout(const unsigned int& timeoutSec) : timer_(io_)
{
    setTimer(timeoutSec);
    callback_ = 0;
}

Timeout::~Timeout()
{
}

void Timeout::setTimer(const int& timeout)
{
    timer_.expires_from_now(boost::chrono::seconds(timeout));
}

void Timeout::startTimer()
{
    timer_.async_wait(boost::bind(&Timeout::on_timeout, this, boost::asio::placeholders::error));
    io_.run();
}

void Timeout::on_timeout(const boost::system::error_code& e)
{
  if (e != boost::asio::error::operation_aborted)
  {
    std::cout << "Timer was not cancelled, take necessary action" << std::endl;
    if (callback_ != 0)
            callback_();
  }
}

void Timeout::stopTimer()
{
    timer_.cancel();
}

void Timeout::registerCallback(const Callback_f& callback)
{
    callback_ = callback;
}
