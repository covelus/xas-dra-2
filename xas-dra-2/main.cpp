/************************************************************************
                                XAS-DRA
  Sistema Extensible de Autenticación con Acceso Dinámico a Restriccións
                        main.cpp - Copyright breo

**************************************************************************/

#include <string>
#include "xasConfigStore.h"
#include "xasLanguage.h"
#include "xasUserInterface.h"
#include "xasShellUserInterface.h"
//#include "xasGUserInterface.h"
#include "xasDB.h"
#include "xasMyDB.h"
//#include "xasOraDB.h"
#include "xasLDAPInterface.h"

#include "xasGlobals.h"

#include "xas_disableExit.h"

#include "xasOSConfigurator.h"



using namespace std;

int main(void)
{

    // variables tiles (useful vars)
    string kind_ui;
    string kind_db;
    string kind_of_user;
	string sh_clear_scrreen = "clear";
	enableSessionStart = true;

// -------------------------------------------------------------------------- //


    // CARGA DO ARQUIVO DE CONFIGURACIÓN (CONFIG FILE LOADING)
    int control;
    xasConfigStore *config = new xasConfigStore(control);
    if ( control = 0 ){
    	enableSessionStart = false;
    	cout<<endl<<"ERROR: FAULT IN CONFIGURATION XML FILE LOADING. RECONFIGURATION NEEDED: please give some advice to the system administrator"<<endl;
    	cout<<endl<<"Computer blocked. Press ENTER to continue"<<endl;
		cin.get();
		system("halt");
    	return -1;
    }

// -------------------------------------------------------------------------- //


    // CARGA DO ARQUIVO DE IDIOMA (LANGUAGE FILE LOADING)

    xasLanguage *lng = new xasLanguage ( config->getLang_used_fileName() );


// -------------------------------------------------------------------------- //

    /*
	xasShellUserInterface *ui = new xasShellUserInterface();
	*/
    // SELECCIÓN DO ENTORNO (shell ou gui) usando polimorfismo e ligadura dinmica

    xasUserInterface *ui;
    xasShellUserInterface *shellui = new xasShellUserInterface();
    /*     NOT NEEDED IN THIS VERSION
    xasGUserInterface *gui = new xasGUserInterface();
    */

    kind_ui = config->getKind_of_login();

    if (kind_ui == "shell" )
       ui = shellui;
     /*     NOT NEEDED IN THIS VERSION
     else if (kind_ui == "gui" )
          ui = gui;
     */
     // error case:
      else {
           // CORTAR EXECUCIÓN ou pedir nova configuracin, o arquivo XML est corrupto
           // tamn se pode tomar a versin shell, como defecto, avisando (cout) de que se tomou a opcin por defecto
           enableSessionStart = false;
      }


// -------------------------------------------------------------------------- //


      // PIDE DATOS DE USUARIO (ASK FOR USER DATA)
      ui->askUserData( lng->getTittle_tag(), lng->getLogin_tag(), lng->getPass_tag() );
      //ui->sendMsg(ui->getLogin());
      //ui->sendMsg(ui->getPass());


// -------------------------------------------------------------------------- //

      // COMPROBACIÓN NO DIRECTORIO DOS DATOS DE USUARIO

	xasDirectoryInterface *dap_init;

	dap_init = new xasDirectoryInterface();

	do
	{
		kind_of_user = "";

		bool result = dap_init->checkUserCredentials( ui->getLogin(), ui->getPass() , kind_of_user);
		if ( result == false)
		{
			enableSessionStart = false;
		}
		else
		{
			enableSessionStart = true;
			ui->setKind_of_user(kind_of_user);


		// -------------------------------------------------------------------------- //

		      /*
		      // COPROBACIÓN NA BASE DE DATOS DE RESTRICCIÓNS SOBRE USUARIOS
		      xasMyDB *my = new xasMyDB("localhost","root","f0rdb_","gp", ui, lng);
		     */
		      xasDB *db;
		      xasMyDB *my = new xasMyDB("localhost","root","f0rdb_","gp", ui, lng);

		      kind_db = config->getKind_of_dbms();
		      if (kind_db == "mysql" )
		         db = my;
                /*
		       else if (kind_db == "oracle" )
		            db = ora;
                */
                // error case:
		        else {
		             // CORTAR EXECUCIN ou pedir nova configuracin, o arquivo XML est corrupto
		             enableSessionStart = false;
		        }
		        if (enableSessionStart == true )
		        {
		            string ip = db->getHostIP();
                    string login = ui->getLogin();

                    string labName = db->getLabIdByIP(ip);
                    cout << endl << " >> Lab: " << labName << endl;
                    string matter = db->getMatterAtCurrentTime(labName);
                    cout << endl << " >> Matter: " << matter << endl;
                    string career = db->getCareerAtCurrentTime(labName);
                    cout << endl << " >> Career: " << career << endl;
                    string group = db->getIdGroupAtCurrentTime(labName);
                    cout << endl << " >> Group: " << group << endl;
                    for ( int i= 1; i < 3; i++ ){
                        int canLogin = db->canUserBeThere(login, group, matter, career);
                        //cout << endl << " >> Pode estar o alumno "+login+" alí: " << canLogin << ", é dicir, ";
                        if ( canLogin < 0 ){
                           cout << "ERRO. Fale co administrador do sistema" << endl;
                           enableSessionStart = false;
                        }
                        else if ( canLogin == 0 )
                           cout << "NON pode acceder" << endl;
                        else if ( canLogin > 0 )
                           cout << "SI pode acceder" << endl;
                    }
		// -------------------------------------------------------------------------- //


		      // ACTUALIZACIÓN BASE E DATOS: ENGADIR A LOG info sobre inicio de sesión

                    if ( enableSessionStart == true ){
                        bool actSuccess = db->updateLogs(login, labName, ip);
                        cout << endl << "Actualizada a base de datos de logs con " << login << ", " << labName << ", " << ip << "? ";
                        if ( actSuccess == true )
                           cout << "Logs: OK" << endl;
                        else
                            cout << "Logs: fail" << endl;

                    }
		        } // if enableSessionStart is true



		// -------------------------------------------------------------------------- //


		      // OPERACIÓNS ADICIONAIS... webdav, etc

		      // non implementadas nesta versión




		// -------------------------------------------------------------------------- //


		      // INICIO DE SESIÓN: INVOCACIÓN DE RUTINAS E SERVIZOS DO S.O.

		      if ( enableSessionStart == true )
		      {
		      	cout<< " Starting session... ";
		      }
		      else
		      {
		      	system( sh_clear_scrreen.c_str() );
		      	cout << endl << "Datos erróneos ou restricción aplicada sobre " << ui->getLogin() << endl;
		      }

		// -------------------------------------------------------------------------- //
		}  // else (LDAP comprobation phase)
	} while ( enableSessionStart == false );

	string sh_let_user_halt = "echo \""+ ui->getLogin() +"  ALL=  NOPASSWD: /sbin/halt\">>/etc/sudoers";
	string sh_let_user_reboot = "echo \""+ ui->getLogin() +"  ALL=  NOPASSWD: /sbin/reboot\">>/etc/sudoers";


    xasOSConfigurator *gdmc = new xasOSConfigurator( ui->getLogin() );
/*
	if (gdmc->delUserInBlacklist() == true)
		cout<<endl<<"Éxito eliminando users"<<endl;
	else
		cout<<endl<<"Fail eliminando users"<<endl;
*/

	if (gdmc->addAutomaticLoginUser() == true)
		cout<<endl<<"OK adding user"<<endl;
	else
		cout<<endl<<"Fail adding user"<<endl;

    string sh_cp_xas_exit_desk_lnk_es = "cp xasfiles/xas_exit.desktop /home/" +ui->getLogin() +"/Escritorio/xas_exit.desktop";
    string sh_cp_xas_exit_desk_lnk_en = "cp xasfiles/xas_exit.desktop /home/" +ui->getLogin() +"/Desktop/xas_exit.desktop";

    system( sh_cp_xas_exit_desk_lnk_es.c_str() );
    system( sh_cp_xas_exit_desk_lnk_en.c_str() );

	xas_disableExit *xasde;
	xasde = new xas_disableExit(ui->getLogin(),"");
	xasde->createFile();
    //system("PAUSE");////////////////////////////////////////////////////////////////

    return 0;

}
