/************************************************************************
                        xasShellUserInterface.h - Copyright breo

**************************************************************************/


#ifndef XASSHELLUSERINTERFACE_H
#define XASSHELLUSERINTERFACE_H

#include "xasUserInterface.h"

//#include "xasGlobals.h"

#include <iostream>

using namespace std;


/**
  * class xasShellUserInterface
  */


class xasShellUserInterface : public xasUserInterface
{

public:

  // Constructors/Destructors
  //


  /**
   * Empty Constructor
   */
  xasShellUserInterface ( );

  /**
   * Empty Destructor
   */
  ~xasShellUserInterface ( );



  /**
   * @param  strMsg
   */
  void sendMsg (string strMsg );

  /**
   * @param  errStr
   */
  void sendnHandleErrMsg (string errStr );

  /**
   * @param  errStr
   */
  void sendnHandleCriticalErrMsg (string errStr );

  /**
   * @param  errStr
   */
  void sendnHandleConfigErrMsg (string errStr );

  /**
   * ask and set the private values of login and passwd
   */
  void askUserData(string tittle_tag, string login_tag, string pass_tag);


  /**
   * @return string
   */
  string getLogin ( );


  /**
   * @return string
   */
  string getPass ( );


  /**
   * @return string
   */
  string getKind_of_user ( );


  /**
   * @param  pass
   */
  void setKind_of_user (string kind );


  // protected attribute accessor methods
  //

protected:



  /**
   * @param  name
   */
  void setLogin (string name );


  /**
   * @param  pass
   */
  void setPass (string pass );


protected:

  string login;
  string passwd;
  string kind_of_user;



};


#endif // XASSHELLUSERINTERFACE_H
