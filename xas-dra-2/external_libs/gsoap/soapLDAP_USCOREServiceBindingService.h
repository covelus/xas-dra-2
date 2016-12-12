/* soapLDAP_USCOREServiceBindingService.h
   Generated by gSOAP 2.7.9k from ldapws.h
   Copyright(C) 2000-2007, Robert van Engelen, Genivia Inc. All Rights Reserved.
   This part of the software is released under one of the following licenses:
   GPL, the gSOAP public license, or Genivia's license for commercial use.
*/

#ifndef soapLDAP_USCOREServiceBindingService_H
#define soapLDAP_USCOREServiceBindingService_H
#include "soapH.h"
class SOAP_CMAC LDAP_USCOREServiceBindingService : public soap
{ public:
	/// Constructor
	LDAP_USCOREServiceBindingService();
	/// Constructor with engine input+output mode control
	LDAP_USCOREServiceBindingService(soap_mode iomode);
	/// Constructor with engine input and output mode control
	LDAP_USCOREServiceBindingService(soap_mode imode, soap_mode omode);
	/// Destructor frees all data
	virtual ~LDAP_USCOREServiceBindingService();
	/// Initializer used by constructor
	virtual	void LDAP_USCOREServiceBindingService_init(soap_mode imode, soap_mode omode);
	/// Return a copy
	virtual	LDAP_USCOREServiceBindingService *copy();
	/// Disables and removes SOAP Header from message
	virtual	void soap_noheader();
	/// Run simple single-thread iterative service on port until a connection error occurs (returns error code or SOAP_OK), use this->bind_flag = SO_REUSEADDR to rebind for a rerun
	virtual	int run(int port);
	/// Bind service to port (returns master socket or SOAP_INVALID_SOCKET)
	virtual	SOAP_SOCKET bind(const char *host, int port, int backlog);
	/// Accept next request (returns socket or SOAP_INVALID_SOCKET)
	virtual	SOAP_SOCKET accept();
	/// Serve this request (returns error code or SOAP_OK)
	virtual	int serve();
	/// Used by serve() to dispatch a request (returns error code or SOAP_OK)
	virtual	int dispatch();
	/// Service operations (you should define these):
	/// Web service operation 'autentificar' (return error code or SOAP_OK)
	virtual	int autentificar(std::string login, std::string password, std::string usuario, std::string &success);
};
#endif
