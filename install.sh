echo "Installing Dependencies..."
sudo yum install alsa-lib alsa-lib-devel qt qt-devel qtwebkit qtwebkit-devel qwt qwt-devel festival-devel festival-lib festival-speechtools-devel festival-speechtools-libs pocketsphinx pocketsphinx-libs pocketsphinx-devel gcc gcc-c++
echo "--------------------------"
cd ./vobrowse/
echo "Building packages..."
if qmake-qt4 && make
then
  echo "---------------------------"
  while true; do
    read -p "Is the user visually disabled? " yn
    case $yn in
        [Yy]* ) touch visually_disabled; break;;
        [Nn]* ) break;;
        * ) echo "Please answer yes or no.";;
    esac
  done
  echo "Installing...."
  sudo ln -sf `pwd`/vobrowse /usr/bin/vobrowse
  sudo cp ./icon.png /usr/share/pixmaps/vobrowse.png
  sudo mkdir -p /usr/share/pixmaps/vobrowse/
  sudo cp ./icon.png /usr/share/pixmaps/vobrowse/
  sudo cp ./vobrowse.desktop /usr/share/applications
  cp ./vobrowse.desktop ~/Desktop
  echo "Installation complete."
  echo "-------------------------"
else
  echo "Failed to build. Check dependencies."
fi
