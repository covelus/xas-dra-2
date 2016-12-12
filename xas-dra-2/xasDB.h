/************************************************************************
                        xasDB.h - Copyright breo

**************************************************************************/

#ifndef XASDB_H
#define XASDB_H

#include <string>

using namespace std;


/**
  * class xasDB
  * Clase Abstracta, clase con funcións virtuais puras. (Abstract Class, with pure virtual methods)
  */

class xasDB
{

public:

  // Constructors/Destructors
  //

  /**
   * @param  ip
   * @return string
   * It returns the string lab ID or "error <and an optonial explanation>" in other case
   */
  virtual string getLabIdByIP(string ip) = 0;


  /**
   * @param  lab
   * @return string
   * It returns the string matter or purpose ID or "error <and an optonial explanation>" in other case
   */
  virtual string getMatterAtCurrentTime(string lab) = 0;


  /**
   * @param  lab
   * @return string
   * It returns the string group ID or "error <and an optonial explanation>" in other case
   */
  virtual string getIdGroupAtCurrentTime(string lab) = 0;


  /**
   * @param  lab
   * @return string
   * It returns the string career or department ID or "error <and an optonial explanation>" in other case
   */
  virtual string getCareerAtCurrentTime(string lab) = 0;


  /**
   * @param  login, group, purpose_or_matter, job_or_career
   * @return int
   * It returns a positive value if the user can login, 0 if he/she can't or -1 if an error has occurred
   */
  virtual int canUserBeThere(string login, string group, string purpose_or_matter, string job_or_career) = 0;


  /**
   * @param  login, idLab, IP
   * @return bool
   * It returns true if the log can be updated or false in other case
   */
  virtual bool updateLogs(string login, string idLab, string IP) = 0;

  /**
   * @return string
   */
  virtual string getHostIP() = 0;
  // protected attribute accessor methods
  //

protected:



};

#endif // XASDB_H
