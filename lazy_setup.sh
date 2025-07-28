sudo apt update -y
#sudo apt upgrade -y
sudo apt install -y qt6-base-dev 
sudo apt install -y qt6-tools-dev-tools
sudo apt install -y qt6-tools-dev
sudo apt install -y libqt4-dev
#sudo apt install -y qt6-network-dev # unable to locate this package, idk why
#sudo apt install -y
#sudo apt install -y

rm -rf ./build
mkdir build
cd build
cmake ..
make
./bin/seti-net

