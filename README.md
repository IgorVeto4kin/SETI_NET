# SETI_NET

GUI application for managing local networks and interface connections.

# Get started
You can just run 
```
chmod +x lazy_setup.sh
./SETI_NET/lazy_setup.sh
```
script, it can do everething automtically. For manual building and launch do this:
```
mkdir build
cd build
cmake ..
make
./bin/seti_net
```
If missing some Qt packages, run this:
```
./SETI_NET/install_dependances.sh
```

## Warning

For correct operation and better user experience, **disabling NetworkManager is required**:

```bash
sudo systemctl stop NetworkManager
```
If needed, you can re-enable it later with:
```bash

sudo systemctl start NetworkManager
```
