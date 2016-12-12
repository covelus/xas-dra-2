/************************************************************************
                        xasConfigStore.cpp - Copyright breo

**************************************************************************/

#include <string>

using namespace std;

#include "xasConfigStore.h"
#include "xasConfigManager.h"


// Constructors/Destructors
//  

// CONFIG MUST BE IN A XML FILE.

xasConfigStore::xasConfigStore ( int control )
{
    xasConfigManager *confLoader = new xasConfigManager();
    int itemsParsed = confLoader->loadFromXmlFile("xasfiles/xas_config.xml", data);
    
    if ( itemsParsed == 0 )
    {
    	control = 0;
         //Se entra aqu, problema... ERRRRRRRRRRRRRRRRRRRRRRRRROOOOOOOOOOOOOOO
    }
    
}

/*
xasConfigStore::xasConfigStore ( ) {
  initAttributes();
}
*/


xasConfigStore::~xasConfigStore ( ) 
{ 
}

// private attribute accessor methods
//  


/**
 * Set the value of dir_ldap
 * @param new_var the new value of dir_ldap
 */
void xasConfigStore::setDir_dap ( string ddap ) 
{
  data.dir_dap = ddap;
}


/**
 * Get the value of dir_ldap
 * @return the value of dir_ldap
 */
string xasConfigStore::getDir_dap ( ) 
{
  return data.dir_dap;
}


/**
* Set the value of kind_of_dap
* @param dap the new value of kind_of_dap
*/
void xasConfigStore::setKind_of_dap ( string dap )
{
     data.kind_of_dap = dap;
}


/**
* Get the value of kind_of_dap
* @return the value of kind_of_dap
*/
string xasConfigStore::getKind_of_dap ( )
{
       return data.kind_of_dap;
}


/**
 * Set the value of ip_bdMngLabs
 * @param new_var the new value of ip_bdMngLabs
 */
void xasConfigStore::setIP_bdMngLabs ( string ipbd ) 
{
  data.ip_bdMngLabs = ipbd;
}


/**
 * Get the value of ip_bdMngLabs
 * @return the value of ip_bdMngLabs
 */
string xasConfigStore::getIP_bdMngLabs ( ) 
{
  return data.ip_bdMngLabs;
}


/**
* Set the value of kind_of_dbms
* @param new_var the new value of kind_of_dbms
*/
void xasConfigStore::setKind_of_dbms ( string kbd ) 
{
  data.kind_of_dbms = kbd;
}


/**
* Get the value of kind_of_dbms
* @return the value of kind_of_dbms
*/
string xasConfigStore::getKind_of_dbms ( ) 
{
  return data.kind_of_dbms;
}


/**
 * Set the value of lang_used_fileName
 * @param new_var the new value of lang_used_fileName
 */
void xasConfigStore::setLang_used_fileName ( string langf ) 
{
  data.lang_used_file = langf;
}


/**
 * Get the value of lang_used_fileName
 * @return the value of lang_used_fileName
 */
string xasConfigStore::getLang_used_fileName ( ) 
{
  return data.lang_used_file;
}


/**
 * Set the value of kind_of_lang_file
 * @param new_var the new value of kind_of_lang_file
 */
void xasConfigStore::setKind_of_lang_file ( string klf ) 
{
  data.kind_of_lang_file = klf;
}


/**
 * Get the value of default_lang_used
 * @return the value of kind_of_lang_file
 */
string xasConfigStore::getKind_of_lang_file ( ) 
{
  return data.kind_of_lang_file;
}


/**
* Set the value of kind_of_login
* @param new_var the new value of kind_of_login
*/
void xasConfigStore::setKind_of_login ( string kl ) 
{
  data.kind_of_login = kl;
}


/**
* Get the value of kind_of_login
* @return the value of kind_of_login
*/
string xasConfigStore::getKind_of_login ( ) 
{
  return data.kind_of_login;
}



// Other methods
//  


