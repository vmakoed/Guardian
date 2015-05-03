# Guardian #
 *A data protection utilitiy for Windows with USB-key security check.*  
**C++**/**Qt**/**WinAPI**

## Goals:
* access restriction to any file, folder or app
* any USB-flash can be used as a key
* multiple USB-keys can be used by one user  
  
The project aims to provide basic data protection from unauthorized access. Each protected *item* (a file, a folder or an app) is expected to have a *guardian*: a USB flash storage. When the guardian is around (the storage is mounted), an item is opened for interaction. If the storage is unmounted, the access to an item is restricted . The application is expected to let users use any USB storage they want. As USB flash storages are pretty popular these days, it would be nice to have a universal physical key to all of one's secured data.  
## Current state:
*as of 04.05.2015*
  

The project is under development.  
  
**What's done**:
* GUI
* SQLite database storage for lists of files, folders and guardians
* add/delete files and folders (automatic sync with database), pairing with guardians (simulation)
* add guardians (simulation)

**What's to be done**:
* acquire the list of mounted USB storage devices
* make desired USB storage a guardian
* pair an item to a guardian
* set access restriction rules
* implement a real-time connected devices monitoring 
  
![current look](/Snapshot-folders.jpg "snapshot")  
  
![current look](/Snapshot-guardians.jpg "snapshot")  
