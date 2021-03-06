#ifndef __SHM_TOPIC_HPP__
#define __SHM_TOPIC_HPP__

#include "ros/ros.h"
#include "shm_publisher.hpp"
#include "shm_subscriber.hpp"

namespace shm_transport
{

class Topic
{
public:
  Topic(const ros::NodeHandle & parent) {
    nh_ = parent;
  }

  ~Topic() {
  }

  template < class M >
  Publisher advertise(const std::string & topic, uint32_t queue_size, uint32_t mem_size) {
    ros::Publisher pub = nh_.advertise< std_msgs::UInt64 >(topic, queue_size);
    return Publisher(pub, topic, mem_size);
  }

  template < class M >
  Subscriber< M > subscribe(const std::string & topic, uint32_t queue_size, void(*fp)(const boost::shared_ptr< const M > &)) {
    SubscriberCallbackHelper< M > * phlp = new SubscriberCallbackHelper< M >(topic, fp);
    ros::Subscriber sub = nh_.subscribe(topic, queue_size, &SubscriberCallbackHelper< M >::callback, phlp);
    return Subscriber< M >(sub, phlp);
  }

private:
  ros::NodeHandle nh_;
};

} // namespace shm_transport

#endif // __SHM_TOPIC_HPP__


