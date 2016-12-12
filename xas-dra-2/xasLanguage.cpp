/************************************************************************                        xasLanguage.cpp - Copyright breo**************************************************************************/#include <string>using namespace std;#include "xasLanguage.h"//#include "xasConfigStore.h"#include "xasConfigManager.h"// Constructors/Destructors//  xasLanguage::xasLanguage ( string langFileName ){	this->initAttributes();    xasConfigManager *confLoader = new xasConfigManager();    int itemsParsed = confLoader->loadFromXmlFile(langFileName, data);        if ( itemsParsed == 0 )    {    	this->initAttributes();         //Se entra aqu, problema...     }}xasLanguage::xasLanguage ( ) {  initAttributes();}xasLanguage::~xasLanguage ( ) { }//  // Methods//  // Accessor methods//  /** * Get the value of lang_name * @return the value of data.lang_name */string xasLanguage::getLang_name ( ) {  return data.lang_name;}/** * Get the value of normal_error * @return the value of data.normal_error */string xasLanguage::getNormal_error ( ) {  return data.normal_error;}/** * Get the value of serious_error * @return the value of data.serious_error */string xasLanguage::getSerious_error ( ) {  return data.serious_error;}/** * Get the value of invalid_dap_credentials * @return the value of data.nvalid_dap_credentials */string xasLanguage::getInvalid_ldap_credentials ( ) {  return data.invalid_dap_credentials;}/** * Get the value of no_conection_error * @return the value of data.no_conection_error */string xasLanguage::getNo_conection_error ( ) {  return data.no_conection_error;}/** * Get the value of mysql_real_connect_error * @return the value of data.mysql_real_connect_error */string xasLanguage::getMysql_real_connect_error ( ) {  return data.mysql_real_connect_error;}/** * Get the value of attempting2connect * @return the value of data.attempting2connect */string xasLanguage::getAttempting2connect ( ) {  return data.attempting2connect;}/*** Get the value of tittle_tag* @return the value of data.tittle_tag*/string xasLanguage::getTittle_tag ( ){       return data.tittle_tag;}    /*** Get the value of login_tag* @return the value of data.login_tag*/string xasLanguage::getLogin_tag ( ){     return data.login_tag;}/*** Get the value of pass_tag* @return the value of data.pass_tag*/string xasLanguage::getPass_tag ( ){     return data.pass_tag;}/*** Get the value of ok_tag* @return the value of data.ok_tag*/string xasLanguage::getOK_tag ( ){     return data.ok_tag;}/*** Get the value of cancel_tag* @return the value of data.cancel_tag*/string xasLanguage::getCancel_tag ( ){     return data.cancel_tag;}/*** Get the value of restart_tag* @return the value of data.restart_tag*/string xasLanguage::getRestart_tag ( ){     return data.restart_tag;}/*** Get the value of shutdown_tag* @return the value of data.shutdown_tag*/string xasLanguage::getShutdown_tag ( ){     return data.shutdown_tag;}/*** Get the value of * @return the value of data.*/string xasLanguage::getExceptionMsg () {       return data.exception; }/*** Get the value of * @return the value of data.*/// Other methods//  void xasLanguage::initAttributes ( ) {  data.lang_name = "English";    data.normal_error = "Error.";    data.serious_error = "Serious error. Talk with admin";    data.invalid_dap_credentials = "Invalid credentials: the given username or password doesn't match with directory server data";    data.mysql_real_connect_error = "Database error (mysql_real_connect)";    data.no_conection_error = "Serious error: no conection. Please, talk with network admin";    data.attempting2connect = "Attempting to connect. Please, wait";    data.tittle_tag = "Breo's XAS Login System. User authentication phase";    data.login_tag = "Login name?";    data.pass_tag = "Password?";    data.ok_tag = "Start session";    data.cancel_tag = "Cancel";    data.restart_tag = "Restart computer";    data.shutdown_tag = "Shutdown computer";    data.exception = "Exception";}