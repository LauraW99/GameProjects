using System.Collections;
using System.Collections.Generic;
using UnityEngine;



public class Hand : MonoBehaviour
{

    [SerializeField] private HandSide handSide;

    public HandSide GetHandSide() { return handSide; }
}
