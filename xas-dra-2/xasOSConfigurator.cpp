/************************************************************************
                        xasOSConfigurator.cpp - Copyright breo

**************************************************************************/
// modificará adecuadamente gdm.conf para que permita autologin

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h> // para system
#include <cstring> // para funcións copia cadenas

#include "xasOSConfigurator.h"


using namespace std;



// Constructors/Destructors
//
/*
xasOSConfigurator::xasOSConfigurator ( string user, string new_gdm_conf_path, string new_gdm_conf_filename )
{
	username = user;
	gdm_conf_path = new_gdm_conf_path;
	gdm_conf_filename = new_gdm_conf_filename;
	AutoLoginEnabLineLit = "AutomaticLoginEnable=false"; // GDM 2.20...
	AutoLoginLineLit = "AutomaticLogin="; // GDM 2.20...
	this->setPath2FilesAndShCmds();
	blacklistFileName = "blacklist.dat";
}
*/
xasOSConfigurator::xasOSConfigurator ( string user )
{
	username = user;
	gdm_conf_path = "/etc/gdm/"; // path in Ubuntu & Debian 2008 versions
	gdm_conf_filename = "gdm.conf";
	AutoLoginEnabLineLit = "AutomaticLoginEnable=false"; // GDM 2.20...
	AutoLoginLineLit = "AutomaticLogin="; // GDM 2.20...
	this->setPath2FilesAndShCmds();
	blacklistFileName = "blacklist.dat";
}

/**
* Empty Destructor
*/
xasOSConfigurator::~xasOSConfigurator ( )
{
}


void xasOSConfigurator::setGdm_conf_path(string new_path)
{
	gdm_conf_path = new_path;
}

string xasOSConfigurator::getGdm_conf_path()
{
	return gdm_conf_path;
}


string xasOSConfigurator::getAutomaticLoginEnableLineLit()
{
	return AutoLoginEnabLineLit;
}

string xasOSConfigurator::getAutomaticLoginLineLit()
{
	return AutoLoginLineLit;
}

void xasOSConfigurator::setAutoLoginLiterals(string enabLit, string usernameLit)
{
	AutoLoginEnabLineLit = enabLit;
	AutoLoginLineLit = usernameLit;

}

bool xasOSConfigurator::setPath2FilesAndShCmds()
{
	// file paths we will use
	seccopyfile = gdm_conf_path + "copy" + gdm_conf_filename;
	fcopy = gdm_conf_path + "tempgdm.conf";
	gdmconff = gdm_conf_path + gdm_conf_filename;

	// system comands we have to use

	sh_makeGdm_confCopy = "cp " + gdmconff + " " + seccopyfile;
	sh_rm_gdm_conf = "rm " + gdmconff;
	sh_rename_tmp2gdm_conf = "mv " + fcopy + " " + gdmconff;
	sh_restoreGdm_confCopy = "cp " + seccopyfile + " " + gdmconff;
}

bool xasOSConfigurator::resetGdm_conf()
{
	cout<<endl<<"Reseteando GDM.conf"<<endl;////////////////////////////////////////////
	bool toRet = true;
	system( sh_rm_gdm_conf.c_str() );
	system( sh_restoreGdm_confCopy.c_str() );

	return toRet;
}

