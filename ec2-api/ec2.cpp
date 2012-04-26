/*
 * @file   ec2.cpp
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

#include <sstream>
#include <iostream>
#include <stdexcept>

#ifdef WIN32
#  include <objbase.h>
#  include <rpcdce.h>
#else /* WIN32 */
#  include <uuid/uuid.h>
#endif /* WIN32 */

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


#include <botan/hmac.h>
#include <botan/sha2_32.h>

#include <ec2-api/ec2.hpp>

#include <ec2-api/CurlRequest.hpp>

#include <parse/parse.hpp>

using namespace ec2;

using namespace boost::posix_time;

/*
  valid Action Command
  DescribeKeyPairs

  DescribeInstances

  Action=TerminateInstances&InstanceId.1=i-3ea74257

  Action=RunInstances&ImageId=ami-60a54009
      MinCount=1&MaxCount=1
      SecurityGroup.1=
      InstanceType=

  Action=DescribeImages
      &ImageId.1=ami-be3adfd7
      &Owner.1=self
*/

CFRuntime::CFRuntime(ec2::RequestObserver::Ptr observer) :
    _observer(observer)
    , _api_version(2)
    , _auth_token("")
    , _request(new ec2::CurlRequest("", ""))
{
}

CFRuntime::CFRuntime(
  ec2::RequestObserver::Ptr observer
  , std::string key
  , std::string access_key
  , std::string account_id
  ) :
    _observer(observer)
    , _key(key)
    , _secret_key(access_key)
    , _account_id(account_id)
    , _api_version(2)
    , _auth_token("")
    , _request(new ec2::CurlRequest("", ""))
{
}

CFRuntime::~CFRuntime() {
}

void parse_url(const std::string& url, std::string& domain, std::string& path)
{
  domain=std::string();
  path=std::string();

  std::string::const_iterator p=url.begin();
  int state=0;
  while(p!=url.end())
  {
    switch(state)
    {
      case 0: if(*p=='/') {state=1;p++;}
         break;
      case 1: if(*p!='/') {domain+=*p;} else {state=2;path+='/';}
         break;
      case 2: path+=*p; 
    }
    p++;
  }
}

xml::parse::type::EC2Response_t CFRuntime::authenticate(
  std::string action
  , const Map_Type &opt
  , const std::string &domain
  , const std::string &expected_response
  ) {
  std::string signature_version("2");

  boost::posix_time::ptime pt = boost::posix_time::second_clock::local_time(); 
  boost::gregorian::date_facet *df = new boost::gregorian::date_facet("%Y-%m-%dT"); 
  std::ostringstream ss;
  ss.imbue(std::locale(std::cout.getloc(), df)); 
  ss <<  pt.date() << pt.time_of_day(); //<< "Z" ; 
  std::string timestamp = ss.str();
  

  Map_Type headers;
  Map_Type query;
  
  if( "" != _auth_token ) {
    headers["X-Amz-Security-Token"] = _auth_token;
    query["SecurityToken"] = _auth_token;
  }
  
  query["Action"] = action;
  
  if( 2 == _api_version ) {
    query["Version"]          = "2011-07-15";
    query["AWSAccessKeyId"]   = _key;
    query["SignatureMethod"]  = "HmacSHA256";
    query["SignatureVersion"] = signature_version;
    query["Timestamp"]        = timestamp;
  }
  
  // copy options
  Map_Type::const_iterator it;
  for(it = opt.begin(); it!=opt.end(); it++) {
    query.insert(*it);
  }

  // sort map?
  std::string canonical_query_string = to_signable_string(query);

  //


  std::string host_header;
  std::string request_uri;
  parse_url(domain,host_header,request_uri);
  request_uri+="/";
  
  if( "2" == signature_version ) {
    std::ostringstream string_to_sign;
    string_to_sign << "GET" << std::endl;
    string_to_sign << host_header << std::endl;
    string_to_sign << request_uri << std::endl;
    string_to_sign << canonical_query_string;
    query["Signature"] = hash_hmac("sha256", string_to_sign.str(), _secret_key);
  }

  //print(query);
  std::string querystring=to_query_string(query);
  std::ostringstream req;
  req <<"http://"<< host_header <<request_uri<< "?" << querystring;
 
  _request->set_request_url(req.str());
  _request->send_request(_observer);
  
  ec2::xml::parse::state::type state;
  std::stringstream iss;
  iss<<  _request->response_body();
  return ec2::xml::parse::parse_EC2Response (iss, state, expected_response);
}

