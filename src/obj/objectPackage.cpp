#include "objectPackage.h"

objectPackage::objectPackage(SdockerData _d_date,Spackage _p_data)
{
  d_data=_d_date;
  p_data=_p_data;
  d_path=d_data.s_dockers_path+"/"+d_data.s_dockers_name;
  p_package_tool_path=d_data.s_dockers_wine_path+"/"+d_data.s_dockers_wine_version+"/wine-package-script";
}
objectPackage::~objectPackage()
{

}

int objectPackage::CopyDocker(){
    return system(("echo "+_password+" | sudo cp -rf -p "+d_path+" "+_tagdir+p_data.sDockerName).toLocal8Bit());
}
int objectPackage::InstallToolDeb(){
    return system(("echo "+_password+" | sudo dpkg -i "+p_package_tool_path+" *.deb").toLocal8Bit());
}
int objectPackage::RepairToolLib(){
    return system(("echo "+_password+" | sudo apt install -f").toLocal8Bit());
}
int objectPackage::RepairToolChmod(){
    return system(("echo "+_password+" | sudo -S chmod +x -R "+p_package_tool_path+"/ *").toLocal8Bit());
}

bool objectPackage::StatCheck(int status){
    if (-1 == status)
    {
        printf("system error!");
        return false;
    }
    else
    {
        printf("exit status value = [0x%x]\n", status);

        if (WIFEXITED(status))
        {
            if (0 == WEXITSTATUS(status))
            {
                printf("run shell script successfully.\n");
                return true;
            }
            else
            {
                printf("run shell script fail, script exit code: %d\n", WEXITSTATUS(status));
                return false;
            }
        }
        else
        {
            printf("exit status = [%d]\n", WEXITSTATUS(status));
            return false;
        }
    }
}

int objectPackage::EXPackage(){
    return system("");
}
