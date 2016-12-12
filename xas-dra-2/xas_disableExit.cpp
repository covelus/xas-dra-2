/************************************************************************
					xas_disableExit.cpp - Copyright breo

**************************************************************************/

#include "xas_disableExit.h"
//#include "external_libs/tinyxml/tinyxml.h" //...NOT ON THIS VERSION

#include <vector>

#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;


/**
* class xas_disableExit
*
*/


// Constructors/Destructors
//

xas_disableExit::xas_disableExit ( string user, string group ){
	username = user;
	groupname = group;
	userHome = "/home/" + user;
//	userHome = "/home/breo/PFC/_partes_Implementando/xas_disableExit/src";
	gconf_pathNFile = "/home/"+user+"/.gconf/apps/panel/global/%gconf.xml";
//	gconf_pathNFile = "/home/breo/PFC/_partes_Implementando/xas_disableExit/src/.gconf/apps/panel/global/%gconf.xml";
	cout<<endl<<gconf_pathNFile<<endl;

	xas_auxFilesPath ="/usr/sbin/xasfiles/";
	gconf_xmlTemplate = xas_auxFilesPath + "%gconf.xml";

}

/**
* Empty Destructor
*/
xas_disableExit::~xas_disableExit ( ){
}

// other functions

bool xas_disableExit::askIfFileExists( ){
	bool toRet = false;


	return toRet;
}
/* ...NOT ON THIS VERSION
bool xas_disableExit::addTheMagicContent(){
	bool toRet = false;

	// we can have acepted XML code in a file and copy it each time to the file


	return toRet;
}
*/
bool xas_disableExit::createFile( ){
	bool toRet;
	string sh_createPathL1 = "mkdir " + userHome + "/.gconf";
	//string sh_change_ownerL1 "";
	string sh_createPathL2 = "mkdir " + userHome  + "/.gconf/apps";
	//string sh_change_ownerL2 "";
	string sh_createPathL3 = "mkdir " + userHome  + "/.gconf/apps/panel";
	//string sh_change_ownerL3 "";
	string sh_createPathL4 = "mkdir " + userHome  + "/.gconf/apps/panel/global";
	string sh_change_ownerDirsFlRecurs = "chown -R " + username +" .gconf";
	string sh_cp_gconf = "cp " + gconf_xmlTemplate + " " + gconf_pathNFile;
	cout<<endl<<"xas_auxFilesPath: " + xas_auxFilesPath<<endl;
	cout<<endl<<"gconf_xmlTemplate: " + gconf_xmlTemplate<<endl;
	cout<<endl<<"gconf_pathNFile: " + gconf_pathNFile<<endl;

	try{
		system( sh_createPathL1.c_str() );
		//system( sh_change_ownerL1 );
		system( sh_createPathL2.c_str() );
		//system( sh_change_ownerL2 );
		system( sh_createPathL3.c_str() );
		//system( sh_change_ownerL3 );
		system( sh_createPathL4.c_str() );
		toRet = true;

	}
	catch ( runtime_error )
	{
		toRet = false;//intentar abrir directorio? Se existe, ok, senón, return false

	}
	catch ( exception )  // por se acaso non entra no bloque anterior
	{
		toRet = false;//intentar abrir directorio? Se existe, ok, senón, return false
	}
	try {
	    cout<<endl<<"CP: "<<sh_cp_gconf<<endl;

		//sh_change_owner2file = ""; // + gconf_pathNFile
		if ( system( sh_cp_gconf.c_str() ) )
			toRet = true;
		else
			toRet = false;

		system( sh_change_ownerDirsFlRecurs.c_str() );
	}
	catch ( runtime_error )
	{
		return false;

	}
	catch ( exception )  // por se acaso non entra no bloque anterior
	{
		return false;
	}
	cout<<endl<<"intentona 4"<<endl;
	cout<<endl<<"CP: "<<sh_cp_gconf<<endl;
    system( sh_change_ownerDirsFlRecurs.c_str() );
    system( sh_cp_gconf.c_str() );
	/* We have to add the configuration to the new XML file (created by touch)... NOT ON THIS VERSION
	if ( this->addTheMagicContent() )
		toRet = true;
    */
	return toRet;
}

