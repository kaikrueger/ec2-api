/*
 * @file   ec2Command.cpp
 * @date   2011-10-17
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

#include <string>

#include <ec2Command.hpp>

using namespace ec2;

namespace ec2 {
  typedef std::map< std::string,  std::string>  ParameterMap_Type;
  

  template <typename T, int N>char (&array(T(&)[N]))[N];

  std::pair<std::string, std::string> init[] = {
    std::pair<std::string, std::string> ( "private-key", "AWSAccessKeyId" )
    //, std::pair<std::string, std::string> ( "", "SecurityToken" )
    , std::pair<std::string, std::string> ( "owner", "Owner.1" )
    , std::pair<std::string, std::string> ( "executable-by", "ExecutableBy.1" )
    , std::pair<std::string, std::string> ( "group", "SecurityGroup.1" )
    , std::pair<std::string, std::string> ( "instance-type", "InstanceType" )
    , std::pair<std::string, std::string> ( "kernel", "KernelId" )
    , std::pair<std::string, std::string> ( "ramdisk", "RamdiskId" )
    //, std::pair<std::string, std::string> ( "", "" )
    //, std::pair<std::string, std::string> ( "", "" ),
    //, std::pair<std::string, std::string> ( "", "" )
    //, std::pair<std::string, std::string> ( "", "" ),
    //, std::pair<std::string, std::string> ( "", "" )
  };

  std::map< std::string,  std::string> opt2key ( init, init + sizeof array ( init ) );

} // namespace ec2

ec2Command::ec2Command(const ec2::options::optionCommand::Ptr specific) :
    _Observer(ec2::RequestObserver::Ptr(new ec2::SimpleRequestObserver()))
    , _sdk(_Observer)
    , _url(ec2::EC2_HOSTNAME) /* value defined in ec2.hpp */
    , _Command(specific)
{
}

void ec2Command::_command(const std::string &arg) 
{
  size_t pos = arg.rfind("/");    // position of "live" in str

  if(pos>0) _commandStr = arg.substr (pos+1);
  else      _commandStr = arg;
}

void ec2Command::Run(
  int argc
  , char **argv
)
{
  _command(argv[0]);
  
  if(_parse_commandline(argc, argv)) return;

  _sdk.print(_opt);
  _ret = _sdk.authenticate(_Command->command(), _opt, _url, _Command->resptag());
  _Command->printResponse(_ret);
}


bool ec2Command::_parse_commandline(
  int argc
  , char **argv
  )
{
  try {
    po::options_description env;
    env.add_options()
      ("private_key", po::value< std::string >())
      ("cert", po::value< std::string >())
      ("url", po::value< std::string >())
      ("user", po::value< std::string >())
      ("access_key", po::value< std::string >())
      ("secret_key", po::value< std::string >())
      ("user_id", po::value< std::string >())
      ("jvm_args", po::value< std::string >())
      ;
    po::variables_map vmEnv;
    po::store(po::parse_environment(env, "EC2_"), vmEnv);
    po::notify(vmEnv);
    
    po::variables_map vm;
    po::parsed_options parsed = 
      po::command_line_parser(argc, argv).options(_Command->cmdline_options()).allow_unregistered().run();      
    std::vector<std::string> rest = po::collect_unrecognized(parsed.options, po::include_positional);

    //po::store(parsed, vm);
    po::store(po::parse_command_line(argc, argv, _Command->cmdline_options()), vm);
    po::notify(vm);

    // print variables

    if (vm.count("help")) {
      //std::cout << cmdline_options << std::endl;
      _Command->help();
      return true;
    }

    if (vm.count("debug")) {
      _sdk.setDebug();
    }

    if (vm.count("private-key")) {
      _sdk.ec2_access_key(vm["private-key"].as<std::string>());
    } else {
      if(vmEnv.count("access_key")) {
        _sdk.ec2_access_key(vmEnv["access_key"].as<std::string>());
      }
    }
    
    if (vm.count("cert")) {
      _sdk.ec2_secret_key(vm["cert"].as<std::string>());
    } else {
      if(vmEnv.count("secret_key")) {
        _sdk.ec2_secret_key(vmEnv["secret_key"].as<std::string>());
      }
    }
    
    if (vm.count("url")) {
      _url = vm["url"].as<std::string>();
    } else {
      if(vmEnv.count("url")) {
        _url = vmEnv["url"].as<std::string>();
      }
    }
    

    po::variables_map::iterator it;
    for ( it=vm.begin() ; it != vm.end(); it++ ) {
      std::map< std::string, std::string>::iterator itkey = opt2key.find((*it).first);
      if(itkey != opt2key.end()) {
        _opt[opt2key[(*it).first]] = (*it).second.as<std::string>();
      }
    }
    _Command->setOptions(vm, rest, _opt);
    
  } catch(std::exception &e){
    throw;
  }
  return false;
}
