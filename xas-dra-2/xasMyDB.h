/************************************************************************
                        xasMyDB.h - Copyright breo

**************************************************************************/

#include "xasDB.h"

#ifndef XASMYDB_H
#define XASMYDB_H

// ----- ONLY IN WINDOWS VERSION ----

//#include <windows.h>

// ----- IN ALL VERSIONS ----

#include <mysql/mysql.h>
#include <mysql/mysqld_error.h>

#include <string>

#include "xasShellUserInterface.h"
#include "xasLanguage.h"


using namespace std;


/**
  * class xasMyDB
  * Clase que se comunicará coa base de datos estando esta nun SXBD MySQL
  */

class xasMyDB : public xasDB
{

private:
  MYSQL *pConnection;

  xasUserInterface *ui;
  xasLanguage *lng;

  string server_addr;
  string user;
  string passwd;
  string db_name;

public:

  // Constructors/Destructors
  //

  xasMyDB ( string server_address, string root_user, string password, string database_name, xasUserInterface *user_inter, xasLanguage *lang );

  /**
   * Empty Destructor
   */
  ~xasMyDB ( );



  /**
   * @param  ip
   * @return string
   * It returns the string lab ID or "error <and an optonial explanation>" in other case
   */
  string getLabIdByIP(string ip);


  /**
   * @param  lab
   * @return string
   * It returns the string matter or purpose ID or "error <and an optonial explanation>" in other case
   */
  string getMatterAtCurrentTime(string lab);


  /**
   * @param  lab
   * @return string
   * It returns the string group ID or "error <and an optonial explanation>" in other case
   */
  string getIdGroupAtCurrentTime(string lab);


  /**
   * @param  lab
   * @return string
   * It returns the string career or department ID or "error <and an optonial explanation>" in other case
   */
  string getCareerAtCurrentTime(string lab);


  /**
   * @param  login, group, purpose_or_matter, job_or_career
   * @return int
   * It returns a positive value if the user can login, 0 if he/she can't or -1 if an error has occurred
   */
  int canUserBeThere(string login, string group, string purpose_or_matter, string job_or_career);


  /**
   * @param  login, idLab, IP
   * @return bool
   * It returns true if the log can be updated or false in other case
   */
  bool updateLogs(string login, string idLab, string IP);

  /**
   * @return string
   */
  string getHostIP();

  // protected attribute accessor methods
  //

protected:



};

#endif // XASMYDB_H