/*
 * Short cuts
 */

xml::parse::type::EC2Response_t CFRuntime::AuthorizeSecurityGroupIngress(
 const Map_Type &opt
  )
{
  return authenticate("AuthorizeSecurityGroupIngress", opt, EC2_HOSTNAME, "AuthorizeSecurityGroupIngressResponse");
}

xml::parse::type::EC2Response_t CFRuntime::CreateSecurityGroup(
  const std::string &groupName
  , const std::string groupDescription
  )
{
  Map_Type opt;
  opt["GroupName"] = groupName;
  opt["GroupDescription"] = groupDescription;
  return authenticate("CreateSecurityGroup", opt, EC2_HOSTNAME);
}

xml::parse::type::EC2Response_t CFRuntime::DescribeImages(
  const Map_Type &opt
  )
{
  try {
    return authenticate("DescribeImages", opt, EC2_HOSTNAME, "DescribeImagesResponse");
  } catch (...) {
    throw; 
    //std::cout<<" E R R O R !!!  --- Cannot parse response:\n";
  }
  //return retval;
}

xml::parse::type::EC2Response_t CFRuntime::DescribeInstances()
{
  ec2::Map_Type opt;
  try {
    return authenticate("DescribeInstances", opt, EC2_HOSTNAME, "DescribeInstancesResponse");
  } catch (...) {
    throw;
    //std::cout<<" E R R O R !!!  --- Cannot parse response:\n";
  }
}

xml::parse::type::EC2Response_t CFRuntime::DescribeSecurityGroups(
  const Map_Type &opt
  ) 
{
  return authenticate("DescribeSecurityGroups", opt, EC2_HOSTNAME, "DescribeSecurityGroupsResponse");
}


xml::parse::type::EC2Response_t CFRuntime::RunInstances(
  const Map_Type &opt
  )
{
  Map_Type lopt = opt;
  lopt["ClientToken"]      = uuidGenerate();

  try {
    //return _fake_RunInstances();
    return authenticate("RunInstances", lopt, EC2_HOSTNAME, "RunInstancesResponse");
  } catch (...) {
    throw;
    //std::cout<<" E R R O R !!!  --- Cannot parse response:\n";
  }
}

xml::parse::type::EC2Response_t CFRuntime::TerminateInstances(
  const Map_Type &opt
  ) 
{
  //xml::parse::type::EC2Response_t retval;
  try {
    return authenticate("TerminateInstances", opt, EC2_HOSTNAME, "TerminateInstancesResponse");
  } catch (...) {
    throw;
  }
}

/* private methods */
std::string CFRuntime::to_signable_string(
  const Map_Type &arr
  ) {
  Map_Type::const_iterator it;

  std::ostringstream ret;
  for(it = arr.begin(); it!=arr.end(); it++) {
    if(it!=arr.begin()) ret << "&";
    ret << encode_signature2( (*it).first) << "=";
    ret << encode_signature2( (*it).second);
   }
 
  return ret.str();
}

std::string CFRuntime::to_query_string(
  const Map_Type &arr
  ) {
  Map_Type::const_iterator it;

  std::ostringstream ret;
  for(it = arr.begin(); it!=arr.end(); it++) {
    if(it!=arr.begin()) ret << "&";
    ret << urlencode( (*it).first) << "=";
    ret << urlencode( (*it).second);
  }
  return ret.str();
}

std::string CFRuntime::encode_signature2(const std::string &str) {
  std::string s = urlencode(str);
  //return str_replace('%7E', '~', $string);
  return s;
}

std::string CFRuntime::hash_hmac(
  const std::string &hash
  , const std::string &string_to_sign
  , const std::string &secret_key
  ) {
  Botan::SymmetricKey mac_key = Botan::SymmetricKey(
    reinterpret_cast<Botan::byte const *>(secret_key.data()),
    secret_key.size());

  Botan::Pipe pipe(
    new Botan::Chain(new Botan::MAC_Filter("HMAC(SHA-256)", mac_key)
                     , new Botan::Base64_Encoder
                     )
	  );
  pipe.start_msg();
  pipe.write(string_to_sign);
  pipe.end_msg();
  std::ostringstream oss;
  oss << pipe;
  return (oss.str());
}

