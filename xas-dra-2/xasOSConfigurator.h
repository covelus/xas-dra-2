/************************************************************************
                        xasOSConfigurator.h - Copyright breo

**************************************************************************/

#ifndef xasOSConfigurator_H
#define xasOSConfigurator_H

#include <fstream>
#include <string>

using namespace std;


/**
  * class xasOSConfigurator
  *
  */

class xasOSConfigurator
{

private:
	fstream fp;
	string username;
	string gdm_conf_path;
	string gdm_conf_filename;
	string AutoLoginEnabLineLit;
    string AutoLoginLineLit;
	string blacklistFileName;

	// file paths we will use
	string seccopyfile;
	string fcopy;
	string gdmconff;

	// system comands we will use
	string sh_makeGdm_confCopy;
	string sh_rm_gdm_conf;
	string sh_rename_tmp2gdm_conf;
	string sh_restoreGdm_confCopy;

public:

	// Constructors/Destructors
	//

//	xasOSConfigurator ( string user, string new_gdm_conf_path, string new_gdm_conf_filename );
	xasOSConfigurator ( string user );

	/**
	* Empty Destructor
	*/
	~xasOSConfigurator ( );

	void addUser( string usern );

	void setGdm_conf_path( string new_path );
	string getGdm_conf_path();

	string getAutomaticLoginEnableLineLit();
    string getAutomaticLoginLineLit();

	void setAutoLoginLiterals( string enabLit, string usernameLit );

	/*
	int getAutomaticLoginEnableLineNumber();
    int getAutomaticLoginLineNumber();
	void setAutomaticLoginEnableLine(string new_value);
    void setAutomaticLoginLine(string new_value);
	*/
	bool setPath2FilesAndShCmds();

	bool resetGdm_conf();
	bool addAutomaticLoginUser();
	bool addLoginUser();
	bool delUserInBlacklist();
	bool addUsername2blacklist(string usern); // the dead pool XD


protected:



};

#endif // xasOSConfigurator_H
