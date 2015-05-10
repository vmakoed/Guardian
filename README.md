# Guardian #
 *A data protection utility for Windows with USB-key security check.*  
**C++**/**Qt**/**WinAPI**

## Goals:
* access restriction to any file, folder or app
* any USB storage can be used as a key
* multiple USB keys can be used by one user  
  
The project aims to provide basic data protection from unauthorized access. Each protected *item* (a file, a folder or an app) is expected to have a *guardian*: a USB flash storage. When a guardian is around (the storage is mounted), an item is opened for interaction. If the storage is unmounted, the access to the item is restricted . The application is expected to let users use any USB storage they want. As USB flash storages are pretty popular these days, it would be nice to have a universal physical key to all of one's secured data.  
## Current state:
*as of 11.05.2015*
  

The project is under development.  
  
**What's done**:
* real-time mounted USB devices scan
* add guardian (a key and decrypted message is written to flash stroage, encrypted message is recorded to database)
* guardian authentication mechanism (scanning USB flash for a pass-file, checking this file's contents)
* GUI
* SQLite database storage for lists of files, folders and guardians

**What's to be done**:
* file/folders/apps protection
* file-guardian pairing
  
![current look](/Snapshot-guardians.jpg "snapshot")  
