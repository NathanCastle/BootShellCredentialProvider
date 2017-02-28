#Note: this script assumes you have Xming or similar installed and configured
#If not, please install VcXsrv first. If you have chocolatey,try (in powershell): choco install Xming

#note, you'll need to use sudo chmod 777 <filename> to allow the provided run scripts to work

#set up display for xming VcXsrv
echo "export DISPLAY=:0.0" >> ~/.bashrc

#set up dbus
sudo sed -i 's$<listen>.*</listen>$<listen>tcp:host=localhost,port=0</listen>$' /etc/dbus-1/session.conf
sudo sed -i 's$<listen>.*</listen>$<listen>tcp:host=localhost,port=1</listen>$' /etc/dbus-1/system.conf

#install Mate

sudo apt-add-repository ppa:ubuntu-mate-dev/ppa
sudo apt-add-repository ppa:ubuntu-mate-dev/trusty-mate
sudo apt-get update
sudo apt-get dist-upgrade
sudo apt-get install mate-desktop-environment-extras

sudo apt-get install unity-settings-daemon #fix for mate-settings-daemon not working
#http://www.ajopaul.com/2012/05/30/ubuntu-fix-for-unable-to-start-the-settings-manager-mate-settings-daemon/

#install XFCE4
sudo apt-get install xubuntu-desktop



#install KDE

#install Gnome