Qefem 0.7

Introduction

Qt based filemanager with two panels. The file actions are running in a separate thread, the spinning icon on the left indicates running actions.

NOTE: To use zip functionality on Win please install 7z from www.7-zip.org.

NOTE: On Ubuntu Linux it can be started by executing /usr/bin/Qefem

NOTE: On Windows the editor or terminal path needs double file separator "\\" or just one unix style "/"
New features in 0.7

	* ALT+q open the settings in editor
	* Supports Qt 4.7
	* F1 opens help

Features

    * History tab (the last 128 dirs are saved into home dir/.Qefem/.lhistory or .rhistory depending on left or right panel)
    * Bookmark tab ( bookmarks are saved to home dir/.Qefem/.bookmarks )
    * Drive tab removed from Maemo release (compiles and works on Maemo)
    * OSX and Win and Ubuntu release
    * Multiselection
    * .zip files are recognized by dubbleclicking and unziped to the other panels current folder 

Shortcuts

    * ALT+1 Left drive tab
    * ALT+2 Right drive list
    * ALT+3 Right file list
    * ALT+4 Left file list
    * ALT+5 Right History tab
    * ALT+6 Right History tab
    * ALT+7 Left Bookmarks tab
    * ALT+8 Right Bookmarks tab
    * ALT+c copy
    * ALT+r rename
    * ALT+d delete
    * ALT+m make dir
    * ALT+z zip
    * ALT+s switch to status 
    * ALT+e Opens the current file in editor
    * ALT+t Opens a terminal in the current directory (on OSX the current dir doesn't work)
    * ALT+f Searches for files 

Plans

    * File properties
    * checking the aviable size before copy
    * CTRL-X support
    * Implement file move
    * Sorting by name size date
    * adding error console to see errors
    * Fix CTRL+C and CTRL+V support
    * Drag and Drop support

Project home page
http://code.google.com/p/qefem/
Development blog
http://qefem.blogspot.com/
Thanks
Thanks to Z0z0 and other anonymous contributors for help. 