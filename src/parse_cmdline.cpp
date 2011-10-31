/*
 * @file   parse_cmdline.cpp
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

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <boost/program_options.hpp>

#include <parse_cmdline.hpp>


namespace po = boost::program_options;



namespace ec2 {
  typedef std::map< std::string,  std::string>  ParameterMap_Type;
  

  template <typename T, int N>char (&array2(T(&)[N]))[N];

  std::pair<std::string, std::string> init2[] = {
    std::pair<std::string, std::string> ( "private-key", "AWSAccessKeyId" ),
    //std::pair<std::string, std::string> ( "", "SecurityToken" ),
    std::pair<std::string, std::string> ( "owner", "Owner.1" ),
    //std::pair<std::string, std::string> ( "", "" ),
    //std::pair<std::string, std::string> ( "", "" ),
    //std::pair<std::string, std::string> ( "", "" )
  };

  std::map< std::string,  std::string> opt2key2 ( init2, init2 + sizeof array2 ( init2 ) );

} // namespace ec2


void ec2::parse_cmdline(
  int argc
  , char **argv
  , const po::options_description &specific
  )
{
  try {
    po::options_description general("GENERAL OPTIONS");
    general.add_options()
      ("private-key,K",po::value< std::string >(), "Specify KEY as the private key to use. Defaults to the value of the "
       "EC2_PRIVATE_KEY environment variable (if set). Overrides the default.")
      ("cert,C",po::value< std::string >(), "Specify CERT as the X509 certificate to use. Defaults to the value "
       "of the EC2_CERT environment variable (if set). Overrides the default.")
      ("url,U",po::value< std::string>(), "Specify URL as the web service URL to use. Defaults to the value of "
       "'https://ec2.amazonaws.com' or to that of the EC2_URL environment "
       "variable (if set). Overrides the default.")
      ("region", po::value< std::string>(), "Specify REGION as the web service region to use."
       "This option will override the URL specified by the \"-U URL\" option"
       "and EC2_URL environment variable.")

      ("help,h,?", "this help message")
      ("verbose,v", "verbose output")
      ("debug","Display additional debugging information.")

   ;
      
    
    po::options_description cmdline_options;
    cmdline_options.add(general).add(specific);


    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, cmdline_options), vm);
    po::notify(vm);

    if (vm.count("help")) {
      std::cout << cmdline_options << std::endl;
    }

    // print variables
  po::variables_map::iterator it;
  for ( it=vm.begin() ; it != vm.end(); it++ ) {
    std::cout << (*it).first << " = ";
    //std::cout << " => " << vm.get((*it).first).value();
    //std::cout << vm[(*it).first].as<std::string>();
    std::cout << (*it).second.as<std::string>();
    std::cout<< std::endl;
  }

  } catch(std::exception &e){
    throw;
  }
}

const po::options_description &ec2::option_describe_images()
{
  static po::options_description specific("SPECIFIC OPTIONS");
  specific.add_options()
    ("all,a", po::value< std::string >(), "Describe all AMIs, public, private or owned, that the user has access to.")
    ("owner,o", po::value< std::string >(), "OWNER Only AMIs owned by the users specified are described. OWNER may either be a"
     "user's account id for images owned by that user, 'self' for images owned by"
     "you, or 'amazon' for images owned by Amazon.")
    ("executable-by,x",po::value< std::string >(), " USER"
     "Only AMIs with launch permissions as specified are described. USER may either"
     "be a user's account id for AMIs owned by you for which the user has explicit"
     "launch permissions, 'self' for AMIs you have explicit launch permissions for,"
     "or 'all' for AMIs with public launch permissions.")
    ;

  return specific;
}




/*
 * Local variables:
 *  tab-width: 2
 *  c-indent-level: 2
 *  c-basic-offset: 2
 *  project-name: ec2-api
 * End:
 */
