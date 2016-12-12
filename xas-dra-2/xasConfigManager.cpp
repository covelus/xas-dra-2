/************************************************************************
                   xasConfigManager.cpp - Copyright breo

**************************************************************************/

#include "xasConfigManager.h"
#include "xasConfigStore.h"
#include "xasLanguage.h"
#include "external_libs/tinyxml/tinyxml.h"
#include <vector>
#include <iostream>

#include "xasUserInterface.h"


using namespace std; 


// Constructors/Destructors
//  

xasConfigManager::xasConfigManager ( ) 
{ 
}

xasConfigManager::~xasConfigManager ( ) 
{
    
}

//  
// Methods
//  

/**
 * Set the value of reg
 * @param new_var the new value of xasConfigStoreReg reg
 */
int xasConfigManager::loadFromXmlFile(string filena, xasConfigStoreReg &reg) 
{
    string filename(filena);
    
    TiXmlDocument doc(filename.c_str());
    
    if(!doc.LoadFile())
    {
    	cout << "CONFIG FILE NOT FOUND OR IT IS INVALID" << endl;
    }
    else
    {
    	// Abriuse correctamente o ficheiro filename
    	TiXmlElement* pElem;	//!current element
        TiXmlElement* pChild;	//!current child of pElem
        TiXmlHandle hDoc(&doc);	//!handle to xml document
        TiXmlHandle hRoot(0); //! handle to root element 'ui_text'
    
        vector<XMLItem> todo_list; //! todo list, data of all 'item' elements in xml
        //get root element 'TodoList', set to hRoot
        pElem = hDoc.FirstChildElement().Element();
        if(!pElem) 
        {
           cout << "XML root invalid! 49!" << endl; 
           return 0;
        } // if
        //else root OK
        
        //debug: cout << "root: " << pElem->Value() << endl;
        hRoot = TiXmlHandle(pElem);
    
        todo_list.clear();//clear vector
        
        int count = 0;
        for( pElem = hRoot.FirstChild("item").Element(); pElem; pElem = pElem->NextSiblingElement() )
        {
             XMLItem current;
             pChild = hRoot.Child("item",count).Element();
             if (!pChild) 
             {
                cout << "\tXML pChild invalid 66!" << endl;
                return 0;
             }
             current.id = pChild->Attribute("id");
             current.descr = pChild->Attribute("descr");
             
             TiXmlElement* pCur = pChild->FirstChildElement("data");
             if(!pCur)
             {
                       cout << "\tXML pCur invalid 73!" << endl;
                       return 0;
             }
             
             const char* pText = pCur->GetText();
             if(pText) 
             {  					
     			current.data = pText;						
        	 }
        	 else
        	 {
        		cout << "\tXML pText: invalid 79!" << endl;
        		return 0;
        	 }
        	 todo_list.push_back(current);
        	 count++;
        } // for

         // Iteraremos a travs do vector
        for(vector<XMLItem>::iterator iter=todo_list.begin();
        	iter != todo_list.end(); iter++)
       	{
       		string itemIdentifier = iter->getID();
       		if ( itemIdentifier == "lang_used_file") {
                 reg.lang_used_file = iter->getData();
            } 
            else if ( itemIdentifier == "kind_of_lang_file") {
                   reg.kind_of_lang_file = iter->getData();
             } 
             else if ( itemIdentifier == "dir_dap") {
                    reg.dir_dap = iter->getData();
              } 
              else if ( itemIdentifier == "kind_of_dap") {
                     reg.kind_of_dap = iter->getData();
               } 
               else if ( itemIdentifier == "ip_bdMngLabs") {
                      reg.ip_bdMngLabs = iter->getData();
                } 
                else if ( itemIdentifier == "kind_of_dbms") {
                       reg.kind_of_dbms = iter->getData();
                } 
                else if ( itemIdentifier == "kind_of_login") {
                       reg.kind_of_login = iter->getData();
                 } 
                 else if ( itemIdentifier == "kind_of_dbmsConn") {
                      	reg.kind_of_dbmsConn = iter->getData();
                  } // last if (else ... )
    	} // for          
    	return count;
    }
}


/**
 * Set the value of reg
 * @param new_var the new value of xasLangReg reg
 */
 
