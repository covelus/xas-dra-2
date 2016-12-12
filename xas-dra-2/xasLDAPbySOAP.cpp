/************************************************************************
                   xasLDAPbySOAP.cpp - Copyright breo
**************************************************************************/

#include <string>

#include <cstring>

#include <stdlib.h>

#include "xasLDAPInterface.h"

#include "external_libs/gsoap/soapLDAP_USCOREServiceBindingProxy.h"
#include "external_libs/gsoap/LDAP_USCOREServiceBinding.nsmap"


using namespace std;

// Constructors/Destructors

xasLDAPInterface::xasLDAPInterface ( string addr ) {
	ldap_address = addr;
}


// Empty Destructor
xasLDAPInterface::~xasLDAPInterface(){

}

// Other methods
//

/**
 * @return bool
 * @param  usr
 * @param  pass
 */
bool xasDirectoryInterface::checkUserCredentials (string usr, string pass, string &kind_of_user ) {
	bool toRet = false;


	LDAP_USCOREServiceBindingProxy service;

	string success_result;

	if ( service.autentificar(usr, pass, kind_of_user, success_result)  == SOAP_OK ){
		toRet = true;
		kind_of_user = success_result;
	}

	return toRet;
}



