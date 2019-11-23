**FAN UPDATE v1.5.73 - 1.5.80 by ArranzCNL**

Added GameAddresses.h to NetScriptFramework.SkyrimSE which stores all memory addresses for easier maintainability.

Changed namespace from Skyrim to SkyrimSE just incase it does get backported to original Skyrim.

Removed Constants.h from NetScriptFramework.SkyrimSE as it is no longer required.



 **Introduction**

.NET Script Framework allows mod authors to write DLL plugins for any game  or application in any .NET language. Currently it only supports 64 bit  but there are plans to support 32 bit applications in the future.

As of right now this is a very early release and it is not recommended to  release any plugins created with the framework just yet or they may end  up breaking if the plugin format is changed. I will try to avoid any  such changes though.

Tutorials for the framework are planned.

The reason for releasing it this early is because mod authors can play  around with it hopefully and let me know if improvements could be made  to make plugin authoring easier or if any issues are found. Regular  users can also benefit from the framework's crash logs to help  troubleshoot other mod issues they may be experiencing.


**Requirements**

[DLL Plugin Loader](https://www.nexusmods.com/skyrimspecialedition/mods/10546) or [SSE Engine Fixes (SKSE64 Plugin)](https://www.nexusmods.com/skyrimspecialedition/mods/17230)


**Installation**

Extract contents of archive to */Data/* directory of the game or use mod manager. You can verify if it works by launching the game once and checking the log file at */Data/NetScriptFramework/NetScriptFramework.log.txt*


**Uninstallation**

Partial uninstall - remove the file */Data/DLLPlugins/NetScriptFramework.Runtime.dll* after doing that the framework or any of its plugins will not load.

Full uninstall - remove the file mentioned above and remove */Data/NetScriptFramework/* directory.


**Troubleshooting**

You can find out any problems from */Data/NetScriptFramework/NetScriptFramework.log.txt* file. If the file remains empty it means the framework did not load at all.

Framework didn't load

First of all check to make sure the DLL Plugin Loader is installed correctly  by creating a new file called binkw64.log in the same directory as  SkyrimSE.exe. After starting the game check the file. If it remains  empty then make sure you installed the framework correctly and */Data/DLLPlugins/NetScriptFramework.Runtime.dll* exists. If it still does not work try starting your mod manager or the game as administrator.

Game crashes

If you suspect the framework or one of the plugins is causing your game to crash then you can check crash logs to see. Make sure crash logs are  enabled in */Data/NetScriptFramework/NetScriptFramework.config.txt* (they are enabled by default) and after the crash check */Data/NetScriptFramework/Crash/* for the log. If you are using a mod manager with virtual file system  the crash log file may be in your mod manager's overwrite folder or  equivalent instead. If it contains a managed exception then it is almost certainly a plugin or the framework at fault. Check the callstack to  find which plugin it may be or post it here. If it is a native exception it can be a bit more tricky, scroll all the way down and see if any  hooks are currently executing, that should tell you which .NET plugins  are causing code to run at the moment. If there are none this may be a  regular game crash, but you can still get some useful information by  checking the callstack, registers and stack trace which say what the  game was doing at the time.

(NotSupportedException): "An attempt was made to load an assembly from a network location which would ...

If you get this exception on startup then go to /Data/NetScriptFramework/  and right click on all the DLLs, go to Properties and Unblock.



Another issue

If you run into some issue that is not explained here post your question in the [comments tab](https://www.nexusmods.com/skyrimspecialedition/mods/21294?tab=posts). 