bool xasOSConfigurator::addAutomaticLoginUser()
{
	bool toRet = true;
	int results = 0; // This will be updated every time we do match in gdm.conf
	string line;
	string search = AutoLoginEnabLineLit; // the first line to search


	cout<<endl<<sh_makeGdm_confCopy<<endl<<sh_rm_gdm_conf<<endl<<sh_rename_tmp2gdm_conf<<endl;////////////////////////////////////////////


	// New values we have to change in the config file.
		//First we use the default values to find the searched text
	string newAutoLoginEnabLineLit = AutoLoginEnabLineLit;
	string newAutoLoginLineLit = AutoLoginLineLit;
		// now we can change the default values to the new values
	newAutoLoginLineLit = newAutoLoginLineLit + username;
	newAutoLoginEnabLineLit.replace(newAutoLoginEnabLineLit.find("false"),5,"true");

	// First thing first
	this->addLoginUser();

	cout<<endl<<newAutoLoginEnabLineLit<<endl<<newAutoLoginLineLit<<endl;///////////////////////////////

	/* If it doesn't exist, this is the first time that this program is executed.
		gdm.conf should be the original one.
	 	We should make a copy of the original gdm.conf before install XAS
	*/
	ifstream copy( seccopyfile.c_str() );
	if (! copy )
	{
		system( sh_makeGdm_confCopy.c_str() );
		cout<<endl<<"Facendo copia de seguridade"<<endl;////////////////////////////////////////////
	}
	else{
		copy.close();
		// We need a default gdm.conf... We will use our default security copy
		this->resetGdm_conf();
	}

	fstream fp( gdmconff.c_str(),ios::in);
	if (! fp )
	{
		return false;
	}


	ofstream fout( fcopy.c_str() );
	if (! fout )
	{
		return false;
	}
	while ( getline(fp,line) ) { // we have to find 2 lines in gdm.conf:

		if (strstr(line.c_str(),search.c_str()) != 0){
			results++;
			search = AutoLoginLineLit; // now we can search the second literal
			if ( results == 1)
				fout<<newAutoLoginEnabLineLit<<endl;
			else  // results == 2
				fout<<newAutoLoginLineLit<<endl;
		} // end if (strstr(line.c_str(),search.c_str()) != 0)...
		else{
			fout<<line<<endl;
		} // end else
	} // end while

	fp.close();
	fout.close();

	system( sh_rm_gdm_conf.c_str() );
	system( sh_rename_tmp2gdm_conf.c_str() );

	return toRet;
}


bool xasOSConfigurator::addLoginUser()
{
	bool toRet = true;
	string sh_adduser_m;
	sh_adduser_m = "useradd -m " + username;
	/*  The user´s home directory will be created if it does not exist.
	 The files contained in SKEL_DIR will be copied to the home directory...
	 EXIT VALUES
       The useradd command exits with the following values:

       0
           success

       1
           can´t update password file

       2
           invalid command syntax

       3
           invalid argument to option

       4
           UID already in use (and no -o)

       6
           specified group doesn´t exist

       9
           username already in use

       10
           can´t update group file

       12
           can´t create home directory

       13
           can´t create mail spool
	*/
	cout<<"Engadindo usuario mediante "<<sh_adduser_m<<endl;
	int retValue = -1;
	retValue = system( sh_adduser_m.c_str() );
	if ( retValue != 0 || retValue != 13 )
		toRet = false;
	this->addUsername2blacklist( username );
	return toRet;

}


bool xasOSConfigurator::delUserInBlacklist()
{
	bool toRet = true;
	string lineUser;

	// We kill every user in the death list XD

	fstream fp( blacklistFileName.c_str(),ios::in|ios::out );
	if (! fp )
	{
		return false;
	}
	while ( getline(fp,lineUser) ) { // we have to find 2 lines in gdm.conf:
		string sh_deluser;
		sh_deluser = "userdel " + lineUser;
		cout<<endl<<"Executando "<<sh_deluser<<endl;
		int retValue = 0; // if there are no users to delete (first time), we need a default value
		if ( lineUser != "breo") // You won't erase me!! >:(  // archaic debugging mode XD
			retValue = system( sh_deluser.c_str() );
		/*
		 NAME
		   userdel - delete a user account and related files

		 SYNOPSIS
		   userdel [options] LOGIN

		 EXIT VALUES
		   The userdel command exits with the following values:

		   0
			   success

		   1
			   can´t update password file

		   2
			   invalid command syntax

		   6
			   specified user doesn´t exist

		   8
			   user currently logged in

		   10
			   can´t update group file

		   12
			   can´t remove home directory


		 */
		if (retValue != 0){
			toRet = false;
			cout<<endl<<"Modo depuración: teclea un nº e Enter para continuar"<<endl;
			int p;
			cin>>p;
		}
	} // end while

	// And finally... we don't need the blacklist now. We'll kill it too.. >D
	if (toRet = true ) {
		string sh_rm_blacklist;
		sh_rm_blacklist = "rm " + blacklistFileName;
		cout<<endl<<"Cargándome a lista negra mediante "<<sh_rm_blacklist<<endl;
		system( sh_rm_blacklist.c_str() );
	}
	return toRet;
}

bool xasOSConfigurator::addUsername2blacklist( string usern )
{
	bool toRet = true;
	string sh_add2blacklist = "echo " + usern + ">>" +blacklistFileName;
	cout<<endl<<usern<<" engadido á lista negra mediante "<<sh_add2blacklist<<endl;
	system( sh_add2blacklist.c_str() );

	// ... it's more easy if whe use (call) the shell command ... XD

	return toRet;
}

