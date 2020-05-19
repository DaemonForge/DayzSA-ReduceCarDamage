class CfgPatches
{
	class ReduceCarDamage
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={};
	};
};

class CfgMods
{
	class ReduceCarDamage
	{
		dir="ReduceCarDamage";
        picture="";
        action="";
        hideName=1;
        hidePicture=1;
        name="ReduceCarDamage";
        credits="DaemonForge";
        author="DaemonForge";
        authorID="0";
        version="0.1";
        extra=0;
        type="mod";
	    dependencies[]={ "World" };
	    class defs
	    {
	        class worldScriptModule
            {
                value="";
                files[]={ "ReduceCarDamage/scripts/4_world" };
            };
        };
    };
};