void CFRuntime::print(const Map_Type &arr) 
{
  Map_Type::const_iterator it;

  for(it = arr.begin(); it!=arr.end(); it++) {
    std::cout<< "Var="<< (*it).first << "  Val="<< (*it).second << std::endl;
  }
  
}

void CFRuntime::setDebug() {
  _request->setDebug();
}

void CFRuntime::unsetDebug() {
  _request->unsetDebug();
}

std::string CFRuntime::urlencode(const std::string url)
{
  std::string escaped="";
  int max = url.length();
  for(int i=0; i<max; i++)
  {
    if ( (48 <= url[i] && url[i] <= 57) ||//0-9
         (65 <= url[i] && url[i] <= 90) ||//abc...xyz
         (97 <= url[i] && url[i] <= 122) || //ABC...XYZ
         (url[i]=='~' || url[i]=='!' || url[i]=='*' || url[i]=='(' || url[i]==')'
           || url[i]=='_' || url[i]=='.' || url[i]=='-' || url[i]=='\'')
         )
    {
      escaped.append( &url[i], 1);
    }
    else
    {
      escaped.append("%");
      escaped.append( char2hex(url[i]) );//converts char 255 to string "ff"
    }
  }
  return escaped;
}

std::string CFRuntime::char2hex( char dec )
{
  char dig1 = (dec&0xF0)>>4;
  char dig2 = (dec&0x0F);
  if ( 0<= dig1 && dig1<= 9) dig1+=48;    //0,48inascii
  if (10<= dig1 && dig1<=15) dig1+=65-10; //a,97inascii
  if ( 0<= dig2 && dig2<= 9) dig2+=48;
  if (10<= dig2 && dig2<=15) dig2+=65-10;

  std::string r;
  r.append( &dig1, 1);
  r.append( &dig2, 1);
  return r;
}
std::string CFRuntime::urldecode(const std::string encodedurl)
{
  std::string r("");
  return r;
}

const std::string CFRuntime::uuidGenerate() {
  std::string uuid_str = "";
  //std::ostringstream oss;
  //oss<<std::hex;

#ifdef WIN32
  ::GUID uuid;
  ::UuidCreateNil(&uuid);

  // Create a uuid with the Co Create GUID
  RPC_STATUS lhResult = ::UuidCreate( &uuid );

  if ( lhResult == RPC_S_UUID_NO_ADDRESS )
  {
    throw std::runtime_error(
      "GUIG::createGUID - Failed Creating GUID");
  }

  // Convert the GUID object to a string.
  unsigned char* guidStr = 0;

  RPC_STATUS result = ::UuidToString(
    const_cast<GUID*>(&uuid), &guidStr);

  if(result == RPC_S_OUT_OF_MEMORY)
  {
    throw std::runtime_error(
      "GUIG::createGUID - Failed Creating GUID");
  }

  uuid_str = (char*)guidStr;
  //oss << (char*)guidStr;

  // Dispose of the GUID string.
  ::RpcStringFree(&guidStr);
#else
  uuid_t uuid;
  memset(&uuid, 0, sizeof(uuid_t));
  uuid_generate(uuid);

  // Create storage for the string buffer
  char buffer[36] = {0};

  // parse the uuid to the string
  uuid_unparse(*(const_cast<uuid_t*>(&uuid)), buffer);

  // Store it in a string
  uuid_str = buffer;
  //for (size_t i=0; i<sizeof(uuid); i++) {
  //oss<<(int)uuid[i];
  //}
#endif
  return uuid_str;
  //return oss.str();
}

#ifdef EC2_DEBUG
xml::parse::type::EC2Response_t CFRuntime::_fake_RunInstances() {
  std::stringstream iss;
  ec2::xml::parse::state::type state;

  iss << RunInstancesResponse;
  return ec2::xml::parse::parse_EC2Response (iss, state);
}
#endif // EC2_DEBUG

/*
 * Local variables:
 *  tab-width: 2
 *  c-indent-level: 2
 *  c-basic-offset: 2
 * End:
 */
