/*
 * @file   http_response.hpp
 * @date   2011-09-05
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


namespace ec2 {
  namespace http {
    int HTTP_CONTINUE=100;
      int HTTP_SWITCHING_PROTOCOLS=101;
      int HTTP_PROCESSING=102;
      int HTTP_OK=200;
      int HTTP_CREATED=201;
      int HTTP_ACCEPTED=202;
      int HTTP_NON_AUTHORITATIVE=203;
      int HTTP_NO_CONTENT=204;
      int HTTP_RESET_CONTENT=205;
      int HTTP_PARTIAL_CONTENT=206;
      int HTTP_MULTI_STATUS=207;
      int HTTP_MULTIPLE_CHOICES=300;
      int HTTP_MOVED_PERMANENTLY=301;
      int HTTP_MOVED_TEMPORARILY=302;
      int HTTP_SEE_OTHER=303;
      int HTTP_NOT_MODIFIED=304;
      int HTTP_USE_PROXY=305;
      int HTTP_TEMPORARY_REDIRECT=307;
      int HTTP_BAD_REQUEST=400;
      int HTTP_UNAUTHORIZED=401;
      int HTTP_PAYMENT_REQUIRED=402;
      int HTTP_FORBIDDEN=403;
      int HTTP_NOT_FOUND=404;
      int HTTP_METHOD_NOT_ALLOWED=405;
      int HTTP_NOT_ACCEPTABLE=406;
      int HTTP_PROXY_AUTHENTICATION_REQUIRED=407;
      int HTTP_REQUEST_TIME_OUT=408;
      int HTTP_CONFLICT=409;
      int HTTP_GONE=410;
      int HTTP_LENGTH_REQUIRED=411;
      int HTTP_PRECONDITION_FAILED=412;
      int HTTP_REQUEST_ENTITY_TOO_LARGE=413;
      int HTTP_REQUEST_URI_TOO_LARGE=414;
      int HTTP_UNSUPPORTED_MEDIA_TYPE=415;
      int HTTP_RANGE_NOT_SATISFIABLE=416;
      int HTTP_EXPECTATION_FAILED=417;
      int HTTP_UNPROCESSABLE_ENTITY=422;
      int HTTP_LOCKED=423;
      int HTTP_FAILED_DEPENDENCY=424;
      int HTTP_UPGRADE_REQUIRED=426;
      int HTTP_INTERNAL_SERVER_ERROR=500;
      int HTTP_NOT_IMPLEMENTED=501;
      int HTTP_BAD_GATEWAY=502;
      int HTTP_SERVICE_UNAVAILABLE=503;
      int HTTP_GATEWAY_TIME_OUT=504;
      int HTTP_VERSION_NOT_SUPPORTED=505;
      int HTTP_VARIANT_ALSO_VARIES=506;
      int HTTP_INSUFFICIENT_STORAGE=507;
      int HTTP_NOT_EXTENDED=510;
  } // namespace http
} // namespace ec2
