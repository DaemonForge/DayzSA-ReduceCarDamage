modded class CarScript 
{
	override void OnContact( string zoneName, vector localPos, IEntity other, Contact data )
	{
		bool rcd_logcrashes = ReduceCarDamageSettings.Get().logcrashes;
		float rcd_dmgModifier = ReduceCarDamageSettings.Get().dmgModifier;
		float rcd_plyrdmgModifier = ReduceCarDamageSettings.Get().plyrdmgModifier;
		float rcd_mindmg = ReduceCarDamageSettings.Get().mindmg;
		bool rcd_subtractmindmg = ReduceCarDamageSettings.Get().subtractmindmg;
		
		if ( zoneName == "" )
		{
			Print("CarScript >> ERROR >> OnContact dmg zone not defined!");
			return;
		}
		
		if ( GetGame().IsServer() && zoneName != "")
		{
			float dmgMin = 150.0;	//Left this here from encase other mods call super on this mod and use it
			float dmgThreshold = 750.0;
			float dmgKillCrew = 3000.0;
			float dmg = data.Impulse * m_dmgContactCoef;
			float rcd_orgdmg = dmg;
			if (rcd_subtractmindmg)
			{
				dmg = dmg - rcd_mindmg;
				dmg = dmg * rcd_dmgModifier;
			}
			else
			{
				dmg = dmg * rcd_dmgModifier;
			}
			if (rcd_plyrdmgModifier > 0){
				dmgKillCrew = dmgKillCrew / rcd_plyrdmgModifier;
			}
			
			if (rcd_orgdmg < rcd_mindmg){
				//Debug Script
				if ( rcd_logcrashes ){Print("[ReduceCarDamage] Below Min Crash to zone: " + zoneName + " Org Damage:" + rcd_orgdmg + " below Min Damage: " + rcd_mindmg);}
				
			}
			else if ( dmg < dmgThreshold) //Low Speed Crash
			{					
					//Debug Script
					if ( rcd_logcrashes ){Print("[ReduceCarDamage] Low Speed Crash to zone: " + zoneName + " Org Damage:" + rcd_orgdmg + " New Damage:" + dmg + " below Low Speed Threshold: " + dmgThreshold);}
					AddHealth( zoneName, "Health", -dmg);
					SynchCrashLightSound( true );
			}
			else
			{
				for( int i =0; i < CrewSize(); i++ )
				{
					Human crew = CrewMember( i );
					if ( !crew )
						continue;

					PlayerBase player;
					if ( Class.CastTo(player, crew ) )
					{
						if ( dmg > dmgKillCrew )
						{		
							if ( rcd_logcrashes ){Print("[ReduceCarDamage] High Speed Crash to zone: " + zoneName + " Org Damage:" + rcd_orgdmg + " New Damage:" + dmg + " below Above Death Threshold: " + dmgKillCrew);}
							player.SetHealth(0.0);
							
						}
						else
						{
							//deal shock to player
							float shockTemp = Math.InverseLerp(dmgThreshold, dmgKillCrew, dmg);
							float shock = Math.Lerp( 50, 100, shockTemp );
							float hp = Math.Lerp( 2, 60, shockTemp ) * rcd_plyrdmgModifier;
							
							if ( rcd_logcrashes ){Print("[ReduceCarDamage] High Speed Crash to zone: " + zoneName + " Org Damage:" + rcd_orgdmg + " New Damage:" + dmg + " Above Low Speed Threshold: " + dmgThreshold);}
							player.AddHealth("", "Shock", -shock );
							player.AddHealth("", "Health", -hp );
						}
					}
				}

				SynchCrashHeavySound( true );
				ProcessDirectDamage( DT_CUSTOM, null, zoneName, "EnviroDmg", "0 0 0", dmg );
			}
		}
				
		UpdateHeadlightState();
		UpdateLights();
	}
}