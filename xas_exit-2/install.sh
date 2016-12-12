mkdir /usr/share/icons/XAS
cp xas_exit /usr/sbin/xas_exit
cp icons/XAS/xas_exit_logo.png /usr/share/icons/XAS/xas_exit_logo.png
cp icons/XAS/xas_exit_icon.png /usr/share/icons/XAS/xas_exit_icon.png


# .- Creates the link of xas_exit in the gnome-panel of all users (in System menu)
sudo cp xasfiles/xas_exit.desktop /usr/share/applications/xas_exit.desktop

