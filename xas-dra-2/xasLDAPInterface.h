/************************************************************************                        xasLDAPInterface.h - Copyright breo**************************************************************************/#ifndef XASLDAPINTERFACE_H#define XASLDAPINTERFACE_H#include <string>#include "xasDirectoryInterface.h"using namespace std; /**  * class xasLDAPInterface  */class xasLDAPInterface// : public xasDirectoryInterface  // : public ... xera un erro "undefined reference to `vtable...".{private:	string ldap_address;		public:	  // Constructors/Destructors			xasLDAPInterface(string addr);		// Empty Destructor	~xasLDAPInterface();  // public attribute accessor methods  //    /**   * @return bool   * @param  usr   * @param  pass   * @param  kind_of_user   */  bool checkUserCredentials (string usr, string pass, string kind_of_user );};#endif // XASLDAPINTERFACE_H