int xasConfigManager::loadFromXmlFile(string filena, xasLangReg &reg) 
{
    string filename(filena);
    TiXmlDocument doc(filename.c_str());
    
    if(!doc.LoadFile())
    {
    	cout << "LANG FILE NOT FOUND OR IT IS INVALID " << endl;
    	return 0;
    }
    else
    {
    	// Abriuse correctamente o ficheiro filename
    	TiXmlElement* pElem;	//!current element
        TiXmlElement* pChild;	//!current child of pElem
        TiXmlHandle hDoc(&doc);	//!handle to xml document
        TiXmlHandle hRoot(0); //! handle to root element 'ui_text'
    
        vector<XMLItem> todo_list; //! todo list, data of all 'item' elements in xml
        //get root element 'TodoList', set to hRoot
        
        pElem = hDoc.FirstChildElement().Element();
        if(!pElem) 
        {
           cout << "XML root invalid! 49!" << endl; 
           return 0;
        } // if
        //else root OK
        
        //debug: cout << "root: " << pElem->Value() << endl;
        hRoot = TiXmlHandle(pElem);
    
        todo_list.clear();//clear vector
        
        int count = 0;
        
        for( pElem = hRoot.FirstChild("item").Element(); pElem; pElem = pElem->NextSiblingElement() )
        {
             XMLItem current;
             pChild = hRoot.Child("item",count).Element();
             if (!pChild) 
             {
                cout << "\tXML pChild invalid 66!" << endl;
                return 0;
             }
             current.id = pChild->Attribute("id");
             current.descr = pChild->Attribute("descr");
             
             TiXmlElement* pCur = pChild->FirstChildElement("data");
             if(!pCur)
             {
                       cout << "\tXML pCur invalid 73!" << endl;
                       return 0;
             }
             
             const char* pText = pCur->GetText();
             if(pText) 
             {  					
     			current.data = pText;						
        	 }
        	 else
        	 {
        		cout << "\tXML pText: invalid 79!" << endl;
        		return 0;
        	 }
        	 todo_list.push_back(current);
        	 count++;
        } // for
        
        for(vector<XMLItem>::iterator iter=todo_list.begin();
            iter != todo_list.end(); iter++)
       	{
//       		string itemdata;
//       		itemdata = iter->getData();
//       		cout << "\t    " << itemdata << endl;
       		string itemIdentifier = iter->getID();
       		
       		if ( itemIdentifier == "lang_name") {
                 reg.lang_name = iter->getData();
            } 
            else if ( itemIdentifier == "normal_error") {
                   reg.normal_error = iter->getData();
             } 
             else if ( itemIdentifier == "serious_error") {
                    reg.serious_error = iter->getData();
              } 
              else if ( itemIdentifier == "invalid_dap_credentials") {
                     reg.invalid_dap_credentials = iter->getData();
               } 
               else if ( itemIdentifier == "mysql_real_connect_error") {
                      reg.mysql_real_connect_error = iter->getData();
                } 
                else if ( itemIdentifier == "no_conection_error") {
                       reg.no_conection_error = iter->getData();
                } 
                else if ( itemIdentifier == "attempting2connect") {
                       reg.attempting2connect = iter->getData();
                 } 
                 else if ( itemIdentifier == "login_tag") {
                        reg.login_tag = iter->getData();
                  } 
                  else if ( itemIdentifier == "pass_tag") {
                         reg.pass_tag = iter->getData();
                   } 
                   else if ( itemIdentifier == "ok_tag") {
                          reg.ok_tag = iter->getData();
                    } 
                    else if ( itemIdentifier == "cancel_tag") {
                           reg.cancel_tag = iter->getData();
                     } 
                     else if ( itemIdentifier == "restart_tag") {
                            reg.restart_tag = iter->getData();
                      } 
                      else if ( itemIdentifier == "shutdown_tag") {
                             reg.shutdown_tag = iter->getData();
                       } 
                       else if ( itemIdentifier == "exception") {
                              reg.exception = iter->getData();
                        } // last if (else ... )
                        /////////////////////////////////////////////////////// 
        } // for
          
    	return count;
    }
}


/*
bool xasConfigManager::updateConfigStore() 
{ // non usada nin precisada nesta versión
}
*/


int xasConfigManager::loadFromFile(string filena, xasLangReg &reg)
{
	int control;
    xasConfigStore *xcs = new xasConfigStore(control);
    if ( control == 0)
    	return 0;
    string kind_of_lang_f = xcs->getKind_of_lang_file();
/*    
    if (kind_of_lang_f == "xml"){
       return loadFromXmlFile(filena, reg);
    }
     else
     {
         //updateConfigStore
         cout << "erro";
         return 0;
     } */
}



// Accessor methods
//  


// Other methods
//  






