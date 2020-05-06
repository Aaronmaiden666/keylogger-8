# Keylogger

Windows OS keylogger with a hook mechanism (i.e. with a keyboard hook procedure).

Mapped most of the keys for the standard US keyboard layout.

Built with Dev-C++ IDE v5.11 (64 bit), compiled with TDM-GCC v4.9.2 (64 bit) and tested on Windows 10 Enterprise OS (64 bit). Download Dev-C++ from [here](https://sourceforge.net/projects/orwelldevcpp/files/Portable%20Releases/).

Made for educational purposes. I hope it will help!

## How to Run

Run ['\\exec\\keylogger.exe'](https://github.com/ivan-sincek/keylogger/tree/master/exec).

## Cleanup

If hide window functionality is enabled, do not forget to shutdown keylogger process through task manager.

If hide files functionality is enabled, do not forget to delete hidden keylogger files after shutting it down first.

If startup functionality is enabled, do not forget to remove keylogger registry key called `keylogger` located at `HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run`.

**Executable provided does not have these functionalities active.**

**If you want to try them out, uncomment the corresponding functions inside the program source code and recompile it.**

## Images

![Keylogger](https://github.com/ivan-sincek/keylogger/blob/master/img/keylogger.jpg)

![Log](https://github.com/ivan-sincek/keylogger/blob/master/img/log.jpg)
