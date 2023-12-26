using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ElectricalConnection : MonoBehaviour
{

    public static bool isConnected = false;
    [SerializeField] private bool connected;

    private void Update()
    {
        connected = isConnected;
    }

}
