using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AmuletPickup : Pickup
{
    [SerializeField] GameObject parent;
    public override void OnSelected()
    {
        PlayerPickupObjects.pickedUpAmulet = true;
        //base.OnSelected();
        transform.SetParent(parent.transform);
        transform.SetLocalPositionAndRotation(new Vector3(-0.03f, -0.04f, -0.04f), Quaternion.Euler(new Vector3(0, 0, 90)));
    }
}