/*
bool xas_disableExit::touchFile( ){
	bool toRet = true;
	string sh_createPathL1 = "mkdir " + userHome + "/.gconf";
	string sh_createPathL2 = "mkdir " + userHome  + "/.gconf/apps";
	string sh_createPathL3 = "mkdir " + userHome  + "/.gconf/apps/panel";
	string sh_createPathL4 = "mkdir " + userHome  + "/.gconf/apps/panel/global";

	try{
		system( sh_createPathL1.c_str() );
		system( sh_createPathL2.c_str() );
		system( sh_createPathL3.c_str() );
		system( sh_createPathL4.c_str() );
	}
	catch ( runtime_error )
	{
		return false;//intentar abrir directorio? Se existe, ok, senón, return false

	}
	catch ( exception )  // por se acaso non entra no bloque anterior
	{
		return false;//intentar abrir directorio? Se existe, ok, senón, return false
	}

	try {
		string sh_touch_fileName = "touch " + gconf_pathNFile;
		if ( system( sh_touch_fileName.c_str() ) )
			toRet = true;
	}
	catch ( runtime_error )
	{
		return false;

	}
	catch ( exception )  // por se acaso non entra no bloque anterior
	{
		return false;
	}

	return toRet;
}*/

/* ...NOT ON THIS VERSION. In this time we use the "easy mode"

bool xas_disableExit::set_disable_log_outValue( ){
	bool toRet = false;
	this->set_disable_log_outValue(true); ////////////////////////// ??????????????????

	return toRet;
}

bool xas_disableExit::set_disable_log_outValue( bool boolValue ){
	bool toRet = false;
	string new_value;
	if ( boolValue = true )
		new_value = "true";
	else
		new_value = "false";

    string filename(gconf_pathNFile);
    TiXmlDocument doc(filename.c_str());
    if(!doc.LoadFile())  // we have to create it
    {
    	this->createFile();



		if(!doc.LoadFile()) // if the file creation fails...
		{
			return false;
		}
    }
    else // the file exists and have some values
    {

    	// the file is OK and opened
    	TiXmlElement* pElem;	//!current element
        TiXmlElement* pChild;	//!current child of pElem
        TiXmlHandle hDoc(&doc);	//!handle to xml document
        TiXmlHandle hRoot(0); //! handle to root element 'ui_text'

        vector<XMLItem> todo_list; //! todo list, data of all 'item' elements in xml
        //get root element 'TodoList', set to hRoot
        pElem = hDoc.FirstChildElement().Element();
        if(!pElem) {
           cout << "XML root invalid! 49!" << endl;
           return 0;
        } // if
        //else root OK
        //debug: cout << "root: " << pElem->Value() << endl;
        hRoot = TiXmlHandle(pElem);

        todo_list.clear();//clear vector
        int count = 0;
        for( pElem = hRoot.FirstChild("entry").Element(); pElem; pElem = pElem->NextSiblingElement() ){

             XMLItem current;
             pChild = hRoot.Child("entry",count).Element();
             if (!pChild) {
                cout << "\tXML pChild invalid 66!" << endl;
                return 0;
             }
             current.name = pChild->Attribute("name");
             current.mtime = pChild->Attribute("mtime");
             current.name = pChild->Attribute("name");
             current.value = pChild->Attribute("value");
			/*
             TiXmlElement* pCur = pChild->FirstChildElement("name");
             if(!pCur){
                       cout << "\tXML pCur invalid 73!" << endl;
                       return 0;
             }
             const char* pText = pCur->GetText();
             if(pText) {
     			current.name = pText;
        	 }else{
        		cout << "\tXML pText: invalid 79!" << endl;
        		return 0;
        	 }
		*/
		/* ...NOT ON THIS VERSION
        	 todo_list.push_back(current);
        	 count++;
        } // for

         // Iteraremos a través do vector
        for(vector<XMLItem>::iterator iter=todo_list.begin();
        	iter != todo_list.end(); iter++) {

				string itemName = iter->getGconfName();

				if ( itemName == "disable_log_out") {
					cout << endl << "name  " << itemName;
					cout << endl << "mtime " << iter->getGconfMtime();
					cout << endl << "type  " << iter->getGconfType();
					cout << endl << "value " << iter->getGconfValue();
					cout << endl << "end ";
					iter->setGconfValue("true");
					cout << endl << "end2 ";
					toRet = true;
				   } // if itenName...
    	} // for
    } // else
	return toRet;
}*/

