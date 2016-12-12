/************************************************************************
					xas_disableExit.h - Copyright breo

**************************************************************************/


#ifndef XAS_DISABLEEXIT_H
#define XAS_DISABLEEXIT_H

#include <string>

//#include "external_libs/tinyxml/tinyxml.h"
#include <vector>
#include <stdexcept>

using namespace std;


/**
  * class xasConfigManager
  * Auxiliary class for use when we read each XML item
  */
class XMLItem {
	public:
		std::string name;	//! Main data, the purpose of the file
		std::string mtime;	//!item identifier
		std::string type;	//!item description
		std::string value; //!item text

		XMLItem() : name(""), mtime(""), type(""), value("") {}


	 	string getGconfName(void) {
               return name;
        }
	 	string getGconfMtime(void) {
               return mtime;
        }
	 	string getGconfType(void) {
               return type;
        }

	 	string getGconfValue(void) {
               return value;
        }
	 	string setGconfValue(string new_val) {
               value = new_val;
        }
};

/*
<gconf>
        <entry name="disable_log_out" mtime="1229267516" type="bool" value="false">
        </entry>
</gconf>
*/


/**
  * class xas_disableExit
  *
  */

class xas_disableExit
{

private:
	string gconf_pathNFile; // /home/<username>/.gconf/apps/panel/global/%gconf.xml
	string userHome;
	string username;
	string groupname;
	string gconf_xmlTemplate;
	string gconf_xmlFileName;
	string xas_auxFilesPath;

public:

	// Constructors/Destructors
	//

	xas_disableExit ( string user, string group  );

	/**
	* Empty Destructor
	*/
	~xas_disableExit ( );


	bool askIfFileExists();
	bool createFile();
	bool touchFile();
	// ...NOT ON THIS VERSION:
//	bool addTheMagicContent(); // it will give the XML code to the file
//	bool set_disable_log_outValue( );
//	bool set_disable_log_outValue( bool value );


protected:



};

#endif // XAS_DISABLEEXIT_H


