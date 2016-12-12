/************************************************************************
                        xasShellUserInterface.cpp - Copyright breo

**************************************************************************/

#include "xasShellUserInterface.h"

#include "xasGlobals.h"


#include <iostream>

using namespace std;


// Constructors/Destructors
//  

xasShellUserInterface::xasShellUserInterface ( ) 
{
  
}

xasShellUserInterface::~xasShellUserInterface ( ) 
{ 
  
}

//  
// Methods
//  




/**
 * Message
 * @param  strMsg
 */
void xasShellUserInterface::sendMsg ( string strMsg ) 
{
     cout << endl << "XAS: " << strMsg << endl;

}

/**
* Erro normal que non abortar a execucin do programa.
* @param  errStr
*/
void xasShellUserInterface::sendnHandleErrMsg ( string errStr ) 
{
     //xasConfigStore: updateConfigStore()
     cout << endl << "XAS ERROR Message: " << errStr << endl;

}
/**
* @param  errStr
*/
void xasShellUserInterface::sendnHandleConfigErrMsg (string errStr ) 
{
     cout << endl << "XAS CONFIGURATION ERROR Notification: " << errStr << endl;
     //xasConfigStore: updateConfigStore() instead of ////////////////////////////////////////
     enableSessionStart = false; // "xasGlobals.h"

}


/**
* Para cando algn erro crtico se produza.
* Non se poder comprobar a posibilidade de inicio de sesin e abortarase
* @param  errStr
*/
void xasShellUserInterface::sendnHandleCriticalErrMsg ( string errStr ) 
{
	
     cout << endl << "XAS CRITICAL ERROR Notification: " << errStr << endl;
	
     enableSessionStart = false; // "xasGlobals.h"

}


  /** 
   * ask and set the private values of login and passwd
   */
void xasShellUserInterface::askUserData(string tittle_tag, string login_tag, string pass_tag)
{

	string loginName, pass;

	this->sendMsg(tittle_tag);

	this->sendMsg(login_tag);
	cin>>loginName;
	this->setLogin(loginName);

	pass = getpass( pass_tag.c_str() );

	this->setPass(pass);
}


// Accessor methods
//  

/**
 * @param  new_data
 */
void xasShellUserInterface::setLogin (string new_data ) 
{
     login = new_data;

}


/**
 * @param  new_data
 */
void xasShellUserInterface::setPass (string new_data ) 
{
     passwd = new_data;

}


/**
 * @param  new_data
 */
void xasShellUserInterface::setKind_of_user (string new_data )
{
	kind_of_user = new_data;
}


/**
 * @return string
 */
string xasShellUserInterface::xasShellUserInterface::getLogin ( ) 
{
       return login;

}


/**
 * @return string
 */
string xasShellUserInterface::getPass ( ) 
{
       return passwd;

}


/**
 * @return string
 */
string xasShellUserInterface::getKind_of_user ( ) 
{
       return kind_of_user;

}

// Other methods
//  

