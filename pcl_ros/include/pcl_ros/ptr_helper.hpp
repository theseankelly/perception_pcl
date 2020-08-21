//
//  ptr_helper.h
//  perception_pcl
//
//  Created by Andreas Klintberg on 5/1/19.
//  Copyright © 2019 Andreas Klintberg. All rights reserved.
//

#ifndef _PCL_ROS__PTR_HELPER_HPP_
#define _PCL_ROS__PTR_HELPER_HPP_

#include <boost/shared_ptr.hpp>
#include <memory>
#include <utility>

// https://stackoverflow.com/a/12605002/1829511

namespace
{
template<class SharedPointer>
struct Holder
{
  SharedPointer p;

  explicit Holder(const SharedPointer & p)
  : p(p) {}
  Holder(const Holder & other)
  : p(other.p) {}
  Holder(Holder && other)
  : p(std::move(other.p)) {}

  void operator()(...) {p.reset();}
};
}  // namespace

template<class T>
std::shared_ptr<T> to_std_ptr(const boost::shared_ptr<T> & p)
{
  typedef Holder<std::shared_ptr<T>> H;
  if (H * h = boost::get_deleter<H>(p)) {
    return h->p;
  } else {
    return std::shared_ptr<T>(p.get(), Holder<boost::shared_ptr<T>>(p));
  }
}

template<class T>
boost::shared_ptr<T> to_boost_ptr(const std::shared_ptr<T> & p)
{
  typedef Holder<boost::shared_ptr<T>> H;
  if (H * h = std::get_deleter<H>(p)) {
    return h->p;
  } else {
    return boost::shared_ptr<T>(p.get(), Holder<std::shared_ptr<T>>(p));
  }
}

#endif  // _PCL_ROS__PTR_HELPER_HPP_
