/************************************************************************
                        xasMyDB.cpp - Copyright breo

**************************************************************************/

#include "xasMyDB.h"

// ----- ONLY IN WINDOWS VERSION ----

//#include <windows.h>

// ----- IN ALL VERSIONS ----

//#include <iostream>
#include <mysql/mysql.h>
#include <mysql/mysqld_error.h>

#include "xasShellUserInterface.h"
#include "xasLanguage.h"
#include <stdlib.h> // para system
#include <cstring>

#include <fstream>

  // Constructors/Destructors
  //


xasMyDB::xasMyDB ( string server_address, string root_user, string password, string database_name, xasUserInterface *user_inter, xasLanguage *lang )
{
  server_addr = server_address;

  user = root_user;

  passwd = password;

  db_name = database_name;

  ui = user_inter;

  lng = lang;
}

/**
* Empty Destructor
*/
xasMyDB::~xasMyDB ( )
{
}



/**
* @param  ip
* @return string
*/
string xasMyDB::getLabIdByIP(string ip)
{
    char toRet[50] = "ERROR";

    pConnection = mysql_init(NULL);
    if(!pConnection)
    { //error, quit the program
        ui->sendnHandleCriticalErrMsg( lng->getNo_conection_error() );
        return "ERROR";
    }

    if(mysql_real_connect(pConnection, server_addr.c_str(), user.c_str(), passwd.c_str(), db_name.c_str(), 0,NULL,0) == NULL)
    { //error, quit the program
              ui->sendnHandleConfigErrMsg(lng->getMysql_real_connect_error());
              return "ERROR";
    }


    string query("SELECT IdLab FROM iplab WHERE ip = '"+ip+"'");

    try
    {
        if(mysql_query(pConnection, query.c_str() ))
        {
            // Error  realizar a consulta:
            ui->sendnHandleCriticalErrMsg(lng->getSerious_error()+ mysql_error(pConnection));
            return "ERROR";
        }

        MYSQL_RES *res;
        if((res = mysql_store_result(pConnection)))
        {
            // Procesar resultados
            int i = (int) mysql_num_rows(res);


            MYSQL_ROW row;

            if (mysql_num_rows(res) == 0)
            {
               strcpy(toRet,"");
            }
            else
            {
                row = mysql_fetch_row(res);
                unsigned long *lon = mysql_fetch_lengths(res);
                if (row[0]==NULL)
                   strcpy(toRet,"");
                else
                    strcpy(toRet,row[0]);
            }
            // Liberar:
            mysql_free_result(res);
        } // if res = mysql_store_restult...
    } // try
    catch ( ... )
    {
          ui->sendnHandleCriticalErrMsg( lng->getExceptionMsg() );
          mysql_close(pConnection);
          return "ERROR";
    }
    mysql_close(pConnection);
    return toRet;
}


/**
* @param  lab
* @return string
*/
string xasMyDB::getMatterAtCurrentTime(string lab)
{
    char toRet[50] = "ERROR";
    pConnection = mysql_init(NULL);
    if(!pConnection){ //error, quit the program
        ui->sendnHandleCriticalErrMsg( lng->getNo_conection_error() );
        return "ERROR";
    }

    if(mysql_real_connect(pConnection, server_addr.c_str(), user.c_str(), passwd.c_str(), db_name.c_str(),0,NULL,0) == NULL)
    { //error, quit the program
              ui->sendnHandleConfigErrMsg(lng->getMysql_real_connect_error());
              return "ERROR";
    }


    string query("SELECT IdAsignatura FROM grupospracticas WHERE IdLab = '"+lab+"' AND (SELECT CURDATE() BETWEEN FechInicio AND FechFin) AND (SELECT CURTIME() BETWEEN HorCom AND HorFin)");

    try
    {
        if(mysql_query(pConnection, query.c_str() ))
        {
            // Error  realizar a consulta:
            ui->sendnHandleCriticalErrMsg( lng->getExceptionMsg() );
            return "ERROR";
        }

        MYSQL_RES *res;
        if((res = mysql_store_result(pConnection)))
        {
            // Procesar resultados
            int i = (int) mysql_num_rows(res);


            MYSQL_ROW row;

            if (mysql_num_rows(res) == 0)
            {
               strcpy(toRet,"");
            }
            else
            {
                row = mysql_fetch_row(res);
                unsigned long *lon = mysql_fetch_lengths(res);
                if (row[0]==NULL)
                   strcpy(toRet,"");
                else
                    strcpy(toRet,row[0]);
            }
            // Liberar:
            mysql_free_result(res);
        } // if res = mysql_store_restult...
    } // try
    catch ( ... )
    {
          ui->sendnHandleCriticalErrMsg( lng->getExceptionMsg() );
          mysql_close(pConnection);
          return "ERROR";
    }
    mysql_close(pConnection);
    return toRet;
}


