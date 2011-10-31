/*
 * @file   ec2.hpp
 * @date   2011-08-09
 *
 * Created by Kai Krueger <kai.krueger@itwm.fraunhofer.de>
 *
 * Copyright (c) 2011 Fraunhofer ITWM
 * All rights reserved.
 * 
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#ifndef _ec2_hpp_
#define _ec2_hpp_
#ifdef _WIN32
# define strcasecmp _stricmp
#else
#  include <strings.h>
#endif /* _WIN32 */

#include <string>
#include <map>
#include <iterator>

#include <botan/botan.h>

#include <ec2-api/EC2Exception.hpp>

#include <ec2-api/RequestCore.hpp>
#include <ec2-api/RequestObserver.hpp>

#include <ec2-api/parse/types.hpp>

//#define EC2_DEBUG 1

namespace ec2 {

  const std::string EC2_HOSTNAME("ec2.amazonaws.com");
  
  struct ciLessLibC : public std::binary_function<std::string, std::string, bool> {
    bool operator()(const std::string &lhs, const std::string &rhs) const {
      return strcasecmp(lhs.c_str(), rhs.c_str()) < 0 ? 1 : 0;
    }
  };

  typedef std::map<const std::string, std::string>  Map_Type;

  class CFRuntime {
  public:
    CFRuntime(ec2::RequestObserver::Ptr);
    CFRuntime(ec2::RequestObserver::Ptr, std::string key, std::string access_key, std::string account_id);
    ~CFRuntime();
    xml::parse::type::EC2Response_t authenticate(std::string action, const Map_Type &opt
                                                 , const std::string &domain = EC2_HOSTNAME
                                                 , const std::string &expected_response = "Response"
                                                 );

    /* update parameters */
    void ec2_access_key(const std::string &v) { _key = v;}
    void ec2_secret_key(const std::string &v) { _secret_key= v;}
    void ec2_account_id(const std::string &v) { _account_id= v;}
    //void ec2_access_key(const std::string &v) { = v;}
    
    /* EC2 Command API */
    xml::parse::type::EC2Response_t     AuthorizeSecurityGroupIngress(const Map_Type &opt);
    xml::parse::type::EC2Response_t     CreateSecurityGroup(const std::string &groupName, const std::string groupDescription);
    xml::parse::type::EC2Response_t     DescribeImages(const Map_Type &opt);
    xml::parse::type::EC2Response_t     DescribeInstances();
    xml::parse::type::EC2Response_t     DescribeSecurityGroups(const Map_Type &opt);
    xml::parse::type::EC2Response_t     RunInstances(const Map_Type &opt);
    xml::parse::type::EC2Response_t     TerminateInstances(const Map_Type &opt);

    void print(const Map_Type &arr);
    void setDebug();
    void unsetDebug();
    
  private:
    std::string to_signable_string(const Map_Type &arr);
    std::string to_query_string(const Map_Type &arr);

    std::string encode_signature2(const std::string &str);
    std::string hash_hmac(const std::string &hash, const std::string &string_to_sign, const std::string &secret_key);

    std::string urlencode(const std::string url);
    std::string char2hex( char dec );
    std::string urldecode(const std::string encodedurl);
    const std::string uuidGenerate();

#ifdef EC2_DEBUG 
    xml::parse::type::EC2Response_t _fake_RunInstances();
#endif

  private:
    RequestObserver::Ptr _observer;
    std::string    _key;         /**> EC2_ACCESS_KEY */
    std::string    _secret_key;  /**> EC2_SECRET_KEY */
    std::string    _account_id;  /**> EC2_USER */
    unsigned short _api_version; /**< Api Version 2 */

    std::string _auth_token;

    RequestCore::Ptr _request;
    
    std::string _hostname;
  };
    
} // name ec2
#endif /* _ec2_hpp_ */
