using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Ghost : MonoBehaviour
{
    private bool hovertOver = false;

    public void HoverOver()
    {

        if (!hovertOver && gameObject.activeSelf)
        {
            hovertOver = true;
            StartCoroutine(CheckShooting());
        }        
    }

    public void HoverExit()
    {
        hovertOver = false;
        GetComponent<Renderer>().material.DisableKeyword("_EMISSION");
    }
    
    private IEnumerator CheckShooting()
    {
        while (hovertOver)
        {
            if (ElectricalConnection.isConnected)
            {
                print("isconnected");
                GetComponent<Renderer>().material.EnableKeyword("_EMISSION");
                //Invoke("CauseDamage", 2);
                CauseDamage();
            }
            else if (PlayerPickupObjects.pickedUpCapacitor && CapacitorSettings.isCharged())
            {
                GetComponent<Renderer>().material.EnableKeyword("_EMISSION");
            }
            yield return new WaitForEndOfFrame();
        }
        
    }

    public void SelectEnter()
    {
        if (PlayerPickupObjects.pickedUpCapacitor && CapacitorSettings.isCharged() && PlayerPickupObjects.pickedupGloves)
        {
            CapacitorSettings.Unload();
            GetComponent<Renderer>().material.EnableKeyword("_EMISSION");
            GetComponent<Renderer>().material.SetColor("_EmissionColor", Color.cyan);

            //Invoke("CauseDamage", 2);
            CauseDamage();
        }
    }

    private void CauseDamage()
    {
        //Destroy(gameObject);
        gameObject.SetActive(false);
    }
}