/**
* @param  lab
* @return string
*/
string xasMyDB::getIdGroupAtCurrentTime(string lab)
{
    char toRet[50] = "ERROR";
    pConnection = mysql_init(NULL);
    if(!pConnection){ //error, quit the program
        ui->sendnHandleCriticalErrMsg( lng->getNo_conection_error() );
        return "ERROR";
    }

    if(mysql_real_connect(pConnection, server_addr.c_str(), user.c_str(), passwd.c_str(), db_name.c_str(),0,NULL,0) == NULL)
    { //error, quit the program
              ui->sendnHandleConfigErrMsg(lng->getMysql_real_connect_error());
              return "ERROR";
    }

    // Miramos se a IP est nese laboratorio
    string query("SELECT IdGrupo FROM grupospracticas WHERE IdLab = '"+lab+"' AND (SELECT CURDATE() BETWEEN FechInicio AND FechFin) AND (SELECT CURTIME() BETWEEN HorCom AND HorFin)");

    try
    {
        if(mysql_query(pConnection, query.c_str() ))
        {
            // Error al realizar la consulta:
            ui->sendnHandleCriticalErrMsg(lng->getSerious_error()+ mysql_error(pConnection));
            return "ERROR";
        }

        // Almacenar el resultado de la consulta, lo necesitaremos despus:
        MYSQL_RES *res;
        if((res = mysql_store_result(pConnection)))
        {

            int i = (int) mysql_num_rows(res);


            MYSQL_ROW row;

            if (mysql_num_rows(res) == 0)
            {
               strcpy(toRet,"");
            }
            else
            {
                row = mysql_fetch_row(res);
                unsigned long *lon = mysql_fetch_lengths(res);
                if (row[0]==NULL) // dame fallo cando non hai resultado que cumpla o select
                   strcpy(toRet,"");
                else
                    strcpy(toRet,row[0]);
            }
            // Liberar resultado:
            mysql_free_result(res);
        } // if res = mysql_store_restult...
    } // try
    catch ( ... )
    {
          ui->sendnHandleCriticalErrMsg( lng->getExceptionMsg() );
          mysql_close(pConnection);
          return "ERROR";
    }
    mysql_close(pConnection);
    return toRet;
}


/**
* @param  lab
* @return string
*/
string xasMyDB::getCareerAtCurrentTime(string lab)
{
    char toRet[50] = "ERROR";
    pConnection = mysql_init(NULL);
    if(!pConnection){ //error, quit the program
        ui->sendnHandleCriticalErrMsg( lng->getNo_conection_error() );
        return "ERROR";
    }

    if(mysql_real_connect(pConnection, server_addr.c_str(), user.c_str(), passwd.c_str(), db_name.c_str(),0,NULL,0) == NULL)
    { //error, quit the program
              ui->sendnHandleConfigErrMsg(lng->getMysql_real_connect_error());
              return "ERROR";
    }

    // Miramos se a IP est nese laboratorio
    string query("SELECT IdCarrera FROM grupospracticas WHERE IdLab = '"+lab+"' AND (SELECT CURDATE() BETWEEN FechInicio AND FechFin) AND (SELECT CURTIME() BETWEEN HorCom AND HorFin)");

    try
    {
        if(mysql_query(pConnection, query.c_str() ))
        {
            // Error  realizar a consulta:
            ui->sendnHandleCriticalErrMsg(lng->getSerious_error()+ mysql_error(pConnection));
            return "ERROR";
        }

        // Almacenar el resultado de la consulta, lo necesitaremos despus:
        MYSQL_RES *res;
        if((res = mysql_store_result(pConnection)))
        {
            // Procesar resultados
            int i = (int) mysql_num_rows(res);
//            int j = (int) mysql_num_fields(res);

            MYSQL_ROW row;

            // Leer registro a registro y mostrar:
            if (mysql_num_rows(res) == 0)
            {
               strcpy(toRet,"");
            }
            else
            {
                row = mysql_fetch_row(res);
                unsigned long *lon = mysql_fetch_lengths(res);
                if (row[0]==NULL) // dame fallo cando non hai resultado que cumpla o select
                   strcpy(toRet,"");
                else
                    strcpy(toRet,row[0]);
            }
            // Liberar el resultado de la consulta:
            mysql_free_result(res);
        } // if res = mysql_store_restult...
    } // try
    catch ( ... )
    {
          ui->sendnHandleCriticalErrMsg( lng->getExceptionMsg() );

          mysql_close(pConnection);
          return "ERROR";
    }
    mysql_close(pConnection);
    return toRet;
}


