#! /bin/sh
#

# author: Breo

# This script must be executed with root privileges
# Este script debe ser executado con privilexios de root

# 1.- Crear directorio dos ficheiros de xas
mkdir /usr/sbin/xasfiles

# 2.- Facer copia de seguridade de sudoers
cp /etc/sudoers /usr/sbin/xasfiles/sudoers

# 3.- Copiar versión a usar de gconf a xasfiles
cp xasfiles/*.xml /usr/sbin/xasfiles/

# 4.- Copiar ficheiros de idioma e configuración a xasfiles
#cp xasfiles/lang_galician.xml /usr/sbin/lang_galician.xml
#cp xasfiles/xas_config.xml /usr/sbin/xas_config.xml

# 4.- Copiar executable xas a /usr/sbin
cp xas /usr/sbin/xas
chmod a+x /usr/sbin/xas

# 5.- Copiar xas_script a /etc/init.d
cp xasfiles/xas_script /etc/init.d/xas

# 6.- Facer enlace simbólico ó script de xas dende /etc/rc2.d para que inicie: 'S', de start
 ln -s /etc/init.d/xas /etc/rc2.d/S30xas

# 7.- Establecer xas como xestor de visualización X por defecto
#echo "/usr/sbin/xas">/etc/X11/default-display-manager

# 8.- Renomear o enlace simbólico de /etc/init.d/gdm (S30gdm)
mv /etc/rc2.d/S30gdm /etc/rc2.d/cpS30gdm

# 9.- Creates the link of xas_exit in the gnome-panel of all users (in System menu)
sudo cp xasfiles/xas_exit.desktop /usr/share/applications/xas_exit.desktop
