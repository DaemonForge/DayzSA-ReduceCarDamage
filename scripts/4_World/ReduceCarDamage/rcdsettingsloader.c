static string ReduceCarDamageDIR = "$profile:ReduceCarDamage";
static string ReduceCarDamagePATH = ReduceCarDamageDIR + "\\config.json";

class ReduceCarDamageSettings
{
	/*
	Credit for this loader class goes to Schana 
	https://github.com/schana 
	
	*/
    private static bool initialized = false;
    private static ref ReduceCarDamageSettings settings;

    float dmgModifier = 0.8;
	float plyrdmgModifier = 0.8;
	float mindmg = 1350;
	bool subtractmindmg = true;

    static ref ReduceCarDamageSettings Get()
    {
        if (initialized)
        {
            return settings;
        }

        ref ReduceCarDamageSettings data = new ref ReduceCarDamageSettings;

        if (FileExist(ReduceCarDamagePATH))
        {
            JsonFileLoader<ReduceCarDamageSettings>.JsonLoadFile(ReduceCarDamagePATH, data);
            initialized = true;
        }
        else
        {
            if (GetGame().IsServer() || !GetGame().IsMultiplayer())
            {
                MakeDirectory(ReduceCarDamageDIR);
                JsonFileLoader<ReduceCarDamageSettings>.JsonSaveFile(ReduceCarDamagePATH, data);
            }
        }

        settings = data;

        return settings;
    }
}