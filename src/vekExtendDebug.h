#ifndef VEKEXTENDDEBUG_H
#define VEKEXTENDDEBUG_H

#include "obj/common.h"
#include "obj/objectExtend.h"
namespace Ui {
class vekExtendDebug;
}

class vekExtendDebug : public QDialog
{
    Q_OBJECT

public:
    explicit vekExtendDebug(QWidget *parent = nullptr);
    ~vekExtendDebug();
    void ConnectDebugObject(QString dockName,QString appCID);
private:
    Ui::vekExtendDebug *ui;   
    QStringList DebugDllStr;
    QProcess *m_cmd=nullptr;
    BaseAppData appData;
    BaseDockData dockData;
    void upDllStr();
    std::vector<QString> dllList={"accel","adpcm","advapi","animate","aspi",
    "atom","avicap","avifile","bidi","bitblt",
    "bitmap","cabinet","capi","caret","cdrom",
    "cfgmgr32","class","clipboard","clipping","combo",
    "comboex","comm","commctrl","commdlg","computername",
    "console","crtdll","crypt","curses","cursor",
    "d3d","d3d_shader","d3d_surface","datetime","dc",
    "ddeml","ddraw","ddraw_fps","ddraw_geom","ddraw_tex",
    "debugstr","devenum","dialog","dinput","dll",
    "dma","dmband","dmcompos","dmfile","dmfiledat",
    "dmime","dmloader","dmscript","dmstyle","dmsynth",
    "dmusic","dosfs","dosmem","dplay","dplayx",
    "dpnhpast","driver","dsound","dsound3d","edit",
    "enhmetafile","environ","event","eventlog","exec",
    "file","fixup","font","fps","g711",
    "gdi","global","glu","graphics","header",
    "heap","hook","hotkey","icmp","icon",
    "imagehlp","imagelist","imm","int","int21",
    "int31","io","ipaddress","iphlpapi","jack",
    "joystick","key","keyboard","listbox","listview",
    "loaddll","local","mapi","mci","mcianim",
    "mciavi","mcicda","mcimidi","mciwave","mdi",
    "menu","menubuilder","message","metafile","midi",
    "mmaux","mmio","mmsys","mmtime","module",
    "monthcal","mpeg3","mpr","msacm","msdmo",
    "msg","mshtml","msi","msimg32","msisys",
    "msrle32","msvcrt","msvideo","mswsock","nativefont",
    "netapi32","netbios","nls","nonclient","ntdll",
    "odbc","ole","oledlg","olerelay","opengl",
    "pager","palette","pidl","powermgnt","print",
    "process","profile","progress","propsheet","psapi",
    "psdrv","qcap","quartz","ras","rebar",
    "reg","region","relay","resource","richedit",
    "rundll32","sblaster","scroll","seh","selector",
    "server","setupapi","shdocvw","shell","shlctrl",
    "snmpapi","snoop","sound","static","statusbar",
    "storage","stress","string","syscolor","system",
    "tab","tape","tapi","task","text",
    "thread","thunk","tid","timer","toolbar",
    "toolhelp","tooltips","trackbar","treeview","ttydrv",
    "twain","typelib","uninstaller","updown","urlmon",
    "uxtheme","ver","virtual","vxd","wave",
    "wc_font","win","win32","wineboot","winecfg",
    "wineconsole","wine_d3d","winevdm","wing","winhelp",
    "wininet","winmm","winsock","winspool","wintab",
    "wintab32","wnet","x11drv","x11settings","xdnd",
    "xrandr","xrender","xvidmode"};
private slots:
    void onReadyRead();
    void executeArgsEnv();
    void ExtendApp();
    void addDll();
    void delDll();
    void startDebug();
    void exitDebug();
signals:
    void _unVekDebug();
};

#endif // VEKDEBUG_H