/**
* @param  login, group, matter, career
* @return int, -1 if error, 0 of no and >0 if yes
*/
int xasMyDB::canUserBeThere(string login, string group, string matter, string career)
{
    int toRet = 0;
    pConnection = mysql_init(NULL);
    if(!pConnection){ //error, quit the program
        ui->sendnHandleCriticalErrMsg( lng->getNo_conection_error() );
        return -1;
    }

    if(mysql_real_connect(pConnection, server_addr.c_str(), user.c_str(), passwd.c_str(), db_name.c_str(),0,NULL,0) == NULL)
    { //error, quit the program
              ui->sendnHandleConfigErrMsg(lng->getMysql_real_connect_error());
              return -1;
    }

    string query("SELECT COUNT(*) FROM grupraalum WHERE login = '"+login+"' AND IdGrupo = '"+group+"' AND IdAsignatura = '"+matter+"' AND IdCarrera = '"+career+"'");

    try
    {
        if(mysql_query(pConnection, query.c_str() )) {
            // Erro  realizar a consulta:
            ui->sendnHandleCriticalErrMsg(lng->getSerious_error()+ mysql_error(pConnection));
            return -1;
        }

        MYSQL_RES *res;
        if((res = mysql_store_result(pConnection))) {
            // Procesar resultados
            int i = (int) mysql_num_rows(res);

            MYSQL_ROW row;

            // Leer rexistro a rexistro e mostrar:
            if (mysql_num_rows(res) == 0) {
               toRet = 0;
            }
            else
            {
                row = mysql_fetch_row(res);
                unsigned long *lon = mysql_fetch_lengths(res);
                if (row[0]==NULL)
                   toRet = 0;
                else
                    toRet = atoi(row [0]);
            }
            // Liberar...
            mysql_free_result(res);
        } // if res = mysql_store_restult...
    } // try
    catch ( ... )
    {
          ui->sendnHandleCriticalErrMsg( lng->getExceptionMsg() );
          mysql_close(pConnection);
          return -1;
    }
    mysql_close(pConnection);
    return toRet;
}


/**
* @param  login, idLab, ip
* @return bool
*/
bool xasMyDB::updateLogs(string login, string idLab, string ip)
{
    int toRet = false;
    pConnection = mysql_init(NULL);
    if(!pConnection){ //error, quit the program
        ui->sendnHandleCriticalErrMsg( lng->getNo_conection_error() );
        return false;
    }

    if(mysql_real_connect(pConnection, server_addr.c_str(), user.c_str(), passwd.c_str(), db_name.c_str(),0,NULL,0) == NULL)
    { //error, quit the program
              ui->sendnHandleConfigErrMsg(lng->getMysql_real_connect_error());
              return false;
    }

    string query("INSERT INTO logs (idLab, ip, login, fechaLogon, horaLogon) VALUES ('"+idLab+"','"+ip+"','"+login+"',(SELECT CURDATE()),(SELECT CURTIME()));");

    try
    {
        if( mysql_query(pConnection, query.c_str()) != 0 )
        { // mysql_query devolve 0 se a consulta vai OK, != 0 se erro
            // Erro  realizar a consulta:
            ui->sendnHandleCriticalErrMsg(lng->getSerious_error()+ mysql_error(pConnection));
            toRet =  false;
        } else {  // mysql_query didn't return an error
               toRet = true;
        }
    } // try
    catch ( ... )
    {
          ui->sendnHandleCriticalErrMsg( lng->getExceptionMsg() );
          mysql_close(pConnection);
          return false;
    } //
    mysql_close(pConnection);
    return toRet;
}


/**
* @return string
*/
string xasMyDB::getHostIP()
{
    string ip;
    string line;

    fstream fp( "ip.dat",ios::in );
	if (! fp )
	{
		return false;
	}

	while ( getline(fp,line) ) {

		if (strcmp(line.c_str(),"127.0.0.1") == 0); // nothing
		else{
			ip = line;
			fp.close();
            return ip; // it take the first IP found, if it is different than 127.0.0.1
		} // end else
	} // end while
    fp.close();
    return ip;
}

// protected attribute accessor methods
//
